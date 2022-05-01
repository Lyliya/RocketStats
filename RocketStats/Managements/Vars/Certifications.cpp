#include "../RocketStats.h"

#pragma region Base
std::string RocketStats::VarCertificationsMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_MVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Savior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_Savior.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Playmaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_Playmaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTeamMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamMVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamSavior.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamPlaymaker.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTotalMVP(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalMVP.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalSavior(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalSavior.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalPlaymaker(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalPlaymaker.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Match
std::string RocketStats::VarCertificationsMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.MVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_MVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Savior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_SaviorMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Playmaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_PlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTeamMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamMVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamSaviorMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TeamPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamPlaymakerMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTotalMVPMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalMVP)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalMVPMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalSaviorMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalSavior)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalSaviorMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalPlaymakerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.TotalPlaymaker)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalPlaymakerMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Cumul
std::string RocketStats::VarCertificationsMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().MVPCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_MVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().SaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_SaviorCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().PlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_PlaymakerCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTeamMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TeamMVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamSaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamSaviorCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTeamPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TeamPlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TeamPlaymakerCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarCertificationsTotalMVPCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_miscs ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalMVPCumul)));

    if (write && (force || (rs_in_file && rs_file_miscs)))
        WriteInFile("RocketStats_TotalMVPCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalSaviorCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalSaviorCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalSaviorCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarCertificationsTotalPlaymakerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_certifications ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().TotalPlaymakerCumul)));

    if (write && (force || (rs_in_file && rs_file_certifications)))
        WriteInFile("RocketStats_TotalPlaymakerCumul.txt", tmp);

    return tmp;
}
#pragma endregion