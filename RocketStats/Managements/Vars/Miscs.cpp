#include "../RocketStats.h"

void RocketStats::ReadMiscs(Stats& stat, json& config)
{
    if (config["Death"].is_number_unsigned())
        stat.Death = int(config["Death"]);
    if (config["Savior"].is_number_unsigned())
        stat.Savior = int(config["Savior"]);
    if (config["LowFive"].is_number_unsigned())
        stat.LowFive = int(config["LowFive"]);
    if (config["HatTrick"].is_number_unsigned())
        stat.HatTrick = int(config["HatTrick"]);
    if (config["HighFive"].is_number_unsigned())
        stat.HighFive = int(config["HighFive"]);
    if (config["Playmaker"].is_number_unsigned())
        stat.Playmaker = int(config["Playmaker"]);
    if (config["FirstTouch"].is_number_unsigned())
        stat.FirstTouch = int(config["FirstTouch"]);
    if (config["Demolitions"].is_number_unsigned())
        stat.Demolitions = int(config["Demolitions"]);
    if (config["TeamDeath"].is_number_unsigned())
        stat.TeamDeath = int(config["TeamDeath"]);
    if (config["TeamSavior"].is_number_unsigned())
        stat.TeamSavior = int(config["TeamSavior"]);
    if (config["TeamLowFive"].is_number_unsigned())
        stat.TeamLowFive = int(config["TeamLowFive"]);
    if (config["TeamHatTrick"].is_number_unsigned())
        stat.TeamHatTrick = int(config["TeamHatTrick"]);
    if (config["TeamHighFive"].is_number_unsigned())
        stat.TeamHighFive = int(config["TeamHighFive"]);
    if (config["TeamPlaymaker"].is_number_unsigned())
        stat.TeamPlaymaker = int(config["TeamPlaymaker"]);
    if (config["TeamDemolitions"].is_number_unsigned())
        stat.TeamDemolitions = int(config["TeamDemolitions"]);
    if (config["TotalDeath"].is_number_unsigned())
        stat.TotalDeath = int(config["TotalDeath"]);
    if (config["TotalSavior"].is_number_unsigned())
        stat.TotalSavior = int(config["TotalSavior"]);
    if (config["TotalLowFive"].is_number_unsigned())
        stat.TotalLowFive = int(config["TotalLowFive"]);
    if (config["TotalHatTrick"].is_number_unsigned())
        stat.TotalHatTrick = int(config["TotalHatTrick"]);
    if (config["TotalHighFive"].is_number_unsigned())
        stat.TotalHighFive = int(config["TotalHighFive"]);
    if (config["TotalPlaymaker"].is_number_unsigned())
        stat.TotalPlaymaker = int(config["TotalPlaymaker"]);
    if (config["TotalDemolitions"].is_number_unsigned())
        stat.TotalDemolitions = int(config["TotalDemolitions"]);

    if (config["DeathCumul"].is_number_unsigned())
        stat.DeathCumul = int(config["DeathCumul"]);
    if (config["SaviorCumul"].is_number_unsigned())
        stat.SaviorCumul = int(config["SaviorCumul"]);
    if (config["LowFiveCumul"].is_number_unsigned())
        stat.LowFiveCumul = int(config["LowFiveCumul"]);
    if (config["HatTrickCumul"].is_number_unsigned())
        stat.HatTrickCumul = int(config["HatTrickCumul"]);
    if (config["HighFiveCumul"].is_number_unsigned())
        stat.HighFiveCumul = int(config["HighFiveCumul"]);
    if (config["PlaymakerCumul"].is_number_unsigned())
        stat.PlaymakerCumul = int(config["PlaymakerCumul"]);
    if (config["FirstTouchCumul"].is_number_unsigned())
        stat.FirstTouchCumul = int(config["FirstTouchCumul"]);
    if (config["DemolitionsCumul"].is_number_unsigned())
        stat.DemolitionsCumul = int(config["DemolitionsCumul"]);
    if (config["TeamDeathCumul"].is_number_unsigned())
        stat.TeamDeathCumul = int(config["TeamDeathCumul"]);
    if (config["TeamSaviorCumul"].is_number_unsigned())
        stat.TeamSaviorCumul = int(config["TeamSaviorCumul"]);
    if (config["TeamLowFiveCumul"].is_number_unsigned())
        stat.TeamLowFiveCumul = int(config["TeamLowFiveCumul"]);
    if (config["TeamHatTrickCumul"].is_number_unsigned())
        stat.TeamHatTrickCumul = int(config["TeamHatTrickCumul"]);
    if (config["TeamHighFiveCumul"].is_number_unsigned())
        stat.TeamHighFiveCumul = int(config["TeamHighFiveCumul"]);
    if (config["TeamPlaymakerCumul"].is_number_unsigned())
        stat.TeamPlaymakerCumul = int(config["TeamPlaymakerCumul"]);
    if (config["TeamDemolitionsCumul"].is_number_unsigned())
        stat.TeamDemolitionsCumul = int(config["TeamDemolitionsCumul"]);
    if (config["TotalDeathCumul"].is_number_unsigned())
        stat.TotalDeathCumul = int(config["TotalDeathCumul"]);
    if (config["TotalSaviorCumul"].is_number_unsigned())
        stat.TotalSaviorCumul = int(config["TotalSaviorCumul"]);
    if (config["TotalLowFiveCumul"].is_number_unsigned())
        stat.TotalLowFiveCumul = int(config["TotalLowFiveCumul"]);
    if (config["TotalHatTrickCumul"].is_number_unsigned())
        stat.TotalHatTrickCumul = int(config["TotalHatTrickCumul"]);
    if (config["TotalHighFiveCumul"].is_number_unsigned())
        stat.TotalHighFiveCumul = int(config["TotalHighFiveCumul"]);
    if (config["TotalPlaymakerCumul"].is_number_unsigned())
        stat.TotalPlaymakerCumul = int(config["TotalPlaymakerCumul"]);
    if (config["TotalDemolitionsCumul"].is_number_unsigned())
        stat.TotalDemolitionsCumul = int(config["TotalDemolitionsCumul"]);
}

