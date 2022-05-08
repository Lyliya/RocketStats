#include "../RocketStats.h"

void RocketStats::ReadGoals(Stats& stat, json& config)
{
    if (config["Goal"].is_number_unsigned())
        stat.Goal = int(config["Goal"]);
    if (config["OwnGoal"].is_number_unsigned())
        stat.OwnGoal = int(config["OwnGoal"]);
    if (config["LongGoal"].is_number_unsigned())
        stat.LongGoal = int(config["LongGoal"]);
    if (config["PoolShot"].is_number_unsigned())
        stat.PoolShot = int(config["PoolShot"]);
    if (config["AerialGoal"].is_number_unsigned())
        stat.AerialGoal = int(config["AerialGoal"]);
    if (config["TurtleGoal"].is_number_unsigned())
        stat.TurtleGoal = int(config["TurtleGoal"]);
    if (config["BicycleGoal"].is_number_unsigned())
        stat.BicycleGoal = int(config["BicycleGoal"]);
    if (config["OvertimeGoal"].is_number_unsigned())
        stat.OvertimeGoal = int(config["OvertimeGoal"]);
    if (config["BackwardsGoal"].is_number_unsigned())
        stat.BackwardsGoal = int(config["BackwardsGoal"]);
    if (config["HoopsSwishGoal"].is_number_unsigned())
        stat.HoopsSwishGoal = int(config["HoopsSwishGoal"]);
    if (config["TeamGoal"].is_number_unsigned())
        stat.TeamGoal = int(config["TeamGoal"]);
    if (config["TeamLongGoal"].is_number_unsigned())
        stat.TeamLongGoal = int(config["TeamLongGoal"]);
    if (config["TeamPoolShot"].is_number_unsigned())
        stat.TeamPoolShot = int(config["TeamPoolShot"]);
    if (config["TeamAerialGoal"].is_number_unsigned())
        stat.TeamAerialGoal = int(config["TeamAerialGoal"]);
    if (config["TeamTurtleGoal"].is_number_unsigned())
        stat.TeamTurtleGoal = int(config["TeamTurtleGoal"]);
    if (config["TeamBicycleGoal"].is_number_unsigned())
        stat.TeamBicycleGoal = int(config["TeamBicycleGoal"]);
    if (config["TeamOvertimeGoal"].is_number_unsigned())
        stat.TeamOvertimeGoal = int(config["TeamOvertimeGoal"]);
    if (config["TeamBackwardsGoal"].is_number_unsigned())
        stat.TeamBackwardsGoal = int(config["TeamBackwardsGoal"]);
    if (config["TeamHoopsSwishGoal"].is_number_unsigned())
        stat.TeamHoopsSwishGoal = int(config["TeamHoopsSwishGoal"]);
    if (config["TotalGoal"].is_number_unsigned())
        stat.TotalGoal = int(config["TotalGoal"]);
    if (config["TotalLongGoal"].is_number_unsigned())
        stat.TotalLongGoal = int(config["TotalLongGoal"]);
    if (config["TotalPoolShot"].is_number_unsigned())
        stat.TotalPoolShot = int(config["TotalPoolShot"]);
    if (config["TotalAerialGoal"].is_number_unsigned())
        stat.TotalAerialGoal = int(config["TotalAerialGoal"]);
    if (config["TotalTurtleGoal"].is_number_unsigned())
        stat.TotalTurtleGoal = int(config["TotalTurtleGoal"]);
    if (config["TotalBicycleGoal"].is_number_unsigned())
        stat.TotalBicycleGoal = int(config["TotalBicycleGoal"]);
    if (config["TotalOvertimeGoal"].is_number_unsigned())
        stat.TotalOvertimeGoal = int(config["TotalOvertimeGoal"]);
    if (config["TotalBackwardsGoal"].is_number_unsigned())
        stat.TotalBackwardsGoal = int(config["TotalBackwardsGoal"]);
    if (config["TotalHoopsSwishGoal"].is_number_unsigned())
        stat.TotalHoopsSwishGoal = int(config["TotalHoopsSwishGoal"]);

    if (config["GoalCumul"].is_number_unsigned())
        stat.GoalCumul = int(config["GoalCumul"]);
    if (config["OwnGoalCumul"].is_number_unsigned())
        stat.OwnGoalCumul = int(config["OwnGoalCumul"]);
    if (config["LongGoalCumul"].is_number_unsigned())
        stat.LongGoalCumul = int(config["LongGoalCumul"]);
    if (config["PoolShotCumul"].is_number_unsigned())
        stat.PoolShotCumul = int(config["PoolShotCumul"]);
    if (config["AerialGoalCumul"].is_number_unsigned())
        stat.AerialGoalCumul = int(config["AerialGoalCumul"]);
    if (config["TurtleGoalCumul"].is_number_unsigned())
        stat.TurtleGoalCumul = int(config["TurtleGoalCumul"]);
    if (config["BicycleGoalCumul"].is_number_unsigned())
        stat.BicycleGoalCumul = int(config["BicycleGoalCumul"]);
    if (config["OvertimeGoalCumul"].is_number_unsigned())
        stat.OvertimeGoalCumul = int(config["OvertimeGoalCumul"]);
    if (config["BackwardsGoalCumul"].is_number_unsigned())
        stat.BackwardsGoalCumul = int(config["BackwardsGoalCumul"]);
    if (config["HoopsSwishGoalCumul"].is_number_unsigned())
        stat.HoopsSwishGoalCumul = int(config["HoopsSwishGoalCumul"]);
    if (config["TeamGoalCumul"].is_number_unsigned())
        stat.TeamGoalCumul = int(config["TeamGoalCumul"]);
    if (config["TeamLongGoalCumul"].is_number_unsigned())
        stat.TeamLongGoalCumul = int(config["TeamLongGoalCumul"]);
    if (config["TeamPoolShotCumul"].is_number_unsigned())
        stat.TeamPoolShotCumul = int(config["TeamPoolShotCumul"]);
    if (config["TeamAerialGoalCumul"].is_number_unsigned())
        stat.TeamAerialGoalCumul = int(config["TeamAerialGoalCumul"]);
    if (config["TeamTurtleGoalCumul"].is_number_unsigned())
        stat.TeamTurtleGoalCumul = int(config["TeamTurtleGoalCumul"]);
    if (config["TeamBicycleGoalCumul"].is_number_unsigned())
        stat.TeamBicycleGoalCumul = int(config["TeamBicycleGoalCumul"]);
    if (config["TeamOvertimeGoalCumul"].is_number_unsigned())
        stat.TeamOvertimeGoalCumul = int(config["TeamOvertimeGoalCumul"]);
    if (config["TeamBackwardsGoalCumul"].is_number_unsigned())
        stat.TeamBackwardsGoalCumul = int(config["TeamBackwardsGoalCumul"]);
    if (config["TeamHoopsSwishGoalCumul"].is_number_unsigned())
        stat.TeamHoopsSwishGoalCumul = int(config["TeamHoopsSwishGoalCumul"]);
    if (config["TotalGoalCumul"].is_number_unsigned())
        stat.TotalGoalCumul = int(config["TotalGoalCumul"]);
    if (config["TotalLongGoalCumul"].is_number_unsigned())
        stat.TotalLongGoalCumul = int(config["TotalLongGoalCumul"]);
    if (config["TotalPoolShotCumul"].is_number_unsigned())
        stat.TotalPoolShotCumul = int(config["TotalPoolShotCumul"]);
    if (config["TotalAerialGoalCumul"].is_number_unsigned())
        stat.TotalAerialGoalCumul = int(config["TotalAerialGoalCumul"]);
    if (config["TotalTurtleGoalCumul"].is_number_unsigned())
        stat.TotalTurtleGoalCumul = int(config["TotalTurtleGoalCumul"]);
    if (config["TotalBicycleGoalCumul"].is_number_unsigned())
        stat.TotalBicycleGoalCumul = int(config["TotalBicycleGoalCumul"]);
    if (config["TotalOvertimeGoalCumul"].is_number_unsigned())
        stat.TotalOvertimeGoalCumul = int(config["TotalOvertimeGoalCumul"]);
    if (config["TotalBackwardsGoalCumul"].is_number_unsigned())
        stat.TotalBackwardsGoalCumul = int(config["TotalBackwardsGoalCumul"]);
    if (config["TotalHoopsSwishGoalCumul"].is_number_unsigned())
        stat.TotalHoopsSwishGoalCumul = int(config["TotalHoopsSwishGoalCumul"]);
}

void RocketStats::WriteGoals(Stats& stat, json& config, bool more)
{
    config["Goal"] = stat.Goal;
    config["OwnGoal"] = stat.OwnGoal;
    config["LongGoal"] = stat.LongGoal;
    config["PoolShot"] = stat.PoolShot;
    config["AerialGoal"] = stat.AerialGoal;
    config["TurtleGoal"] = stat.TurtleGoal;
    config["BicycleGoal"] = stat.BicycleGoal;
    config["OvertimeGoal"] = stat.OvertimeGoal;
    config["BackwardsGoal"] = stat.BackwardsGoal;
    config["HoopsSwishGoal"] = stat.HoopsSwishGoal;
    config["TeamGoal"] = stat.TeamGoal;
    config["TeamLongGoal"] = stat.TeamLongGoal;
    config["TeamAerialGoal"] = stat.TeamAerialGoal;
    config["TeamTurtleGoal"] = stat.TeamTurtleGoal;
    config["TeamBicycleGoal"] = stat.TeamBicycleGoal;
    config["TeamOvertimeGoal"] = stat.TeamOvertimeGoal;
    config["TeamBackwardsGoal"] = stat.TeamBackwardsGoal;
    config["TeamHoopsSwishGoal"] = stat.TeamHoopsSwishGoal;
    config["TotalGoal"] = stat.TotalGoal;
    config["TotalLongGoal"] = stat.TotalLongGoal;
    config["TotalAerialGoal"] = stat.TotalAerialGoal;
    config["TotalTurtleGoal"] = stat.TotalTurtleGoal;
    config["TotalBicycleGoal"] = stat.TotalBicycleGoal;
    config["TotalOvertimeGoal"] = stat.TotalOvertimeGoal;
    config["TotalBackwardsGoal"] = stat.TotalBackwardsGoal;
    config["TotalHoopsSwishGoal"] = stat.TotalHoopsSwishGoal;

    config["GoalCumul"] = stat.GoalCumul;
    config["OwnGoalCumul"] = stat.OwnGoalCumul;
    config["LongGoalCumul"] = stat.LongGoalCumul;
    config["PoolShotCumul"] = stat.PoolShotCumul;
    config["AerialGoalCumul"] = stat.AerialGoalCumul;
    config["TurtleGoalCumul"] = stat.TurtleGoalCumul;
    config["BicycleGoalCumul"] = stat.BicycleGoalCumul;
    config["OvertimeGoalCumul"] = stat.OvertimeGoalCumul;
    config["BackwardsGoalCumul"] = stat.BackwardsGoalCumul;
    config["HoopsSwishGoalCumul"] = stat.HoopsSwishGoalCumul;
    config["TeamGoalCumul"] = stat.TeamGoalCumul;
    config["TeamLongGoalCumul"] = stat.TeamLongGoalCumul;
    config["TeamPoolShotCumul"] = stat.TeamPoolShotCumul;
    config["TeamAerialGoalCumul"] = stat.TeamAerialGoalCumul;
    config["TeamTurtleGoalCumul"] = stat.TeamTurtleGoalCumul;
    config["TeamBicycleGoalCumul"] = stat.TeamBicycleGoalCumul;
    config["TeamOvertimeGoalCumul"] = stat.TeamOvertimeGoalCumul;
    config["TeamBackwardsGoalCumul"] = stat.TeamBackwardsGoalCumul;
    config["TeamHoopsSwishGoalCumul"] = stat.TeamHoopsSwishGoalCumul;
    config["TotalGoalCumul"] = stat.TotalGoalCumul;
    config["TotalLongGoalCumul"] = stat.TotalLongGoalCumul;
    config["TotalPoolShotCumul"] = stat.TotalPoolShotCumul;
    config["TotalAerialGoalCumul"] = stat.TotalAerialGoalCumul;
    config["TotalTurtleGoalCumul"] = stat.TotalTurtleGoalCumul;
    config["TotalBicycleGoalCumul"] = stat.TotalBicycleGoalCumul;
    config["TotalOvertimeGoalCumul"] = stat.TotalOvertimeGoalCumul;
    config["TotalBackwardsGoalCumul"] = stat.TotalBackwardsGoalCumul;
    config["TotalHoopsSwishGoalCumul"] = stat.TotalHoopsSwishGoalCumul;
}

void RocketStats::ReplaceGoals(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["Goal"] = VarGoalsGoal();
    vars["OwnGoal"] = VarGoalsOwnGoal();
    vars["LongGoal"] = VarGoalsLongGoal();
    vars["PoolShot"] = VarGoalsPoolShot();
    vars["AerialGoal"] = VarGoalsAerialGoal();
    vars["TurtleGoal"] = VarGoalsTurtleGoal();
    vars["BicycleGoal"] = VarGoalsBicycleGoal();
    vars["OvertimeGoal"] = VarGoalsOvertimeGoal();
    vars["BackwardsGoal"] = VarGoalsBackwardsGoal();
    vars["HoopsSwishGoal"] = VarGoalsHoopsSwishGoal();
    vars["TeamGoal"] = VarGoalsTeamGoal();
    vars["TeamLongGoal"] = VarGoalsTeamLongGoal();
    vars["TeamPoolShot"] = VarGoalsTeamPoolShot();
    vars["TeamAerialGoal"] = VarGoalsTeamAerialGoal();
    vars["TeamTurtleGoal"] = VarGoalsTeamTurtleGoal();
    vars["TeamBicycleGoal"] = VarGoalsTeamBicycleGoal();
    vars["TeamOvertimeGoal"] = VarGoalsTeamOvertimeGoal();
    vars["TeamBackwardsGoal"] = VarGoalsTeamBackwardsGoal();
    vars["TeamHoopsSwishGoal"] = VarGoalsTeamHoopsSwishGoal();
    vars["TotalGoal"] = VarGoalsTotalGoal();
    vars["TotalLongGoal"] = VarGoalsTotalLongGoal();
    vars["TotalPoolShot"] = VarGoalsTotalPoolShot();
    vars["TotalAerialGoal"] = VarGoalsTotalAerialGoal();
    vars["TotalTurtleGoal"] = VarGoalsTotalTurtleGoal();
    vars["TotalBicycleGoal"] = VarGoalsTotalBicycleGoal();
    vars["TotalOvertimeGoal"] = VarGoalsTotalOvertimeGoal();
    vars["TotalBackwardsGoal"] = VarGoalsTotalBackwardsGoal();
    vars["TotalHoopsSwishGoal"] = VarGoalsTotalHoopsSwishGoal();

    /// Match
    vars["GoalMatch"] = VarGoalsGoalMatch();
    vars["OwnGoalMatch"] = VarGoalsOwnGoalMatch();
    vars["LongGoalMatch"] = VarGoalsLongGoalMatch();
    vars["PoolShotMatch"] = VarGoalsPoolShotMatch();
    vars["AerialGoalMatch"] = VarGoalsAerialGoalMatch();
    vars["TurtleGoalMatch"] = VarGoalsTurtleGoalMatch();
    vars["BicycleGoalMatch"] = VarGoalsBicycleGoalMatch();
    vars["OvertimeGoalMatch"] = VarGoalsOvertimeGoalMatch();
    vars["BackwardsGoalMatch"] = VarGoalsBackwardsGoalMatch();
    vars["HoopsSwishGoalMatch"] = VarGoalsHoopsSwishGoalMatch();
    vars["TeamGoalMatch"] = VarGoalsTeamGoalMatch();
    vars["TeamLongGoalMatch"] = VarGoalsTeamLongGoalMatch();
    vars["TeamPoolShotMatch"] = VarGoalsTeamPoolShotMatch();
    vars["TeamAerialGoalMatch"] = VarGoalsTeamAerialGoalMatch();
    vars["TeamTurtleGoalMatch"] = VarGoalsTeamTurtleGoalMatch();
    vars["TeamBicycleGoalMatch"] = VarGoalsTeamBicycleGoalMatch();
    vars["TeamOvertimeGoalMatch"] = VarGoalsTeamOvertimeGoalMatch();
    vars["TeamBackwardsGoalMatch"] = VarGoalsTeamBackwardsGoalMatch();
    vars["TeamHoopsSwishGoalMatch"] = VarGoalsTeamHoopsSwishGoalMatch();
    vars["TotalGoalMatch"] = VarGoalsTotalGoalMatch();
    vars["TotalLongGoalMatch"] = VarGoalsTotalLongGoalMatch();
    vars["TotalPoolShotMatch"] = VarGoalsTotalPoolShotMatch();
    vars["TotalAerialGoalMatch"] = VarGoalsTotalAerialGoalMatch();
    vars["TotalTurtleGoalMatch"] = VarGoalsTotalTurtleGoalMatch();
    vars["TotalBicycleGoalMatch"] = VarGoalsTotalBicycleGoalMatch();
    vars["TotalOvertimeGoalMatch"] = VarGoalsTotalOvertimeGoalMatch();
    vars["TotalBackwardsGoalMatch"] = VarGoalsTotalBackwardsGoalMatch();
    vars["TotalHoopsSwishGoalMatch"] = VarGoalsTotalHoopsSwishGoalMatch();

    /// Cumul
    vars["GoalCumul"] = VarGoalsGoalCumul();
    vars["OwnGoalCumul"] = VarGoalsOwnGoalCumul();
    vars["OwnGoalCumul"] = VarGoalsOwnGoalCumul();
    vars["LongGoalCumul"] = VarGoalsLongGoalCumul();
    vars["PoolShotCumul"] = VarGoalsPoolShotCumul();
    vars["AerialGoalCumul"] = VarGoalsAerialGoalCumul();
    vars["TurtleGoalCumul"] = VarGoalsTurtleGoalCumul();
    vars["BicycleGoalCumul"] = VarGoalsBicycleGoalCumul();
    vars["OvertimeGoalCumul"] = VarGoalsOvertimeGoalCumul();
    vars["BackwardsGoalCumul"] = VarGoalsBackwardsGoalCumul();
    vars["HoopsSwishGoalCumul"] = VarGoalsHoopsSwishGoalCumul();
    vars["TeamGoalCumul"] = VarGoalsTeamGoalCumul();
    vars["TeamLongGoalCumul"] = VarGoalsTeamLongGoalCumul();
    vars["TeamPoolShotCumul"] = VarGoalsTeamPoolShotCumul();
    vars["TeamAerialGoalCumul"] = VarGoalsTeamAerialGoalCumul();
    vars["TeamTurtleGoalCumul"] = VarGoalsTeamTurtleGoalCumul();
    vars["TeamBicycleGoalCumul"] = VarGoalsTeamBicycleGoalCumul();
    vars["TeamOvertimeGoalCumul"] = VarGoalsTeamOvertimeGoalCumul();
    vars["TeamBackwardsGoalCumul"] = VarGoalsTeamBackwardsGoalCumul();
    vars["TeamHoopsSwishGoalCumul"] = VarGoalsTeamHoopsSwishGoalCumul();
    vars["TotalGoalCumul"] = VarGoalsTotalGoalCumul();
    vars["TotalLongGoalCumul"] = VarGoalsTotalLongGoalCumul();
    vars["TotalPoolShotCumul"] = VarGoalsTotalPoolShotCumul();
    vars["TotalAerialGoalCumul"] = VarGoalsTotalAerialGoalCumul();
    vars["TotalTurtleGoalCumul"] = VarGoalsTotalTurtleGoalCumul();
    vars["TotalBicycleGoalCumul"] = VarGoalsTotalBicycleGoalCumul();
    vars["TotalOvertimeGoalCumul"] = VarGoalsTotalOvertimeGoalCumul();
    vars["TotalBackwardsGoalCumul"] = VarGoalsTotalBackwardsGoalCumul();
    vars["TotalHoopsSwishGoalCumul"] = VarGoalsTotalHoopsSwishGoalCumul();
}

