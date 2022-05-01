#include "../RocketStats.h"

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