#include "../RocketStats.h"

std::string RocketStats::GetPath(std::string _path, bool root)
{
    std::string _return = gameWrapper->GetBakkesModPath().string() + "/";

    if (root)
        _return += _path;
    else
        _return += "data/RocketStats/" + _path;

    return _return;
}

bool RocketStats::ExistsPath(std::string _filename, bool root)
{
    return fs::exists(GetPath(_filename, root));
}

bool RocketStats::RemoveFile(std::string _filename, bool root)
{
    if (!ExistsPath(_filename, root))
        return true;

    try
    {
        return fs::remove(GetPath(_filename, root));
    }
    catch (const std::exception&) {}

    return false;
}

std::string RocketStats::ReadFile(std::string _filename, bool root)
{
    std::string _value = "";
    std::string _path = GetPath(_filename, root);
    if (fs::exists(_path) && fs::is_regular_file(_path) && (fs::status(_path).permissions() & fs::perms::owner_read) == fs::perms::owner_read)
    {
        std::ifstream stream(_path, std::ios::in | std::ios::binary);

        if (stream.is_open())
        {
            std::ostringstream os;
            os << stream.rdbuf();
            _value = os.str();
            stream.close();
        }
        else
            cvarManager->log("Can't read this file: " + _filename);
    }
    else
        cvarManager->log("Bad path: " + _filename);

    return _value;
}

json RocketStats::ReadJSON(std::string _filename, bool root)
{
    cvarManager->log("Read JSON: " + _filename);
    return json::parse(ReadFile(_filename, root));
}

void RocketStats::WriteInFile(std::string _filename, std::string _value, bool root)
{
    std::string _path = GetPath(_filename, root);
    if (!fs::exists(_path) || fs::is_regular_file(_path))
    {
        std::ofstream stream(_path, std::ios::out | std::ios::trunc);

        if (stream.is_open())
        {
            stream << _value;
            stream.close();
        }
        else
        {
            cvarManager->log("Can't write to file: " + _filename);
            cvarManager->log("Value to write was: " + _value);
        }
    }
}

bool RocketStats::WriteResInFile(std::string _filename, int id, const char* type, bool root)
{
    std::string _path = GetPath(_filename, root);
    if (!fs::exists(_path) || fs::is_regular_file(_path))
    {
        Resource res = Resource(id, type, GetModuleHandle("RocketStats"));
        std::span<const char> obj = res.GetResource();

        if (obj.data())
        {
            std::ofstream stream(_path, std::ios::out | std::ios::trunc | std::ios::binary);

            if (stream.is_open())
            {
                stream.write(obj.data(), obj.size());
                stream.close();
                return true;
            }
            else
                cvarManager->log("Can't write to file: " + _filename);
        }
    }

    return false;
}

void RocketStats::MigrateFolder()
{
    // If the old folder exist, copy everything to the new path
    if (ExistsPath("RocketStats", true))
    {
        std::string old_path = GetPath("RocketStats", true);
        fs::copy(old_path, GetPath(), (fs::copy_options::recursive | fs::copy_options::update_existing));
        MigrateRemove();
    }
}

void RocketStats::MigrateRemove()
{
    if (ExistsPath("RocketStats", true))
        fs::remove_all(GetPath("RocketStats", true));

    RemoveFile("RocketStats_Loose.txt"); // Delete the old file
    RemoveFile("RocketStats_images/BoostState.txt"); // Delete the old file
}

void RocketStats::UpdateFiles(bool force)
{
    WriteGames(force);
    WriteGameMode(force);
    WriteRank(force);
    WriteDiv(force);
    WriteMMR(force);
    WriteMMRChange(force);
    WriteWin(force);
    WriteLoss(force);
    WriteStreak(force);
    WriteWinRatio(force);
    WriteWinPercentage(force);
    WriteDemo(force);
    WriteDeath(force);
    WriteBoost(force, ((is_game_started && !is_game_ended) ? 0 : -1));
}

void RocketStats::ResetFiles()
{
    last_rank = "";
    last_division = "";

    WriteInFile("RocketStats_Games.txt", std::to_string(0));
    WriteInFile("RocketStats_GameMode.txt", "");
    WriteInFile("RocketStats_Rank.txt", last_rank);
    WriteInFile("RocketStats_RankName.txt", last_rank);
    WriteInFile("RocketStats_RankNumber.txt", (rs_roman_numbers ? "" : std::to_string(0)));
    WriteInFile("RocketStats_Div.txt", last_division);
    WriteInFile("RocketStats_DivName.txt", last_division);
    WriteInFile("RocketStats_DivNumber.txt", (rs_roman_numbers ? "" : std::to_string(0)));
    WriteInFile("RocketStats_MMR.txt", std::to_string(0));
    WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));
    WriteInFile("RocketStats_MMRCumulChange.txt", std::to_string(0));
    WriteInFile("RocketStats_Win.txt", std::to_string(0));
    WriteInFile("RocketStats_Loss.txt", std::to_string(0));
    WriteInFile("RocketStats_Streak.txt", std::to_string(0));
    WriteInFile("RocketStats_WinRatio.txt", std::to_string(0));
    WriteInFile("RocketStats_WinPercentage.txt", "N/A");
    WriteInFile("RocketStats_Demolition.txt", std::to_string(0));
    WriteInFile("RocketStats_DemolitionMatch.txt", std::to_string(0));
    WriteInFile("RocketStats_DemolitionCumul.txt", std::to_string(0));
    WriteInFile("RocketStats_Death.txt", std::to_string(0));
    WriteInFile("RocketStats_DeathMatch.txt", std::to_string(0));
    WriteInFile("RocketStats_DeathCumul.txt", std::to_string(0));
    WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));
}