void RocketStats::SessionGoals(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.Goal += stats[index].Goal;
        stat.OwnGoal += stats[index].OwnGoal;
        stat.LongGoal += stats[index].LongGoal;
        stat.PoolShot += stats[index].PoolShot;
        stat.AerialGoal += stats[index].AerialGoal;
        stat.TurtleGoal += stats[index].TurtleGoal;
        stat.BicycleGoal += stats[index].BicycleGoal;
        stat.OvertimeGoal += stats[index].OvertimeGoal;
        stat.BackwardsGoal += stats[index].BackwardsGoal;
        stat.HoopsSwishGoal += stats[index].HoopsSwishGoal;
        stat.TeamGoal += stats[index].TeamGoal;
        stat.TeamLongGoal += stats[index].TeamLongGoal;
        stat.TeamPoolShot += stats[index].TeamPoolShot;
        stat.TeamAerialGoal += stats[index].TeamAerialGoal;
        stat.TeamTurtleGoal += stats[index].TeamTurtleGoal;
        stat.TeamBicycleGoal += stats[index].TeamBicycleGoal;
        stat.TeamOvertimeGoal += stats[index].TeamOvertimeGoal;
        stat.TeamBackwardsGoal += stats[index].TeamBackwardsGoal;
        stat.TeamHoopsSwishGoal += stats[index].TeamHoopsSwishGoal;
        stat.TotalGoal += stats[index].TotalGoal;
        stat.TotalLongGoal += stats[index].TotalLongGoal;
        stat.TotalPoolShot += stats[index].TotalPoolShot;
        stat.TotalAerialGoal += stats[index].TotalAerialGoal;
        stat.TotalTurtleGoal += stats[index].TotalTurtleGoal;
        stat.TotalBicycleGoal += stats[index].TotalBicycleGoal;
        stat.TotalOvertimeGoal += stats[index].TotalOvertimeGoal;
        stat.TotalBackwardsGoal += stats[index].TotalBackwardsGoal;
        stat.TotalHoopsSwishGoal += stats[index].TotalHoopsSwishGoal;
    }
    else
    {
        session.GoalCumul = stat.Goal;
        session.OwnGoalCumul = stat.OwnGoal;
        session.LongGoalCumul = stat.LongGoal;
        session.PoolShotCumul = stat.PoolShot;
        session.AerialGoalCumul = stat.AerialGoal;
        session.TurtleGoalCumul = stat.TurtleGoal;
        session.BicycleGoalCumul = stat.BicycleGoal;
        session.OvertimeGoalCumul = stat.OvertimeGoal;
        session.BackwardsGoalCumul = stat.BackwardsGoal;
        session.HoopsSwishGoalCumul = stat.HoopsSwishGoal;
        session.TeamGoalCumul = stat.TeamGoal;
        session.TeamLongGoalCumul = stat.TeamLongGoal;
        session.TeamPoolShotCumul = stat.TeamPoolShot;
        session.TeamAerialGoalCumul = stat.TeamAerialGoal;
        session.TeamTurtleGoalCumul = stat.TeamTurtleGoal;
        session.TeamBicycleGoalCumul = stat.TeamBicycleGoal;
        session.TeamOvertimeGoalCumul = stat.TeamOvertimeGoal;
        session.TeamBackwardsGoalCumul = stat.TeamBackwardsGoal;
        session.TeamHoopsSwishGoalCumul = stat.TeamHoopsSwishGoal;
        session.TotalGoalCumul = stat.TotalGoal;
        session.TotalLongGoalCumul = stat.TotalLongGoal;
        session.TotalPoolShotCumul = stat.TotalPoolShot;
        session.TotalAerialGoalCumul = stat.TotalAerialGoal;
        session.TotalTurtleGoalCumul = stat.TotalTurtleGoal;
        session.TotalBicycleGoalCumul = stat.TotalBicycleGoal;
        session.TotalOvertimeGoalCumul = stat.TotalOvertimeGoal;
        session.TotalBackwardsGoalCumul = stat.TotalBackwardsGoal;
        session.TotalHoopsSwishGoalCumul = stat.TotalHoopsSwishGoal;
    }
}

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

