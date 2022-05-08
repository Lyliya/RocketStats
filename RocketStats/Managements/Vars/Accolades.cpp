#include "../RocketStats.h"

void RocketStats::ReadAccolades(Stats& stat, json& config)
{
    if (config["MVP"].is_number_unsigned())
        stat.MVP = int(config["MVP"]);
    if (config["CarTouches"].is_number_unsigned())
        stat.CarTouches = int(config["CarTouches"]);
    if (config["FastestGoal"].is_number_unsigned())
        stat.FastestGoal = int(config["FastestGoal"]);
    if (config["SlowestGoal"].is_number_unsigned())
        stat.SlowestGoal = int(config["SlowestGoal"]);
    if (config["BoostPickups"].is_number_unsigned())
        stat.BoostPickups = int(config["BoostPickups"]);
    if (config["FurthestGoal"].is_number_unsigned())
        stat.FurthestGoal = int(config["FurthestGoal"]);
    if (config["MostBallTouches"].is_number_unsigned())
        stat.MostBallTouches = int(config["MostBallTouches"]);
    if (config["MostBoostPickups"].is_number_unsigned())
        stat.MostBoostPickups = int(config["MostBoostPickups"]);
    if (config["FewestBallTouches"].is_number_unsigned())
        stat.FewestBallTouches = int(config["FewestBallTouches"]);
    if (config["TeamMVP"].is_number_unsigned())
        stat.TeamMVP = int(config["TeamMVP"]);
    if (config["TotalMVP"].is_number_unsigned())
        stat.TotalMVP = int(config["TotalMVP"]);

    if (config["MVPCumul"].is_number_unsigned())
        stat.MVPCumul = int(config["MVPCumul"]);
    if (config["CarTouchesCumul"].is_number_unsigned())
        stat.CarTouchesCumul = int(config["CarTouchesCumul"]);
    if (config["FastestGoalCumul"].is_number_unsigned())
        stat.FastestGoalCumul = int(config["FastestGoalCumul"]);
    if (config["SlowestGoalCumul"].is_number_unsigned())
        stat.SlowestGoalCumul = int(config["SlowestGoalCumul"]);
    if (config["BoostPickupsCumul"].is_number_unsigned())
        stat.BoostPickupsCumul = int(config["BoostPickupsCumul"]);
    if (config["FurthestGoalCumul"].is_number_unsigned())
        stat.FurthestGoalCumul = int(config["FurthestGoalCumul"]);
    if (config["MostBallTouchesCumul"].is_number_unsigned())
        stat.MostBallTouchesCumul = int(config["MostBallTouchesCumul"]);
    if (config["MostBoostPickupsCumul"].is_number_unsigned())
        stat.MostBoostPickupsCumul = int(config["MostBoostPickupsCumul"]);
    if (config["FewestBallTouchesCumul"].is_number_unsigned())
        stat.FewestBallTouchesCumul = int(config["FewestBallTouchesCumul"]);
    if (config["TeamMVPCumul"].is_number_unsigned())
        stat.TeamMVPCumul = int(config["TeamMVPCumul"]);
    if (config["TotalMVPCumul"].is_number_unsigned())
        stat.TotalMVPCumul = int(config["TotalMVPCumul"]);
}

void RocketStats::WriteAccolades(Stats& stat, json& config, bool more)
{
    config["MVP"] = stat.MVP;
    config["CarTouches"] = stat.CarTouches;
    config["FastestGoal"] = stat.FastestGoal;
    config["SlowestGoal"] = stat.SlowestGoal;
    config["BoostPickups"] = stat.BoostPickups;
    config["FurthestGoal"] = stat.FurthestGoal;
    config["MostBallTouches"] = stat.MostBallTouches;
    config["MostBoostPickups"] = stat.MostBoostPickups;
    config["FewestBallTouches"] = stat.FewestBallTouches;
    config["TeamMVP"] = stat.TeamMVP;
    config["TotalMVP"] = stat.TotalMVP;

    config["MVPCumul"] = stat.MVPCumul;
    config["CarTouchesCumul"] = stat.CarTouchesCumul;
    config["FastestGoalCumul"] = stat.FastestGoalCumul;
    config["SlowestGoalCumul"] = stat.SlowestGoalCumul;
    config["BoostPickupsCumul"] = stat.BoostPickupsCumul;
    config["FurthestGoalCumul"] = stat.FurthestGoalCumul;
    config["MostBallTouchesCumul"] = stat.MostBallTouchesCumul;
    config["MostBoostPickupsCumul"] = stat.MostBoostPickupsCumul;
    config["FewestBallTouchesCumul"] = stat.FewestBallTouchesCumul;
    config["TeamMVPCumul"] = stat.TeamMVPCumul;
    config["TotalMVPCumul"] = stat.TotalMVPCumul;
}

void RocketStats::ReplaceAccolades(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["MVP"] = VarAccoladesMVP();
    vars["CarTouches"] = VarAccoladesCarTouches();
    vars["FastestGoal"] = VarAccoladesFastestGoal();
    vars["SlowestGoal"] = VarAccoladesSlowestGoal();
    vars["BoostPickups"] = VarAccoladesBoostPickups();
    vars["FurthestGoal"] = VarAccoladesFurthestGoal();
    vars["MostBallTouches"] = VarAccoladesMostBallTouches();
    vars["MostBoostPickups"] = VarAccoladesMostBoostPickups();
    vars["FewestBallTouches"] = VarAccoladesFewestBallTouches();
    vars["TeamMVP"] = VarAccoladesTeamMVP();
    vars["TotalMVP"] = VarAccoladesTotalMVP();

    /// Match
    vars["MVPMatch"] = VarAccoladesMVPMatch();
    vars["CarTouchesMatch"] = VarAccoladesCarTouchesMatch();
    vars["FastestGoalMatch"] = VarAccoladesFastestGoalMatch();
    vars["SlowestGoalMatch"] = VarAccoladesSlowestGoalMatch();
    vars["BoostPickupsMatch"] = VarAccoladesBoostPickupsMatch();
    vars["FurthestGoalMatch"] = VarAccoladesFurthestGoalMatch();
    vars["MostBallTouchesMatch"] = VarAccoladesMostBallTouchesMatch();
    vars["MostBoostPickupsMatch"] = VarAccoladesMostBoostPickupsMatch();
    vars["FewestBallTouchesMatch"] = VarAccoladesFewestBallTouchesMatch();
    vars["TeamMVPMatch"] = VarAccoladesTeamMVPMatch();
    vars["TotalMVPMatch"] = VarAccoladesTotalMVPMatch();

    /// Cumul
    vars["MVPCumul"] = VarAccoladesMVPCumul();
    vars["CarTouchesCumul"] = VarAccoladesCarTouchesCumul();
    vars["FastestGoalCumul"] = VarAccoladesFastestGoalCumul();
    vars["SlowestGoalCumul"] = VarAccoladesSlowestGoalCumul();
    vars["BoostPickupsCumul"] = VarAccoladesBoostPickupsCumul();
    vars["FurthestGoalCumul"] = VarAccoladesFurthestGoalCumul();
    vars["MostBallTouchesCumul"] = VarAccoladesMostBallTouchesCumul();
    vars["MostBoostPickupsCumul"] = VarAccoladesMostBoostPickupsCumul();
    vars["FewestBallTouchesCumul"] = VarAccoladesFewestBallTouchesCumul();
    vars["TeamMVPCumul"] = VarAccoladesTeamMVPCumul();
    vars["TotalMVPCumul"] = VarAccoladesTotalMVPCumul();
}