bool RocketStats::ReadConfig()
{
    cvarManager->log("===== ReadConfig =====");

    std::string file = "data/rocketstats.json";
    bool exists = ExistsPath(file, true);
    if (exists)
    {
        try
        {
            // Read the plugin settings JSON file
            json config = ReadJSON(file, true);
            cvarManager->log(nlohmann::to_string(config));

            if (config.is_object())
            {
                if (config["settings"].is_object() && !config["settings"].is_null())
                {
                    if (config["settings"]["mode"].is_number_unsigned())
                        rs_mode = config["settings"]["mode"];

                    if (config["settings"]["theme"].is_string())
                        SetTheme(config["settings"]["theme"]);

                    if (config["settings"]["themes"].is_object() && !config["settings"]["themes"].is_null() && config["settings"]["themes"].size())
                    {
                        json tmp = json::object();
                        for (auto it = config["settings"]["themes"].begin(); it != config["settings"]["themes"].end(); ++it)
                        {
                            if (!it.value().is_null())
                            {
                                json ctmp = json::object();
                                for (auto cit = it.value().begin(); cit != it.value().end(); ++cit)
                                {
                                    if (!cit.value().is_null())
                                        ctmp[cit.key()] = cit.value();
                                }

                                if (ctmp.size())
                                    tmp[it.key()] = ctmp;
                            }
                        }

                        if (tmp.size())
                            themes_values = tmp;
                    }

                    if (config["settings"]["overlay"].is_boolean())
                        rs_disp_overlay = config["settings"]["overlay"];

                    if (config["settings"]["inmenu"].is_boolean())
                        rs_enable_inmenu = config["settings"]["inmenu"];
                    if (config["settings"]["ingame"].is_boolean())
                        rs_enable_ingame = config["settings"]["ingame"];
                    if (config["settings"]["inscoreboard"].is_boolean())
                        rs_enable_inscoreboard = config["settings"]["inscoreboard"];
                    if (config["settings"]["float"].is_boolean())
                        rs_enable_float = config["settings"]["float"];
                    if (config["settings"]["preview"].is_boolean())
                        rs_preview_rank = config["settings"]["preview"];
                    if (config["settings"]["roman"].is_boolean())
                        rs_roman_numbers = config["settings"]["roman"];

                    if (config["settings"]["replace_mmr"].is_boolean())
                        rs_replace_mmr = config["settings"]["replace_mmr"];
                    if (config["settings"]["replace_mmr_cc"].is_boolean())
                        rs_replace_mmr_cc = config["settings"]["replace_mmr_cc"];
                    if (config["settings"]["replace_mmrc"].is_boolean())
                        rs_replace_mmrc = config["settings"]["replace_mmrc"];
                    if (config["settings"]["replace_mmrc_cc"].is_boolean())
                        rs_replace_mmrc_cc = config["settings"]["replace_mmrc_cc"];
                    if (config["settings"]["replace_mmrcc"].is_boolean())
                        rs_replace_mmrcc = config["settings"]["replace_mmrcc"];
                    if (config["settings"]["replace_mmrcc_c"].is_boolean())
                        rs_replace_mmrcc_c = config["settings"]["replace_mmrcc_c"];

                    if (config["settings"]["files"].is_object() && !config["settings"]["files"].is_null())
                    {
                        if (config["settings"]["files"]["on"].is_boolean())
                            rs_in_file = config["settings"]["files"]["on"];
                        if (config["settings"]["files"]["games"].is_boolean())
                            rs_file_games = config["settings"]["files"]["games"];
                        if (config["settings"]["files"]["gm"].is_boolean())
                            rs_file_gm = config["settings"]["files"]["gm"];
                        if (config["settings"]["files"]["rank"].is_boolean())
                            rs_file_rank = config["settings"]["files"]["rank"];
                        if (config["settings"]["files"]["div"].is_boolean())
                            rs_file_div = config["settings"]["files"]["div"];
                        if (config["settings"]["files"]["mmr"].is_boolean())
                            rs_file_mmr = config["settings"]["files"]["mmr"];
                        if (config["settings"]["files"]["mmrc"].is_boolean())
                            rs_file_mmrc = config["settings"]["files"]["mmrc"];
                        if (config["settings"]["files"]["mmrcc"].is_boolean())
                            rs_file_mmrcc = config["settings"]["files"]["mmrcc"];
                        if (config["settings"]["files"]["win"].is_boolean())
                            rs_file_win = config["settings"]["files"]["win"];
                        if (config["settings"]["files"]["loss"].is_boolean())
                            rs_file_loss = config["settings"]["files"]["loss"];
                        if (config["settings"]["files"]["streak"].is_boolean())
                            rs_file_streak = config["settings"]["files"]["streak"];
                        if (config["settings"]["files"]["winratio"].is_boolean())
                            rs_file_winratio = config["settings"]["files"]["winratio"];
                        if (config["settings"]["files"]["winpercentage"].is_boolean())
                            rs_file_winpercentage = config["settings"]["files"]["winpercentage"];
                        if (config["settings"]["files"]["demo"].is_boolean())
                            rs_file_demo = config["settings"]["files"]["demo"];
                        if (config["settings"]["files"]["demom"].is_boolean())
                            rs_file_demom = config["settings"]["files"]["demom"];
                        if (config["settings"]["files"]["democ"].is_boolean())
                            rs_file_democ = config["settings"]["files"]["democ"];
                        if (config["settings"]["files"]["death"].is_boolean())
                            rs_file_death = config["settings"]["files"]["death"];
                        if (config["settings"]["files"]["deathm"].is_boolean())
                            rs_file_deathm = config["settings"]["files"]["deathm"];
                        if (config["settings"]["files"]["deathc"].is_boolean())
                            rs_file_deathc = config["settings"]["files"]["deathc"];
                        if (config["settings"]["files"]["boost"].is_boolean())
                            rs_file_boost = config["settings"]["files"]["boost"];
                    }

                    if (config["settings"]["hides"].is_object() && !config["settings"]["hides"].is_null())
                    {
                        if (config["settings"]["hides"]["games"].is_boolean())
                            rs_hide_games = config["settings"]["hides"]["games"];
                        if (config["settings"]["hides"]["gm"].is_boolean())
                            rs_hide_gm = config["settings"]["hides"]["gm"];
                        if (config["settings"]["hides"]["rank"].is_boolean())
                            rs_hide_rank = config["settings"]["hides"]["rank"];
                        if (config["settings"]["hides"]["div"].is_boolean())
                            rs_hide_div = config["settings"]["hides"]["div"];
                        if (config["settings"]["hides"]["mmr"].is_boolean())
                            rs_hide_mmr = config["settings"]["hides"]["mmr"];
                        if (config["settings"]["hides"]["mmrc"].is_boolean())
                            rs_hide_mmrc = config["settings"]["hides"]["mmrc"];
                        if (config["settings"]["hides"]["mmrcc"].is_boolean())
                            rs_hide_mmrcc = config["settings"]["hides"]["mmrcc"];
                        if (config["settings"]["hides"]["win"].is_boolean())
                            rs_hide_win = config["settings"]["hides"]["win"];
                        if (config["settings"]["hides"]["loss"].is_boolean())
                            rs_hide_loss = config["settings"]["hides"]["loss"];
                        if (config["settings"]["hides"]["streak"].is_boolean())
                            rs_hide_streak = config["settings"]["hides"]["streak"];
                        if (config["settings"]["hides"]["winratio"].is_boolean())
                            rs_hide_winratio = config["settings"]["hides"]["winratio"];
                        if (config["settings"]["hides"]["winpercentage"].is_boolean())
                            rs_hide_winpercentage = config["settings"]["hides"]["winpercentage"];
                        if (config["settings"]["hides"]["demo"].is_boolean())
                            rs_hide_demo = config["settings"]["hides"]["demo"];
                        if (config["settings"]["hides"]["demom"].is_boolean())
                            rs_hide_demom = config["settings"]["hides"]["demom"];
                        if (config["settings"]["hides"]["democ"].is_boolean())
                            rs_hide_democ = config["settings"]["hides"]["democ"];
                        if (config["settings"]["hides"]["death"].is_boolean())
                            rs_hide_death = config["settings"]["hides"]["death"];
                        if (config["settings"]["hides"]["deathm"].is_boolean())
                            rs_hide_deathm = config["settings"]["hides"]["deathm"];
                        if (config["settings"]["hides"]["deathc"].is_boolean())
                            rs_hide_deathc = config["settings"]["hides"]["deathc"];

                        cvarManager->log("Config: hides loaded");
                    }

                    cvarManager->log("Config: settings loaded");
                }

                if (config["always"].is_object() && !config["always"].is_null())
                {
                    if (config["always"]["Games"].is_number_unsigned())
                        always.games = int(config["always"]["Games"]);

                    if (config["always"]["MMRCumulChange"].is_number())
                        always.MMRCumulChange = float(config["always"]["MMRCumulChange"]);

                    if (config["always"]["Win"].is_number_unsigned())
                        always.win = int(config["always"]["Win"]);

                    if (config["always"]["Loss"].is_number_unsigned())
                        always.loss = int(config["always"]["Loss"]);

                    if (config["always"]["Streak"].is_number_unsigned() || config["always"]["Streak"].is_number_integer())
                        always.streak = int(config["always"]["Streak"]);

                    if (config["always"]["Demo"].is_number_unsigned())
                        always.demo = int(config["always"]["Demo"]);

                    if (config["always"]["DemoCumul"].is_number_unsigned())
                        always.demoCumul = int(config["always"]["DemoCumul"]);

                    if (config["always"]["Death"].is_number_unsigned())
                        always.death = int(config["always"]["Death"]);

                    if (config["always"]["DeathCumul"].is_number_unsigned())
                        always.deathCumul = int(config["always"]["DeathCumul"]);

                    cvarManager->log("Config: stats loaded");
                    always.isInit = true;
                }

                if (config["always_gm_idx"].is_number_unsigned() && int(config["always_gm_idx"]) < playlist_name.size())
                    current.playlist = config["always_gm_idx"];

                if (config["always_gm"].is_array())
                {
                    for (int i = 0; i < config["always_gm"].size() && i < playlist_name.size(); ++i)
                    {
                        if (config["always_gm"][i].is_object() && !config["always_gm"][i].is_null())
                        {
                            if (config["always_gm"][i]["Games"].is_number_unsigned())
                                always_gm[i].games = int(config["always_gm"][i]["Games"]);

                            if (config["always_gm"][i]["MMRCumulChange"].is_number())
                                always_gm[i].MMRCumulChange = float(config["always_gm"][i]["MMRCumulChange"]);

                            if (config["always_gm"][i]["Win"].is_number_unsigned())
                                always_gm[i].win = int(config["always_gm"][i]["Win"]);

                            if (config["always_gm"][i]["Loss"].is_number_unsigned())
                                always_gm[i].loss = int(config["always_gm"][i]["Loss"]);

                            if (config["always_gm"][i]["Streak"].is_number_unsigned() || config["always_gm"][i]["Streak"].is_number_integer())
                                always_gm[i].streak = int(config["always_gm"][i]["Streak"]);

                            if (config["always_gm"][i]["Demo"].is_number_unsigned())
                                always_gm[i].demo = int(config["always_gm"][i]["Demo"]);

                            if (config["always_gm"][i]["DemoCumul"].is_number_unsigned())
                                always_gm[i].demoCumul = int(config["always_gm"][i]["DemoCumul"]);

                            if (config["always_gm"][i]["Death"].is_number_unsigned())
                                always_gm[i].death = int(config["always_gm"][i]["Death"]);

                            if (config["always_gm"][i]["DeathCumul"].is_number_unsigned())
                                always_gm[i].deathCumul = int(config["always_gm"][i]["DeathCumul"]);

                            always_gm[i].isInit = true;
                        }
                    }

                    cvarManager->log("Config: stats loaded");
                }

                SetRefresh(RefreshFlags_Refresh);
            }
            else
                cvarManager->log("Config: bad JSON");
        }
        catch (json::parse_error& e)
        {
            cvarManager->log("Config: bad JSON -> " + std::string(e.what()));
        }
    }

    cvarManager->log("===== !ReadConfig =====");
    return exists;
}