void RocketStats::WriteMiscs(Stats& stat, json& config)
{
    config["Death"] = stat.Death;
    config["Savior"] = stat.Savior;
    config["LowFive"] = stat.LowFive;
    config["HatTrick"] = stat.HatTrick;
    config["HighFive"] = stat.HighFive;
    config["Playmaker"] = stat.Playmaker;
    config["FirstTouch"] = stat.FirstTouch;
    config["Demolitions"] = stat.Demolitions;
    config["TeamDeath"] = stat.TeamDeath;
    config["TeamSavior"] = stat.TeamSavior;
    config["TeamLowFive"] = stat.TeamLowFive;
    config["TeamHatTrick"] = stat.TeamHatTrick;
    config["TeamHighFive"] = stat.TeamHighFive;
    config["TeamPlaymaker"] = stat.TeamPlaymaker;
    config["TeamDemolitions"] = stat.TeamDemolitions;
    config["TotalDeath"] = stat.TotalDeath;
    config["TotalSavior"] = stat.TotalSavior;
    config["TotalLowFive"] = stat.TotalLowFive;
    config["TotalHatTrick"] = stat.TotalHatTrick;
    config["TotalHighFive"] = stat.TotalHighFive;
    config["TotalPlaymaker"] = stat.TotalPlaymaker;
    config["TotalDemolitions"] = stat.TotalDemolitions;

    config["DeathCumul"] = stat.DeathCumul;
    config["SaviorCumul"] = stat.SaviorCumul;
    config["LowFiveCumul"] = stat.LowFiveCumul;
    config["HatTrickCumul"] = stat.HatTrickCumul;
    config["HighFiveCumul"] = stat.HighFiveCumul;
    config["PlaymakerCumul"] = stat.PlaymakerCumul;
    config["FirstTouchCumul"] = stat.FirstTouchCumul;
    config["DemolitionsCumul"] = stat.DemolitionsCumul;
    config["TeamDeathCumul"] = stat.TeamDeathCumul;
    config["TeamSaviorCumul"] = stat.TeamSaviorCumul;
    config["TeamLowFiveCumul"] = stat.TeamLowFiveCumul;
    config["TeamHatTrickCumul"] = stat.TeamHatTrickCumul;
    config["TeamHighFiveCumul"] = stat.TeamHighFiveCumul;
    config["TeamPlaymakerCumul"] = stat.TeamPlaymakerCumul;
    config["TeamDemolitionsCumul"] = stat.TeamDemolitionsCumul;
    config["TotalDeathCumul"] = stat.TotalDeathCumul;
    config["TotalSaviorCumul"] = stat.TotalSaviorCumul;
    config["TotalLowFiveCumul"] = stat.TotalLowFiveCumul;
    config["TotalHatTrickCumul"] = stat.TotalHatTrickCumul;
    config["TotalHighFiveCumul"] = stat.TotalHighFiveCumul;
    config["TotalPlaymakerCumul"] = stat.TotalPlaymakerCumul;
    config["TotalDemolitionsCumul"] = stat.TotalDemolitionsCumul;
}

