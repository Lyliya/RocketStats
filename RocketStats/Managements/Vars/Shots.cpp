#include "../RocketStats.h"

void RocketStats::ReadShots(Stats& stat, json& config)
{
    if (config["Clear"].is_number_unsigned())
        stat.Clear = int(config["Clear"]);
    if (config["Assist"].is_number_unsigned())
        stat.Assist = int(config["Assist"]);
    if (config["Center"].is_number_unsigned())
        stat.Center = int(config["Center"]);
    if (config["AerialHit"].is_number_unsigned())
        stat.AerialHit = int(config["AerialHit"]);
    if (config["BicycleHit"].is_number_unsigned())
        stat.BicycleHit = int(config["BicycleHit"]);
    if (config["ShotOnGoal"].is_number_unsigned())
        stat.ShotOnGoal = int(config["ShotOnGoal"]);
    if (config["TeamAssist"].is_number_unsigned())
        stat.TeamAssist = int(config["TeamAssist"]);
    if (config["TeamBicycleHit"].is_number_unsigned())
        stat.TeamBicycleHit = int(config["TeamBicycleHit"]);
    if (config["TeamShotOnGoal"].is_number_unsigned())
        stat.TeamShotOnGoal = int(config["TeamShotOnGoal"]);
    if (config["TotalAssist"].is_number_unsigned())
        stat.TotalAssist = int(config["TotalAssist"]);
    if (config["TotalBicycleHit"].is_number_unsigned())
        stat.TotalBicycleHit = int(config["TotalBicycleHit"]);
    if (config["TotalShotOnGoal"].is_number_unsigned())
        stat.TotalShotOnGoal = int(config["TotalShotOnGoal"]);

    if (config["ClearCumul"].is_number_unsigned())
        stat.ClearCumul = int(config["ClearCumul"]);
    if (config["AssistCumul"].is_number_unsigned())
        stat.AssistCumul = int(config["AssistCumul"]);
    if (config["CenterCumul"].is_number_unsigned())
        stat.CenterCumul = int(config["CenterCumul"]);
    if (config["AerialHitCumul"].is_number_unsigned())
        stat.AerialHitCumul = int(config["AerialHitCumul"]);
    if (config["BicycleHitCumul"].is_number_unsigned())
        stat.BicycleHitCumul = int(config["BicycleHitCumul"]);
    if (config["ShotOnGoalCumul"].is_number_unsigned())
        stat.ShotOnGoalCumul = int(config["ShotOnGoalCumul"]);
    if (config["TeamAssistCumul"].is_number_unsigned())
        stat.TeamAssistCumul = int(config["TeamAssistCumul"]);
    if (config["TeamBicycleHitCumul"].is_number_unsigned())
        stat.TeamBicycleHitCumul = int(config["TeamBicycleHitCumul"]);
    if (config["TeamShotOnGoalCumul"].is_number_unsigned())
        stat.TeamShotOnGoalCumul = int(config["TeamShotOnGoalCumul"]);
    if (config["TotalAssistCumul"].is_number_unsigned())
        stat.TotalAssistCumul = int(config["TotalAssistCumul"]);
    if (config["TotalBicycleHitCumul"].is_number_unsigned())
        stat.TotalBicycleHitCumul = int(config["TotalBicycleHitCumul"]);
    if (config["TotalShotOnGoalCumul"].is_number_unsigned())
        stat.TotalShotOnGoalCumul = int(config["TotalShotOnGoalCumul"]);
}

void RocketStats::WriteShots(Stats& stat, json& config, bool more)
{
    config["Clear"] = stat.Clear;
    config["Assist"] = stat.Assist;
    config["Center"] = stat.Center;
    config["AerialHit"] = stat.AerialHit;
    config["BicycleHit"] = stat.BicycleHit;
    config["ShotOnGoal"] = stat.ShotOnGoal;
    config["TeamAssist"] = stat.TeamAssist;
    config["TeamBicycleHit"] = stat.TeamBicycleHit;
    config["TeamShotOnGoal"] = stat.TeamShotOnGoal;
    config["TotalAssist"] = stat.TotalAssist;
    config["TotalBicycleHit"] = stat.TotalBicycleHit;
    config["TotalShotOnGoal"] = stat.TotalShotOnGoal;

    config["ClearCumul"] = stat.ClearCumul;
    config["AssistCumul"] = stat.AssistCumul;
    config["CenterCumul"] = stat.CenterCumul;
    config["AerialHitCumul"] = stat.AerialHitCumul;
    config["BicycleHitCumul"] = stat.BicycleHitCumul;
    config["ShotOnGoalCumul"] = stat.ShotOnGoalCumul;
    config["TeamAssistCumul"] = stat.TeamAssistCumul;
    config["TeamBicycleHitCumul"] = stat.TeamBicycleHitCumul;
    config["TeamShotOnGoalCumul"] = stat.TeamShotOnGoalCumul;
    config["TotalAssistCumul"] = stat.TotalAssistCumul;
    config["TotalBicycleHitCumul"] = stat.TotalBicycleHitCumul;
    config["TotalShotOnGoalCumul"] = stat.TotalShotOnGoalCumul;
}

void RocketStats::ReplaceShots(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["Clear"] = VarShotsClear();
    vars["Assist"] = VarShotsAssist();
    vars["Center"] = VarShotsCenter();
    vars["AerialHit"] = VarShotsAerialHit();
    vars["BicycleHit"] = VarShotsBicycleHit();
    vars["ShotOnGoal"] = VarShotsShotOnGoal();
    vars["TeamAssist"] = VarShotsTeamAssist();
    vars["TeamBicycleHit"] = VarShotsTeamBicycleHit();
    vars["TeamShotOnGoal"] = VarShotsTeamShotOnGoal();
    vars["TotalAssist"] = VarShotsTotalAssist();
    vars["TotalBicycleHit"] = VarShotsTotalBicycleHit();
    vars["TotalShotOnGoal"] = VarShotsTotalShotOnGoal();

    /// Match
    vars["ClearMatch"] = VarShotsClearMatch();
    vars["AssistMatch"] = VarShotsAssistMatch();
    vars["CenterMatch"] = VarShotsCenterMatch();
    vars["AerialHitMatch"] = VarShotsAerialHitMatch();
    vars["BicycleHitMatch"] = VarShotsBicycleHitMatch();
    vars["ShotOnGoalMatch"] = VarShotsShotOnGoalMatch();
    vars["TeamAssistMatch"] = VarShotsTeamAssistMatch();
    vars["TeamBicycleHitMatch"] = VarShotsTeamBicycleHitMatch();
    vars["TeamShotOnGoalMatch"] = VarShotsTeamShotOnGoalMatch();
    vars["TotalAssistMatch"] = VarShotsTotalAssistMatch();
    vars["TotalBicycleHitMatch"] = VarShotsTotalBicycleHitMatch();
    vars["TotalShotOnGoalMatch"] = VarShotsTotalShotOnGoalMatch();

    /// Cumul
    vars["ClearCumul"] = VarShotsClearCumul();
    vars["AssistCumul"] = VarShotsAssistCumul();
    vars["CenterCumul"] = VarShotsCenterCumul();
    vars["AerialHitCumul"] = VarShotsAerialHitCumul();
    vars["BicycleHitCumul"] = VarShotsBicycleHitCumul();
    vars["ShotOnGoalCumul"] = VarShotsShotOnGoalCumul();
    vars["TeamAssistCumul"] = VarShotsTeamAssistCumul();
    vars["TeamBicycleHitCumul"] = VarShotsTeamBicycleHitCumul();
    vars["TeamShotOnGoalCumul"] = VarShotsTeamShotOnGoalCumul();
    vars["TotalAssistCumul"] = VarShotsTotalAssistCumul();
    vars["TotalBicycleHitCumul"] = VarShotsTotalBicycleHitCumul();
    vars["TotalShotOnGoalCumul"] = VarShotsTotalShotOnGoalCumul();
}

void RocketStats::SessionShots(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.Clear += stats[index].Clear;
        stat.Assist += stats[index].Assist;
        stat.Center += stats[index].Center;
        stat.AerialHit += stats[index].AerialHit;
        stat.BicycleHit += stats[index].BicycleHit;
        stat.ShotOnGoal += stats[index].ShotOnGoal;
        stat.TeamAssist += stats[index].TeamAssist;
        stat.TeamBicycleHit += stats[index].TeamBicycleHit;
        stat.TeamShotOnGoal += stats[index].TeamShotOnGoal;
        stat.TotalAssist += stats[index].TotalAssist;
        stat.TotalBicycleHit += stats[index].TotalBicycleHit;
        stat.TotalShotOnGoal += stats[index].TotalShotOnGoal;
    }
    else
    {
        session.ClearCumul = stat.Clear;
        session.CenterCumul = stat.Center;
        session.AssistCumul = stat.Assist;
        session.ShotOnGoalCumul = stat.ShotOnGoal;
        session.AerialHitCumul = stat.AerialHit;
        session.BicycleHitCumul = stat.BicycleHit;
        session.TeamAssistCumul = stat.TeamAssist;
        session.TeamShotOnGoalCumul = stat.TeamShotOnGoal;
        session.TeamBicycleHitCumul = stat.TeamBicycleHit;
        session.TotalAssistCumul = stat.TotalAssist;
        session.TotalShotOnGoalCumul = stat.TotalShotOnGoal;
        session.TotalBicycleHitCumul = stat.TotalBicycleHit;
    }
}

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

std::string RocketStats::VarShotsShotOnGoal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().ShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ShotOnGoal.txt", tmp);

    return tmp;
}

#pragma region BaseTeam
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
#pragma endregion

#pragma region BaseTotal
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

std::string RocketStats::VarShotsShotOnGoalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.ShotOnGoal)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ShotOnGoalMatch.txt", tmp);

    return tmp;
}

#pragma region MatchTeam
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
#pragma endregion

#pragma region MatchTotal
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

std::string RocketStats::VarShotsShotOnGoalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_shots ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().ShotOnGoalCumul)));

    if (write && (force || (rs_in_file && rs_file_shots)))
        WriteInFile("RocketStats_ShotOnGoalCumul.txt", tmp);

    return tmp;
}

#pragma region CumulTeam
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
#pragma endregion

#pragma region CumulTotal
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
#pragma endregion