void RocketStats::WriteConfig()
{
    cvarManager->log("===== WriteConfig =====");

    json tmp = json::object();

    tmp["settings"] = json::object();
    tmp["settings"]["mode"] = rs_mode;
    tmp["settings"]["theme"] = theme_render.name;
    tmp["settings"]["overlay"] = rs_disp_overlay;
    tmp["settings"]["inmenu"] = rs_enable_inmenu;
    tmp["settings"]["ingame"] = rs_enable_ingame;
    tmp["settings"]["inscoreboard"] = rs_enable_inscoreboard;
    tmp["settings"]["float"] = rs_enable_float;
    tmp["settings"]["preview"] = rs_preview_rank;
    tmp["settings"]["roman"] = rs_roman_numbers;

    tmp["settings"]["replace_mmr"] = rs_replace_mmr;
    tmp["settings"]["replace_mmr_cc"] = rs_replace_mmr_cc;
    tmp["settings"]["replace_mmrc"] = rs_replace_mmrc;
    tmp["settings"]["replace_mmrc_cc"] = rs_replace_mmrc_cc;
    tmp["settings"]["replace_mmrcc"] = rs_replace_mmrcc;
    tmp["settings"]["replace_mmrcc_c"] = rs_replace_mmrcc_c;

    // Save only existing themes
    tmp["settings"]["themes"] = json::object();
    for (int i = 0; i < themes.size(); ++i)
    {
        std::string name = themes.at(i).name;
        if (themes_values[name].is_object() && !themes_values[name].is_null() && themes_values[name].size())
            tmp["settings"]["themes"][name] = themes_values[name];
    }

    tmp["settings"]["files"] = json::object();
    tmp["settings"]["files"]["on"] = rs_in_file;
    tmp["settings"]["files"]["games"] = rs_file_games;
    tmp["settings"]["files"]["gm"] = rs_file_gm;
    tmp["settings"]["files"]["rank"] = rs_file_rank;
    tmp["settings"]["files"]["div"] = rs_file_div;
    tmp["settings"]["files"]["mmr"] = rs_file_mmr;
    tmp["settings"]["files"]["mmr"] = rs_file_mmr;
    tmp["settings"]["files"]["mmrc"] = rs_file_mmrc;
    tmp["settings"]["files"]["mmrcc"] = rs_file_mmrcc;
    tmp["settings"]["files"]["win"] = rs_file_win;
    tmp["settings"]["files"]["loss"] = rs_file_loss;
    tmp["settings"]["files"]["streak"] = rs_file_streak;
    tmp["settings"]["files"]["winratio"] = rs_file_winratio;
    tmp["settings"]["files"]["winpercentage"] = rs_file_winpercentage;
    tmp["settings"]["files"]["demo"] = rs_file_demo;
    tmp["settings"]["files"]["demom"] = rs_file_demom;
    tmp["settings"]["files"]["democ"] = rs_file_democ;
    tmp["settings"]["files"]["death"] = rs_file_death;
    tmp["settings"]["files"]["deathm"] = rs_file_deathm;
    tmp["settings"]["files"]["deathc"] = rs_file_deathc;
    tmp["settings"]["files"]["boost"] = rs_file_boost;

    tmp["settings"]["hides"] = json::object();
    tmp["settings"]["hides"]["games"] = rs_hide_games;
    tmp["settings"]["hides"]["gm"] = rs_hide_gm;
    tmp["settings"]["hides"]["rank"] = rs_hide_rank;
    tmp["settings"]["hides"]["div"] = rs_hide_div;
    tmp["settings"]["hides"]["mmr"] = rs_hide_mmr;
    tmp["settings"]["hides"]["mmrc"] = rs_hide_mmrc;
    tmp["settings"]["hides"]["mmrcc"] = rs_hide_mmrcc;
    tmp["settings"]["hides"]["win"] = rs_hide_win;
    tmp["settings"]["hides"]["loss"] = rs_hide_loss;
    tmp["settings"]["hides"]["streak"] = rs_hide_streak;
    tmp["settings"]["hides"]["winratio"] = rs_hide_winratio;
    tmp["settings"]["hides"]["winpercentage"] = rs_hide_winpercentage;
    tmp["settings"]["hides"]["demo"] = rs_hide_demo;
    tmp["settings"]["hides"]["demom"] = rs_hide_demom;
    tmp["settings"]["hides"]["democ"] = rs_hide_democ;
    tmp["settings"]["hides"]["death"] = rs_hide_death;
    tmp["settings"]["hides"]["deathm"] = rs_hide_deathm;
    tmp["settings"]["hides"]["deathc"] = rs_hide_deathc;

    tmp["always"] = json::object();
    tmp["always"]["Games"] = always.games;
    tmp["always"]["MMRCumulChange"] = always.MMRCumulChange;
    tmp["always"]["Win"] = always.win;
    tmp["always"]["Loss"] = always.loss;
    tmp["always"]["Streak"] = always.streak;
    tmp["always"]["Demo"] = always.demo;
    tmp["always"]["DemoCumul"] = always.demoCumul;
    tmp["always"]["Death"] = always.death;
    tmp["always"]["DeathCumul"] = always.deathCumul;

    tmp["always_gm_idx"] = current.playlist;
    tmp["always_gm"] = json::array();
    for (int i = 0; i < always_gm.size(); ++i)
    {
        tmp["always_gm"][i] = json::object();
        tmp["always_gm"][i]["Games"] = always_gm[i].games;
        tmp["always_gm"][i]["MMRCumulChange"] = always_gm[i].MMRCumulChange;
        tmp["always_gm"][i]["Win"] = always_gm[i].win;
        tmp["always_gm"][i]["Loss"] = always_gm[i].loss;
        tmp["always_gm"][i]["Streak"] = always_gm[i].streak;
        tmp["always_gm"][i]["Demo"] = always_gm[i].demo;
        tmp["always_gm"][i]["DemoCumul"] = always_gm[i].demoCumul;
        tmp["always_gm"][i]["Death"] = always_gm[i].death;
        tmp["always_gm"][i]["DeathCumul"] = always_gm[i].deathCumul;
    }

    WriteInFile("data/rocketstats.json", tmp.dump(2), true); // Save plugin settings in JSON format

    cvarManager->log("===== !WriteConfig =====");
}

void RocketStats::WriteGames(bool force)
{
    if (force || (rs_in_file && rs_file_games))
        WriteInFile("RocketStats_Games.txt", (rs_hide_games ? theme_hide_value : std::to_string(GetStats().games)));
}

void RocketStats::WriteGameMode(bool force)
{
    if (force || (rs_in_file && rs_file_gm))
        WriteInFile("RocketStats_GameMode.txt", (rs_hide_gm ? theme_hide_value : GetPlaylistName(current.playlist)));
}

void RocketStats::WriteRank(bool force)
{
    t_current base;
    std::string tmp = theme_hide_value;
    int number = (rs_preview_rank ? current.preview_rank_number : current.rank_number);
    if (!rs_hide_rank)
    {
        tmp = AddRoman((rs_preview_rank ? current.preview_rank : current.rank), number);
        if (tmp == base.rank)
            tmp = "";
    }

    if (force || (rs_in_file && rs_file_rank && tmp != last_rank))
    {
        last_rank = tmp;
        std::string tnumber = (rs_roman_numbers ? GetRoman(number) : std::to_string(number));

        WriteInFile("RocketStats_Rank.txt", tmp);
        WriteInFile("RocketStats_RankName.txt", (rs_hide_rank ? theme_hide_value : (number ? tmp.substr(0, (tmp.size() - (tnumber.size() + 1))) : tmp)));
        WriteInFile("RocketStats_RankNumber.txt", (rs_hide_rank ? theme_hide_value : tnumber));
    }
}

void RocketStats::WriteDiv(bool force)
{
    t_current base;
    std::string tmp = theme_hide_value;
    int number = (rs_preview_rank ? current.preview_division_number : current.division_number);
    if (!rs_hide_div)
    {
        tmp = AddRoman((rs_preview_rank ? current.preview_division : current.division), number);
        if (tmp == base.division)
            tmp = "";
    }

    if (force || (rs_in_file && rs_file_div && tmp != last_division))
    {
        last_division = tmp;
        std::string tnumber = (rs_roman_numbers ? GetRoman(number) : std::to_string(number));

        WriteInFile("RocketStats_Div.txt", tmp);
        WriteInFile("RocketStats_DivName.txt", (rs_hide_div ? theme_hide_value : (number ? tmp.substr(0, (tmp.size() - (tnumber.size() + 1))) : tmp)));
        WriteInFile("RocketStats_DivNumber.txt", (rs_hide_div ? theme_hide_value : tnumber));
    }
}

void RocketStats::WriteMMR(bool force)
{
    if (!force && (!rs_in_file || !rs_file_mmr))
        return;

    std::string tmp = (rs_hide_mmr ? theme_hide_value : Utils::FloatFixer(stats[current.playlist].myMMR, (rs_enable_float ? 2 : 0)));

    WriteInFile("RocketStats_MMR.txt", tmp);
}

void RocketStats::WriteMMRChange(bool force)
{
    if (force || (rs_in_file && rs_file_mmrc))
    {
        std::string tmp = theme_hide_value;
        if (!rs_hide_mmrc)
        {
            Stats tstats = GetStats();
            tmp = Utils::FloatFixer(tstats.MMRChange, (rs_enable_float ? 2 : 0));

            if (tstats.MMRChange > 0)
                tmp = ("+" + tmp);
        }

        WriteInFile("RocketStats_MMRChange.txt", tmp);
    }

    if (force || (rs_in_file && rs_file_mmrcc))
    {
        std::string tmp = theme_hide_value;
        if (!rs_hide_mmrcc)
        {
            Stats tstats = GetStats();
            tmp = Utils::FloatFixer(tstats.MMRCumulChange, (rs_enable_float ? 2 : 0));

            if (tstats.MMRCumulChange > 0)
                tmp = ("+" + tmp);
        }

        WriteInFile("RocketStats_MMRCumulChange.txt", tmp);
    }
}

void RocketStats::WriteWin(bool force)
{
    if (force || (rs_in_file && rs_file_win))
        WriteInFile("RocketStats_Win.txt", (rs_hide_win ? theme_hide_value : std::to_string(GetStats().win)));
}

void RocketStats::WriteLoss(bool force)
{
    if (force || (rs_in_file && rs_file_loss))
        WriteInFile("RocketStats_Loss.txt", (rs_hide_loss ? theme_hide_value : std::to_string(GetStats().loss)));
}

