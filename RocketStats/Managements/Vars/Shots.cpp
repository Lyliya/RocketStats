#include "../RocketStats.h"

#pragma region Base
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
#pragma endregion

#pragma region Match
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
#pragma endregion

#pragma region Cumul
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