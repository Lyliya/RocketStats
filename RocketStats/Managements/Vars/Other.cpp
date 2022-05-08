#include "../RocketStats.h"

void RocketStats::ReadOther(Stats& stat, json& config)
{
    if (config["Games"].is_number_unsigned())
        stat.games = int(config["Games"]);
    if (config["MMRCumulChange"].is_number())
        stat.MMRCumulChange = float(config["MMRCumulChange"]);
    if (config["Win"].is_number_unsigned())
        stat.win = int(config["Win"]);
    if (config["Loss"].is_number_unsigned())
        stat.loss = int(config["Loss"]);
    if (config["Streak"].is_number_unsigned() || config["Streak"].is_number_integer())
        stat.streak = int(config["Streak"]);
}

void RocketStats::WriteOther(Stats& stat, json& config)
{
    config["Games"] = stat.games;
    config["MMRCumulChange"] = stat.MMRCumulChange;
    config["Win"] = stat.win;
    config["Loss"] = stat.loss;
    config["Streak"] = stat.streak;
}

void RocketStats::ReplaceOther(std::map<std::string, std::string>& vars)
{
    // Creation of the different variables used in Text elements
    int number = 0;

    /// Base
    vars["Games"] = VarGames();
    vars["GameMode"] = VarGameMode();
    vars["Rank"] = VarRank(false, false, false, &number);
    vars["RankName"] = SubVarRankName(theme_vars["Rank"], number);
    vars["RankNumber"] = SubVarRankNumber(theme_vars["Rank"], number);
    vars["Div"] = VarDiv(false, false, false, &number);
    vars["DivName"] = SubVarDivName(theme_vars["Div"], number);
    vars["DivNumber"] = SubVarDivNumber(theme_vars["Div"], number);
    vars["MMR"] = VarMMR();
    vars["MMRChange"] = VarMMRChange();
    vars["MMRCumulChange"] = VarMMRCumulChange();
    vars["Win"] = VarWin();
    vars["Loss"] = VarLoss();
    vars["Streak"] = VarStreak();
    vars["WinRatio"] = VarWinRatio();
    vars["WinPercentage"] = VarWinPercentage();
    vars["ScorePlayer"] = VarScorePlayer();
    vars["ScoreOpposite"] = VarScoreOpposite();

    // Replace underscores with spaces
    Utils::ReplaceAll(vars["Rank"], "_", " ");

    // Replaces the MMR with another MMR
    std::string mmr = vars["MMR"];
    std::string mmrc = vars["MMRChange"];
    std::string mmrcc = vars["MMRCumulChange"];

    if (rs_replace_mmr)
        vars["MMR"] = mmrc;
    else if (rs_replace_mmr_cc)
        vars["MMR"] = mmrcc;
    if (rs_replace_mmrc)
        vars["MMRChange"] = mmr;
    else if (rs_replace_mmrc_cc)
        vars["MMRChange"] = mmrcc;
    if (rs_replace_mmrcc)
        vars["MMRCumulChange"] = mmr;
    else if (rs_replace_mmrcc_c)
        vars["MMRCumulChange"] = mmrc;
}

void RocketStats::SessionOther(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.games += stats[index].games;
        stat.MMRCumulChange += stats[index].MMRChange;
        stat.win += stats[index].win;
        stat.loss += stats[index].loss;
    }
    else
    {
        session.games = stat.games;
        session.myMMR = stats[current.playlist].myMMR;
        session.MMRChange = stats[current.playlist].MMRChange;
        session.win = stat.win;
        session.loss = stat.loss;
    }
}

#pragma region Base
std::string RocketStats::VarGames(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_games ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().games)));

    if (write && (force || (rs_in_file && rs_file_games)))
        WriteInFile("RocketStats_Games.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGameMode(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_gm ? theme_hide_value : (default_value ? "" : GetPlaylistName(current.playlist)));

    if (write && (force || (rs_in_file && rs_file_gm)))
        WriteInFile("RocketStats_GameMode.txt", tmp);

    return tmp;
}