void RocketStats::WriteStreak(bool force)
{
    if (!force && (!rs_in_file || !rs_file_streak))
        return;

    std::string tmp = theme_hide_value;
    if (!rs_hide_streak)
    {
        Stats tstats = GetStats();
        tmp = std::to_string(tstats.streak);

        if (tstats.streak > 0)
            tmp = ("+" + tmp);
    }

    WriteInFile("RocketStats_Streak.txt", tmp);
}

void RocketStats::WriteWinRatio(bool force)
{
    if (!force && (!rs_in_file || !rs_file_winratio))
        return;

    std::string tmp = theme_hide_value;
    if (!rs_hide_winratio)
    {
        Stats tstats = GetStats();
        tmp = std::to_string(tstats.win - tstats.loss);

        if ((tstats.win - tstats.loss) > 0)
            tmp = ("+" + tmp);
    }

    WriteInFile("RocketStats_WinRatio.txt", tmp);
}

void RocketStats::WriteWinPercentage(bool force)
{
    if (!force && (!rs_in_file || !rs_file_winpercentage))
        return;

    std::string tmp = theme_hide_value;
    if (!rs_hide_winpercentage)
    {
        Stats tstats = GetStats();

        int total = tstats.win + tstats.loss;
        if (total == 0) {
            tmp = "N/A";
        }
        else {
            tmp = Utils::FloatFixer((float)tstats.win / (float)total * 100.F, (rs_enable_float ? 2 : 0));
        }
    }

    WriteInFile("RocketStats_WinPercentage.txt", tmp);
}

void RocketStats::WriteDemo(bool force)
{
    if (force || (rs_in_file && rs_file_demo))
        WriteInFile("RocketStats_Demo.txt", (rs_hide_demo ? theme_hide_value : std::to_string(GetStats().demo)));

    if (force || (rs_in_file && rs_file_demom))
        WriteInFile("RocketStats_DemoMatch.txt", (rs_hide_demom ? theme_hide_value : std::to_string(current.demo)));

    if (force || (rs_in_file && rs_file_democ))
        WriteInFile("RocketStats_DemoCumul.txt", (rs_hide_democ ? theme_hide_value : std::to_string(GetStats().demoCumul)));
}

void RocketStats::WriteDeath(bool force)
{
    if (force || (rs_in_file && rs_file_death))
        WriteInFile("RocketStats_Death.txt", (rs_hide_death ? theme_hide_value : std::to_string(GetStats().death)));

    if (force || (rs_in_file && rs_file_deathm))
        WriteInFile("RocketStats_DeathMatch.txt", (rs_hide_deathm ? theme_hide_value : std::to_string(current.death)));

    if (force || (rs_in_file && rs_file_deathc))
        WriteInFile("RocketStats_DeathCumul.txt", (rs_hide_deathc ? theme_hide_value : std::to_string(GetStats().deathCumul)));
}

void RocketStats::WriteBoost(bool force, int value)
{
    if (force || (rs_in_file && rs_file_boost))
        WriteInFile("RocketStats_BoostState.txt", std::to_string(value));
}