void RocketStats::ReplaceMiscs(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["Death"] = VarMiscsDeath();
    vars["Savior"] = VarMiscsSavior();
    vars["LowFive"] = VarMiscsLowFive();
    vars["HatTrick"] = VarMiscsHatTrick();
    vars["HighFive"] = VarMiscsHighFive();
    vars["Playmaker"] = VarMiscsPlaymaker();
    vars["FirstTouch"] = VarMiscsFirstTouch();
    vars["Demolitions"] = VarMiscsDemolitions();
    vars["TeamDeath"] = VarMiscsTeamDeath();
    vars["TeamSavior"] = VarMiscsTeamSavior();
    vars["TeamLowFive"] = VarMiscsTeamLowFive();
    vars["TeamHatTrick"] = VarMiscsTeamHatTrick();
    vars["TeamHighFive"] = VarMiscsTeamHighFive();
    vars["TeamPlaymaker"] = VarMiscsTeamPlaymaker();
    vars["TeamDemolitions"] = VarMiscsTeamDemolitions();
    vars["TotalDeath"] = VarMiscsTotalDeath();
    vars["TotalSavior"] = VarMiscsTotalSavior();
    vars["TotalLowFive"] = VarMiscsTotalLowFive();
    vars["TotalHatTrick"] = VarMiscsTotalHatTrick();
    vars["TotalHighFive"] = VarMiscsTotalHighFive();
    vars["TotalPlaymaker"] = VarMiscsTotalPlaymaker();
    vars["TotalDemolitions"] = VarMiscsTotalDemolitions();

    /// Match
    vars["DeathMatch"] = VarMiscsDeathMatch();
    vars["SaviorMatch"] = VarMiscsSaviorMatch();
    vars["LowFiveMatch"] = VarMiscsLowFiveMatch();
    vars["HatTrickMatch"] = VarMiscsHatTrickMatch();
    vars["HighFiveMatch"] = VarMiscsHighFiveMatch();
    vars["PlaymakerMatch"] = VarMiscsPlaymakerMatch();
    vars["FirstTouchMatch"] = VarMiscsFirstTouchMatch();
    vars["DemolitionsMatch"] = VarMiscsDemolitionsMatch();
    vars["TeamDeathMatch"] = VarMiscsTeamDeathMatch();
    vars["TeamSaviorMatch"] = VarMiscsTeamSaviorMatch();
    vars["TeamLowFiveMatch"] = VarMiscsTeamLowFiveMatch();
    vars["TeamHatTrickMatch"] = VarMiscsTeamHatTrickMatch();
    vars["TeamHighFiveMatch"] = VarMiscsTeamHighFiveMatch();
    vars["TeamPlaymakerMatch"] = VarMiscsTeamPlaymakerMatch();
    vars["TeamDemolitionsMatch"] = VarMiscsTeamDemolitionsMatch();
    vars["TotalDeathMatch"] = VarMiscsTotalDeathMatch();
    vars["TotalSaviorMatch"] = VarMiscsTotalSaviorMatch();
    vars["TotalLowFiveMatch"] = VarMiscsTotalLowFiveMatch();
    vars["TotalHatTrickMatch"] = VarMiscsTotalHatTrickMatch();
    vars["TotalHighFiveMatch"] = VarMiscsTotalHighFiveMatch();
    vars["TotalPlaymakerMatch"] = VarMiscsTotalPlaymakerMatch();
    vars["TotalDemolitionsMatch"] = VarMiscsTotalDemolitionsMatch();

    /// Cumul
    vars["DeathCumul"] = VarMiscsDeathCumul();
    vars["SaviorCumul"] = VarMiscsSaviorCumul();
    vars["LowFiveCumul"] = VarMiscsLowFiveCumul();
    vars["HatTrickCumul"] = VarMiscsHatTrickCumul();
    vars["HighFiveCumul"] = VarMiscsHighFiveCumul();
    vars["PlaymakerCumul"] = VarMiscsPlaymakerCumul();
    vars["FirstTouchCumul"] = VarMiscsFirstTouchCumul();
    vars["DemolitionsCumul"] = VarMiscsDemolitionsCumul();
    vars["TeamDeathCumul"] = VarMiscsTeamDeathCumul();
    vars["TeamSaviorCumul"] = VarMiscsTeamSaviorCumul();
    vars["TeamLowFiveCumul"] = VarMiscsTeamLowFiveCumul();
    vars["TeamHatTrickCumul"] = VarMiscsTeamHatTrickCumul();
    vars["TeamHighFiveCumul"] = VarMiscsTeamHighFiveCumul();
    vars["TeamPlaymakerCumul"] = VarMiscsTeamPlaymakerCumul();
    vars["TeamDemolitionsCumul"] = VarMiscsTeamDemolitionsCumul();
    vars["TotalDeathCumul"] = VarMiscsTotalDeathCumul();
    vars["TotalSaviorCumul"] = VarMiscsTotalSaviorCumul();
    vars["TotalLowFiveCumul"] = VarMiscsTotalLowFiveCumul();
    vars["TotalHatTrickCumul"] = VarMiscsTotalHatTrickCumul();
    vars["TotalHighFiveCumul"] = VarMiscsTotalHighFiveCumul();
    vars["TotalPlaymakerCumul"] = VarMiscsTotalPlaymakerCumul();
    vars["TotalDemolitionsCumul"] = VarMiscsTotalDemolitionsCumul();
}

void RocketStats::SessionMiscs(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.Death += stats[index].Death;
        stat.Savior += stats[index].Savior;
        stat.LowFive += stats[index].LowFive;
        stat.HatTrick += stats[index].HatTrick;
        stat.HighFive += stats[index].HighFive;
        stat.Playmaker += stats[index].Playmaker;
        stat.FirstTouch += stats[index].FirstTouch;
        stat.Demolitions += stats[index].Demolitions;
        stat.TeamDeath += stats[index].TeamDeath;
        stat.TeamSavior += stats[index].TeamSavior;
        stat.TeamLowFive += stats[index].TeamLowFive;
        stat.TeamHatTrick += stats[index].TeamHatTrick;
        stat.TeamHighFive += stats[index].TeamHighFive;
        stat.TeamPlaymaker += stats[index].TeamPlaymaker;
        stat.TeamDemolitions += stats[index].TeamDemolitions;
        stat.TotalDeath += stats[index].TotalDeath;
        stat.TotalSavior += stats[index].TotalSavior;
        stat.TotalLowFive += stats[index].TotalLowFive;
        stat.TotalHatTrick += stats[index].TotalHatTrick;
        stat.TotalHighFive += stats[index].TotalHighFive;
        stat.TotalPlaymaker += stats[index].TotalPlaymaker;
        stat.TotalDemolitions += stats[index].TotalDemolitions;
    }
    else
    {
        session.DeathCumul = stat.Death;
        session.SaviorCumul = stat.Savior;
        session.LowFiveCumul = stat.LowFive;
        session.HatTrickCumul = stat.HatTrick;
        session.HighFiveCumul = stat.HighFive;
        session.PlaymakerCumul = stat.Playmaker;
        session.FirstTouchCumul = stat.FirstTouch;
        session.DemolitionsCumul = stat.Demolitions;
        session.TeamDeathCumul = stat.TeamDeath;
        session.TeamSaviorCumul = stat.TeamSavior;
        session.TeamLowFiveCumul = stat.TeamLowFive;
        session.TeamHatTrickCumul = stat.TeamHatTrick;
        session.TeamHighFiveCumul = stat.TeamHighFive;
        session.TeamPlaymakerCumul = stat.TeamPlaymaker;
        session.TeamDemolitionsCumul = stat.TeamDemolitions;
        session.TotalDeathCumul = stat.TotalDeath;
        session.TotalSaviorCumul = stat.TotalSavior;
        session.TotalLowFiveCumul = stat.TotalLowFive;
        session.TotalHatTrickCumul = stat.TotalHatTrick;
        session.TotalHighFiveCumul = stat.TotalHighFive;
        session.TotalPlaymakerCumul = stat.TotalPlaymaker;
        session.TotalDemolitionsCumul = stat.TotalDemolitions;
    }
}

#pragma region Base
std::string RocketStats::VarMiscsDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Death)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_Death.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Savior)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_Savior.txt", tmp);

    return tmp;
}

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

std::string RocketStats::VarMiscsPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Playmaker)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_Playmaker.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsFirstTouch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FirstTouch)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_FirstTouch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsDemolitions(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Demolitions)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_Demolitions.txt", tmp);

    return tmp;
}

#pragma region BaseTeam
std::string RocketStats::VarMiscsTeamDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamDeath)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamSavior.txt", tmp);

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

std::string RocketStats::VarMiscsTeamPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamPlaymaker.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamDemolitions(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamDemolitions)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamDemolitions.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region BaseTotal
std::string RocketStats::VarMiscsTotalDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalDeath)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalSavior.txt", tmp);

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

std::string RocketStats::VarMiscsTotalPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalPlaymaker.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalDemolitions(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalDemolitions)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalDemolitions.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Match
std::string RocketStats::VarMiscsDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Death)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_DeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Savior)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_SaviorMatch.txt", tmp);

    return tmp;
}

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

std::string RocketStats::VarMiscsPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Playmaker)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_PlaymakerMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsFirstTouchMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.FirstTouch)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_FirstTouchMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsDemolitionsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Demolitions)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_DemolitionsMatch.txt", tmp);

    return tmp;
}

#pragma region MatchTeam
std::string RocketStats::VarMiscsTeamDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamDeath)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamDeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamSaviorMatch.txt", tmp);

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

std::string RocketStats::VarMiscsTeamPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamPlaymakerMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamDemolitionsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamDemolitions)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamDemolitionsMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region MatchTotal
std::string RocketStats::VarMiscsTotalDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalDeath)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalDeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalSaviorMatch.txt", tmp);

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

std::string RocketStats::VarMiscsTotalPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalPlaymakerMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalDemolitionsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalDemolitions)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalDemolitionsMatch.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Cumul
std::string RocketStats::VarMiscsDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().DeathCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_DeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_SaviorCumul.txt", tmp);

    return tmp;
}

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

std::string RocketStats::VarMiscsPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_PlaymakerCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsFirstTouchCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().FirstTouchCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_FirstTouchCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsDemolitionsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().DemolitionsCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_DemolitionsCumul.txt", tmp);

    return tmp;
}

#pragma region CumulTeam
std::string RocketStats::VarMiscsTeamDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamSaviorCumul.txt", tmp);

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

std::string RocketStats::VarMiscsTeamPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamPlaymakerCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTeamDemolitionsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamDemolitionsCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamDemolitionsCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region CumulTotal
std::string RocketStats::VarMiscsTotalDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalSaviorCumul.txt", tmp);

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

std::string RocketStats::VarMiscsTotalPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalPlaymakerCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarMiscsTotalDemolitionsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalDemolitionsCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalDemolitionsCumul.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion