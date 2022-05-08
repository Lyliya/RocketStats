#include "../RocketStats.h"

void RocketStats::ReadDropshot(Stats& stat, json& config)
{
    if (config["BreakoutDamage"].is_number_unsigned())
        stat.BreakoutDamage = int(config["BreakoutDamage"]);
    if (config["BreakoutDamageLarge"].is_number_unsigned())
        stat.BreakoutDamageLarge = int(config["BreakoutDamageLarge"]);
    if (config["TeamBreakoutDamage"].is_number_unsigned())
        stat.TeamBreakoutDamage = int(config["TeamBreakoutDamage"]);
    if (config["TeamBreakoutDamageLarge"].is_number_unsigned())
        stat.TeamBreakoutDamageLarge = int(config["TeamBreakoutDamageLarge"]);
    if (config["TotalBreakoutDamage"].is_number_unsigned())
        stat.TotalBreakoutDamage = int(config["TotalBreakoutDamage"]);
    if (config["TotalBreakoutDamageLarge"].is_number_unsigned())
        stat.TotalBreakoutDamageLarge = int(config["TotalBreakoutDamageLarge"]);

    if (config["BreakoutDamageCumul"].is_number_unsigned())
        stat.BreakoutDamageCumul = int(config["BreakoutDamageCumul"]);
    if (config["BreakoutDamageLargeCumul"].is_number_unsigned())
        stat.BreakoutDamageLargeCumul = int(config["BreakoutDamageLargeCumul"]);
    if (config["TeamBreakoutDamageCumul"].is_number_unsigned())
        stat.TeamBreakoutDamageCumul = int(config["TeamBreakoutDamageCumul"]);
    if (config["TeamBreakoutDamageLargeCumul"].is_number_unsigned())
        stat.TeamBreakoutDamageLargeCumul = int(config["TeamBreakoutDamageLargeCumul"]);
    if (config["TotalBreakoutDamageCumul"].is_number_unsigned())
        stat.TotalBreakoutDamageCumul = int(config["TotalBreakoutDamageCumul"]);
    if (config["TotalBreakoutDamageLargeCumul"].is_number_unsigned())
        stat.TotalBreakoutDamageLargeCumul = int(config["TotalBreakoutDamageLargeCumul"]);
}

void RocketStats::WriteDropshot(Stats& stat, json& config, bool more)
{
    config["BreakoutDamage"] = stat.BreakoutDamage;
    config["BreakoutDamageLarge"] = stat.BreakoutDamageLarge;
    config["TeamBreakoutDamage"] = stat.TeamBreakoutDamage;
    config["TeamBreakoutDamageLarge"] = stat.TeamBreakoutDamageLarge;
    config["TotalBreakoutDamage"] = stat.TotalBreakoutDamage;
    config["TotalBreakoutDamageLarge"] = stat.TotalBreakoutDamageLarge;

    config["BreakoutDamageCumul"] = stat.BreakoutDamageCumul;
    config["BreakoutDamageLargeCumul"] = stat.BreakoutDamageLargeCumul;
    config["TeamBreakoutDamageCumul"] = stat.TeamBreakoutDamageCumul;
    config["TeamBreakoutDamageLargeCumul"] = stat.TeamBreakoutDamageLargeCumul;
    config["TotalBreakoutDamageCumul"] = stat.TotalBreakoutDamageCumul;
    config["TotalBreakoutDamageLargeCumul"] = stat.TotalBreakoutDamageLargeCumul;
}

void RocketStats::ReplaceDropshot(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["BreakoutDamage"] = VarDropshotBreakoutDamage();
    vars["BreakoutDamageLarge"] = VarDropshotBreakoutDamageLarge();
    vars["TeamBreakoutDamage"] = VarDropshotTeamBreakoutDamage();
    vars["TeamBreakoutDamageLarge"] = VarDropshotTeamBreakoutDamageLarge();
    vars["TotalBreakoutDamage"] = VarDropshotTotalBreakoutDamage();
    vars["TotalBreakoutDamageLarge"] = VarDropshotTotalBreakoutDamageLarge();

    /// Match
    vars["BreakoutDamageMatch"] = VarDropshotBreakoutDamageMatch();
    vars["BreakoutDamageLargeMatch"] = VarDropshotBreakoutDamageLargeMatch();
    vars["TeamBreakoutDamageMatch"] = VarDropshotTeamBreakoutDamageMatch();
    vars["TeamBreakoutDamageLargeMatch"] = VarDropshotTeamBreakoutDamageLargeMatch();
    vars["TotalBreakoutDamageMatch"] = VarDropshotTotalBreakoutDamageMatch();
    vars["TotalBreakoutDamageLargeMatch"] = VarDropshotTotalBreakoutDamageLargeMatch();

    /// Cumul
    vars["BreakoutDamageCumul"] = VarDropshotBreakoutDamageCumul();
    vars["BreakoutDamageLargeCumul"] = VarDropshotBreakoutDamageLargeCumul();
    vars["TeamBreakoutDamageCumul"] = VarDropshotTeamBreakoutDamageCumul();
    vars["TeamBreakoutDamageLargeCumul"] = VarDropshotTeamBreakoutDamageLargeCumul();
    vars["TotalBreakoutDamageCumul"] = VarDropshotTotalBreakoutDamageCumul();
    vars["TotalBreakoutDamageLargeCumul"] = VarDropshotTotalBreakoutDamageLargeCumul();
}

void RocketStats::SessionDropshot(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.BreakoutDamage += stats[index].BreakoutDamage;
        stat.BreakoutDamageLarge += stats[index].BreakoutDamageLarge;
        stat.TeamBreakoutDamage += stats[index].TeamBreakoutDamage;
        stat.TeamBreakoutDamageLarge += stats[index].TeamBreakoutDamageLarge;
        stat.TotalBreakoutDamage += stats[index].TotalBreakoutDamage;
        stat.TotalBreakoutDamageLarge += stats[index].TotalBreakoutDamageLarge;
    }
    else
    {
        session.BreakoutDamageCumul = stat.BreakoutDamage;
        session.BreakoutDamageLargeCumul = stat.BreakoutDamageLarge;
        session.TeamBreakoutDamageCumul = stat.TeamBreakoutDamage;
        session.TeamBreakoutDamageLargeCumul = stat.TeamBreakoutDamageLarge;
        session.TotalBreakoutDamageCumul = stat.TotalBreakoutDamage;
        session.TotalBreakoutDamageLargeCumul = stat.TotalBreakoutDamageLarge;
    }
}

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

#pragma region BaseTeam
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
#pragma endregion

#pragma region BaseTotal
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

#pragma region MatchTeam
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
#pragma endregion

#pragma region MatchTotal
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

#pragma region CumulTeam
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
#pragma endregion

#pragma region CumulTotal
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
#pragma endregion