void RocketStats::SessionAccolades(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.MVP += stats[index].MVP;
        stat.CarTouches += stats[index].CarTouches;
        stat.FastestGoal += stats[index].FastestGoal;
        stat.SlowestGoal += stats[index].SlowestGoal;
        stat.BoostPickups += stats[index].BoostPickups;
        stat.FurthestGoal += stats[index].FurthestGoal;
        stat.MostBallTouches += stats[index].MostBallTouches;
        stat.MostBoostPickups += stats[index].MostBoostPickups;
        stat.FewestBallTouches += stats[index].FewestBallTouches;
        stat.TeamMVP += stats[index].TeamMVP;
        stat.TotalMVP += stats[index].TotalMVP;
    }
    else
    {
        session.MVPCumul = stat.MVP;
        session.CarTouchesCumul = stat.CarTouches;
        session.FastestGoalCumul = stat.FastestGoal;
        session.SlowestGoalCumul = stat.SlowestGoal;
        session.BoostPickupsCumul = stat.BoostPickups;
        session.FurthestGoalCumul = stat.FurthestGoal;
        session.MostBallTouchesCumul = stat.MostBallTouches;
        session.MostBoostPickupsCumul = stat.MostBoostPickups;
        session.FewestBallTouchesCumul = stat.FewestBallTouches;
        session.TeamMVPCumul = stat.TeamMVP;
        session.TotalMVPCumul = stat.TotalMVP;
    }
}

#pragma region Base
std::string RocketStats::VarAccoladesMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVP)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesCarTouches(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().CarTouches)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_CarTouches.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFastestGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FastestGoal)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FastestGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesSlowestGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SlowestGoal)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_SlowestGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesBoostPickups(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BoostPickups)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_BoostPickups.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFurthestGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FurthestGoal)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FurthestGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesMostBallTouches(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBallTouches)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MostBallTouches.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesMostBoostPickups(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBoostPickups)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MostBoostPickups.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFewestBallTouches(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FewestBallTouches)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FewestBallTouches.txt", tmp);

    return tmp;
}

#pragma region BaseTeam
std::string RocketStats::VarAccoladesTeamMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_TeamMVP.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region BaseTotal
std::string RocketStats::VarAccoladesTotalMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_TotalMVP.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Match
std::string RocketStats::VarAccoladesMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MVP)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesCarTouchesMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.CarTouches)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_CarTouchesMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFastestGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FastestGoal)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FastestGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesSlowestGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.SlowestGoal)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_SlowestGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesBoostPickupsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BoostPickups)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_BoostPickupsMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFurthestGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FurthestGoal)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FurthestGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesMostBallTouchesMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MostBallTouches)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MostBallTouchesMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesMostBoostPickupsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MostBoostPickups)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MostBoostPickupsMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFewestBallTouchesMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FewestBallTouches)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FewestBallTouchesMatch.txt", tmp);

    return tmp;
}

#pragma region MatchTeam
std::string RocketStats::VarAccoladesTeamMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_TeamMVPMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region MatchTotal
std::string RocketStats::VarAccoladesTotalMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_TotalMVPMatch.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Cumul
std::string RocketStats::VarAccoladesMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVPCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesCarTouchesCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().CarTouchesCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_CarTouchesCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFastestGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FastestGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FastestGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesSlowestGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SlowestGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_SlowestGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesBoostPickupsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BoostPickupsCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_BoostPickupsCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFurthestGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FurthestGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FurthestGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesMostBallTouchesCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBallTouchesCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MostBallTouchesCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesMostBoostPickupsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBoostPickupsCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_MostBoostPickupsCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarAccoladesFewestBallTouchesCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FewestBallTouchesCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_FewestBallTouchesCumul.txt", tmp);

    return tmp;
}

#pragma region CumulTeam
std::string RocketStats::VarAccoladesTeamMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_TeamMVPCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region CumulTotal
std::string RocketStats::VarAccoladesTotalMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_accolades ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_accolades)))
        WriteInFile("RocketStats_TotalMVPCumul.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion