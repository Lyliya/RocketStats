#include "../RocketStats.h"

#pragma region Base
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
#pragma endregion

#pragma region Match
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
#pragma endregion

#pragma region Cumul
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