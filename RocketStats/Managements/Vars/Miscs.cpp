#include "../RocketStats.h"

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