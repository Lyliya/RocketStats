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
#pragma endregion

#pragma region Shots
void RocketStats::AllShots(bool force, bool default_value)
{
    AllShotsShot(force, default_value);
    AllShotsCenterBall(force, default_value);
    AllShotsClearBall(force, default_value);
    AllShotsFirstTouch(force, default_value);
    AllShotsShotOnGoal(force, default_value);
    AllShotsBicycleHit(force, default_value);
}

void RocketStats::AllShotsShot(bool force, bool default_value)
{
    VarShotsShot(true, force, default_value);
    VarShotsTeamShot(true, force, default_value);
    VarShotsTotalShot(true, force, default_value);

    VarShotsShotMatch(true, force, default_value);
    VarShotsTeamShotMatch(true, force, default_value);
    VarShotsTotalShotMatch(true, force, default_value);

    VarShotsShotCumul(true, force, default_value);
    VarShotsTeamShotCumul(true, force, default_value);
    VarShotsTotalShotCumul(true, force, default_value);
}

void RocketStats::AllShotsCenterBall(bool force, bool default_value)
{
    VarShotsCenterBall(true, force, default_value);
    VarShotsTeamCenterBall(true, force, default_value);
    VarShotsTotalCenterBall(true, force, default_value);

    VarShotsCenterBallMatch(true, force, default_value);
    VarShotsTeamCenterBallMatch(true, force, default_value);
    VarShotsTotalCenterBallMatch(true, force, default_value);

    VarShotsCenterBallCumul(true, force, default_value);
    VarShotsTeamCenterBallCumul(true, force, default_value);
    VarShotsTotalCenterBallCumul(true, force, default_value);
}

void RocketStats::AllShotsClearBall(bool force, bool default_value)
{
    VarShotsClearBall(true, force, default_value);
    VarShotsTeamClearBall(true, force, default_value);
    VarShotsTotalClearBall(true, force, default_value);

    VarShotsClearBallMatch(true, force, default_value);
    VarShotsTeamClearBallMatch(true, force, default_value);
    VarShotsTotalClearBallMatch(true, force, default_value);

    VarShotsClearBallCumul(true, force, default_value);
    VarShotsTeamClearBallCumul(true, force, default_value);
    VarShotsTotalClearBallCumul(true, force, default_value);
}

void RocketStats::AllShotsFirstTouch(bool force, bool default_value)
{
    VarShotsFirstTouch(true, force, default_value);
    VarShotsTeamFirstTouch(true, force, default_value);
    VarShotsTotalFirstTouch(true, force, default_value);

    VarShotsFirstTouchMatch(true, force, default_value);
    VarShotsTeamFirstTouchMatch(true, force, default_value);
    VarShotsTotalFirstTouchMatch(true, force, default_value);

    VarShotsFirstTouchCumul(true, force, default_value);
    VarShotsTeamFirstTouchCumul(true, force, default_value);
    VarShotsTotalFirstTouchCumul(true, force, default_value);
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


std::string RocketStats::VarShotsShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.Shot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_Shot.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsCenterBall(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.CenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_CenterBall.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsClearBall(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.ClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ClearBall.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsFirstTouch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.FirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_FirstTouch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsShotOnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.ShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ShotOnGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsBicycleHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.BicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleHit.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTeamShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamShot.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamCenterBall(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamCenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamCenterBall.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamClearBall(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamClearBall.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamFirstTouch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamFirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamFirstTouch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamShotOnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamShotOnGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamBicycleHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleHit.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTotalShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalShot.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalCenterBall(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalCenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalCenterBall.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalClearBall(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalClearBall.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalFirstTouch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalFirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalFirstTouch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalShotOnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalShotOnGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalBicycleHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleHit.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.Shot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ShotMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsCenterBallMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.CenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_CenterBallMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsClearBallMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.ClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ClearBallMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsFirstTouchMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.FirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_FirstTouchMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsShotOnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.ShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ShotOnGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsBicycleHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.BicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleHitMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTeamShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamShotMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamCenterBallMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamCenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamCenterBallMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamClearBallMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamClearBallMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamFirstTouchMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamFirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamFirstTouchMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamShotOnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamShotOnGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamBicycleHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleHitMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTotalShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalShotMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalCenterBallMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalCenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalCenterBallMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalClearBallMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalClearBallMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalFirstTouchMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalFirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalFirstTouchMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalShotOnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalShotOnGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalBicycleHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleHitMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Shot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ShotCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsCenterBallCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().CenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_CenterBallCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsClearBallCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().ClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ClearBallCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsFirstTouchCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_FirstTouchCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsShotOnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().ShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_ShotOnGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsBicycleHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleHitCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTeamShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamShotCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamCenterBallCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamCenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamCenterBallCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamClearBallCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamClearBallCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamFirstTouchCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamFirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamFirstTouchCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamShotOnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamShotOnGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTeamBicycleHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleHitCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarShotsTotalShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalShotCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalCenterBallCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalCenterBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalCenterBallCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalClearBallCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalClearBall)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalClearBallCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalFirstTouchCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalFirstTouch)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalFirstTouchCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalShotOnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalShotOnGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarShotsTotalBicycleHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleHit)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleHitCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Miscs
void RocketStats::AllMiscs(bool force, bool default_value)
{
    AllMiscsHatTrick(force, default_value);
    AllMiscsLowFive(force, default_value);
    AllMiscsHighFive(force, default_value);
    AllMiscsMVP(force, default_value);
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

void RocketStats::AllMiscsMVP(bool force, bool default_value)
{
    VarMiscsMVP(true, force, default_value);
    VarMiscsTeamMVP(true, force, default_value);
    VarMiscsTotalMVP(true, force, default_value);

    VarMiscsMVPMatch(true, force, default_value);
    VarMiscsTeamMVPMatch(true, force, default_value);
    VarMiscsTotalMVPMatch(true, force, default_value);

    VarMiscsMVPCumul(true, force, default_value);
    VarMiscsTeamMVPCumul(true, force, default_value);
    VarMiscsTotalMVPCumul(true, force, default_value);
}


std::string RocketStats::VarMiscsHatTrick(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.HatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HatTrick.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsLowFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.LowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LowFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHighFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.HighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HighFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.MVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_MVP.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTeamHatTrick(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamHatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHatTrick.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamLowFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamLowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLowFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHighFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamHighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHighFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamMVP.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTotalHatTrick(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalHatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHatTrick.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalLowFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalLowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLowFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHighFive(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalHighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHighFive.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalMVP.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsHatTrickMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.HatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HatTrickMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsLowFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.LowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LowFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHighFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.HighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HighFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.MVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_MVPMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTeamHatTrickMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamHatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHatTrickMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamLowFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamLowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLowFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHighFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamHighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHighFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamMVPMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTotalHatTrickMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalHatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHatTrickMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalLowFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalLowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLowFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHighFiveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalHighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHighFiveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalMVPMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsHatTrickCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HatTrickCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsLowFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LowFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsHighFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HighFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_MVPCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTeamHatTrickCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHatTrickCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamLowFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLowFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamHighFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHighFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamMVPCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarMiscsTotalHatTrickCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHatTrick)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHatTrickCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalLowFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLowFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLowFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalHighFiveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHighFive)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHighFiveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalMVPCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Assists
void RocketStats::AllAssists(bool force, bool default_value)
{
    AllAssistsAssist(force, default_value);
    AllAssistsPlaymaker(force, default_value);
}

void RocketStats::AllAssistsAssist(bool force, bool default_value)
{
    VarAssistsAssist(true, force, default_value);
    VarAssistsTeamAssist(true, force, default_value);
    VarAssistsTotalAssist(true, force, default_value);

    VarAssistsAssistMatch(true, force, default_value);
    VarAssistsTeamAssistMatch(true, force, default_value);
    VarAssistsTotalAssistMatch(true, force, default_value);

    VarAssistsAssistCumul(true, force, default_value);
    VarAssistsTeamAssistCumul(true, force, default_value);
    VarAssistsTotalAssistCumul(true, force, default_value);
}

void RocketStats::AllAssistsPlaymaker(bool force, bool default_value)
{
    VarAssistsPlaymaker(true, force, default_value);
    VarAssistsTeamPlaymaker(true, force, default_value);
    VarAssistsTotalPlaymaker(true, force, default_value);

    VarAssistsPlaymakerMatch(true, force, default_value);
    VarAssistsTeamPlaymakerMatch(true, force, default_value);
    VarAssistsTotalPlaymakerMatch(true, force, default_value);

    VarAssistsPlaymakerCumul(true, force, default_value);
    VarAssistsTeamPlaymakerCumul(true, force, default_value);
    VarAssistsTotalPlaymakerCumul(true, force, default_value);
}


std::string RocketStats::VarAssistsAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.Assist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_Assist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.Playmaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_Playmaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsTeamAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamAssist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamAssist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsTeamPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamPlaymaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsTotalAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalAssist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalAssist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsTotalPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalPlaymaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.Assist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_AssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.Playmaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_PlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsTeamAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamAssist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamAssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsTeamPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamPlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsTotalAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalAssist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalAssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsTotalPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalPlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Assist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_AssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Playmaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_PlaymakerCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsTeamAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAssist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamAssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsTeamPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamPlaymakerCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarAssistsTotalAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalAssist)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalAssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAssistsTotalPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalPlaymakerCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Goals
void RocketStats::AllGoals(bool force, bool default_value)
{
    AllGoalsGoal(force, default_value);
    AllGoalsAerialGoal(force, default_value);
    AllGoalsBackwardsGoal(force, default_value);
    AllGoalsBicycleGoal(force, default_value);
    AllGoalsLongGoal(force, default_value);
    AllGoalsTurtleGoal(force, default_value);
    AllGoalsOvertimeGoal(force, default_value);
    AllGoalsSwishGoal(force, default_value);
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

void RocketStats::AllGoalsSwishGoal(bool force, bool default_value)
{
    VarGoalsSwishGoal(true, force, default_value);
    VarGoalsTeamSwishGoal(true, force, default_value);
    VarGoalsTotalSwishGoal(true, force, default_value);

    VarGoalsSwishGoalMatch(true, force, default_value);
    VarGoalsTeamSwishGoalMatch(true, force, default_value);
    VarGoalsTotalSwishGoalMatch(true, force, default_value);

    VarGoalsSwishGoalCumul(true, force, default_value);
    VarGoalsTeamSwishGoalCumul(true, force, default_value);
    VarGoalsTotalSwishGoalCumul(true, force, default_value);
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
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.Goal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_Goal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.AerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.BackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.BicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.LongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.OvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.SwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_SwishGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.PoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShot.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTeamGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamSwishGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShot.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTotalGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalSwishGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShot.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.Goal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_GoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.AerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.BackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.BicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.LongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.OvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.SwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_SwishGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.PoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShotMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTeamGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamSwishGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShotMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTotalGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalSwishGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShotMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Goal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_GoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().OvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_SwishGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShotCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTeamGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamSwishGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShotCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarGoalsTotalGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalSwishGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShotCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Saves
void RocketStats::AllSaves(bool force, bool default_value)
{
    AllSavesSave(force, default_value);
    AllSavesEpicSave(force, default_value);
    AllSavesSavior(force, default_value);
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

void RocketStats::AllSavesSavior(bool force, bool default_value)
{
    VarSavesSavior(true, force, default_value);
    VarSavesTeamSavior(true, force, default_value);
    VarSavesTotalSavior(true, force, default_value);

    VarSavesSaviorMatch(true, force, default_value);
    VarSavesTeamSaviorMatch(true, force, default_value);
    VarSavesTotalSaviorMatch(true, force, default_value);

    VarSavesSaviorCumul(true, force, default_value);
    VarSavesTeamSaviorCumul(true, force, default_value);
    VarSavesTotalSaviorCumul(true, force, default_value);
}


std::string RocketStats::VarSavesSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.Save)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_Save.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.EpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.Savior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_Savior.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTeamSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSavior.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTotalSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSavior.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.Save)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.EpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.Savior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaviorMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTeamSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaviorMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTotalSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaviorMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Save)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().EpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Savior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaviorCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTeamSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaviorCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarSavesTotalSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaviorCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Dropshot
void RocketStats::AllDropshot(bool force, bool default_value)
{
    AllDropshotDamage(force, default_value);
    AllDropshotUltraDamage(force, default_value);
}

void RocketStats::AllDropshotDamage(bool force, bool default_value)
{
    VarDropshotDamage(true, force, default_value);
    VarDropshotTeamDamage(true, force, default_value);
    VarDropshotTotalDamage(true, force, default_value);

    VarDropshotDamageMatch(true, force, default_value);
    VarDropshotTeamDamageMatch(true, force, default_value);
    VarDropshotTotalDamageMatch(true, force, default_value);

    VarDropshotDamageCumul(true, force, default_value);
    VarDropshotTeamDamageCumul(true, force, default_value);
    VarDropshotTotalDamageCumul(true, force, default_value);
}

void RocketStats::AllDropshotUltraDamage(bool force, bool default_value)
{
    VarDropshotUltraDamage(true, force, default_value);
    VarDropshotTeamUltraDamage(true, force, default_value);
    VarDropshotTotalUltraDamage(true, force, default_value);

    VarDropshotUltraDamageMatch(true, force, default_value);
    VarDropshotTeamUltraDamageMatch(true, force, default_value);
    VarDropshotTotalUltraDamageMatch(true, force, default_value);

    VarDropshotUltraDamageCumul(true, force, default_value);
    VarDropshotTeamUltraDamageCumul(true, force, default_value);
    VarDropshotTotalUltraDamageCumul(true, force, default_value);
}


std::string RocketStats::VarDropshotDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.Damage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_Damage.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotUltraDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.UltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_UltraDamage.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTeamDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamDamage.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTeamUltraDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamUltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamUltraDamage.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTotalDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalDamage.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTotalUltraDamage(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalUltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalUltraDamage.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.Damage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_DamageMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotUltraDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.UltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_UltraDamageMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTeamDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamDamageMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTeamUltraDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TeamUltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamUltraDamageMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTotalDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalDamageMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTotalUltraDamageMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(current.TotalUltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalUltraDamageMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Damage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_DamageCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotUltraDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().UltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_UltraDamageCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTeamDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamDamageCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTeamUltraDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamUltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TeamUltraDamageCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarDropshotTotalDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalDamageCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarDropshotTotalUltraDamageCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_assists ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalUltraDamage)));

    if (write && (force || (rs_in_file && rs_file_assists)))
        WriteInFile("RocketStats_TotalUltraDamageCumul.txt", tmp);

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