std::string RocketStats::VarGoalsLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShot.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().OvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsHoopsSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HoopsSwishGoal.txt", tmp);

    return tmp;
}

#pragma region BaseTeam
std::string RocketStats::VarGoalsTeamGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShot.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamHoopsSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHoopsSwishGoal.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region BaseTotal
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

std::string RocketStats::VarGoalsTotalLongGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShot(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShot.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalHoopsSwishGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHoopsSwishGoal.txt", tmp);

    return tmp;
}
#pragma endregion
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

std::string RocketStats::VarGoalsLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.LongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.PoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShotMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.AerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.OvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsHoopsSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.HoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HoopsSwishGoalMatch.txt", tmp);

    return tmp;
}

#pragma region MatchTeam
std::string RocketStats::VarGoalsTeamGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShotMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamHoopsSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHoopsSwishGoalMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region MatchTotal
std::string RocketStats::VarGoalsTotalGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalLongGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShotMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalPoolShot)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShotMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalAerialGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalTurtleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalBicycleGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalOvertimeGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalBackwardsGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalHoopsSwishGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalHoopsSwishGoal)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHoopsSwishGoalMatch.txt", tmp);

    return tmp;
}
#pragma endregion
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

std::string RocketStats::VarGoalsLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().LongGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_LongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PoolShotCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_PoolShotCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().AerialGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_AerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TurtleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BicycleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().OvertimeGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_OvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BackwardsGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_BackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsHoopsSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().HoopsSwishGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_HoopsSwishGoalCumul.txt", tmp);

    return tmp;
}

#pragma region CumulTeam
std::string RocketStats::VarGoalsTeamGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamLongGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamLongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPoolShotCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamPoolShotCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamAerialGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamAerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamTurtleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamTurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBicycleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamOvertimeGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamOvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamBackwardsGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamBackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTeamHoopsSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamHoopsSwishGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TeamHoopsSwishGoalCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region CumulTotal
std::string RocketStats::VarGoalsTotalGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalLongGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalLongGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalLongGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalPoolShotCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPoolShotCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalPoolShotCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalAerialGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalAerialGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalAerialGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalTurtleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalTurtleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalTurtleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBicycleGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBicycleGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBicycleGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalOvertimeGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalOvertimeGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalOvertimeGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalBackwardsGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalBackwardsGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalBackwardsGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarGoalsTotalHoopsSwishGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_goals ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalHoopsSwishGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_goals)))
        WriteInFile("RocketStats_TotalHoopsSwishGoalCumul.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion