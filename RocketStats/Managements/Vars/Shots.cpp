#include "../RocketStats.h"

void RocketStats::ReadShots(Stats& stat, json& config)
{
    if (config["Knockout"].is_number_unsigned())
        stat.Knockout = int(config["Knockout"]);
    if (config["KnockoutDeath"].is_number_unsigned())
        stat.KnockoutDeath = int(config["KnockoutDeath"]);
    if (config["KnockoutAssist"].is_number_unsigned())
        stat.KnockoutAssist = int(config["KnockoutAssist"]);
    if (config["KnockoutDoubleKO"].is_number_unsigned())
        stat.KnockoutDoubleKO = int(config["KnockoutDoubleKO"]);
    if (config["KnockoutHeavyHit"].is_number_unsigned())
        stat.KnockoutHeavyHit = int(config["KnockoutHeavyHit"]);
    if (config["KnockoutTripleKO"].is_number_unsigned())
        stat.KnockoutTripleKO = int(config["KnockoutTripleKO"]);
    if (config["KnockoutHeavyBlock"].is_number_unsigned())
        stat.KnockoutHeavyBlock = int(config["KnockoutHeavyBlock"]);
    if (config["KnockoutAerialHeavyHit"].is_number_unsigned())
        stat.KnockoutAerialHeavyHit = int(config["KnockoutAerialHeavyHit"]);
    if (config["KnockoutAerialLightHit"].is_number_unsigned())
        stat.KnockoutAerialLightHit = int(config["KnockoutAerialLightHit"]);
    if (config["KnockoutTeam"].is_number_unsigned())
        stat.KnockoutTeam = int(config["KnockoutTeam"]);
    if (config["KnockoutTeamDeath"].is_number_unsigned())
        stat.KnockoutTeamDeath = int(config["KnockoutTeamDeath"]);
    if (config["KnockoutTeamAssist"].is_number_unsigned())
        stat.KnockoutTeamAssist = int(config["KnockoutTeamAssist"]);
    if (config["KnockoutTeamDoubleKO"].is_number_unsigned())
        stat.KnockoutTeamDoubleKO = int(config["KnockoutTeamDoubleKO"]);
    if (config["KnockoutTeamHeavyHit"].is_number_unsigned())
        stat.KnockoutTeamHeavyHit = int(config["KnockoutTeamHeavyHit"]);
    if (config["KnockoutTeamTripleKO"].is_number_unsigned())
        stat.KnockoutTeamTripleKO = int(config["KnockoutTeamTripleKO"]);
    if (config["KnockoutTeamHeavyBlock"].is_number_unsigned())
        stat.KnockoutTeamHeavyBlock = int(config["KnockoutTeamHeavyBlock"]);
    if (config["KnockoutTeamAerialHeavyHit"].is_number_unsigned())
        stat.KnockoutTeamAerialHeavyHit = int(config["KnockoutTeamAerialHeavyHit"]);
    if (config["KnockoutTeamAerialLightHit"].is_number_unsigned())
        stat.KnockoutTeamAerialLightHit = int(config["KnockoutTeamAerialLightHit"]);
    if (config["KnockoutTotal"].is_number_unsigned())
        stat.KnockoutTotal = int(config["KnockoutTotal"]);
    if (config["KnockoutTotalDeath"].is_number_unsigned())
        stat.KnockoutTotalDeath = int(config["KnockoutTotalDeath"]);
    if (config["KnockoutTotalAssist"].is_number_unsigned())
        stat.KnockoutTotalAssist = int(config["KnockoutTotalAssist"]);
    if (config["KnockoutTotalDoubleKO"].is_number_unsigned())
        stat.KnockoutTotalDoubleKO = int(config["KnockoutTotalDoubleKO"]);
    if (config["KnockoutTotalHeavyHit"].is_number_unsigned())
        stat.KnockoutTotalHeavyHit = int(config["KnockoutTotalHeavyHit"]);
    if (config["KnockoutTotalTripleKO"].is_number_unsigned())
        stat.KnockoutTotalTripleKO = int(config["KnockoutTotalTripleKO"]);
    if (config["KnockoutTotalHeavyBlock"].is_number_unsigned())
        stat.KnockoutTotalHeavyBlock = int(config["KnockoutTotalHeavyBlock"]);
    if (config["KnockoutTotalAerialHeavyHit"].is_number_unsigned())
        stat.KnockoutTotalAerialHeavyHit = int(config["KnockoutTotalAerialHeavyHit"]);
    if (config["KnockoutTotalAerialLightHit"].is_number_unsigned())
        stat.KnockoutTotalAerialLightHit = int(config["KnockoutTotalAerialLightHit"]);

    if (config["KnockoutCumul"].is_number_unsigned())
        stat.KnockoutCumul = int(config["KnockoutCumul"]);
    if (config["KnockoutDeathCumul"].is_number_unsigned())
        stat.KnockoutDeathCumul = int(config["KnockoutDeathCumul"]);
    if (config["KnockoutAssistCumul"].is_number_unsigned())
        stat.KnockoutAssistCumul = int(config["KnockoutAssistCumul"]);
    if (config["KnockoutDoubleKOCumul"].is_number_unsigned())
        stat.KnockoutDoubleKOCumul = int(config["KnockoutDoubleKOCumul"]);
    if (config["KnockoutHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutHeavyHitCumul = int(config["KnockoutHeavyHitCumul"]);
    if (config["KnockoutTripleKOCumul"].is_number_unsigned())
        stat.KnockoutTripleKOCumul = int(config["KnockoutTripleKOCumul"]);
    if (config["KnockoutHeavyBlockCumul"].is_number_unsigned())
        stat.KnockoutHeavyBlockCumul = int(config["KnockoutHeavyBlockCumul"]);
    if (config["KnockoutAerialHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutAerialHeavyHitCumul = int(config["KnockoutAerialHeavyHitCumul"]);
    if (config["KnockoutAerialLightHitCumul"].is_number_unsigned())
        stat.KnockoutAerialLightHitCumul = int(config["KnockoutAerialLightHitCumul"]);
    if (config["KnockoutTeamCumul"].is_number_unsigned())
        stat.KnockoutTeamCumul = int(config["KnockoutTeamCumul"]);
    if (config["KnockoutTeamDeathCumul"].is_number_unsigned())
        stat.KnockoutTeamDeathCumul = int(config["KnockoutTeamDeathCumul"]);
    if (config["KnockoutTeamAssistCumul"].is_number_unsigned())
        stat.KnockoutTeamAssistCumul = int(config["KnockoutTeamAssistCumul"]);
    if (config["KnockoutTeamDoubleKOCumul"].is_number_unsigned())
        stat.KnockoutTeamDoubleKOCumul = int(config["KnockoutTeamDoubleKOCumul"]);
    if (config["KnockoutTeamHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutTeamHeavyHitCumul = int(config["KnockoutTeamHeavyHitCumul"]);
    if (config["KnockoutTeamTripleKOCumul"].is_number_unsigned())
        stat.KnockoutTeamTripleKOCumul = int(config["KnockoutTeamTripleKOCumul"]);
    if (config["KnockoutTeamHeavyBlockCumul"].is_number_unsigned())
        stat.KnockoutTeamHeavyBlockCumul = int(config["KnockoutTeamHeavyBlockCumul"]);
    if (config["KnockoutTeamAerialHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutTeamAerialHeavyHitCumul = int(config["KnockoutTeamAerialHeavyHitCumul"]);
    if (config["KnockoutTeamAerialLightHitCumul"].is_number_unsigned())
        stat.KnockoutTeamAerialLightHitCumul = int(config["KnockoutTeamAerialLightHitCumul"]);
    if (config["KnockoutTotalCumul"].is_number_unsigned())
        stat.KnockoutTotalCumul = int(config["KnockoutTotalCumul"]);
    if (config["KnockoutTotalDeathCumul"].is_number_unsigned())
        stat.KnockoutTotalDeathCumul = int(config["KnockoutTotalDeathCumul"]);
    if (config["KnockoutTotalAssistCumul"].is_number_unsigned())
        stat.KnockoutTotalAssistCumul = int(config["KnockoutTotalAssistCumul"]);
    if (config["KnockoutTotalDoubleKOCumul"].is_number_unsigned())
        stat.KnockoutTotalDoubleKOCumul = int(config["KnockoutTotalDoubleKOCumul"]);
    if (config["KnockoutTotalHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutTotalHeavyHitCumul = int(config["KnockoutTotalHeavyHitCumul"]);
    if (config["KnockoutTotalTripleKOCumul"].is_number_unsigned())
        stat.KnockoutTotalTripleKOCumul = int(config["KnockoutTotalTripleKOCumul"]);
    if (config["KnockoutTotalHeavyBlockCumul"].is_number_unsigned())
        stat.KnockoutTotalHeavyBlockCumul = int(config["KnockoutTotalHeavyBlockCumul"]);
    if (config["KnockoutTotalAerialHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutTotalAerialHeavyHitCumul = int(config["KnockoutTotalAerialHeavyHitCumul"]);
    if (config["KnockoutTotalAerialLightHitCumul"].is_number_unsigned())
        stat.KnockoutTotalAerialLightHitCumul = int(config["KnockoutTotalAerialLightHitCumul"]);
}

void RocketStats::WriteShots(Stats& stat, json& config)
{
    config["Knockout"] = stat.Knockout;
    config["KnockoutDeath"] = stat.KnockoutDeath;
    config["KnockoutAssist"] = stat.KnockoutAssist;
    config["KnockoutDoubleKO"] = stat.KnockoutDoubleKO;
    config["KnockoutHeavyHit"] = stat.KnockoutHeavyHit;
    config["KnockoutTripleKO"] = stat.KnockoutTripleKO;
    config["KnockoutHeavyBlock"] = stat.KnockoutHeavyBlock;
    config["KnockoutAerialHeavyHit"] = stat.KnockoutAerialHeavyHit;
    config["KnockoutAerialLightHit"] = stat.KnockoutAerialLightHit;
    config["KnockoutTeam"] = stat.KnockoutTeam;
    config["KnockoutTeamDeath"] = stat.KnockoutTeamDeath;
    config["KnockoutTeamAssist"] = stat.KnockoutTeamAssist;
    config["KnockoutTeamDoubleKO"] = stat.KnockoutTeamDoubleKO;
    config["KnockoutTeamHeavyHit"] = stat.KnockoutTeamHeavyHit;
    config["KnockoutTeamTripleKO"] = stat.KnockoutTeamTripleKO;
    config["KnockoutTeamHeavyBlock"] = stat.KnockoutTeamHeavyBlock;
    config["KnockoutTeamAerialHeavyHit"] = stat.KnockoutTeamAerialHeavyHit;
    config["KnockoutTeamAerialLightHit"] = stat.KnockoutTeamAerialLightHit;
    config["KnockoutTotal"] = stat.KnockoutTotal;
    config["KnockoutTotalDeath"] = stat.KnockoutTotalDeath;
    config["KnockoutTotalAssist"] = stat.KnockoutTotalAssist;
    config["KnockoutTotalDoubleKO"] = stat.KnockoutTotalDoubleKO;
    config["KnockoutTotalHeavyHit"] = stat.KnockoutTotalHeavyHit;
    config["KnockoutTotalTripleKO"] = stat.KnockoutTotalTripleKO;
    config["KnockoutTotalHeavyBlock"] = stat.KnockoutTotalHeavyBlock;
    config["KnockoutTotalAerialHeavyHit"] = stat.KnockoutTotalAerialHeavyHit;
    config["KnockoutTotalAerialLightHit"] = stat.KnockoutTotalAerialLightHit;

    config["KnockoutCumul"] = stat.KnockoutCumul;
    config["KnockoutDeathCumul"] = stat.KnockoutDeathCumul;
    config["KnockoutAssistCumul"] = stat.KnockoutAssistCumul;
    config["KnockoutDoubleKOCumul"] = stat.KnockoutDoubleKOCumul;
    config["KnockoutHeavyHitCumul"] = stat.KnockoutHeavyHitCumul;
    config["KnockoutTripleKOCumul"] = stat.KnockoutTripleKOCumul;
    config["KnockoutHeavyBlockCumul"] = stat.KnockoutHeavyBlockCumul;
    config["KnockoutAerialHeavyHitCumul"] = stat.KnockoutAerialHeavyHitCumul;
    config["KnockoutAerialLightHitCumul"] = stat.KnockoutAerialLightHitCumul;
    config["KnockoutTeamCumul"] = stat.KnockoutTeamCumul;
    config["KnockoutTeamDeathCumul"] = stat.KnockoutTeamDeathCumul;
    config["KnockoutTeamAssistCumul"] = stat.KnockoutTeamAssistCumul;
    config["KnockoutTeamDoubleKOCumul"] = stat.KnockoutTeamDoubleKOCumul;
    config["KnockoutTeamHeavyHitCumul"] = stat.KnockoutTeamHeavyHitCumul;
    config["KnockoutTeamTripleKOCumul"] = stat.KnockoutTeamTripleKOCumul;
    config["KnockoutTeamHeavyBlockCumul"] = stat.KnockoutTeamHeavyBlockCumul;
    config["KnockoutTeamAerialHeavyHitCumul"] = stat.KnockoutTeamAerialHeavyHitCumul;
    config["KnockoutTeamAerialLightHitCumul"] = stat.KnockoutTeamAerialLightHitCumul;
    config["KnockoutTotalCumul"] = stat.KnockoutTotalCumul;
    config["KnockoutTotalDeathCumul"] = stat.KnockoutTotalDeathCumul;
    config["KnockoutTotalAssistCumul"] = stat.KnockoutTotalAssistCumul;
    config["KnockoutTotalDoubleKOCumul"] = stat.KnockoutTotalDoubleKOCumul;
    config["KnockoutTotalHeavyHitCumul"] = stat.KnockoutTotalHeavyHitCumul;
    config["KnockoutTotalTripleKOCumul"] = stat.KnockoutTotalTripleKOCumul;
    config["KnockoutTotalHeavyBlockCumul"] = stat.KnockoutTotalHeavyBlockCumul;
    config["KnockoutTotalAerialHeavyHitCumul"] = stat.KnockoutTotalAerialHeavyHitCumul;
    config["KnockoutTotalAerialLightHitCumul"] = stat.KnockoutTotalAerialLightHitCumul;
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