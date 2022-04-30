#include "../RocketStats.h"

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

std::string RocketStats::VarDemolitions(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_demo ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().demo)));

    if (write && (force || (rs_in_file && rs_file_demo)))
        WriteInFile("RocketStats_Demolitions.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDemolitionsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_demom ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.demo)));

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
    std::string tmp = (rs_hide_deathm ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.death)));

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
#pragma endregion

#pragma region Shots
void RocketStats::AllShots(bool force, bool default_value)
{
    AllShotsClear(force, default_value);
    AllShotsAssist(force, default_value);
    AllShotsCenter(force, default_value);
    AllShotsAerialHit(force, default_value);
    AllShotsBicycleHit(force, default_value);
    AllShotsFirstTouch(force, default_value);
    AllShotsShotOnGoal(force, default_value);
}

void RocketStats::AllShotsClear(bool force, bool default_value)
{
    VarShotsClear(true, force, default_value);
    VarShotsClearMatch(true, force, default_value);
    VarShotsClearCumul(true, force, default_value);
}

void RocketStats::AllShotsAssist(bool force, bool default_value)
{
    VarShotsAssist(true, force, default_value);
    VarShotsTeamAssist(true, force, default_value);
    VarShotsTotalAssist(true, force, default_value);

    VarShotsAssistMatch(true, force, default_value);
    VarShotsTeamAssistMatch(true, force, default_value);
    VarShotsTotalAssistMatch(true, force, default_value);

    VarShotsAssistCumul(true, force, default_value);
    VarShotsTeamAssistCumul(true, force, default_value);
    VarShotsTotalAssistCumul(true, force, default_value);
}

void RocketStats::AllShotsCenter(bool force, bool default_value)
{
    VarShotsCenter(true, force, default_value);
    VarShotsCenterMatch(true, force, default_value);
    VarShotsCenterCumul(true, force, default_value);
}

void RocketStats::AllShotsAerialHit(bool force, bool default_value)
{
    VarShotsAerialHit(true, force, default_value);
    VarShotsAerialHitMatch(true, force, default_value);
    VarShotsAerialHitCumul(true, force, default_value);
}

void RocketStats::AllShotsBicycleHit(bool force, bool default_value)
{
    VarShotsBicycleHit(true, force, default_value);
    VarShotsTeamBicycleHit(true, force, default_value);
    VarShotsTotalBicycleHit(true, force, default_value);

    VarShotsBicycleHitMatch(true, force, default_value);
    VarShotsTeamBicycleHitMatch(true, force, default_value);
    VarShotsTotalBicycleHitMatch(true, force, default_value);

    VarShotsBicycleHitCumul(true, force, default_value);
    VarShotsTeamBicycleHitCumul(true, force, default_value);
    VarShotsTotalBicycleHitCumul(true, force, default_value);
}

void RocketStats::AllShotsFirstTouch(bool force, bool default_value)
{
    VarShotsFirstTouch(true, force, default_value);
    VarShotsFirstTouchMatch(true, force, default_value);
    VarShotsFirstTouchCumul(true, force, default_value);
}

void RocketStats::AllShotsShotOnGoal(bool force, bool default_value)
{
    VarShotsShotOnGoal(true, force, default_value);
    VarShotsTeamShotOnGoal(true, force, default_value);
    VarShotsTotalShotOnGoal(true, force, default_value);

    VarShotsShotOnGoalMatch(true, force, default_value);
    VarShotsTeamShotOnGoalMatch(true, force, default_value);
    VarShotsTotalShotOnGoalMatch(true, force, default_value);

    VarShotsShotOnGoalCumul(true, force, default_value);
    VarShotsTeamShotOnGoalCumul(true, force, default_value);
    VarShotsTotalShotOnGoalCumul(true, force, default_value);
}


std::string RocketStats::VarShotsClear(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Clear)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_Clear.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Assist)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_Assist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsCenter(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Center)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_Center.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsAerialHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AerialHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_AerialHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsBicycleHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_BicycleHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsFirstTouch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FirstTouch)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_FirstTouch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsShotOnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().ShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ShotOnGoal.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTeamAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAssist)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamAssist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamBicycleHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamBicycleHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamShotOnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamShotOnGoal.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTotalAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalAssist)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalAssist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalBicycleHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalBicycleHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalShotOnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalShotOnGoal.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsClearMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Clear)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ClearMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Assist)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_AssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsCenterMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Center)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_CenterMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsAerialHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.AerialHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_AerialHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsBicycleHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BicycleHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_BicycleHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsFirstTouchMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FirstTouch)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_FirstTouchMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsShotOnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.ShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ShotOnGoalMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTeamAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamAssist)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamAssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamBicycleHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamBicycleHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamShotOnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamShotOnGoalMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTotalAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalAssist)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalAssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalBicycleHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalBicycleHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalShotOnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalShotOnGoalMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsClearCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().ClearCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ClearCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AssistCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_AssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsCenterCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().CenterCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_CenterCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsAerialHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AerialHitCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_AerialHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsBicycleHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleHitCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_BicycleHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsFirstTouchCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FirstTouchCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_FirstTouchCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsShotOnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().ShotOnGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ShotOnGoalCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTeamAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAssistCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamAssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamBicycleHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleHitCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamBicycleHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamShotOnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamShotOnGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TeamShotOnGoalCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTotalAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalAssistCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalAssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalBicycleHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleHitCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalBicycleHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalShotOnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalShotOnGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_TotalShotOnGoalCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Saves
void RocketStats::AllSaves(bool force, bool default_value)
{
    AllSavesSave(force, default_value);
    AllSavesEpicSave(force, default_value);
}

void RocketStats::AllSavesSave(bool force, bool default_value)
{
    VarSavesSave(true, force, default_value);
    VarSavesTeamSave(true, force, default_value);
    VarSavesTotalSave(true, force, default_value);

    VarSavesSaveMatch(true, force, default_value);
    VarSavesTeamSaveMatch(true, force, default_value);
    VarSavesTotalSaveMatch(true, force, default_value);

    VarSavesSaveCumul(true, force, default_value);
    VarSavesTeamSaveCumul(true, force, default_value);
    VarSavesTotalSaveCumul(true, force, default_value);
}

void RocketStats::AllSavesEpicSave(bool force, bool default_value)
{
    VarSavesEpicSave(true, force, default_value);
    VarSavesTeamEpicSave(true, force, default_value);
    VarSavesTotalEpicSave(true, force, default_value);

    VarSavesEpicSaveMatch(true, force, default_value);
    VarSavesTeamEpicSaveMatch(true, force, default_value);
    VarSavesTotalEpicSaveMatch(true, force, default_value);

    VarSavesEpicSaveCumul(true, force, default_value);
    VarSavesTeamEpicSaveCumul(true, force, default_value);
    VarSavesTotalEpicSaveCumul(true, force, default_value);
}


std::string RocketStats::VarSavesSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Save)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_Save.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().EpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSave.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTeamSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSave.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTotalSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSave.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Save)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.EpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSaveMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTeamSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSaveMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTotalSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSaveMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().EpicSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSaveCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTeamSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamEpicSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSaveCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTotalSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalEpicSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSaveCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Goals
void RocketStats::AllGoals(bool force, bool default_value)
{
    AllGoalsGoal(force, default_value);
    AllGoalsOwnGoal(force, default_value);
    AllGoalsAerialGoal(force, default_value);
    AllGoalsBackwardsGoal(force, default_value);
    AllGoalsBicycleGoal(force, default_value);
    AllGoalsLongGoal(force, default_value);
    AllGoalsTurtleGoal(force, default_value);
    AllGoalsOvertimeGoal(force, default_value);
    AllGoalsHoopsSwishGoal(force, default_value);
    AllGoalsPoolShot(force, default_value);
}

void RocketStats::AllGoalsGoal(bool force, bool default_value)
{
    VarGoalsGoal(true, force, default_value);
    VarGoalsTeamGoal(true, force, default_value);
    VarGoalsTotalGoal(true, force, default_value);

    VarGoalsGoalMatch(true, force, default_value);
    VarGoalsTeamGoalMatch(true, force, default_value);
    VarGoalsTotalGoalMatch(true, force, default_value);

    VarGoalsGoalCumul(true, force, default_value);
    VarGoalsTeamGoalCumul(true, force, default_value);
    VarGoalsTotalGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsOwnGoal(bool force, bool default_value)
{
    VarGoalsOwnGoal(true, force, default_value);
    VarGoalsOwnGoalMatch(true, force, default_value);
    VarGoalsOwnGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsAerialGoal(bool force, bool default_value)
{
    VarGoalsAerialGoal(true, force, default_value);
    VarGoalsTeamAerialGoal(true, force, default_value);
    VarGoalsTotalAerialGoal(true, force, default_value);

    VarGoalsAerialGoalMatch(true, force, default_value);
    VarGoalsTeamAerialGoalMatch(true, force, default_value);
    VarGoalsTotalAerialGoalMatch(true, force, default_value);

    VarGoalsAerialGoalCumul(true, force, default_value);
    VarGoalsTeamAerialGoalCumul(true, force, default_value);
    VarGoalsTotalAerialGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsBackwardsGoal(bool force, bool default_value)
{
    VarGoalsBackwardsGoal(true, force, default_value);
    VarGoalsTeamBackwardsGoal(true, force, default_value);
    VarGoalsTotalBackwardsGoal(true, force, default_value);

    VarGoalsBackwardsGoalMatch(true, force, default_value);
    VarGoalsTeamBackwardsGoalMatch(true, force, default_value);
    VarGoalsTotalBackwardsGoalMatch(true, force, default_value);

    VarGoalsBackwardsGoalCumul(true, force, default_value);
    VarGoalsTeamBackwardsGoalCumul(true, force, default_value);
    VarGoalsTotalBackwardsGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsBicycleGoal(bool force, bool default_value)
{
    VarGoalsBicycleGoal(true, force, default_value);
    VarGoalsTeamBicycleGoal(true, force, default_value);
    VarGoalsTotalBicycleGoal(true, force, default_value);

    VarGoalsBicycleGoalMatch(true, force, default_value);
    VarGoalsTeamBicycleGoalMatch(true, force, default_value);
    VarGoalsTotalBicycleGoalMatch(true, force, default_value);

    VarGoalsBicycleGoalCumul(true, force, default_value);
    VarGoalsTeamBicycleGoalCumul(true, force, default_value);
    VarGoalsTotalBicycleGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsLongGoal(bool force, bool default_value)
{
    VarGoalsLongGoal(true, force, default_value);
    VarGoalsTeamLongGoal(true, force, default_value);
    VarGoalsTotalLongGoal(true, force, default_value);

    VarGoalsLongGoalMatch(true, force, default_value);
    VarGoalsTeamLongGoalMatch(true, force, default_value);
    VarGoalsTotalLongGoalMatch(true, force, default_value);

    VarGoalsLongGoalCumul(true, force, default_value);
    VarGoalsTeamLongGoalCumul(true, force, default_value);
    VarGoalsTotalLongGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsTurtleGoal(bool force, bool default_value)
{
    VarGoalsTurtleGoal(true, force, default_value);
    VarGoalsTeamTurtleGoal(true, force, default_value);
    VarGoalsTotalTurtleGoal(true, force, default_value);

    VarGoalsTurtleGoalMatch(true, force, default_value);
    VarGoalsTeamTurtleGoalMatch(true, force, default_value);
    VarGoalsTotalTurtleGoalMatch(true, force, default_value);

    VarGoalsTurtleGoalCumul(true, force, default_value);
    VarGoalsTeamTurtleGoalCumul(true, force, default_value);
    VarGoalsTotalTurtleGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsOvertimeGoal(bool force, bool default_value)
{
    VarGoalsOvertimeGoal(true, force, default_value);
    VarGoalsTeamOvertimeGoal(true, force, default_value);
    VarGoalsTotalOvertimeGoal(true, force, default_value);

    VarGoalsOvertimeGoalMatch(true, force, default_value);
    VarGoalsTeamOvertimeGoalMatch(true, force, default_value);
    VarGoalsTotalOvertimeGoalMatch(true, force, default_value);

    VarGoalsOvertimeGoalCumul(true, force, default_value);
    VarGoalsTeamOvertimeGoalCumul(true, force, default_value);
    VarGoalsTotalOvertimeGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsHoopsSwishGoal(bool force, bool default_value)
{
    VarGoalsHoopsSwishGoal(true, force, default_value);
    VarGoalsTeamHoopsSwishGoal(true, force, default_value);
    VarGoalsTotalHoopsSwishGoal(true, force, default_value);

    VarGoalsHoopsSwishGoalMatch(true, force, default_value);
    VarGoalsTeamHoopsSwishGoalMatch(true, force, default_value);
    VarGoalsTotalHoopsSwishGoalMatch(true, force, default_value);

    VarGoalsHoopsSwishGoalCumul(true, force, default_value);
    VarGoalsTeamHoopsSwishGoalCumul(true, force, default_value);
    VarGoalsTotalHoopsSwishGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsPoolShot(bool force, bool default_value)
{
    VarGoalsPoolShot(true, force, default_value);
    VarGoalsTeamPoolShot(true, force, default_value);
    VarGoalsTotalPoolShot(true, force, default_value);

    VarGoalsPoolShotMatch(true, force, default_value);
    VarGoalsTeamPoolShotMatch(true, force, default_value);
    VarGoalsTotalPoolShotMatch(true, force, default_value);

    VarGoalsPoolShotCumul(true, force, default_value);
    VarGoalsTeamPoolShotCumul(true, force, default_value);
    VarGoalsTotalPoolShotCumul(true, force, default_value);
}


std::string RocketStats::VarGoalsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Goal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_Goal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOwnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().OwnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OwnGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().OvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsHoopsSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HoopsSwishGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShot.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTeamGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamHoopsSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHoopsSwishGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShot.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTotalGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalHoopsSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHoopsSwishGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShot.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Goal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_GoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOwnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.OwnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OwnGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.AerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.LongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.OvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsHoopsSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.HoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HoopsSwishGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.PoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShotMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTeamGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamHoopsSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHoopsSwishGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShotMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTotalGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalHoopsSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHoopsSwishGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShotMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().GoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_GoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOwnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().OwnGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OwnGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AerialGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BackwardsGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LongGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TurtleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().OvertimeGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsHoopsSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HoopsSwishGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HoopsSwishGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PoolShotCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShotCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTeamGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAerialGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBackwardsGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLongGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamTurtleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamOvertimeGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamHoopsSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHoopsSwishGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHoopsSwishGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPoolShotCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShotCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTotalGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalAerialGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBackwardsGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLongGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalTurtleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalOvertimeGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalHoopsSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHoopsSwishGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHoopsSwishGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPoolShotCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShotCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Dropshot
void RocketStats::AllDropshot(bool force, bool default_value)
{
    AllDropshotBreakoutDamage(force, default_value);
    AllDropshotBreakoutDamageLarge(force, default_value);
}

void RocketStats::AllDropshotBreakoutDamage(bool force, bool default_value)
{
    VarDropshotBreakoutDamage(true, force, default_value);
    VarDropshotTeamBreakoutDamage(true, force, default_value);
    VarDropshotTotalBreakoutDamage(true, force, default_value);

    VarDropshotBreakoutDamageMatch(true, force, default_value);
    VarDropshotTeamBreakoutDamageMatch(true, force, default_value);
    VarDropshotTotalBreakoutDamageMatch(true, force, default_value);

    VarDropshotBreakoutDamageCumul(true, force, default_value);
    VarDropshotTeamBreakoutDamageCumul(true, force, default_value);
    VarDropshotTotalBreakoutDamageCumul(true, force, default_value);
}

void RocketStats::AllDropshotBreakoutDamageLarge(bool force, bool default_value)
{
    VarDropshotBreakoutDamageLarge(true, force, default_value);
    VarDropshotTeamBreakoutDamageLarge(true, force, default_value);
    VarDropshotTotalBreakoutDamageLarge(true, force, default_value);

    VarDropshotBreakoutDamageLargeMatch(true, force, default_value);
    VarDropshotTeamBreakoutDamageLargeMatch(true, force, default_value);
    VarDropshotTotalBreakoutDamageLargeMatch(true, force, default_value);

    VarDropshotBreakoutDamageLargeCumul(true, force, default_value);
    VarDropshotTeamBreakoutDamageLargeCumul(true, force, default_value);
    VarDropshotTotalBreakoutDamageLargeCumul(true, force, default_value);
}


std::string RocketStats::VarDropshotBreakoutDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BreakoutDamage)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_BreakoutDamage.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotBreakoutDamageLarge(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BreakoutDamageLarge)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_BreakoutDamageLarge.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTeamBreakoutDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBreakoutDamage)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TeamBreakoutDamage.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTeamBreakoutDamageLarge(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBreakoutDamageLarge)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TeamBreakoutDamageLarge.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTotalBreakoutDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBreakoutDamage)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TotalBreakoutDamage.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTotalBreakoutDamageLarge(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBreakoutDamageLarge)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TotalBreakoutDamageLarge.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotBreakoutDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BreakoutDamage)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_BreakoutDamageMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotBreakoutDamageLargeMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BreakoutDamageLarge)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_BreakoutDamageLargeMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTeamBreakoutDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamBreakoutDamage)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TeamBreakoutDamageMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTeamBreakoutDamageLargeMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamBreakoutDamageLarge)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TeamBreakoutDamageLargeMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTotalBreakoutDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalBreakoutDamage)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TotalBreakoutDamageMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTotalBreakoutDamageLargeMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalBreakoutDamageLarge)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TotalBreakoutDamageLargeMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotBreakoutDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BreakoutDamageCumul)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_BreakoutDamageCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotBreakoutDamageLargeCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BreakoutDamageLargeCumul)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_BreakoutDamageLargeCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTeamBreakoutDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBreakoutDamageCumul)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TeamBreakoutDamageCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTeamBreakoutDamageLargeCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBreakoutDamageLargeCumul)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TeamBreakoutDamageLargeCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTotalBreakoutDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBreakoutDamageCumul)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TotalBreakoutDamageCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTotalBreakoutDamageLargeCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_dropshot ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBreakoutDamageLargeCumul)));

    if (write && (force || (rs_in_file && rs_file_dropshot)))
        WriteInFile("RocketStats_TotalBreakoutDamageLargeCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Knockout
void RocketStats::AllKnockout(bool force, bool default_value)
{
    AllKnockoutBase(force, default_value);
    AllKnockoutDeath(force, default_value);
    AllKnockoutThrown(force, default_value);
    AllKnockoutGrabbed(force, default_value);
    AllKnockoutHitTaken(force, default_value);
}

void RocketStats::AllKnockoutBase(bool force, bool default_value)
{
    VarKnockout(true, force, default_value);
    VarKnockoutTeam(true, force, default_value);
    VarKnockoutTotal(true, force, default_value);

    VarKnockoutMatch(true, force, default_value);
    VarKnockoutTeamMatch(true, force, default_value);
    VarKnockoutTotalMatch(true, force, default_value);

    VarKnockoutCumul(true, force, default_value);
    VarKnockoutTeamCumul(true, force, default_value);
    VarKnockoutTotalCumul(true, force, default_value);
}

void RocketStats::AllKnockoutDeath(bool force, bool default_value)
{
    VarKnockoutDeath(true, force, default_value);
    VarKnockoutTeamDeath(true, force, default_value);
    VarKnockoutTotalDeath(true, force, default_value);

    VarKnockoutDeathMatch(true, force, default_value);
    VarKnockoutTeamDeathMatch(true, force, default_value);
    VarKnockoutTotalDeathMatch(true, force, default_value);

    VarKnockoutDeathCumul(true, force, default_value);
    VarKnockoutTeamDeathCumul(true, force, default_value);
    VarKnockoutTotalDeathCumul(true, force, default_value);
}

void RocketStats::AllKnockoutThrown(bool force, bool default_value)
{
    VarKnockoutThrown(true, force, default_value);
    VarKnockoutThrownMatch(true, force, default_value);
    VarKnockoutThrownCumul(true, force, default_value);
}

void RocketStats::AllKnockoutGrabbed(bool force, bool default_value)
{
    VarKnockoutGrabbed(true, force, default_value);
    VarKnockoutGrabbedMatch(true, force, default_value);
    VarKnockoutGrabbedCumul(true, force, default_value);
}

void RocketStats::AllKnockoutDoubleKO(bool force, bool default_value)
{
    VarKnockoutDoubleKO(true, force, default_value);
    VarKnockoutTeamDoubleKO(true, force, default_value);
    VarKnockoutTotalDoubleKO(true, force, default_value);

    VarKnockoutDoubleKOMatch(true, force, default_value);
    VarKnockoutTeamDoubleKOMatch(true, force, default_value);
    VarKnockoutTotalDoubleKOMatch(true, force, default_value);

    VarKnockoutDoubleKOCumul(true, force, default_value);
    VarKnockoutTeamDoubleKOCumul(true, force, default_value);
    VarKnockoutTotalDoubleKOCumul(true, force, default_value);
}

void RocketStats::AllKnockoutHeavyHit(bool force, bool default_value)
{
    VarKnockoutHeavyHit(true, force, default_value);
    VarKnockoutTeamHeavyHit(true, force, default_value);
    VarKnockoutTotalHeavyHit(true, force, default_value);

    VarKnockoutHeavyHitMatch(true, force, default_value);
    VarKnockoutTeamHeavyHitMatch(true, force, default_value);
    VarKnockoutTotalHeavyHitMatch(true, force, default_value);

    VarKnockoutHeavyHitCumul(true, force, default_value);
    VarKnockoutTeamHeavyHitCumul(true, force, default_value);
    VarKnockoutTotalHeavyHitCumul(true, force, default_value);
}

void RocketStats::AllKnockoutHitTaken(bool force, bool default_value)
{
    VarKnockoutHitTaken(true, force, default_value);
    VarKnockoutHitTakenMatch(true, force, default_value);
    VarKnockoutHitTakenCumul(true, force, default_value);
}

void RocketStats::AllKnockoutLightHit(bool force, bool default_value)
{
    VarKnockoutLightHit(true, force, default_value);
    VarKnockoutLightHitMatch(true, force, default_value);
    VarKnockoutLightHitCumul(true, force, default_value);
}

void RocketStats::AllKnockoutBlockTaken(bool force, bool default_value)
{
    VarKnockoutBlockTaken(true, force, default_value);
    VarKnockoutBlockTakenMatch(true, force, default_value);
    VarKnockoutBlockTakenCumul(true, force, default_value);
}

void RocketStats::AllKnockoutHeavyBlock(bool force, bool default_value)
{
    VarKnockoutHeavyBlock(true, force, default_value);
    VarKnockoutTeamHeavyBlock(true, force, default_value);
    VarKnockoutTotalHeavyBlock(true, force, default_value);

    VarKnockoutHeavyBlockMatch(true, force, default_value);
    VarKnockoutTeamHeavyBlockMatch(true, force, default_value);
    VarKnockoutTotalHeavyBlockMatch(true, force, default_value);

    VarKnockoutHeavyBlockCumul(true, force, default_value);
    VarKnockoutTeamHeavyBlockCumul(true, force, default_value);
    VarKnockoutTotalHeavyBlockCumul(true, force, default_value);
}


std::string RocketStats::VarKnockout(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Knockout)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_Knockout.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutThrown(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutThrown)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutThrown.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutGrabbed(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutGrabbed)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutGrabbed.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDoubleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDoubleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHitTaken(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHitTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHitTaken.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutBlockTaken(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutBlockTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutBlockTaken.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyBlock(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyBlock.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeam(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeam)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeam.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDoubleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDoubleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyBlock(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyBlock.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotal)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_TotalKnockout.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDoubleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDoubleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyBlock(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyBlock.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Knockout)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutThrownMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutThrown)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutThrownMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutGrabbedMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutGrabbed)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutGrabbedMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDoubleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDoubleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHitTakenMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutHitTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHitTakenMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutBlockTakenMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutBlockTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutBlockTakenMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyBlockMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyBlockMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTeamMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeam)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDeathMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTeamDoubleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDoubleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyHitMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTeamHeavyBlockMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyBlockMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTotalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotal)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDeathMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTotalDoubleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDoubleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyHitMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTotalHeavyBlockMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyBlockMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutThrownCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutThrownCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutThrownCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutGrabbedCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutGrabbedCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutGrabbedCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDoubleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDoubleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDoubleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHitTakenCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHitTakenCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHitTakenCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutLightHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutBlockTakenCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutBlockTakenCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutBlockTakenCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyBlockCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyBlockCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyBlockCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTeamCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDoubleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDoubleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDoubleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyBlockCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyBlockCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyBlockCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTotalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDoubleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDoubleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDoubleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyBlockCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyBlockCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyBlockCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Miscs
void RocketStats::AllMiscs(bool force, bool default_value)
{
    AllMiscsHatTrick(force, default_value);
    AllMiscsLowFive(force, default_value);
    AllMiscsHighFive(force, default_value);
}

void RocketStats::AllMiscsLowFive(bool force, bool default_value)
{
    VarMiscsLowFive(true, force, default_value);
    VarMiscsTeamLowFive(true, force, default_value);
    VarMiscsTotalLowFive(true, force, default_value);

    VarMiscsLowFiveMatch(true, force, default_value);
    VarMiscsTeamLowFiveMatch(true, force, default_value);
    VarMiscsTotalLowFiveMatch(true, force, default_value);

    VarMiscsLowFiveCumul(true, force, default_value);
    VarMiscsTeamLowFiveCumul(true, force, default_value);
    VarMiscsTotalLowFiveCumul(true, force, default_value);
}

void RocketStats::AllMiscsHatTrick(bool force, bool default_value)
{
    VarMiscsHatTrick(true, force, default_value);
    VarMiscsTeamHatTrick(true, force, default_value);
    VarMiscsTotalHatTrick(true, force, default_value);

    VarMiscsHatTrickMatch(true, force, default_value);
    VarMiscsTeamHatTrickMatch(true, force, default_value);
    VarMiscsTotalHatTrickMatch(true, force, default_value);

    VarMiscsHatTrickCumul(true, force, default_value);
    VarMiscsTeamHatTrickCumul(true, force, default_value);
    VarMiscsTotalHatTrickCumul(true, force, default_value);
}

void RocketStats::AllMiscsHighFive(bool force, bool default_value)
{
    VarMiscsHighFive(true, force, default_value);
    VarMiscsTeamHighFive(true, force, default_value);
    VarMiscsTotalHighFive(true, force, default_value);

    VarMiscsHighFiveMatch(true, force, default_value);
    VarMiscsTeamHighFiveMatch(true, force, default_value);
    VarMiscsTotalHighFiveMatch(true, force, default_value);

    VarMiscsHighFiveCumul(true, force, default_value);
    VarMiscsTeamHighFiveCumul(true, force, default_value);
    VarMiscsTotalHighFiveCumul(true, force, default_value);
}


std::string RocketStats::VarMiscsLowFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LowFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_LowFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHatTrick(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HatTrick)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_HatTrick.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHighFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HighFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_HighFive.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTeamLowFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLowFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamLowFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHatTrick(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHatTrick)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamHatTrick.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHighFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHighFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamHighFive.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTotalLowFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLowFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalLowFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHatTrick(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHatTrick)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalHatTrick.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHighFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHighFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalHighFive.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsLowFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.LowFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_LowFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHatTrickMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.HatTrick)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_HatTrickMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHighFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.HighFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_HighFiveMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTeamLowFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamLowFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamLowFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHatTrickMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamHatTrick)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamHatTrickMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHighFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamHighFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamHighFiveMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTotalLowFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalLowFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalLowFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHatTrickMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalHatTrick)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalHatTrickMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHighFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalHighFive)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalHighFiveMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsLowFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LowFiveCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_LowFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHatTrickCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HatTrickCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_HatTrickCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHighFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HighFiveCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_HighFiveCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTeamLowFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLowFiveCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamLowFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHatTrickCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHatTrickCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamHatTrickCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHighFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHighFiveCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamHighFiveCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTotalLowFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLowFiveCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalLowFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHatTrickCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHatTrickCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalHatTrickCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHighFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHighFiveCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalHighFiveCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Certifications
void RocketStats::AllCertifications(bool force, bool default_value)
{
    AllCertificationsMVP(force, default_value);
    AllCertificationsSavior(force, default_value);
    AllCertificationsPlaymaker(force, default_value);
}

void RocketStats::AllCertificationsMVP(bool force, bool default_value)
{
    VarCertificationsMVP(true, force, default_value);
    VarCertificationsTeamMVP(true, force, default_value);
    VarCertificationsTotalMVP(true, force, default_value);

    VarCertificationsMVPMatch(true, force, default_value);
    VarCertificationsTeamMVPMatch(true, force, default_value);
    VarCertificationsTotalMVPMatch(true, force, default_value);

    VarCertificationsMVPCumul(true, force, default_value);
    VarCertificationsTeamMVPCumul(true, force, default_value);
    VarCertificationsTotalMVPCumul(true, force, default_value);
}

void RocketStats::AllCertificationsSavior(bool force, bool default_value)
{
    VarCertificationsSavior(true, force, default_value);
    VarCertificationsTeamSavior(true, force, default_value);
    VarCertificationsTotalSavior(true, force, default_value);

    VarCertificationsSaviorMatch(true, force, default_value);
    VarCertificationsTeamSaviorMatch(true, force, default_value);
    VarCertificationsTotalSaviorMatch(true, force, default_value);

    VarCertificationsSaviorCumul(true, force, default_value);
    VarCertificationsTeamSaviorCumul(true, force, default_value);
    VarCertificationsTotalSaviorCumul(true, force, default_value);
}

void RocketStats::AllCertificationsPlaymaker(bool force, bool default_value)
{
    VarCertificationsPlaymaker(true, force, default_value);
    VarCertificationsTeamPlaymaker(true, force, default_value);
    VarCertificationsTotalPlaymaker(true, force, default_value);

    VarCertificationsPlaymakerMatch(true, force, default_value);
    VarCertificationsTeamPlaymakerMatch(true, force, default_value);
    VarCertificationsTotalPlaymakerMatch(true, force, default_value);

    VarCertificationsPlaymakerCumul(true, force, default_value);
    VarCertificationsTeamPlaymakerCumul(true, force, default_value);
    VarCertificationsTotalPlaymakerCumul(true, force, default_value);
}


std::string RocketStats::VarCertificationsMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_MVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Savior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_Savior.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Playmaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_Playmaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTeamMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamMVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamSavior.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamPlaymaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTotalMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalMVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalSavior.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalPlaymaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_MVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Savior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_SaviorMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Playmaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_PlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTeamMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamMVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamSaviorMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamPlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTotalMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalMVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalSaviorMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalPlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVPCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_MVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_SaviorCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_PlaymakerCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTeamMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamMVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamSaviorCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamPlaymakerCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTotalMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalMVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalSaviorCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalPlaymakerCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Other
std::string RocketStats::VarBoost(bool write, bool force, bool default_value, bool enabled)
{
    std::string tmp = (default_value ? "-1" : (enabled ? "1" : "0"));

    if (write && (force || (rs_in_file && rs_file_boost)))
        WriteInFile("RocketStats_BoostState.txt", tmp);

    return tmp;
}
#pragma endregion