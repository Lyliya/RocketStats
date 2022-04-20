#include "../RocketStats.h"

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
            tmp = (number ? tmp.substr(0, (tmp.size() - (stmp.size() + 1))) : t_current().rank);
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
            tmp = (number ? tmp.substr(0, (tmp.size() - (stmp.size() + 1))) : t_current().division);
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

std::string RocketStats::VarDemolitions(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_demo ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().demo)));

    if (write && (force || (rs_in_file && rs_file_demo)))
        WriteInFile("RocketStats_Demolitions.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDemolitionsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_demom ? theme_hide_value : (default_value ? "0" : std::to_string(current.demo)));

    if (write && (force || (rs_in_file && rs_file_demom)))
        WriteInFile("RocketStats_DemolitionsMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDemolitionsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_democ ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().demoCumul)));

    if (write && (force || (rs_in_file && rs_file_democ)))
        WriteInFile("RocketStats_DemolitionsCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_death ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().death)));

    if (write && (force || (rs_in_file && rs_file_death)))
        WriteInFile("RocketStats_Death.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_deathm ? theme_hide_value : (default_value ? "0" : std::to_string(current.death)));

    if (write && (force || (rs_in_file && rs_file_deathm)))
        WriteInFile("RocketStats_DeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_deathc ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().deathCumul)));

    if (write && (force || (rs_in_file && rs_file_deathc)))
        WriteInFile("RocketStats_DeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarBoost(bool write, bool force, bool default_value, bool enabled)
{
    std::string tmp = (default_value ? "-1" : (enabled ? "1" : "0"));

    if (write && (force || (rs_in_file && rs_file_boost)))
        WriteInFile("RocketStats_BoostState.txt", tmp);

    return tmp;
}