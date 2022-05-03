#include "../RocketStats.h"

void RocketStats::ReadCertifications(Stats& stat, json& config)
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

void RocketStats::WriteCertifications(Stats& stat, json& config)
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

void RocketStats::ReplaceCertifications(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["MVP"] = VarCertificationsMVP();
    vars["CarTouches"] = VarCertificationsCarTouches();
    vars["FastestGoal"] = VarCertificationsFastestGoal();
    vars["SlowestGoal"] = VarCertificationsSlowestGoal();
    vars["BoostPickups"] = VarCertificationsBoostPickups();
    vars["FurthestGoal"] = VarCertificationsFurthestGoal();
    vars["MostBallTouches"] = VarCertificationsMostBallTouches();
    vars["MostBoostPickups"] = VarCertificationsMostBoostPickups();
    vars["FewestBallTouches"] = VarCertificationsFewestBallTouches();
    vars["TeamMVP"] = VarCertificationsTeamMVP();
    vars["TotalMVP"] = VarCertificationsTotalMVP();

    /// Match
    vars["MVPMatch"] = VarCertificationsMVPMatch();
    vars["CarTouchesMatch"] = VarCertificationsCarTouchesMatch();
    vars["FastestGoalMatch"] = VarCertificationsFastestGoalMatch();
    vars["SlowestGoalMatch"] = VarCertificationsSlowestGoalMatch();
    vars["BoostPickupsMatch"] = VarCertificationsBoostPickupsMatch();
    vars["FurthestGoalMatch"] = VarCertificationsFurthestGoalMatch();
    vars["MostBallTouchesMatch"] = VarCertificationsMostBallTouchesMatch();
    vars["MostBoostPickupsMatch"] = VarCertificationsMostBoostPickupsMatch();
    vars["FewestBallTouchesMatch"] = VarCertificationsFewestBallTouchesMatch();
    vars["TeamMVPMatch"] = VarCertificationsTeamMVPMatch();
    vars["TotalMVPMatch"] = VarCertificationsTotalMVPMatch();

    /// Cumul
    vars["MVPCumul"] = VarCertificationsMVPCumul();
    vars["CarTouchesCumul"] = VarCertificationsCarTouchesCumul();
    vars["FastestGoalCumul"] = VarCertificationsFastestGoalCumul();
    vars["SlowestGoalCumul"] = VarCertificationsSlowestGoalCumul();
    vars["BoostPickupsCumul"] = VarCertificationsBoostPickupsCumul();
    vars["FurthestGoalCumul"] = VarCertificationsFurthestGoalCumul();
    vars["MostBallTouchesCumul"] = VarCertificationsMostBallTouchesCumul();
    vars["MostBoostPickupsCumul"] = VarCertificationsMostBoostPickupsCumul();
    vars["FewestBallTouchesCumul"] = VarCertificationsFewestBallTouchesCumul();
    vars["TeamMVPCumul"] = VarCertificationsTeamMVPCumul();
    vars["TotalMVPCumul"] = VarCertificationsTotalMVPCumul();
}

void RocketStats::SessionCertifications(Stats& stat, int index, bool playlists)
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
std::string RocketStats::VarCertificationsMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVP)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsCarTouches(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().CarTouches)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_CarTouches.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFastestGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FastestGoal)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FastestGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSlowestGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SlowestGoal)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_SlowestGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsBoostPickups(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BoostPickups)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_BoostPickups.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFurthestGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FurthestGoal)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FurthestGoal.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsMostBallTouches(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBallTouches)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MostBallTouches.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsMostBoostPickups(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBoostPickups)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MostBoostPickups.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFewestBallTouches(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FewestBallTouches)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FewestBallTouches.txt", tmp);

    return tmp;
}

#pragma region BaseTeam
std::string RocketStats::VarCertificationsTeamMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamMVP.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region BaseTotal
std::string RocketStats::VarCertificationsTotalMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalMVP.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Match
std::string RocketStats::VarCertificationsMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MVP)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsCarTouchesMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.CarTouches)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_CarTouchesMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFastestGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FastestGoal)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FastestGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSlowestGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.SlowestGoal)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_SlowestGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsBoostPickupsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.BoostPickups)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_BoostPickupsMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFurthestGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FurthestGoal)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FurthestGoalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsMostBallTouchesMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MostBallTouches)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MostBallTouchesMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsMostBoostPickupsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MostBoostPickups)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MostBoostPickupsMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFewestBallTouchesMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FewestBallTouches)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FewestBallTouchesMatch.txt", tmp);

    return tmp;
}

#pragma region MatchTeam
std::string RocketStats::VarCertificationsTeamMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamMVPMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region MatchTotal
std::string RocketStats::VarCertificationsTotalMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalMVPMatch.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Cumul
std::string RocketStats::VarCertificationsMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVPCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsCarTouchesCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().CarTouchesCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_CarTouchesCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFastestGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FastestGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FastestGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSlowestGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SlowestGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_SlowestGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsBoostPickupsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().BoostPickupsCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_BoostPickupsCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFurthestGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FurthestGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FurthestGoalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsMostBallTouchesCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBallTouchesCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MostBallTouchesCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsMostBoostPickupsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MostBoostPickupsCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_MostBoostPickupsCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsFewestBallTouchesCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FewestBallTouchesCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_FewestBallTouchesCumul.txt", tmp);

    return tmp;
}

#pragma region CumulTeam
std::string RocketStats::VarCertificationsTeamMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamMVPCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region CumulTotal
std::string RocketStats::VarCertificationsTotalMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalMVPCumul.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion