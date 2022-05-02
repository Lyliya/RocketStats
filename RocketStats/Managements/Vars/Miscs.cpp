#include "../RocketStats.h"

void RocketStats::ReadMiscs(Stats& stat, json& config)
{
    if (config["LowFive"].is_number_unsigned())
        stat.LowFive = int(config["LowFive"]);
    if (config["HatTrick"].is_number_unsigned())
        stat.HatTrick = int(config["HatTrick"]);
    if (config["HighFive"].is_number_unsigned())
        stat.HighFive = int(config["HighFive"]);
    if (config["TeamLowFive"].is_number_unsigned())
        stat.TeamLowFive = int(config["TeamLowFive"]);
    if (config["TeamHatTrick"].is_number_unsigned())
        stat.TeamHatTrick = int(config["TeamHatTrick"]);
    if (config["TeamHighFive"].is_number_unsigned())
        stat.TeamHighFive = int(config["TeamHighFive"]);
    if (config["TotalLowFive"].is_number_unsigned())
        stat.TotalLowFive = int(config["TotalLowFive"]);
    if (config["TotalHatTrick"].is_number_unsigned())
        stat.TotalHatTrick = int(config["TotalHatTrick"]);
    if (config["TotalHighFive"].is_number_unsigned())
        stat.TotalHighFive = int(config["TotalHighFive"]);

    if (config["LowFiveCumul"].is_number_unsigned())
        stat.LowFiveCumul = int(config["LowFiveCumul"]);
    if (config["HatTrickCumul"].is_number_unsigned())
        stat.HatTrickCumul = int(config["HatTrickCumul"]);
    if (config["HighFiveCumul"].is_number_unsigned())
        stat.HighFiveCumul = int(config["HighFiveCumul"]);
    if (config["TeamLowFiveCumul"].is_number_unsigned())
        stat.TeamLowFiveCumul = int(config["TeamLowFiveCumul"]);
    if (config["TeamHatTrickCumul"].is_number_unsigned())
        stat.TeamHatTrickCumul = int(config["TeamHatTrickCumul"]);
    if (config["TeamHighFiveCumul"].is_number_unsigned())
        stat.TeamHighFiveCumul = int(config["TeamHighFiveCumul"]);
    if (config["TotalLowFiveCumul"].is_number_unsigned())
        stat.TotalLowFiveCumul = int(config["TotalLowFiveCumul"]);
    if (config["TotalHatTrickCumul"].is_number_unsigned())
        stat.TotalHatTrickCumul = int(config["TotalHatTrickCumul"]);
    if (config["TotalHighFiveCumul"].is_number_unsigned())
        stat.TotalHighFiveCumul = int(config["TotalHighFiveCumul"]);
}

void RocketStats::WriteMiscs(Stats& stat, json& config)
{
    config["HatTrick"] = stat.HatTrick;
    config["LowFive"] = stat.LowFive;
    config["HighFive"] = stat.HighFive;
    config["MVP"] = stat.MVP;
    config["TeamHatTrick"] = stat.TeamHatTrick;
    config["TeamLowFive"] = stat.TeamLowFive;
    config["TeamHighFive"] = stat.TeamHighFive;
    config["TeamMVP"] = stat.TeamMVP;
    config["TotalHatTrick"] = stat.TotalHatTrick;
    config["TotalLowFive"] = stat.TotalLowFive;
    config["TotalHighFive"] = stat.TotalHighFive;
    config["TotalMVP"] = stat.TotalMVP;

    config["HatTrickCumul"] = stat.HatTrickCumul;
    config["LowFiveCumul"] = stat.LowFiveCumul;
    config["HighFiveCumul"] = stat.HighFiveCumul;
    config["MVPCumul"] = stat.MVPCumul;
    config["TeamHatTrickCumul"] = stat.TeamHatTrickCumul;
    config["TeamLowFiveCumul"] = stat.TeamLowFiveCumul;
    config["TeamHighFiveCumul"] = stat.TeamHighFiveCumul;
    config["TeamMVPCumul"] = stat.TeamMVPCumul;
    config["TotalHatTrickCumul"] = stat.TotalHatTrickCumul;
    config["TotalLowFiveCumul"] = stat.TotalLowFiveCumul;
    config["TotalHighFiveCumul"] = stat.TotalHighFiveCumul;
    config["TotalMVPCumul"] = stat.TotalMVPCumul;
}

void RocketStats::ReplaceMiscs(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["HatTrick"] = VarMiscsHatTrick();
    vars["LowFive"] = VarMiscsLowFive();
    vars["HighFive"] = VarMiscsHighFive();
    vars["TeamHatTrick"] = VarMiscsTeamHatTrick();
    vars["TeamLowFive"] = VarMiscsTeamLowFive();
    vars["TeamHighFive"] = VarMiscsTeamHighFive();
    vars["TotalHatTrick"] = VarMiscsTotalHatTrick();
    vars["TotalLowFive"] = VarMiscsTotalLowFive();
    vars["TotalHighFive"] = VarMiscsTotalHighFive();

    /// Match
    vars["HatTrickMatch"] = VarMiscsHatTrickMatch();
    vars["LowFiveMatch"] = VarMiscsLowFiveMatch();
    vars["HighFiveMatch"] = VarMiscsHighFiveMatch();
    vars["TeamHatTrickMatch"] = VarMiscsTeamHatTrickMatch();
    vars["TeamLowFiveMatch"] = VarMiscsTeamLowFiveMatch();
    vars["TeamHighFiveMatch"] = VarMiscsTeamHighFiveMatch();
    vars["TotalHatTrickMatch"] = VarMiscsTotalHatTrickMatch();
    vars["TotalLowFiveMatch"] = VarMiscsTotalLowFiveMatch();
    vars["TotalHighFiveMatch"] = VarMiscsTotalHighFiveMatch();

    /// Cumul
    vars["HatTrickCumul"] = VarMiscsHatTrickCumul();
    vars["LowFiveCumul"] = VarMiscsLowFiveCumul();
    vars["HighFiveCumul"] = VarMiscsHighFiveCumul();
    vars["TeamHatTrickCumul"] = VarMiscsTeamHatTrickCumul();
    vars["TeamLowFiveCumul"] = VarMiscsTeamLowFiveCumul();
    vars["TeamHighFiveCumul"] = VarMiscsTeamHighFiveCumul();
    vars["TotalHatTrickCumul"] = VarMiscsTotalHatTrickCumul();
    vars["TotalLowFiveCumul"] = VarMiscsTotalLowFiveCumul();
    vars["TotalHighFiveCumul"] = VarMiscsTotalHighFiveCumul();
}

void RocketStats::SessionMiscs(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.LowFive += stats[index].LowFive;
        stat.HatTrick += stats[index].HatTrick;
        stat.HighFive += stats[index].HighFive;
        stat.TeamLowFive += stats[index].TeamLowFive;
        stat.TeamHatTrick += stats[index].TeamHatTrick;
        stat.TeamHighFive += stats[index].TeamHighFive;
        stat.TotalLowFive += stats[index].TotalLowFive;
        stat.TotalHatTrick += stats[index].TotalHatTrick;
        stat.TotalHighFive += stats[index].TotalHighFive;
    }
    else
    {
        session.LowFiveCumul = stat.LowFive;
        session.HatTrickCumul = stat.HatTrick;
        session.HighFiveCumul = stat.HighFive;
        session.TeamLowFiveCumul = stat.TeamLowFive;
        session.TeamHatTrickCumul = stat.TeamHatTrick;
        session.TeamHighFiveCumul = stat.TeamHighFive;
        session.TotalLowFiveCumul = stat.TotalLowFive;
        session.TotalHatTrickCumul = stat.TotalHatTrick;
        session.TotalHighFiveCumul = stat.TotalHighFive;
    }
}

#pragma region Base
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
#pragma endregion

#pragma region Match
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
#pragma endregion

#pragma region Cumul
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