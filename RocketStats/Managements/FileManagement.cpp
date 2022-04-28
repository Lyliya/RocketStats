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
    VarGames(true, force);
    VarGameMode(true, force);
    VarRank(true, force);
    VarDiv(true, force);
    VarMMR(true, force);
    VarMMRChange(true, force);
    VarMMRCumulChange(true, force);
    VarWin(true, force);
    VarLoss(true, force);
    VarStreak(true, force);
    VarWinRatio(true, force);
    VarWinPercentage(true, force);
    VarDemolitions(true, force);
    VarDemolitionsMatch(true, force);
    VarDemolitionsCumul(true, force);
    VarDeath(true, force);
    VarDeathMatch(true, force);
    VarDeathCumul(true, force);

    AllShots(force);
    AllMiscs(force);
    AllAssists(force);
    AllGoals(force);
    AllSaves(force);
    AllDropshot(force);

    VarBoost(true, force, (!is_game_started || is_game_ended), false);
}

void RocketStats::ResetFiles()
{
    last_rank = "";
    last_division = "";

    VarGames(true, true, true);
    VarGameMode(true, true, true);
    VarRank(true, true, true);
    VarDiv(true, true, true);
    VarMMR(true, true, true);
    VarMMRChange(true, true, true);
    VarMMRCumulChange(true, true, true);
    VarWin(true, true, true);
    VarLoss(true, true, true);
    VarStreak(true, true, true);
    VarWinRatio(true, true, true);
    VarWinPercentage(true, true, true);
    VarDemolitions(true, true, true);
    VarDemolitionsMatch(true, true, true);
    VarDemolitionsCumul(true, true, true);
    VarDeath(true, true, true);
    VarDeathMatch(true, true, true);
    VarDeathCumul(true, true, true);

    AllShots(true, true);
    AllMiscs(true, true);
    AllAssists(true, true);
    AllGoals(true, true);
    AllSaves(true, true);
    AllDropshot(true, true);

    VarBoost(true, true, true);
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
                        if (config["settings"]["files"]["shots"].is_boolean())
                            rs_file_shots = config["settings"]["files"]["shots"];
                        if (config["settings"]["files"]["miscs"].is_boolean())
                            rs_file_miscs = config["settings"]["files"]["miscs"];
                        if (config["settings"]["files"]["assists"].is_boolean())
                            rs_file_assists = config["settings"]["files"]["assists"];
                        if (config["settings"]["files"]["goals"].is_boolean())
                            rs_file_goals = config["settings"]["files"]["goals"];
                        if (config["settings"]["files"]["saves"].is_boolean())
                            rs_file_saves = config["settings"]["files"]["saves"];
                        if (config["settings"]["files"]["dropshot"].is_boolean())
                            rs_file_dropshot = config["settings"]["files"]["dropshot"];
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
                        if (config["settings"]["hides"]["shots"].is_boolean())
                            rs_hide_shots = config["settings"]["hides"]["shots"];
                        if (config["settings"]["hides"]["miscs"].is_boolean())
                            rs_hide_miscs = config["settings"]["hides"]["miscs"];
                        if (config["settings"]["hides"]["assists"].is_boolean())
                            rs_hide_assists = config["settings"]["hides"]["assists"];
                        if (config["settings"]["hides"]["goals"].is_boolean())
                            rs_hide_goals = config["settings"]["hides"]["goals"];
                        if (config["settings"]["hides"]["saves"].is_boolean())
                            rs_hide_saves = config["settings"]["hides"]["saves"];
                        if (config["settings"]["hides"]["dropshot"].is_boolean())
                            rs_hide_dropshot = config["settings"]["hides"]["dropshot"];

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

                    /// Shots
                    if (config["always"]["Shot"].is_number_unsigned())
                        always.Shot = int(config["always"]["Shot"]);
                    if (config["always"]["CenterBall"].is_number_unsigned())
                        always.CenterBall = int(config["always"]["CenterBall"]);
                    if (config["always"]["ClearBall"].is_number_unsigned())
                        always.ClearBall = int(config["always"]["ClearBall"]);
                    if (config["always"]["FirstTouch"].is_number_unsigned())
                        always.FirstTouch = int(config["always"]["FirstTouch"]);
                    if (config["always"]["ShotOnGoal"].is_number_unsigned())
                        always.ShotOnGoal = int(config["always"]["ShotOnGoal"]);
                    if (config["always"]["BicycleHit"].is_number_unsigned())
                        always.BicycleHit = int(config["always"]["BicycleHit"]);
                    if (config["always"]["TeamShot"].is_number_unsigned())
                        always.TeamShot = int(config["always"]["TeamShot"]);
                    if (config["always"]["TeamCenterBall"].is_number_unsigned())
                        always.TeamCenterBall = int(config["always"]["TeamCenterBall"]);
                    if (config["always"]["TeamClearBall"].is_number_unsigned())
                        always.TeamClearBall = int(config["always"]["TeamClearBall"]);
                    if (config["always"]["TeamFirstTouch"].is_number_unsigned())
                        always.TeamFirstTouch = int(config["always"]["TeamFirstTouch"]);
                    if (config["always"]["TeamShotOnGoal"].is_number_unsigned())
                        always.TeamShotOnGoal = int(config["always"]["TeamShotOnGoal"]);
                    if (config["always"]["TeamBicycleHit"].is_number_unsigned())
                        always.TeamBicycleHit = int(config["always"]["TeamBicycleHit"]);
                    if (config["always"]["TotalShot"].is_number_unsigned())
                        always.TotalShot = int(config["always"]["TotalShot"]);
                    if (config["always"]["TotalCenterBall"].is_number_unsigned())
                        always.TotalCenterBall = int(config["always"]["TotalCenterBall"]);
                    if (config["always"]["TotalClearBall"].is_number_unsigned())
                        always.TotalClearBall = int(config["always"]["TotalClearBall"]);
                    if (config["always"]["TotalFirstTouch"].is_number_unsigned())
                        always.TotalFirstTouch = int(config["always"]["TotalFirstTouch"]);
                    if (config["always"]["TotalShotOnGoal"].is_number_unsigned())
                        always.TotalShotOnGoal = int(config["always"]["TotalShotOnGoal"]);
                    if (config["always"]["TotalBicycleHit"].is_number_unsigned())
                        always.TotalBicycleHit = int(config["always"]["TotalBicycleHit"]);

                    if (config["always"]["ShotCumul"].is_number_unsigned())
                        always.ShotCumul = int(config["always"]["ShotCumul"]);
                    if (config["always"]["CenterBallCumul"].is_number_unsigned())
                        always.CenterBallCumul = int(config["always"]["CenterBallCumul"]);
                    if (config["always"]["ClearBallCumul"].is_number_unsigned())
                        always.ClearBallCumul = int(config["always"]["ClearBallCumul"]);
                    if (config["always"]["FirstTouchCumul"].is_number_unsigned())
                        always.FirstTouchCumul = int(config["always"]["FirstTouchCumul"]);
                    if (config["always"]["ShotOnGoalCumul"].is_number_unsigned())
                        always.ShotOnGoalCumul = int(config["always"]["ShotOnGoalCumul"]);
                    if (config["always"]["BicycleHitCumul"].is_number_unsigned())
                        always.BicycleHitCumul = int(config["always"]["BicycleHitCumul"]);
                    if (config["always"]["TeamShotCumul"].is_number_unsigned())
                        always.TeamShotCumul = int(config["always"]["TeamShotCumul"]);
                    if (config["always"]["TeamCenterBallCumul"].is_number_unsigned())
                        always.TeamCenterBallCumul = int(config["always"]["TeamCenterBallCumul"]);
                    if (config["always"]["TeamClearBallCumul"].is_number_unsigned())
                        always.TeamClearBallCumul = int(config["always"]["TeamClearBallCumul"]);
                    if (config["always"]["TeamFirstTouchCumul"].is_number_unsigned())
                        always.TeamFirstTouchCumul = int(config["always"]["TeamFirstTouchCumul"]);
                    if (config["always"]["TeamShotOnGoalCumul"].is_number_unsigned())
                        always.TeamShotOnGoalCumul = int(config["always"]["TeamShotOnGoalCumul"]);
                    if (config["always"]["TeamBicycleHitCumul"].is_number_unsigned())
                        always.TeamBicycleHitCumul = int(config["always"]["TeamBicycleHitCumul"]);
                    if (config["always"]["TotalShotCumul"].is_number_unsigned())
                        always.TotalShotCumul = int(config["always"]["TotalShotCumul"]);
                    if (config["always"]["TotalCenterBallCumul"].is_number_unsigned())
                        always.TotalCenterBallCumul = int(config["always"]["TotalCenterBallCumul"]);
                    if (config["always"]["TotalClearBallCumul"].is_number_unsigned())
                        always.TotalClearBallCumul = int(config["always"]["TotalClearBallCumul"]);
                    if (config["always"]["TotalFirstTouchCumul"].is_number_unsigned())
                        always.TotalFirstTouchCumul = int(config["always"]["TotalFirstTouchCumul"]);
                    if (config["always"]["TotalShotOnGoalCumul"].is_number_unsigned())
                        always.TotalShotOnGoalCumul = int(config["always"]["TotalShotOnGoalCumul"]);
                    if (config["always"]["TotalBicycleHitCumul"].is_number_unsigned())
                        always.TotalBicycleHitCumul = int(config["always"]["TotalBicycleHitCumul"]);

                    /// Miscs
                    if (config["always"]["HatTrick"].is_number_unsigned())
                        always.HatTrick = int(config["always"]["HatTrick"]);
                    if (config["always"]["LowFive"].is_number_unsigned())
                        always.LowFive = int(config["always"]["LowFive"]);
                    if (config["always"]["HighFive"].is_number_unsigned())
                        always.HighFive = int(config["always"]["HighFive"]);
                    if (config["always"]["MVP"].is_number_unsigned())
                        always.MVP = int(config["always"]["MVP"]);
                    if (config["always"]["TeamHatTrick"].is_number_unsigned())
                        always.TeamHatTrick = int(config["always"]["TeamHatTrick"]);
                    if (config["always"]["TeamLowFive"].is_number_unsigned())
                        always.TeamLowFive = int(config["always"]["TeamLowFive"]);
                    if (config["always"]["TeamHighFive"].is_number_unsigned())
                        always.TeamHighFive = int(config["always"]["TeamHighFive"]);
                    if (config["always"]["TeamMVP"].is_number_unsigned())
                        always.TeamMVP = int(config["always"]["TeamMVP"]);
                    if (config["always"]["TotalHatTrick"].is_number_unsigned())
                        always.TotalHatTrick = int(config["always"]["TotalHatTrick"]);
                    if (config["always"]["TotalLowFive"].is_number_unsigned())
                        always.TotalLowFive = int(config["always"]["TotalLowFive"]);
                    if (config["always"]["TotalHighFive"].is_number_unsigned())
                        always.TotalHighFive = int(config["always"]["TotalHighFive"]);
                    if (config["always"]["TotalMVP"].is_number_unsigned())
                        always.TotalMVP = int(config["always"]["TotalMVP"]);

                    if (config["always"]["HatTrickCumul"].is_number_unsigned())
                        always.HatTrickCumul = int(config["always"]["HatTrickCumul"]);
                    if (config["always"]["LowFiveCumul"].is_number_unsigned())
                        always.LowFiveCumul = int(config["always"]["LowFiveCumul"]);
                    if (config["always"]["HighFiveCumul"].is_number_unsigned())
                        always.HighFiveCumul = int(config["always"]["HighFiveCumul"]);
                    if (config["always"]["MVPCumul"].is_number_unsigned())
                        always.MVPCumul = int(config["always"]["MVPCumul"]);
                    if (config["always"]["TeamHatTrickCumul"].is_number_unsigned())
                        always.TeamHatTrickCumul = int(config["always"]["TeamHatTrickCumul"]);
                    if (config["always"]["TeamLowFiveCumul"].is_number_unsigned())
                        always.TeamLowFiveCumul = int(config["always"]["TeamLowFiveCumul"]);
                    if (config["always"]["TeamHighFiveCumul"].is_number_unsigned())
                        always.TeamHighFiveCumul = int(config["always"]["TeamHighFiveCumul"]);
                    if (config["always"]["TeamMVPCumul"].is_number_unsigned())
                        always.TeamMVPCumul = int(config["always"]["TeamMVPCumul"]);
                    if (config["always"]["TotalHatTrickCumul"].is_number_unsigned())
                        always.TotalHatTrickCumul = int(config["always"]["TotalHatTrickCumul"]);
                    if (config["always"]["TotalLowFiveCumul"].is_number_unsigned())
                        always.TotalLowFiveCumul = int(config["always"]["TotalLowFiveCumul"]);
                    if (config["always"]["TotalHighFiveCumul"].is_number_unsigned())
                        always.TotalHighFiveCumul = int(config["always"]["TotalHighFiveCumul"]);
                    if (config["always"]["TotalMVPCumul"].is_number_unsigned())
                        always.TotalMVPCumul = int(config["always"]["TotalMVPCumul"]);

                    /// Assists
                    if (config["always"]["Assist"].is_number_unsigned())
                        always.Assist = int(config["always"]["Assist"]);
                    if (config["always"]["Playmaker"].is_number_unsigned())
                        always.Playmaker = int(config["always"]["Playmaker"]);
                    if (config["always"]["TeamAssist"].is_number_unsigned())
                        always.TeamAssist = int(config["always"]["TeamAssist"]);
                    if (config["always"]["TeamPlaymaker"].is_number_unsigned())
                        always.TeamPlaymaker = int(config["always"]["TeamPlaymaker"]);
                    if (config["always"]["TotalAssist"].is_number_unsigned())
                        always.TotalAssist = int(config["always"]["TotalAssist"]);
                    if (config["always"]["TotalPlaymaker"].is_number_unsigned())
                        always.TotalPlaymaker = int(config["always"]["TotalPlaymaker"]);

                    if (config["always"]["AssistCumul"].is_number_unsigned())
                        always.AssistCumul = int(config["always"]["AssistCumul"]);
                    if (config["always"]["PlaymakerCumul"].is_number_unsigned())
                        always.PlaymakerCumul = int(config["always"]["PlaymakerCumul"]);
                    if (config["always"]["TeamAssistCumul"].is_number_unsigned())
                        always.TeamAssistCumul = int(config["always"]["TeamAssistCumul"]);
                    if (config["always"]["TeamPlaymakerCumul"].is_number_unsigned())
                        always.TeamPlaymakerCumul = int(config["always"]["TeamPlaymakerCumul"]);
                    if (config["always"]["TotalAssistCumul"].is_number_unsigned())
                        always.TotalAssistCumul = int(config["always"]["TotalAssistCumul"]);
                    if (config["always"]["TotalPlaymakerCumul"].is_number_unsigned())
                        always.TotalPlaymakerCumul = int(config["always"]["TotalPlaymakerCumul"]);

                    /// Goals
                    if (config["always"]["Goal"].is_number_unsigned())
                        always.Goal = int(config["always"]["Goal"]);
                    if (config["always"]["AerialGoal"].is_number_unsigned())
                        always.AerialGoal = int(config["always"]["AerialGoal"]);
                    if (config["always"]["BackwardsGoal"].is_number_unsigned())
                        always.BackwardsGoal = int(config["always"]["BackwardsGoal"]);
                    if (config["always"]["BicycleGoal"].is_number_unsigned())
                        always.BicycleGoal = int(config["always"]["BicycleGoal"]);
                    if (config["always"]["LongGoal"].is_number_unsigned())
                        always.LongGoal = int(config["always"]["LongGoal"]);
                    if (config["always"]["TurtleGoal"].is_number_unsigned())
                        always.TurtleGoal = int(config["always"]["TurtleGoal"]);
                    if (config["always"]["OvertimeGoal"].is_number_unsigned())
                        always.OvertimeGoal = int(config["always"]["OvertimeGoal"]);
                    if (config["always"]["SwishGoal"].is_number_unsigned())
                        always.SwishGoal = int(config["always"]["SwishGoal"]);
                    if (config["always"]["TeamGoal"].is_number_unsigned())
                        always.TeamGoal = int(config["always"]["TeamGoal"]);
                    if (config["always"]["TeamAerialGoal"].is_number_unsigned())
                        always.TeamAerialGoal = int(config["always"]["TeamAerialGoal"]);
                    if (config["always"]["TeamBackwardsGoal"].is_number_unsigned())
                        always.TeamBackwardsGoal = int(config["always"]["TeamBackwardsGoal"]);
                    if (config["always"]["TeamBicycleGoal"].is_number_unsigned())
                        always.TeamBicycleGoal = int(config["always"]["TeamBicycleGoal"]);
                    if (config["always"]["TeamLongGoal"].is_number_unsigned())
                        always.TeamLongGoal = int(config["always"]["TeamLongGoal"]);
                    if (config["always"]["TeamTurtleGoal"].is_number_unsigned())
                        always.TeamTurtleGoal = int(config["always"]["TeamTurtleGoal"]);
                    if (config["always"]["TeamOvertimeGoal"].is_number_unsigned())
                        always.TeamOvertimeGoal = int(config["always"]["TeamOvertimeGoal"]);
                    if (config["always"]["TeamSwishGoal"].is_number_unsigned())
                        always.TeamSwishGoal = int(config["always"]["TeamSwishGoal"]);
                    if (config["always"]["TotalGoal"].is_number_unsigned())
                        always.TotalGoal = int(config["always"]["TotalGoal"]);
                    if (config["always"]["TotalAerialGoal"].is_number_unsigned())
                        always.TotalAerialGoal = int(config["always"]["TotalAerialGoal"]);
                    if (config["always"]["TotalBackwardsGoal"].is_number_unsigned())
                        always.TotalBackwardsGoal = int(config["always"]["TotalBackwardsGoal"]);
                    if (config["always"]["TotalBicycleGoal"].is_number_unsigned())
                        always.TotalBicycleGoal = int(config["always"]["TotalBicycleGoal"]);
                    if (config["always"]["TotalLongGoal"].is_number_unsigned())
                        always.TotalLongGoal = int(config["always"]["TotalLongGoal"]);
                    if (config["always"]["TotalTurtleGoal"].is_number_unsigned())
                        always.TotalTurtleGoal = int(config["always"]["TotalTurtleGoal"]);
                    if (config["always"]["TotalOvertimeGoal"].is_number_unsigned())
                        always.TotalOvertimeGoal = int(config["always"]["TotalOvertimeGoal"]);
                    if (config["always"]["TotalSwishGoal"].is_number_unsigned())
                        always.TotalSwishGoal = int(config["always"]["TotalSwishGoal"]);

                    if (config["always"]["GoalCumul"].is_number_unsigned())
                        always.GoalCumul = int(config["always"]["GoalCumul"]);
                    if (config["always"]["AerialGoalCumul"].is_number_unsigned())
                        always.AerialGoalCumul = int(config["always"]["AerialGoalCumul"]);
                    if (config["always"]["BackwardsGoalCumul"].is_number_unsigned())
                        always.BackwardsGoalCumul = int(config["always"]["BackwardsGoalCumul"]);
                    if (config["always"]["BicycleGoalCumul"].is_number_unsigned())
                        always.BicycleGoalCumul = int(config["always"]["BicycleGoalCumul"]);
                    if (config["always"]["LongGoalCumul"].is_number_unsigned())
                        always.LongGoalCumul = int(config["always"]["LongGoalCumul"]);
                    if (config["always"]["TurtleGoalCumul"].is_number_unsigned())
                        always.TurtleGoalCumul = int(config["always"]["TurtleGoalCumul"]);
                    if (config["always"]["OvertimeGoalCumul"].is_number_unsigned())
                        always.OvertimeGoalCumul = int(config["always"]["OvertimeGoalCumul"]);
                    if (config["always"]["SwishGoalCumul"].is_number_unsigned())
                        always.SwishGoalCumul = int(config["always"]["SwishGoalCumul"]);
                    if (config["always"]["TeamGoalCumul"].is_number_unsigned())
                        always.TeamGoalCumul = int(config["always"]["TeamGoalCumul"]);
                    if (config["always"]["TeamAerialGoalCumul"].is_number_unsigned())
                        always.TeamAerialGoalCumul = int(config["always"]["TeamAerialGoalCumul"]);
                    if (config["always"]["TeamBackwardsGoalCumul"].is_number_unsigned())
                        always.TeamBackwardsGoalCumul = int(config["always"]["TeamBackwardsGoalCumul"]);
                    if (config["always"]["TeamBicycleGoalCumul"].is_number_unsigned())
                        always.TeamBicycleGoalCumul = int(config["always"]["TeamBicycleGoalCumul"]);
                    if (config["always"]["TeamLongGoalCumul"].is_number_unsigned())
                        always.TeamLongGoalCumul = int(config["always"]["TeamLongGoalCumul"]);
                    if (config["always"]["TeamTurtleGoalCumul"].is_number_unsigned())
                        always.TeamTurtleGoalCumul = int(config["always"]["TeamTurtleGoalCumul"]);
                    if (config["always"]["TeamOvertimeGoalCumul"].is_number_unsigned())
                        always.TeamOvertimeGoalCumul = int(config["always"]["TeamOvertimeGoalCumul"]);
                    if (config["always"]["TeamSwishGoalCumul"].is_number_unsigned())
                        always.TeamSwishGoalCumul = int(config["always"]["TeamSwishGoalCumul"]);
                    if (config["always"]["TotalGoalCumul"].is_number_unsigned())
                        always.TotalGoalCumul = int(config["always"]["TotalGoalCumul"]);
                    if (config["always"]["TotalAerialGoalCumul"].is_number_unsigned())
                        always.TotalAerialGoalCumul = int(config["always"]["TotalAerialGoalCumul"]);
                    if (config["always"]["TotalBackwardsGoalCumul"].is_number_unsigned())
                        always.TotalBackwardsGoalCumul = int(config["always"]["TotalBackwardsGoalCumul"]);
                    if (config["always"]["TotalBicycleGoalCumul"].is_number_unsigned())
                        always.TotalBicycleGoalCumul = int(config["always"]["TotalBicycleGoalCumul"]);
                    if (config["always"]["TotalLongGoalCumul"].is_number_unsigned())
                        always.TotalLongGoalCumul = int(config["always"]["TotalLongGoalCumul"]);
                    if (config["always"]["TotalTurtleGoalCumul"].is_number_unsigned())
                        always.TotalTurtleGoalCumul = int(config["always"]["TotalTurtleGoalCumul"]);
                    if (config["always"]["TotalOvertimeGoalCumul"].is_number_unsigned())
                        always.TotalOvertimeGoalCumul = int(config["always"]["TotalOvertimeGoalCumul"]);
                    if (config["always"]["TotalSwishGoalCumul"].is_number_unsigned())
                        always.TotalSwishGoalCumul = int(config["always"]["TotalSwishGoalCumul"]);

                    /// Saves
                    if (config["always"]["Save"].is_number_unsigned())
                        always.Save = int(config["always"]["Save"]);
                    if (config["always"]["EpicSave"].is_number_unsigned())
                        always.EpicSave = int(config["always"]["EpicSave"]);
                    if (config["always"]["Savior"].is_number_unsigned())
                        always.Savior = int(config["always"]["Savior"]);
                    if (config["always"]["TeamSave"].is_number_unsigned())
                        always.TeamSave = int(config["always"]["TeamSave"]);
                    if (config["always"]["TeamEpicSave"].is_number_unsigned())
                        always.TeamEpicSave = int(config["always"]["TeamEpicSave"]);
                    if (config["always"]["TeamSavior"].is_number_unsigned())
                        always.TeamSavior = int(config["always"]["TeamSavior"]);
                    if (config["always"]["TotalSave"].is_number_unsigned())
                        always.TotalSave = int(config["always"]["TotalSave"]);
                    if (config["always"]["TotalEpicSave"].is_number_unsigned())
                        always.TotalEpicSave = int(config["always"]["TotalEpicSave"]);
                    if (config["always"]["TotalSavior"].is_number_unsigned())
                        always.TotalSavior = int(config["always"]["TotalSavior"]);

                    if (config["always"]["SaveCumul"].is_number_unsigned())
                        always.SaveCumul = int(config["always"]["SaveCumul"]);
                    if (config["always"]["EpicSaveCumul"].is_number_unsigned())
                        always.EpicSaveCumul = int(config["always"]["EpicSaveCumul"]);
                    if (config["always"]["SaviorCumul"].is_number_unsigned())
                        always.SaviorCumul = int(config["always"]["SaviorCumul"]);
                    if (config["always"]["TeamSaveCumul"].is_number_unsigned())
                        always.TeamSaveCumul = int(config["always"]["TeamSaveCumul"]);
                    if (config["always"]["TeamEpicSaveCumul"].is_number_unsigned())
                        always.TeamEpicSaveCumul = int(config["always"]["TeamEpicSaveCumul"]);
                    if (config["always"]["TeamSaviorCumul"].is_number_unsigned())
                        always.TeamSaviorCumul = int(config["always"]["TeamSaviorCumul"]);
                    if (config["always"]["TotalSaveCumul"].is_number_unsigned())
                        always.TotalSaveCumul = int(config["always"]["TotalSaveCumul"]);
                    if (config["always"]["TotalEpicSaveCumul"].is_number_unsigned())
                        always.TotalEpicSaveCumul = int(config["always"]["TotalEpicSaveCumul"]);
                    if (config["always"]["TotalSaviorCumul"].is_number_unsigned())
                        always.TotalSaviorCumul = int(config["always"]["TotalSaviorCumul"]);

                    /// Dropshot
                    if (config["always"]["Damage"].is_number_unsigned())
                        always.Damage = int(config["always"]["Damage"]);
                    if (config["always"]["UltraDamage"].is_number_unsigned())
                        always.UltraDamage = int(config["always"]["UltraDamage"]);
                    if (config["always"]["TeamDamage"].is_number_unsigned())
                        always.TeamDamage = int(config["always"]["TeamDamage"]);
                    if (config["always"]["TeamUltraDamage"].is_number_unsigned())
                        always.TeamUltraDamage = int(config["always"]["TeamUltraDamage"]);
                    if (config["always"]["TotalDamage"].is_number_unsigned())
                        always.TotalDamage = int(config["always"]["TotalDamage"]);
                    if (config["always"]["TotalUltraDamage"].is_number_unsigned())
                        always.TotalUltraDamage = int(config["always"]["TotalUltraDamage"]);

                    if (config["always"]["DamageCumul"].is_number_unsigned())
                        always.DamageCumul = int(config["always"]["DamageCumul"]);
                    if (config["always"]["UltraDamageCumul"].is_number_unsigned())
                        always.UltraDamageCumul = int(config["always"]["UltraDamageCumul"]);
                    if (config["always"]["TeamDamageCumul"].is_number_unsigned())
                        always.TeamDamageCumul = int(config["always"]["TeamDamageCumul"]);
                    if (config["always"]["TeamUltraDamageCumul"].is_number_unsigned())
                        always.TeamUltraDamageCumul = int(config["always"]["TeamUltraDamageCumul"]);
                    if (config["always"]["TotalDamageCumul"].is_number_unsigned())
                        always.TotalDamageCumul = int(config["always"]["TotalDamageCumul"]);
                    if (config["always"]["TotalUltraDamageCumul"].is_number_unsigned())
                        always.TotalUltraDamageCumul = int(config["always"]["TotalUltraDamageCumul"]);

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

                            /// Shots
                            if (config["always_gm"][i]["Shot"].is_number_unsigned())
                                always_gm[i].Shot = int(config["always_gm"][i]["Shot"]);
                            if (config["always_gm"][i]["CenterBall"].is_number_unsigned())
                                always_gm[i].CenterBall = int(config["always_gm"][i]["CenterBall"]);
                            if (config["always_gm"][i]["ClearBall"].is_number_unsigned())
                                always_gm[i].ClearBall = int(config["always_gm"][i]["ClearBall"]);
                            if (config["always_gm"][i]["FirstTouch"].is_number_unsigned())
                                always_gm[i].FirstTouch = int(config["always_gm"][i]["FirstTouch"]);
                            if (config["always_gm"][i]["ShotOnGoal"].is_number_unsigned())
                                always_gm[i].ShotOnGoal = int(config["always_gm"][i]["ShotOnGoal"]);
                            if (config["always_gm"][i]["BicycleHit"].is_number_unsigned())
                                always_gm[i].BicycleHit = int(config["always_gm"][i]["BicycleHit"]);
                            if (config["always_gm"][i]["TeamShot"].is_number_unsigned())
                                always_gm[i].TeamShot = int(config["always_gm"][i]["TeamShot"]);
                            if (config["always_gm"][i]["TeamCenterBall"].is_number_unsigned())
                                always_gm[i].TeamCenterBall = int(config["always_gm"][i]["TeamCenterBall"]);
                            if (config["always_gm"][i]["TeamClearBall"].is_number_unsigned())
                                always_gm[i].TeamClearBall = int(config["always_gm"][i]["TeamClearBall"]);
                            if (config["always_gm"][i]["TeamFirstTouch"].is_number_unsigned())
                                always_gm[i].TeamFirstTouch = int(config["always_gm"][i]["TeamFirstTouch"]);
                            if (config["always_gm"][i]["TeamShotOnGoal"].is_number_unsigned())
                                always_gm[i].TeamShotOnGoal = int(config["always_gm"][i]["TeamShotOnGoal"]);
                            if (config["always_gm"][i]["TeamBicycleHit"].is_number_unsigned())
                                always_gm[i].TeamBicycleHit = int(config["always_gm"][i]["TeamBicycleHit"]);
                            if (config["always_gm"][i]["TotalShot"].is_number_unsigned())
                                always_gm[i].TotalShot = int(config["always_gm"][i]["TotalShot"]);
                            if (config["always_gm"][i]["TotalCenterBall"].is_number_unsigned())
                                always_gm[i].TotalCenterBall = int(config["always_gm"][i]["TotalCenterBall"]);
                            if (config["always_gm"][i]["TotalClearBall"].is_number_unsigned())
                                always_gm[i].TotalClearBall = int(config["always_gm"][i]["TotalClearBall"]);
                            if (config["always_gm"][i]["TotalFirstTouch"].is_number_unsigned())
                                always_gm[i].TotalFirstTouch = int(config["always_gm"][i]["TotalFirstTouch"]);
                            if (config["always_gm"][i]["TotalShotOnGoal"].is_number_unsigned())
                                always_gm[i].TotalShotOnGoal = int(config["always_gm"][i]["TotalShotOnGoal"]);
                            if (config["always_gm"][i]["TotalBicycleHit"].is_number_unsigned())
                                always_gm[i].TotalBicycleHit = int(config["always_gm"][i]["TotalBicycleHit"]);

                            if (config["always_gm"][i]["ShotCumul"].is_number_unsigned())
                                always_gm[i].ShotCumul = int(config["always_gm"][i]["ShotCumul"]);
                            if (config["always_gm"][i]["CenterBallCumul"].is_number_unsigned())
                                always_gm[i].CenterBallCumul = int(config["always_gm"][i]["CenterBallCumul"]);
                            if (config["always_gm"][i]["ClearBallCumul"].is_number_unsigned())
                                always_gm[i].ClearBallCumul = int(config["always_gm"][i]["ClearBallCumul"]);
                            if (config["always_gm"][i]["FirstTouchCumul"].is_number_unsigned())
                                always_gm[i].FirstTouchCumul = int(config["always_gm"][i]["FirstTouchCumul"]);
                            if (config["always_gm"][i]["ShotOnGoalCumul"].is_number_unsigned())
                                always_gm[i].ShotOnGoalCumul = int(config["always_gm"][i]["ShotOnGoalCumul"]);
                            if (config["always_gm"][i]["BicycleHitCumul"].is_number_unsigned())
                                always_gm[i].BicycleHitCumul = int(config["always_gm"][i]["BicycleHitCumul"]);
                            if (config["always_gm"][i]["TeamShotCumul"].is_number_unsigned())
                                always_gm[i].TeamShotCumul = int(config["always_gm"][i]["TeamShotCumul"]);
                            if (config["always_gm"][i]["TeamCenterBallCumul"].is_number_unsigned())
                                always_gm[i].TeamCenterBallCumul = int(config["always_gm"][i]["TeamCenterBallCumul"]);
                            if (config["always_gm"][i]["TeamClearBallCumul"].is_number_unsigned())
                                always_gm[i].TeamClearBallCumul = int(config["always_gm"][i]["TeamClearBallCumul"]);
                            if (config["always_gm"][i]["TeamFirstTouchCumul"].is_number_unsigned())
                                always_gm[i].TeamFirstTouchCumul = int(config["always_gm"][i]["TeamFirstTouchCumul"]);
                            if (config["always_gm"][i]["TeamShotOnGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamShotOnGoalCumul = int(config["always_gm"][i]["TeamShotOnGoalCumul"]);
                            if (config["always_gm"][i]["TeamBicycleHitCumul"].is_number_unsigned())
                                always_gm[i].TeamBicycleHitCumul = int(config["always_gm"][i]["TeamBicycleHitCumul"]);
                            if (config["always_gm"][i]["TotalShotCumul"].is_number_unsigned())
                                always_gm[i].TotalShotCumul = int(config["always_gm"][i]["TotalShotCumul"]);
                            if (config["always_gm"][i]["TotalCenterBallCumul"].is_number_unsigned())
                                always_gm[i].TotalCenterBallCumul = int(config["always_gm"][i]["TotalCenterBallCumul"]);
                            if (config["always_gm"][i]["TotalClearBallCumul"].is_number_unsigned())
                                always_gm[i].TotalClearBallCumul = int(config["always_gm"][i]["TotalClearBallCumul"]);
                            if (config["always_gm"][i]["TotalFirstTouchCumul"].is_number_unsigned())
                                always_gm[i].TotalFirstTouchCumul = int(config["always_gm"][i]["TotalFirstTouchCumul"]);
                            if (config["always_gm"][i]["TotalShotOnGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalShotOnGoalCumul = int(config["always_gm"][i]["TotalShotOnGoalCumul"]);
                            if (config["always_gm"][i]["TotalBicycleHitCumul"].is_number_unsigned())
                                always_gm[i].TotalBicycleHitCumul = int(config["always_gm"][i]["TotalBicycleHitCumul"]);

                            /// Miscs
                            if (config["always_gm"][i]["HatTrick"].is_number_unsigned())
                                always_gm[i].HatTrick = int(config["always_gm"][i]["HatTrick"]);
                            if (config["always_gm"][i]["LowFive"].is_number_unsigned())
                                always_gm[i].LowFive = int(config["always_gm"][i]["LowFive"]);
                            if (config["always_gm"][i]["HighFive"].is_number_unsigned())
                                always_gm[i].HighFive = int(config["always_gm"][i]["HighFive"]);
                            if (config["always_gm"][i]["MVP"].is_number_unsigned())
                                always_gm[i].MVP = int(config["always_gm"][i]["MVP"]);
                            if (config["always_gm"][i]["TeamHatTrick"].is_number_unsigned())
                                always_gm[i].TeamHatTrick = int(config["always_gm"][i]["TeamHatTrick"]);
                            if (config["always_gm"][i]["TeamLowFive"].is_number_unsigned())
                                always_gm[i].TeamLowFive = int(config["always_gm"][i]["TeamLowFive"]);
                            if (config["always_gm"][i]["TeamHighFive"].is_number_unsigned())
                                always_gm[i].TeamHighFive = int(config["always_gm"][i]["TeamHighFive"]);
                            if (config["always_gm"][i]["TeamMVP"].is_number_unsigned())
                                always_gm[i].TeamMVP = int(config["always_gm"][i]["TeamMVP"]);
                            if (config["always_gm"][i]["TotalHatTrick"].is_number_unsigned())
                                always_gm[i].TotalHatTrick = int(config["always_gm"][i]["TotalHatTrick"]);
                            if (config["always_gm"][i]["TotalLowFive"].is_number_unsigned())
                                always_gm[i].TotalLowFive = int(config["always_gm"][i]["TotalLowFive"]);
                            if (config["always_gm"][i]["TotalHighFive"].is_number_unsigned())
                                always_gm[i].TotalHighFive = int(config["always_gm"][i]["TotalHighFive"]);
                            if (config["always_gm"][i]["TotalMVP"].is_number_unsigned())
                                always_gm[i].TotalMVP = int(config["always_gm"][i]["TotalMVP"]);

                            if (config["always_gm"][i]["HatTrickCumul"].is_number_unsigned())
                                always_gm[i].HatTrickCumul = int(config["always_gm"][i]["HatTrickCumul"]);
                            if (config["always_gm"][i]["LowFiveCumul"].is_number_unsigned())
                                always_gm[i].LowFiveCumul = int(config["always_gm"][i]["LowFiveCumul"]);
                            if (config["always_gm"][i]["HighFiveCumul"].is_number_unsigned())
                                always_gm[i].HighFiveCumul = int(config["always_gm"][i]["HighFiveCumul"]);
                            if (config["always_gm"][i]["MVPCumul"].is_number_unsigned())
                                always_gm[i].MVPCumul = int(config["always_gm"][i]["MVPCumul"]);
                            if (config["always_gm"][i]["TeamHatTrickCumul"].is_number_unsigned())
                                always_gm[i].TeamHatTrickCumul = int(config["always_gm"][i]["TeamHatTrickCumul"]);
                            if (config["always_gm"][i]["TeamLowFiveCumul"].is_number_unsigned())
                                always_gm[i].TeamLowFiveCumul = int(config["always_gm"][i]["TeamLowFiveCumul"]);
                            if (config["always_gm"][i]["TeamHighFiveCumul"].is_number_unsigned())
                                always_gm[i].TeamHighFiveCumul = int(config["always_gm"][i]["TeamHighFiveCumul"]);
                            if (config["always_gm"][i]["TeamMVPCumul"].is_number_unsigned())
                                always_gm[i].TeamMVPCumul = int(config["always_gm"][i]["TeamMVPCumul"]);
                            if (config["always_gm"][i]["TotalHatTrickCumul"].is_number_unsigned())
                                always_gm[i].TotalHatTrickCumul = int(config["always_gm"][i]["TotalHatTrickCumul"]);
                            if (config["always_gm"][i]["TotalLowFiveCumul"].is_number_unsigned())
                                always_gm[i].TotalLowFiveCumul = int(config["always_gm"][i]["TotalLowFiveCumul"]);
                            if (config["always_gm"][i]["TotalHighFiveCumul"].is_number_unsigned())
                                always_gm[i].TotalHighFiveCumul = int(config["always_gm"][i]["TotalHighFiveCumul"]);
                            if (config["always_gm"][i]["TotalMVPCumul"].is_number_unsigned())
                                always_gm[i].TotalMVPCumul = int(config["always_gm"][i]["TotalMVPCumul"]);

                            /// Assists
                            if (config["always_gm"][i]["Assist"].is_number_unsigned())
                                always_gm[i].Assist = int(config["always_gm"][i]["Assist"]);
                            if (config["always_gm"][i]["Playmaker"].is_number_unsigned())
                                always_gm[i].Playmaker = int(config["always_gm"][i]["Playmaker"]);
                            if (config["always_gm"][i]["TeamAssist"].is_number_unsigned())
                                always_gm[i].TeamAssist = int(config["always_gm"][i]["TeamAssist"]);
                            if (config["always_gm"][i]["TeamPlaymaker"].is_number_unsigned())
                                always_gm[i].TeamPlaymaker = int(config["always_gm"][i]["TeamPlaymaker"]);
                            if (config["always_gm"][i]["TotalAssist"].is_number_unsigned())
                                always_gm[i].TotalAssist = int(config["always_gm"][i]["TotalAssist"]);
                            if (config["always_gm"][i]["TotalPlaymaker"].is_number_unsigned())
                                always_gm[i].TotalPlaymaker = int(config["always_gm"][i]["TotalPlaymaker"]);

                            if (config["always_gm"][i]["AssistCumul"].is_number_unsigned())
                                always_gm[i].AssistCumul = int(config["always_gm"][i]["AssistCumul"]);
                            if (config["always_gm"][i]["PlaymakerCumul"].is_number_unsigned())
                                always_gm[i].PlaymakerCumul = int(config["always_gm"][i]["PlaymakerCumul"]);
                            if (config["always_gm"][i]["TeamAssistCumul"].is_number_unsigned())
                                always_gm[i].TeamAssistCumul = int(config["always_gm"][i]["TeamAssistCumul"]);
                            if (config["always_gm"][i]["TeamPlaymakerCumul"].is_number_unsigned())
                                always_gm[i].TeamPlaymakerCumul = int(config["always_gm"][i]["TeamPlaymakerCumul"]);
                            if (config["always_gm"][i]["TotalAssistCumul"].is_number_unsigned())
                                always_gm[i].TotalAssistCumul = int(config["always_gm"][i]["TotalAssistCumul"]);
                            if (config["always_gm"][i]["TotalPlaymakerCumul"].is_number_unsigned())
                                always_gm[i].TotalPlaymakerCumul = int(config["always_gm"][i]["TotalPlaymakerCumul"]);

                            /// Goals
                            if (config["always_gm"][i]["Goal"].is_number_unsigned())
                                always_gm[i].Goal = int(config["always_gm"][i]["Goal"]);
                            if (config["always_gm"][i]["AerialGoal"].is_number_unsigned())
                                always_gm[i].AerialGoal = int(config["always_gm"][i]["AerialGoal"]);
                            if (config["always_gm"][i]["BackwardsGoal"].is_number_unsigned())
                                always_gm[i].BackwardsGoal = int(config["always_gm"][i]["BackwardsGoal"]);
                            if (config["always_gm"][i]["BicycleGoal"].is_number_unsigned())
                                always_gm[i].BicycleGoal = int(config["always_gm"][i]["BicycleGoal"]);
                            if (config["always_gm"][i]["LongGoal"].is_number_unsigned())
                                always_gm[i].LongGoal = int(config["always_gm"][i]["LongGoal"]);
                            if (config["always_gm"][i]["TurtleGoal"].is_number_unsigned())
                                always_gm[i].TurtleGoal = int(config["always_gm"][i]["TurtleGoal"]);
                            if (config["always_gm"][i]["OvertimeGoal"].is_number_unsigned())
                                always_gm[i].OvertimeGoal = int(config["always_gm"][i]["OvertimeGoal"]);
                            if (config["always_gm"][i]["SwishGoal"].is_number_unsigned())
                                always_gm[i].SwishGoal = int(config["always_gm"][i]["SwishGoal"]);
                            if (config["always_gm"][i]["TeamGoal"].is_number_unsigned())
                                always_gm[i].TeamGoal = int(config["always_gm"][i]["TeamGoal"]);
                            if (config["always_gm"][i]["TeamAerialGoal"].is_number_unsigned())
                                always_gm[i].TeamAerialGoal = int(config["always_gm"][i]["TeamAerialGoal"]);
                            if (config["always_gm"][i]["TeamBackwardsGoal"].is_number_unsigned())
                                always_gm[i].TeamBackwardsGoal = int(config["always_gm"][i]["TeamBackwardsGoal"]);
                            if (config["always_gm"][i]["TeamBicycleGoal"].is_number_unsigned())
                                always_gm[i].TeamBicycleGoal = int(config["always_gm"][i]["TeamBicycleGoal"]);
                            if (config["always_gm"][i]["TeamLongGoal"].is_number_unsigned())
                                always_gm[i].TeamLongGoal = int(config["always_gm"][i]["TeamLongGoal"]);
                            if (config["always_gm"][i]["TeamTurtleGoal"].is_number_unsigned())
                                always_gm[i].TeamTurtleGoal = int(config["always_gm"][i]["TeamTurtleGoal"]);
                            if (config["always_gm"][i]["TeamOvertimeGoal"].is_number_unsigned())
                                always_gm[i].TeamOvertimeGoal = int(config["always_gm"][i]["TeamOvertimeGoal"]);
                            if (config["always_gm"][i]["TeamSwishGoal"].is_number_unsigned())
                                always_gm[i].TeamSwishGoal = int(config["always_gm"][i]["TeamSwishGoal"]);
                            if (config["always_gm"][i]["TotalGoal"].is_number_unsigned())
                                always_gm[i].TotalGoal = int(config["always_gm"][i]["TotalGoal"]);
                            if (config["always_gm"][i]["TotalAerialGoal"].is_number_unsigned())
                                always_gm[i].TotalAerialGoal = int(config["always_gm"][i]["TotalAerialGoal"]);
                            if (config["always_gm"][i]["TotalBackwardsGoal"].is_number_unsigned())
                                always_gm[i].TotalBackwardsGoal = int(config["always_gm"][i]["TotalBackwardsGoal"]);
                            if (config["always_gm"][i]["TotalBicycleGoal"].is_number_unsigned())
                                always_gm[i].TotalBicycleGoal = int(config["always_gm"][i]["TotalBicycleGoal"]);
                            if (config["always_gm"][i]["TotalLongGoal"].is_number_unsigned())
                                always_gm[i].TotalLongGoal = int(config["always_gm"][i]["TotalLongGoal"]);
                            if (config["always_gm"][i]["TotalTurtleGoal"].is_number_unsigned())
                                always_gm[i].TotalTurtleGoal = int(config["always_gm"][i]["TotalTurtleGoal"]);
                            if (config["always_gm"][i]["TotalOvertimeGoal"].is_number_unsigned())
                                always_gm[i].TotalOvertimeGoal = int(config["always_gm"][i]["TotalOvertimeGoal"]);
                            if (config["always_gm"][i]["TotalSwishGoal"].is_number_unsigned())
                                always_gm[i].TotalSwishGoal = int(config["always_gm"][i]["TotalSwishGoal"]);

                            if (config["always_gm"][i]["GoalCumul"].is_number_unsigned())
                                always_gm[i].GoalCumul = int(config["always_gm"][i]["GoalCumul"]);
                            if (config["always_gm"][i]["AerialGoalCumul"].is_number_unsigned())
                                always_gm[i].AerialGoalCumul = int(config["always_gm"][i]["AerialGoalCumul"]);
                            if (config["always_gm"][i]["BackwardsGoalCumul"].is_number_unsigned())
                                always_gm[i].BackwardsGoalCumul = int(config["always_gm"][i]["BackwardsGoalCumul"]);
                            if (config["always_gm"][i]["BicycleGoalCumul"].is_number_unsigned())
                                always_gm[i].BicycleGoalCumul = int(config["always_gm"][i]["BicycleGoalCumul"]);
                            if (config["always_gm"][i]["LongGoalCumul"].is_number_unsigned())
                                always_gm[i].LongGoalCumul = int(config["always_gm"][i]["LongGoalCumul"]);
                            if (config["always_gm"][i]["TurtleGoalCumul"].is_number_unsigned())
                                always_gm[i].TurtleGoalCumul = int(config["always_gm"][i]["TurtleGoalCumul"]);
                            if (config["always_gm"][i]["OvertimeGoalCumul"].is_number_unsigned())
                                always_gm[i].OvertimeGoalCumul = int(config["always_gm"][i]["OvertimeGoalCumul"]);
                            if (config["always_gm"][i]["SwishGoalCumul"].is_number_unsigned())
                                always_gm[i].SwishGoalCumul = int(config["always_gm"][i]["SwishGoalCumul"]);
                            if (config["always_gm"][i]["TeamGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamGoalCumul = int(config["always_gm"][i]["TeamGoalCumul"]);
                            if (config["always_gm"][i]["TeamAerialGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamAerialGoalCumul = int(config["always_gm"][i]["TeamAerialGoalCumul"]);
                            if (config["always_gm"][i]["TeamBackwardsGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamBackwardsGoalCumul = int(config["always_gm"][i]["TeamBackwardsGoalCumul"]);
                            if (config["always_gm"][i]["TeamBicycleGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamBicycleGoalCumul = int(config["always_gm"][i]["TeamBicycleGoalCumul"]);
                            if (config["always_gm"][i]["TeamLongGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamLongGoalCumul = int(config["always_gm"][i]["TeamLongGoalCumul"]);
                            if (config["always_gm"][i]["TeamTurtleGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamTurtleGoalCumul = int(config["always_gm"][i]["TeamTurtleGoalCumul"]);
                            if (config["always_gm"][i]["TeamOvertimeGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamOvertimeGoalCumul = int(config["always_gm"][i]["TeamOvertimeGoalCumul"]);
                            if (config["always_gm"][i]["TeamSwishGoalCumul"].is_number_unsigned())
                                always_gm[i].TeamSwishGoalCumul = int(config["always_gm"][i]["TeamSwishGoalCumul"]);
                            if (config["always_gm"][i]["TotalGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalGoalCumul = int(config["always_gm"][i]["TotalGoalCumul"]);
                            if (config["always_gm"][i]["TotalAerialGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalAerialGoalCumul = int(config["always_gm"][i]["TotalAerialGoalCumul"]);
                            if (config["always_gm"][i]["TotalBackwardsGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalBackwardsGoalCumul = int(config["always_gm"][i]["TotalBackwardsGoalCumul"]);
                            if (config["always_gm"][i]["TotalBicycleGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalBicycleGoalCumul = int(config["always_gm"][i]["TotalBicycleGoalCumul"]);
                            if (config["always_gm"][i]["TotalLongGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalLongGoalCumul = int(config["always_gm"][i]["TotalLongGoalCumul"]);
                            if (config["always_gm"][i]["TotalTurtleGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalTurtleGoalCumul = int(config["always_gm"][i]["TotalTurtleGoalCumul"]);
                            if (config["always_gm"][i]["TotalOvertimeGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalOvertimeGoalCumul = int(config["always_gm"][i]["TotalOvertimeGoalCumul"]);
                            if (config["always_gm"][i]["TotalSwishGoalCumul"].is_number_unsigned())
                                always_gm[i].TotalSwishGoalCumul = int(config["always_gm"][i]["TotalSwishGoalCumul"]);

                            /// Saves
                            if (config["always_gm"][i]["Save"].is_number_unsigned())
                                always_gm[i].Save = int(config["always_gm"][i]["Save"]);
                            if (config["always_gm"][i]["EpicSave"].is_number_unsigned())
                                always_gm[i].EpicSave = int(config["always_gm"][i]["EpicSave"]);
                            if (config["always_gm"][i]["Savior"].is_number_unsigned())
                                always_gm[i].Savior = int(config["always_gm"][i]["Savior"]);
                            if (config["always_gm"][i]["TeamSave"].is_number_unsigned())
                                always_gm[i].TeamSave = int(config["always_gm"][i]["TeamSave"]);
                            if (config["always_gm"][i]["TeamEpicSave"].is_number_unsigned())
                                always_gm[i].TeamEpicSave = int(config["always_gm"][i]["TeamEpicSave"]);
                            if (config["always_gm"][i]["TeamSavior"].is_number_unsigned())
                                always_gm[i].TeamSavior = int(config["always_gm"][i]["TeamSavior"]);
                            if (config["always_gm"][i]["TotalSave"].is_number_unsigned())
                                always_gm[i].TotalSave = int(config["always_gm"][i]["TotalSave"]);
                            if (config["always_gm"][i]["TotalEpicSave"].is_number_unsigned())
                                always_gm[i].TotalEpicSave = int(config["always_gm"][i]["TotalEpicSave"]);
                            if (config["always_gm"][i]["TotalSavior"].is_number_unsigned())
                                always_gm[i].TotalSavior = int(config["always_gm"][i]["TotalSavior"]);

                            if (config["always_gm"][i]["SaveCumul"].is_number_unsigned())
                                always_gm[i].SaveCumul = int(config["always_gm"][i]["SaveCumul"]);
                            if (config["always_gm"][i]["EpicSaveCumul"].is_number_unsigned())
                                always_gm[i].EpicSaveCumul = int(config["always_gm"][i]["EpicSaveCumul"]);
                            if (config["always_gm"][i]["SaviorCumul"].is_number_unsigned())
                                always_gm[i].SaviorCumul = int(config["always_gm"][i]["SaviorCumul"]);
                            if (config["always_gm"][i]["TeamSaveCumul"].is_number_unsigned())
                                always_gm[i].TeamSaveCumul = int(config["always_gm"][i]["TeamSaveCumul"]);
                            if (config["always_gm"][i]["TeamEpicSaveCumul"].is_number_unsigned())
                                always_gm[i].TeamEpicSaveCumul = int(config["always_gm"][i]["TeamEpicSaveCumul"]);
                            if (config["always_gm"][i]["TeamSaviorCumul"].is_number_unsigned())
                                always_gm[i].TeamSaviorCumul = int(config["always_gm"][i]["TeamSaviorCumul"]);
                            if (config["always_gm"][i]["TotalSaveCumul"].is_number_unsigned())
                                always_gm[i].TotalSaveCumul = int(config["always_gm"][i]["TotalSaveCumul"]);
                            if (config["always_gm"][i]["TotalEpicSaveCumul"].is_number_unsigned())
                                always_gm[i].TotalEpicSaveCumul = int(config["always_gm"][i]["TotalEpicSaveCumul"]);
                            if (config["always_gm"][i]["TotalSaviorCumul"].is_number_unsigned())
                                always_gm[i].TotalSaviorCumul = int(config["always_gm"][i]["TotalSaviorCumul"]);

                            /// Dropshot
                            if (config["always_gm"][i]["Damage"].is_number_unsigned())
                                always_gm[i].Damage = int(config["always_gm"][i]["Damage"]);
                            if (config["always_gm"][i]["UltraDamage"].is_number_unsigned())
                                always_gm[i].UltraDamage = int(config["always_gm"][i]["UltraDamage"]);
                            if (config["always_gm"][i]["TeamDamage"].is_number_unsigned())
                                always_gm[i].TeamDamage = int(config["always_gm"][i]["TeamDamage"]);
                            if (config["always_gm"][i]["TeamUltraDamage"].is_number_unsigned())
                                always_gm[i].TeamUltraDamage = int(config["always_gm"][i]["TeamUltraDamage"]);
                            if (config["always_gm"][i]["TotalDamage"].is_number_unsigned())
                                always_gm[i].TotalDamage = int(config["always_gm"][i]["TotalDamage"]);
                            if (config["always_gm"][i]["TotalUltraDamage"].is_number_unsigned())
                                always_gm[i].TotalUltraDamage = int(config["always_gm"][i]["TotalUltraDamage"]);

                            if (config["always_gm"][i]["DamageCumul"].is_number_unsigned())
                                always_gm[i].DamageCumul = int(config["always_gm"][i]["DamageCumul"]);
                            if (config["always_gm"][i]["UltraDamageCumul"].is_number_unsigned())
                                always_gm[i].UltraDamageCumul = int(config["always_gm"][i]["UltraDamageCumul"]);
                            if (config["always_gm"][i]["TeamDamageCumul"].is_number_unsigned())
                                always_gm[i].TeamDamageCumul = int(config["always_gm"][i]["TeamDamageCumul"]);
                            if (config["always_gm"][i]["TeamUltraDamageCumul"].is_number_unsigned())
                                always_gm[i].TeamUltraDamageCumul = int(config["always_gm"][i]["TeamUltraDamageCumul"]);
                            if (config["always_gm"][i]["TotalDamageCumul"].is_number_unsigned())
                                always_gm[i].TotalDamageCumul = int(config["always_gm"][i]["TotalDamageCumul"]);
                            if (config["always_gm"][i]["TotalUltraDamageCumul"].is_number_unsigned())
                                always_gm[i].TotalUltraDamageCumul = int(config["always_gm"][i]["TotalUltraDamageCumul"]);

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
    tmp["settings"]["files"]["shots"] = rs_file_shots;
    tmp["settings"]["files"]["miscs"] = rs_file_miscs;
    tmp["settings"]["files"]["assists"] = rs_file_assists;
    tmp["settings"]["files"]["goals"] = rs_file_goals;
    tmp["settings"]["files"]["saves"] = rs_file_saves;
    tmp["settings"]["files"]["dropshot"] = rs_file_dropshot;
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
    tmp["settings"]["hides"]["shots"] = rs_hide_shots;
    tmp["settings"]["hides"]["miscs"] = rs_hide_miscs;
    tmp["settings"]["hides"]["assists"] = rs_hide_assists;
    tmp["settings"]["hides"]["goals"] = rs_hide_goals;
    tmp["settings"]["hides"]["saves"] = rs_hide_saves;
    tmp["settings"]["hides"]["dropshot"] = rs_hide_dropshot;

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

    /// Shots
    tmp["always"]["Shot"] = always.Shot;
    tmp["always"]["CenterBall"] = always.CenterBall;
    tmp["always"]["ClearBall"] = always.ClearBall;
    tmp["always"]["FirstTouch"] = always.FirstTouch;
    tmp["always"]["ShotOnGoal"] = always.ShotOnGoal;
    tmp["always"]["BicycleHit"] = always.BicycleHit;
    tmp["always"]["TeamShot"] = always.TeamShot;
    tmp["always"]["TeamCenterBall"] = always.TeamCenterBall;
    tmp["always"]["TeamClearBall"] = always.TeamClearBall;
    tmp["always"]["TeamFirstTouch"] = always.TeamFirstTouch;
    tmp["always"]["TeamShotOnGoal"] = always.TeamShotOnGoal;
    tmp["always"]["TeamBicycleHit"] = always.TeamBicycleHit;
    tmp["always"]["TotalShot"] = always.TotalShot;
    tmp["always"]["TotalCenterBall"] = always.TotalCenterBall;
    tmp["always"]["TotalClearBall"] = always.TotalClearBall;
    tmp["always"]["TotalFirstTouch"] = always.TotalFirstTouch;
    tmp["always"]["TotalShotOnGoal"] = always.TotalShotOnGoal;
    tmp["always"]["TotalBicycleHit"] = always.TotalBicycleHit;

    tmp["always"]["ShotCumul"] = always.ShotCumul;
    tmp["always"]["CenterBallCumul"] = always.CenterBallCumul;
    tmp["always"]["ClearBallCumul"] = always.ClearBallCumul;
    tmp["always"]["FirstTouchCumul"] = always.FirstTouchCumul;
    tmp["always"]["ShotOnGoalCumul"] = always.ShotOnGoalCumul;
    tmp["always"]["BicycleHitCumul"] = always.BicycleHitCumul;
    tmp["always"]["TeamShotCumul"] = always.TeamShotCumul;
    tmp["always"]["TeamCenterBallCumul"] = always.TeamCenterBallCumul;
    tmp["always"]["TeamClearBallCumul"] = always.TeamClearBallCumul;
    tmp["always"]["TeamFirstTouchCumul"] = always.TeamFirstTouchCumul;
    tmp["always"]["TeamShotOnGoalCumul"] = always.TeamShotOnGoalCumul;
    tmp["always"]["TeamBicycleHitCumul"] = always.TeamBicycleHitCumul;
    tmp["always"]["TotalShotCumul"] = always.TotalShotCumul;
    tmp["always"]["TotalCenterBallCumul"] = always.TotalCenterBallCumul;
    tmp["always"]["TotalClearBallCumul"] = always.TotalClearBallCumul;
    tmp["always"]["TotalFirstTouchCumul"] = always.TotalFirstTouchCumul;
    tmp["always"]["TotalShotOnGoalCumul"] = always.TotalShotOnGoalCumul;
    tmp["always"]["TotalBicycleHitCumul"] = always.TotalBicycleHitCumul;

    /// Miscs
    tmp["always"]["HatTrick"] = always.HatTrick;
    tmp["always"]["LowFive"] = always.LowFive;
    tmp["always"]["HighFive"] = always.HighFive;
    tmp["always"]["MVP"] = always.MVP;
    tmp["always"]["TeamHatTrick"] = always.TeamHatTrick;
    tmp["always"]["TeamLowFive"] = always.TeamLowFive;
    tmp["always"]["TeamHighFive"] = always.TeamHighFive;
    tmp["always"]["TeamMVP"] = always.TeamMVP;
    tmp["always"]["TotalHatTrick"] = always.TotalHatTrick;
    tmp["always"]["TotalLowFive"] = always.TotalLowFive;
    tmp["always"]["TotalHighFive"] = always.TotalHighFive;
    tmp["always"]["TotalMVP"] = always.TotalMVP;

    tmp["always"]["HatTrickCumul"] = always.HatTrickCumul;
    tmp["always"]["LowFiveCumul"] = always.LowFiveCumul;
    tmp["always"]["HighFiveCumul"] = always.HighFiveCumul;
    tmp["always"]["MVPCumul"] = always.MVPCumul;
    tmp["always"]["TeamHatTrickCumul"] = always.TeamHatTrickCumul;
    tmp["always"]["TeamLowFiveCumul"] = always.TeamLowFiveCumul;
    tmp["always"]["TeamHighFiveCumul"] = always.TeamHighFiveCumul;
    tmp["always"]["TeamMVPCumul"] = always.TeamMVPCumul;
    tmp["always"]["TotalHatTrickCumul"] = always.TotalHatTrickCumul;
    tmp["always"]["TotalLowFiveCumul"] = always.TotalLowFiveCumul;
    tmp["always"]["TotalHighFiveCumul"] = always.TotalHighFiveCumul;
    tmp["always"]["TotalMVPCumul"] = always.TotalMVPCumul;

    /// Assists
    tmp["always"]["Assist"] = always.Assist;
    tmp["always"]["Playmaker"] = always.Playmaker;
    tmp["always"]["TeamAssist"] = always.TeamAssist;
    tmp["always"]["TeamPlaymaker"] = always.TeamPlaymaker;
    tmp["always"]["TotalAssist"] = always.TotalAssist;
    tmp["always"]["TotalPlaymaker"] = always.TotalPlaymaker;

    tmp["always"]["AssistCumul"] = always.AssistCumul;
    tmp["always"]["PlaymakerCumul"] = always.PlaymakerCumul;
    tmp["always"]["TeamAssistCumul"] = always.TeamAssistCumul;
    tmp["always"]["TeamPlaymakerCumul"] = always.TeamPlaymakerCumul;
    tmp["always"]["TotalAssistCumul"] = always.TotalAssistCumul;
    tmp["always"]["TotalPlaymakerCumul"] = always.TotalPlaymakerCumul;

    /// Goals
    tmp["always"]["Goal"] = always.Goal;
    tmp["always"]["AerialGoal"] = always.AerialGoal;
    tmp["always"]["BackwardsGoal"] = always.BackwardsGoal;
    tmp["always"]["BicycleGoal"] = always.BicycleGoal;
    tmp["always"]["LongGoal"] = always.LongGoal;
    tmp["always"]["TurtleGoal"] = always.TurtleGoal;
    tmp["always"]["OvertimeGoal"] = always.OvertimeGoal;
    tmp["always"]["SwishGoal"] = always.SwishGoal;
    tmp["always"]["TeamGoal"] = always.TeamGoal;
    tmp["always"]["TeamAerialGoal"] = always.TeamAerialGoal;
    tmp["always"]["TeamBackwardsGoal"] = always.TeamBackwardsGoal;
    tmp["always"]["TeamBicycleGoal"] = always.TeamBicycleGoal;
    tmp["always"]["TeamLongGoal"] = always.TeamLongGoal;
    tmp["always"]["TeamTurtleGoal"] = always.TeamTurtleGoal;
    tmp["always"]["TeamOvertimeGoal"] = always.TeamOvertimeGoal;
    tmp["always"]["TeamSwishGoal"] = always.TeamSwishGoal;
    tmp["always"]["TotalGoal"] = always.TotalGoal;
    tmp["always"]["TotalAerialGoal"] = always.TotalAerialGoal;
    tmp["always"]["TotalBackwardsGoal"] = always.TotalBackwardsGoal;
    tmp["always"]["TotalBicycleGoal"] = always.TotalBicycleGoal;
    tmp["always"]["TotalLongGoal"] = always.TotalLongGoal;
    tmp["always"]["TotalTurtleGoal"] = always.TotalTurtleGoal;
    tmp["always"]["TotalOvertimeGoal"] = always.TotalOvertimeGoal;
    tmp["always"]["TotalSwishGoal"] = always.TotalSwishGoal;

    tmp["always"]["GoalCumul"] = always.GoalCumul;
    tmp["always"]["AerialGoalCumul"] = always.AerialGoalCumul;
    tmp["always"]["BackwardsGoalCumul"] = always.BackwardsGoalCumul;
    tmp["always"]["BicycleGoalCumul"] = always.BicycleGoalCumul;
    tmp["always"]["LongGoalCumul"] = always.LongGoalCumul;
    tmp["always"]["TurtleGoalCumul"] = always.TurtleGoalCumul;
    tmp["always"]["OvertimeGoalCumul"] = always.OvertimeGoalCumul;
    tmp["always"]["SwishGoalCumul"] = always.SwishGoalCumul;
    tmp["always"]["TeamGoalCumul"] = always.TeamGoalCumul;
    tmp["always"]["TeamAerialGoalCumul"] = always.TeamAerialGoalCumul;
    tmp["always"]["TeamBackwardsGoalCumul"] = always.TeamBackwardsGoalCumul;
    tmp["always"]["TeamBicycleGoalCumul"] = always.TeamBicycleGoalCumul;
    tmp["always"]["TeamLongGoalCumul"] = always.TeamLongGoalCumul;
    tmp["always"]["TeamTurtleGoalCumul"] = always.TeamTurtleGoalCumul;
    tmp["always"]["TeamOvertimeGoalCumul"] = always.TeamOvertimeGoalCumul;
    tmp["always"]["TeamSwishGoalCumul"] = always.TeamSwishGoalCumul;
    tmp["always"]["TotalGoalCumul"] = always.TotalGoalCumul;
    tmp["always"]["TotalAerialGoalCumul"] = always.TotalAerialGoalCumul;
    tmp["always"]["TotalBackwardsGoalCumul"] = always.TotalBackwardsGoalCumul;
    tmp["always"]["TotalBicycleGoalCumul"] = always.TotalBicycleGoalCumul;
    tmp["always"]["TotalLongGoalCumul"] = always.TotalLongGoalCumul;
    tmp["always"]["TotalTurtleGoalCumul"] = always.TotalTurtleGoalCumul;
    tmp["always"]["TotalOvertimeGoalCumul"] = always.TotalOvertimeGoalCumul;
    tmp["always"]["TotalSwishGoalCumul"] = always.TotalSwishGoalCumul;

    /// Saves
    tmp["always"]["Save"] = always.Save;
    tmp["always"]["EpicSave"] = always.EpicSave;
    tmp["always"]["Savior"] = always.Savior;
    tmp["always"]["TeamSave"] = always.TeamSave;
    tmp["always"]["TeamEpicSave"] = always.TeamEpicSave;
    tmp["always"]["TeamSavior"] = always.TeamSavior;
    tmp["always"]["TotalSave"] = always.TotalSave;
    tmp["always"]["TotalEpicSave"] = always.TotalEpicSave;
    tmp["always"]["TotalSavior"] = always.TotalSavior;

    tmp["always"]["SaveCumul"] = always.SaveCumul;
    tmp["always"]["EpicSaveCumul"] = always.EpicSaveCumul;
    tmp["always"]["SaviorCumul"] = always.SaviorCumul;
    tmp["always"]["TeamSaveCumul"] = always.TeamSaveCumul;
    tmp["always"]["TeamEpicSaveCumul"] = always.TeamEpicSaveCumul;
    tmp["always"]["TeamSaviorCumul"] = always.TeamSaviorCumul;
    tmp["always"]["TotalSaveCumul"] = always.TotalSaveCumul;
    tmp["always"]["TotalEpicSaveCumul"] = always.TotalEpicSaveCumul;
    tmp["always"]["TotalSaviorCumul"] = always.TotalSaviorCumul;

    /// Dropshot
    tmp["always"]["Damage"] = always.Damage;
    tmp["always"]["UltraDamage"] = always.UltraDamage;
    tmp["always"]["TeamDamage"] = always.TeamDamage;
    tmp["always"]["TeamUltraDamage"] = always.TeamUltraDamage;
    tmp["always"]["TotalDamage"] = always.TotalDamage;
    tmp["always"]["TotalUltraDamage"] = always.TotalUltraDamage;

    tmp["always"]["DamageCumul"] = always.DamageCumul;
    tmp["always"]["UltraDamageCumul"] = always.UltraDamageCumul;
    tmp["always"]["TeamDamageCumul"] = always.TeamDamageCumul;
    tmp["always"]["TeamUltraDamageCumul"] = always.TeamUltraDamageCumul;
    tmp["always"]["TotalDamageCumul"] = always.TotalDamageCumul;
    tmp["always"]["TotalUltraDamageCumul"] = always.TotalUltraDamageCumul;

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

        /// Shots
        tmp["always_gm"][i]["Shot"] = always_gm[i].Shot;
        tmp["always_gm"][i]["CenterBall"] = always_gm[i].CenterBall;
        tmp["always_gm"][i]["ClearBall"] = always_gm[i].ClearBall;
        tmp["always_gm"][i]["FirstTouch"] = always_gm[i].FirstTouch;
        tmp["always_gm"][i]["ShotOnGoal"] = always_gm[i].ShotOnGoal;
        tmp["always_gm"][i]["BicycleHit"] = always_gm[i].BicycleHit;
        tmp["always_gm"][i]["TeamShot"] = always_gm[i].TeamShot;
        tmp["always_gm"][i]["TeamCenterBall"] = always_gm[i].TeamCenterBall;
        tmp["always_gm"][i]["TeamClearBall"] = always_gm[i].TeamClearBall;
        tmp["always_gm"][i]["TeamFirstTouch"] = always_gm[i].TeamFirstTouch;
        tmp["always_gm"][i]["TeamShotOnGoal"] = always_gm[i].TeamShotOnGoal;
        tmp["always_gm"][i]["TeamBicycleHit"] = always_gm[i].TeamBicycleHit;
        tmp["always_gm"][i]["TotalShot"] = always_gm[i].TotalShot;
        tmp["always_gm"][i]["TotalCenterBall"] = always_gm[i].TotalCenterBall;
        tmp["always_gm"][i]["TotalClearBall"] = always_gm[i].TotalClearBall;
        tmp["always_gm"][i]["TotalFirstTouch"] = always_gm[i].TotalFirstTouch;
        tmp["always_gm"][i]["TotalShotOnGoal"] = always_gm[i].TotalShotOnGoal;
        tmp["always_gm"][i]["TotalBicycleHit"] = always_gm[i].TotalBicycleHit;

        tmp["always_gm"][i]["ShotCumul"] = always_gm[i].ShotCumul;
        tmp["always_gm"][i]["CenterBallCumul"] = always_gm[i].CenterBallCumul;
        tmp["always_gm"][i]["ClearBallCumul"] = always_gm[i].ClearBallCumul;
        tmp["always_gm"][i]["FirstTouchCumul"] = always_gm[i].FirstTouchCumul;
        tmp["always_gm"][i]["ShotOnGoalCumul"] = always_gm[i].ShotOnGoalCumul;
        tmp["always_gm"][i]["BicycleHitCumul"] = always_gm[i].BicycleHitCumul;
        tmp["always_gm"][i]["TeamShotCumul"] = always_gm[i].TeamShotCumul;
        tmp["always_gm"][i]["TeamCenterBallCumul"] = always_gm[i].TeamCenterBallCumul;
        tmp["always_gm"][i]["TeamClearBallCumul"] = always_gm[i].TeamClearBallCumul;
        tmp["always_gm"][i]["TeamFirstTouchCumul"] = always_gm[i].TeamFirstTouchCumul;
        tmp["always_gm"][i]["TeamShotOnGoalCumul"] = always_gm[i].TeamShotOnGoalCumul;
        tmp["always_gm"][i]["TeamBicycleHitCumul"] = always_gm[i].TeamBicycleHitCumul;
        tmp["always_gm"][i]["TotalShotCumul"] = always_gm[i].TotalShotCumul;
        tmp["always_gm"][i]["TotalCenterBallCumul"] = always_gm[i].TotalCenterBallCumul;
        tmp["always_gm"][i]["TotalClearBallCumul"] = always_gm[i].TotalClearBallCumul;
        tmp["always_gm"][i]["TotalFirstTouchCumul"] = always_gm[i].TotalFirstTouchCumul;
        tmp["always_gm"][i]["TotalShotOnGoalCumul"] = always_gm[i].TotalShotOnGoalCumul;
        tmp["always_gm"][i]["TotalBicycleHitCumul"] = always_gm[i].TotalBicycleHitCumul;

        /// Miscs
        tmp["always_gm"][i]["HatTrick"] = always_gm[i].HatTrick;
        tmp["always_gm"][i]["LowFive"] = always_gm[i].LowFive;
        tmp["always_gm"][i]["HighFive"] = always_gm[i].HighFive;
        tmp["always_gm"][i]["MVP"] = always_gm[i].MVP;
        tmp["always_gm"][i]["TeamHatTrick"] = always_gm[i].TeamHatTrick;
        tmp["always_gm"][i]["TeamLowFive"] = always_gm[i].TeamLowFive;
        tmp["always_gm"][i]["TeamHighFive"] = always_gm[i].TeamHighFive;
        tmp["always_gm"][i]["TeamMVP"] = always_gm[i].TeamMVP;
        tmp["always_gm"][i]["TotalHatTrick"] = always_gm[i].TotalHatTrick;
        tmp["always_gm"][i]["TotalLowFive"] = always_gm[i].TotalLowFive;
        tmp["always_gm"][i]["TotalHighFive"] = always_gm[i].TotalHighFive;
        tmp["always_gm"][i]["TotalMVP"] = always_gm[i].TotalMVP;

        tmp["always_gm"][i]["HatTrickCumul"] = always_gm[i].HatTrickCumul;
        tmp["always_gm"][i]["LowFiveCumul"] = always_gm[i].LowFiveCumul;
        tmp["always_gm"][i]["HighFiveCumul"] = always_gm[i].HighFiveCumul;
        tmp["always_gm"][i]["MVPCumul"] = always_gm[i].MVPCumul;
        tmp["always_gm"][i]["TeamHatTrickCumul"] = always_gm[i].TeamHatTrickCumul;
        tmp["always_gm"][i]["TeamLowFiveCumul"] = always_gm[i].TeamLowFiveCumul;
        tmp["always_gm"][i]["TeamHighFiveCumul"] = always_gm[i].TeamHighFiveCumul;
        tmp["always_gm"][i]["TeamMVPCumul"] = always_gm[i].TeamMVPCumul;
        tmp["always_gm"][i]["TotalHatTrickCumul"] = always_gm[i].TotalHatTrickCumul;
        tmp["always_gm"][i]["TotalLowFiveCumul"] = always_gm[i].TotalLowFiveCumul;
        tmp["always_gm"][i]["TotalHighFiveCumul"] = always_gm[i].TotalHighFiveCumul;
        tmp["always_gm"][i]["TotalMVPCumul"] = always_gm[i].TotalMVPCumul;

        /// Assists
        tmp["always_gm"][i]["Assist"] = always_gm[i].Assist;
        tmp["always_gm"][i]["Playmaker"] = always_gm[i].Playmaker;
        tmp["always_gm"][i]["TeamAssist"] = always_gm[i].TeamAssist;
        tmp["always_gm"][i]["TeamPlaymaker"] = always_gm[i].TeamPlaymaker;
        tmp["always_gm"][i]["TotalAssist"] = always_gm[i].TotalAssist;
        tmp["always_gm"][i]["TotalPlaymaker"] = always_gm[i].TotalPlaymaker;

        tmp["always_gm"][i]["AssistCumul"] = always_gm[i].AssistCumul;
        tmp["always_gm"][i]["PlaymakerCumul"] = always_gm[i].PlaymakerCumul;
        tmp["always_gm"][i]["TeamAssistCumul"] = always_gm[i].TeamAssistCumul;
        tmp["always_gm"][i]["TeamPlaymakerCumul"] = always_gm[i].TeamPlaymakerCumul;
        tmp["always_gm"][i]["TotalAssistCumul"] = always_gm[i].TotalAssistCumul;
        tmp["always_gm"][i]["TotalPlaymakerCumul"] = always_gm[i].TotalPlaymakerCumul;

        /// Goals
        tmp["always_gm"][i]["Goal"] = always_gm[i].Goal;
        tmp["always_gm"][i]["AerialGoal"] = always_gm[i].AerialGoal;
        tmp["always_gm"][i]["BackwardsGoal"] = always_gm[i].BackwardsGoal;
        tmp["always_gm"][i]["BicycleGoal"] = always_gm[i].BicycleGoal;
        tmp["always_gm"][i]["LongGoal"] = always_gm[i].LongGoal;
        tmp["always_gm"][i]["TurtleGoal"] = always_gm[i].TurtleGoal;
        tmp["always_gm"][i]["OvertimeGoal"] = always_gm[i].OvertimeGoal;
        tmp["always_gm"][i]["SwishGoal"] = always_gm[i].SwishGoal;
        tmp["always_gm"][i]["TeamGoal"] = always_gm[i].TeamGoal;
        tmp["always_gm"][i]["TeamAerialGoal"] = always_gm[i].TeamAerialGoal;
        tmp["always_gm"][i]["TeamBackwardsGoal"] = always_gm[i].TeamBackwardsGoal;
        tmp["always_gm"][i]["TeamBicycleGoal"] = always_gm[i].TeamBicycleGoal;
        tmp["always_gm"][i]["TeamLongGoal"] = always_gm[i].TeamLongGoal;
        tmp["always_gm"][i]["TeamTurtleGoal"] = always_gm[i].TeamTurtleGoal;
        tmp["always_gm"][i]["TeamOvertimeGoal"] = always_gm[i].TeamOvertimeGoal;
        tmp["always_gm"][i]["TeamSwishGoal"] = always_gm[i].TeamSwishGoal;
        tmp["always_gm"][i]["TotalGoal"] = always_gm[i].TotalGoal;
        tmp["always_gm"][i]["TotalAerialGoal"] = always_gm[i].TotalAerialGoal;
        tmp["always_gm"][i]["TotalBackwardsGoal"] = always_gm[i].TotalBackwardsGoal;
        tmp["always_gm"][i]["TotalBicycleGoal"] = always_gm[i].TotalBicycleGoal;
        tmp["always_gm"][i]["TotalLongGoal"] = always_gm[i].TotalLongGoal;
        tmp["always_gm"][i]["TotalTurtleGoal"] = always_gm[i].TotalTurtleGoal;
        tmp["always_gm"][i]["TotalOvertimeGoal"] = always_gm[i].TotalOvertimeGoal;
        tmp["always_gm"][i]["TotalSwishGoal"] = always_gm[i].TotalSwishGoal;

        tmp["always_gm"][i]["GoalCumul"] = always_gm[i].GoalCumul;
        tmp["always_gm"][i]["AerialGoalCumul"] = always_gm[i].AerialGoalCumul;
        tmp["always_gm"][i]["BackwardsGoalCumul"] = always_gm[i].BackwardsGoalCumul;
        tmp["always_gm"][i]["BicycleGoalCumul"] = always_gm[i].BicycleGoalCumul;
        tmp["always_gm"][i]["LongGoalCumul"] = always_gm[i].LongGoalCumul;
        tmp["always_gm"][i]["TurtleGoalCumul"] = always_gm[i].TurtleGoalCumul;
        tmp["always_gm"][i]["OvertimeGoalCumul"] = always_gm[i].OvertimeGoalCumul;
        tmp["always_gm"][i]["SwishGoalCumul"] = always_gm[i].SwishGoalCumul;
        tmp["always_gm"][i]["TeamGoalCumul"] = always_gm[i].TeamGoalCumul;
        tmp["always_gm"][i]["TeamAerialGoalCumul"] = always_gm[i].TeamAerialGoalCumul;
        tmp["always_gm"][i]["TeamBackwardsGoalCumul"] = always_gm[i].TeamBackwardsGoalCumul;
        tmp["always_gm"][i]["TeamBicycleGoalCumul"] = always_gm[i].TeamBicycleGoalCumul;
        tmp["always_gm"][i]["TeamLongGoalCumul"] = always_gm[i].TeamLongGoalCumul;
        tmp["always_gm"][i]["TeamTurtleGoalCumul"] = always_gm[i].TeamTurtleGoalCumul;
        tmp["always_gm"][i]["TeamOvertimeGoalCumul"] = always_gm[i].TeamOvertimeGoalCumul;
        tmp["always_gm"][i]["TeamSwishGoalCumul"] = always_gm[i].TeamSwishGoalCumul;
        tmp["always_gm"][i]["TotalGoalCumul"] = always_gm[i].TotalGoalCumul;
        tmp["always_gm"][i]["TotalAerialGoalCumul"] = always_gm[i].TotalAerialGoalCumul;
        tmp["always_gm"][i]["TotalBackwardsGoalCumul"] = always_gm[i].TotalBackwardsGoalCumul;
        tmp["always_gm"][i]["TotalBicycleGoalCumul"] = always_gm[i].TotalBicycleGoalCumul;
        tmp["always_gm"][i]["TotalLongGoalCumul"] = always_gm[i].TotalLongGoalCumul;
        tmp["always_gm"][i]["TotalTurtleGoalCumul"] = always_gm[i].TotalTurtleGoalCumul;
        tmp["always_gm"][i]["TotalOvertimeGoalCumul"] = always_gm[i].TotalOvertimeGoalCumul;
        tmp["always_gm"][i]["TotalSwishGoalCumul"] = always_gm[i].TotalSwishGoalCumul;

        /// Saves
        tmp["always_gm"][i]["Save"] = always_gm[i].Save;
        tmp["always_gm"][i]["EpicSave"] = always_gm[i].EpicSave;
        tmp["always_gm"][i]["Savior"] = always_gm[i].Savior;
        tmp["always_gm"][i]["TeamSave"] = always_gm[i].TeamSave;
        tmp["always_gm"][i]["TeamEpicSave"] = always_gm[i].TeamEpicSave;
        tmp["always_gm"][i]["TeamSavior"] = always_gm[i].TeamSavior;
        tmp["always_gm"][i]["TotalSave"] = always_gm[i].TotalSave;
        tmp["always_gm"][i]["TotalEpicSave"] = always_gm[i].TotalEpicSave;
        tmp["always_gm"][i]["TotalSavior"] = always_gm[i].TotalSavior;

        tmp["always_gm"][i]["SaveCumul"] = always_gm[i].SaveCumul;
        tmp["always_gm"][i]["EpicSaveCumul"] = always_gm[i].EpicSaveCumul;
        tmp["always_gm"][i]["SaviorCumul"] = always_gm[i].SaviorCumul;
        tmp["always_gm"][i]["TeamSaveCumul"] = always_gm[i].TeamSaveCumul;
        tmp["always_gm"][i]["TeamEpicSaveCumul"] = always_gm[i].TeamEpicSaveCumul;
        tmp["always_gm"][i]["TeamSaviorCumul"] = always_gm[i].TeamSaviorCumul;
        tmp["always_gm"][i]["TotalSaveCumul"] = always_gm[i].TotalSaveCumul;
        tmp["always_gm"][i]["TotalEpicSaveCumul"] = always_gm[i].TotalEpicSaveCumul;
        tmp["always_gm"][i]["TotalSaviorCumul"] = always_gm[i].TotalSaviorCumul;

        /// Dropshot
        tmp["always_gm"][i]["Damage"] = always_gm[i].Damage;
        tmp["always_gm"][i]["UltraDamage"] = always_gm[i].UltraDamage;
        tmp["always_gm"][i]["TeamDamage"] = always_gm[i].TeamDamage;
        tmp["always_gm"][i]["TeamUltraDamage"] = always_gm[i].TeamUltraDamage;
        tmp["always_gm"][i]["TotalDamage"] = always_gm[i].TotalDamage;
        tmp["always_gm"][i]["TotalUltraDamage"] = always_gm[i].TotalUltraDamage;

        tmp["always_gm"][i]["DamageCumul"] = always_gm[i].DamageCumul;
        tmp["always_gm"][i]["UltraDamageCumul"] = always_gm[i].UltraDamageCumul;
        tmp["always_gm"][i]["TeamDamageCumul"] = always_gm[i].TeamDamageCumul;
        tmp["always_gm"][i]["TeamUltraDamageCumul"] = always_gm[i].TeamUltraDamageCumul;
        tmp["always_gm"][i]["TotalDamageCumul"] = always_gm[i].TotalDamageCumul;
        tmp["always_gm"][i]["TotalUltraDamageCumul"] = always_gm[i].TotalUltraDamageCumul;
    }

    WriteInFile("data/rocketstats.json", tmp.dump(2), true); // Save plugin settings in JSON format

    cvarManager->log("===== !WriteConfig =====");
}