std::string RocketStats::VarRank(bool write, bool force, bool default_value, int* number)
{
    std::string tmp = theme_hide_value;
    int tmp_number = (rs_preview_rank ? current.preview_rank_number : current.rank_number);
    if (!rs_hide_rank)
    {
        if (!default_value)
            tmp = AddRoman((rs_preview_rank ? current.preview_rank : current.rank), tmp_number);
        else
            tmp = t_current().rank;
    }

    if (write && (force || (rs_in_file && rs_file_rank && tmp != last_rank)))
    {
        last_rank = tmp;

        WriteInFile("RocketStats_Rank.txt", tmp);
        WriteInFile("RocketStats_RankName.txt", SubVarRankName(tmp, tmp_number));
        WriteInFile("RocketStats_RankNumber.txt", SubVarRankNumber(tmp, tmp_number));
    }

    if (number != nullptr)
        *number = tmp_number;

    return tmp;
}

std::string RocketStats::SubVarRankName(std::string value, int number, bool default_value)
{
    std::string tmp = theme_hide_value;
    if (!rs_hide_rank)
    {
        if (!default_value)
        {
            std::string stmp = (rs_roman_numbers ? GetRoman(number) : std::to_string(number));
            tmp = (number ? value.substr(0, (value.size() - (stmp.size() + 1))) : t_current().rank);
        }
        else
            tmp = t_current().rank;
    }

    return tmp;
}

std::string RocketStats::SubVarRankNumber(std::string value, int number, bool default_value)
{
    std::string tmp = theme_hide_value;
    if (!rs_hide_rank)
        tmp = (default_value ? "0" : (rs_roman_numbers ? GetRoman(number) : std::to_string(number)));

    return tmp;
}

std::string RocketStats::VarDiv(bool write, bool force, bool default_value, int* number)
{
    std::string tmp = theme_hide_value;
    int tmp_number = (rs_preview_rank ? current.preview_division_number : current.division_number);
    if (!rs_hide_div)
    {
        if (!default_value)
            tmp = AddRoman((rs_preview_rank ? current.preview_division : current.division), tmp_number);
        else
            tmp = t_current().division;
    }

    if (write && (force || (rs_in_file && rs_file_div && tmp != last_division)))
    {
        last_division = tmp;

        WriteInFile("RocketStats_Div.txt", tmp);
        WriteInFile("RocketStats_DivName.txt", SubVarDivName(tmp, tmp_number));
        WriteInFile("RocketStats_DivNumber.txt", SubVarDivNumber(tmp, tmp_number));
    }

    if (number != nullptr)
        *number = tmp_number;

    return tmp;
}

std::string RocketStats::SubVarDivName(std::string value, int number, bool default_value)
{
    std::string tmp = theme_hide_value;
    if (!rs_hide_div)
    {
        if (!default_value)
        {
            std::string stmp = (rs_roman_numbers ? GetRoman(number) : std::to_string(number));
            tmp = (number ? value.substr(0, (value.size() - (stmp.size() + 1))) : t_current().division);
        }
        else
            tmp = t_current().division;
    }

    return tmp;
}

std::string RocketStats::SubVarDivNumber(std::string value, int number, bool default_value)
{
    std::string tmp = theme_hide_value;
    if (!rs_hide_div)
        tmp = (default_value ? "0" : (rs_roman_numbers ? GetRoman(number) : std::to_string(number)));

    return tmp;
}

std::string RocketStats::VarMMR(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_mmr ? theme_hide_value : Utils::FloatFixer((default_value ? 100.f : stats[current.playlist].myMMR), (rs_enable_float ? 2 : 0)));

    if (write && (force || (rs_in_file && rs_file_mmr)))
        WriteInFile("RocketStats_MMR.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMMRChange(bool write, bool force, bool default_value)
{
    bool positive = false;
    std::string tmp = theme_hide_value;
    if (!rs_hide_mmrc)
    {
        Stats tstats = GetStats();
        tmp = Utils::FloatFixer(tstats.MMRChange, (rs_enable_float ? 2 : 0));

        if (tstats.MMRChange > 0)
            positive = true;
    }

    if (write && (force || (rs_in_file && rs_file_mmrc)))
    {
        if (positive)
            tmp = ("+" + tmp);

        WriteInFile("RocketStats_MMRChange.txt", tmp);
    }

    return tmp;
}

std::string RocketStats::VarMMRCumulChange(bool write, bool force, bool default_value)
{
    bool positive = false;
    std::string tmp = theme_hide_value;
    if (!rs_hide_mmrcc)
    {
        Stats tstats = GetStats();
        tmp = Utils::FloatFixer(tstats.MMRCumulChange, (rs_enable_float ? 2 : 0));

        if (tstats.MMRCumulChange > 0)
            positive = true;
    }

    if (write && (force || (rs_in_file && rs_file_mmrcc)))
    {
        if (positive)
            tmp = ("+" + tmp);

        WriteInFile("RocketStats_MMRCumulChange.txt", tmp);
    }

    return tmp;
}

std::string RocketStats::VarWin(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_win ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().win)));

    if (write && (force || (rs_in_file && rs_file_win)))
        WriteInFile("RocketStats_Win.txt", tmp);

    return tmp;
}

std::string RocketStats::VarLoss(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_loss ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().loss)));

    if (write && (force || (rs_in_file && rs_file_loss)))
        WriteInFile("RocketStats_Loss.txt", tmp);

    return tmp;
}

std::string RocketStats::VarStreak(bool write, bool force, bool default_value)
{
    bool positive = false;
    std::string tmp = theme_hide_value;
    if (!rs_hide_streak)
    {
        Stats tstats = GetStats();
        tmp = std::to_string(tstats.streak);

        if (tstats.streak > 0)
            positive = true;
    }

    if (write && (force || (rs_in_file && rs_file_streak)))
    {
        if (positive)
            tmp = ("+" + tmp);

        WriteInFile("RocketStats_Streak.txt", tmp);
    }

    return tmp;
}

std::string RocketStats::VarWinRatio(bool write, bool force, bool default_value)
{
    bool positive = false;
    std::string tmp = theme_hide_value;
    if (!rs_hide_winratio)
    {
        Stats tstats = GetStats();
        tmp = std::to_string(tstats.win - tstats.loss);

        if ((tstats.win - tstats.loss) > 0)
            positive = true;
    }

    if (write && (force || (rs_in_file && rs_file_winratio)))
    {
        if (positive)
            tmp = ("+" + tmp);

        WriteInFile("RocketStats_WinRatio.txt", tmp);
    }

    return tmp;
}

std::string RocketStats::VarWinPercentage(bool write, bool force, bool default_value)
{
    std::string tmp = theme_hide_value;
    if (!rs_hide_winpercentage)
    {
        Stats tstats = GetStats();
        int total = (tstats.win + tstats.loss);

        if (total)
            tmp = Utils::FloatFixer((float(tstats.win) / float(total) * 100.f), (rs_enable_float ? 2 : 0));
        else
            tmp = "N/A";
    }

    if (write && (force || (rs_in_file && rs_file_winpercentage)))
        WriteInFile("RocketStats_WinPercentage.txt", tmp);

    return tmp;
}

std::string RocketStats::VarScorePlayer(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_score ? theme_hide_value : (default_value ? "0" : std::to_string(current.score_player)));

    if (write && (force || (rs_in_file && rs_file_score)))
        WriteInFile("RocketStats_ScorePlayer.txt", tmp);

    return tmp;
}

std::string RocketStats::VarScoreOpposite(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_score ? theme_hide_value : (default_value ? "0" : std::to_string(current.score_opposite)));

    if (write && (force || (rs_in_file && rs_file_score)))
        WriteInFile("RocketStats_ScoreOpposite.txt", tmp);

    return tmp;
}

std::string RocketStats::VarBoost(bool write, bool force, bool default_value, bool enabled)
{
    std::string tmp = (default_value ? "-1" : (enabled ? "1" : "0"));

    if (write && (force || (rs_in_file && rs_file_boost)))
        WriteInFile("RocketStats_BoostState.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Match
#pragma endregion

#pragma region Cumul
#pragma endregion