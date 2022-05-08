#include "../RocketStats.h"

void RocketStats::ReadSaves(Stats& stat, json& config)
{
    if (config["Save"].is_number_unsigned())
        stat.Save = int(config["Save"]);
    if (config["EpicSave"].is_number_unsigned())
        stat.EpicSave = int(config["EpicSave"]);
    if (config["TeamSave"].is_number_unsigned())
        stat.TeamSave = int(config["TeamSave"]);
    if (config["TeamEpicSave"].is_number_unsigned())
        stat.TeamEpicSave = int(config["TeamEpicSave"]);
    if (config["TotalSave"].is_number_unsigned())
        stat.TotalSave = int(config["TotalSave"]);
    if (config["TotalEpicSave"].is_number_unsigned())
        stat.TotalEpicSave = int(config["TotalEpicSave"]);

    if (config["SaveCumul"].is_number_unsigned())
        stat.SaveCumul = int(config["SaveCumul"]);
    if (config["EpicSaveCumul"].is_number_unsigned())
        stat.EpicSaveCumul = int(config["EpicSaveCumul"]);
    if (config["TeamSaveCumul"].is_number_unsigned())
        stat.TeamSaveCumul = int(config["TeamSaveCumul"]);
    if (config["TeamEpicSaveCumul"].is_number_unsigned())
        stat.TeamEpicSaveCumul = int(config["TeamEpicSaveCumul"]);
    if (config["TotalSaveCumul"].is_number_unsigned())
        stat.TotalSaveCumul = int(config["TotalSaveCumul"]);
    if (config["TotalEpicSaveCumul"].is_number_unsigned())
        stat.TotalEpicSaveCumul = int(config["TotalEpicSaveCumul"]);
}

void RocketStats::WriteSaves(Stats& stat, json& config, bool more)
{
    config["Save"] = stat.Save;
    config["EpicSave"] = stat.EpicSave;
    config["Savior"] = stat.Savior;
    config["TeamSave"] = stat.TeamSave;
    config["TeamEpicSave"] = stat.TeamEpicSave;
    config["TeamSavior"] = stat.TeamSavior;
    config["TotalSave"] = stat.TotalSave;
    config["TotalEpicSave"] = stat.TotalEpicSave;
    config["TotalSavior"] = stat.TotalSavior;

    config["SaveCumul"] = stat.SaveCumul;
    config["EpicSaveCumul"] = stat.EpicSaveCumul;
    config["SaviorCumul"] = stat.SaviorCumul;
    config["TeamSaveCumul"] = stat.TeamSaveCumul;
    config["TeamEpicSaveCumul"] = stat.TeamEpicSaveCumul;
    config["TeamSaviorCumul"] = stat.TeamSaviorCumul;
    config["TotalSaveCumul"] = stat.TotalSaveCumul;
    config["TotalEpicSaveCumul"] = stat.TotalEpicSaveCumul;
    config["TotalSaviorCumul"] = stat.TotalSaviorCumul;
}

void RocketStats::ReplaceSaves(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["Save"] = VarSavesSave();
    vars["EpicSave"] = VarSavesEpicSave();
    vars["TeamSave"] = VarSavesTeamSave();
    vars["TeamEpicSave"] = VarSavesTeamEpicSave();
    vars["TotalSave"] = VarSavesTotalSave();
    vars["TotalEpicSave"] = VarSavesTotalEpicSave();

    /// Match
    vars["SaveMatch"] = VarSavesSaveMatch();
    vars["EpicSaveMatch"] = VarSavesEpicSaveMatch();
    vars["TeamSaveMatch"] = VarSavesTeamSaveMatch();
    vars["TeamEpicSaveMatch"] = VarSavesTeamEpicSaveMatch();
    vars["TotalSaveMatch"] = VarSavesTotalSaveMatch();
    vars["TotalEpicSaveMatch"] = VarSavesTotalEpicSaveMatch();

    /// Cumul
    vars["SaveCumul"] = VarSavesSaveCumul();
    vars["EpicSaveCumul"] = VarSavesEpicSaveCumul();
    vars["TeamSaveCumul"] = VarSavesTeamSaveCumul();
    vars["TeamEpicSaveCumul"] = VarSavesTeamEpicSaveCumul();
    vars["TotalSaveCumul"] = VarSavesTotalSaveCumul();
    vars["TotalEpicSaveCumul"] = VarSavesTotalEpicSaveCumul();
}

void RocketStats::SessionSaves(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.Save += stats[index].Save;
        stat.EpicSave += stats[index].EpicSave;
        stat.TeamSave += stats[index].TeamSave;
        stat.TeamEpicSave += stats[index].TeamEpicSave;
        stat.TotalSave += stats[index].TotalSave;
        stat.TotalEpicSave += stats[index].TotalEpicSave;
    }
    else
    {
        session.SaveCumul = stat.Save;
        session.EpicSaveCumul = stat.EpicSave;
        session.TeamSaveCumul = stat.TeamSave;
        session.TeamEpicSaveCumul = stat.TeamEpicSave;
        session.TotalSaveCumul = stat.TotalSave;
        session.TotalEpicSaveCumul = stat.TotalEpicSave;
    }
}

#pragma region Base
std::string RocketStats::VarSavesSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Save)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_Save.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().EpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSave.txt", tmp);

    return tmp;
}

#pragma region BaseTeam
std::string RocketStats::VarSavesTeamSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSave.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region BaseTotal
std::string RocketStats::VarSavesTotalSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSave.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSave(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSave.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Match
std::string RocketStats::VarSavesSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Save)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.EpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSaveMatch.txt", tmp);

    return tmp;
}

#pragma region MatchTeam
std::string RocketStats::VarSavesTeamSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSaveMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region MatchTotal
std::string RocketStats::VarSavesTotalSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaveMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSaveMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalEpicSave)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSaveMatch.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion

#pragma region Cumul
std::string RocketStats::VarSavesSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_SaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().EpicSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_EpicSaveCumul.txt", tmp);

    return tmp;
}

#pragma region CumulTeam
std::string RocketStats::VarSavesTeamSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTeamEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamEpicSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TeamEpicSaveCumul.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region CumulTotal
std::string RocketStats::VarSavesTotalSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalSaveCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarSavesTotalEpicSaveCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_saves ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalEpicSaveCumul)));

    if (write && (force || (rs_in_file && rs_file_saves)))
        WriteInFile("RocketStats_TotalEpicSaveCumul.txt", tmp);

    return tmp;
}
#pragma endregion
#pragma endregion