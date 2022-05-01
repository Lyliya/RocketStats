#include "../RocketStats.h"

#pragma region Base
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
#pragma endregion

#pragma region Match
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
#pragma endregion

#pragma region Cumul
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