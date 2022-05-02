#include "../RocketStats.h"

void RocketStats::ReadCertifications(Stats& stat, json& config)
{
    if (config["MVP"].is_number_unsigned())
        stat.MVP = int(config["MVP"]);
    if (config["Savior"].is_number_unsigned())
        stat.Savior = int(config["Savior"]);
    if (config["Playmaker"].is_number_unsigned())
        stat.Playmaker = int(config["Playmaker"]);
    if (config["TeamMVP"].is_number_unsigned())
        stat.TeamMVP = int(config["TeamMVP"]);
    if (config["TeamSavior"].is_number_unsigned())
        stat.TeamSavior = int(config["TeamSavior"]);
    if (config["TeamPlaymaker"].is_number_unsigned())
        stat.TeamPlaymaker = int(config["TeamPlaymaker"]);
    if (config["TotalMVP"].is_number_unsigned())
        stat.TotalMVP = int(config["TotalMVP"]);
    if (config["TotalSavior"].is_number_unsigned())
        stat.TotalSavior = int(config["TotalSavior"]);
    if (config["TotalPlaymaker"].is_number_unsigned())
        stat.TotalPlaymaker = int(config["TotalPlaymaker"]);

    if (config["SaviorCumul"].is_number_unsigned())
        stat.SaviorCumul = int(config["SaviorCumul"]);
    if (config["MVPCumul"].is_number_unsigned())
        stat.MVPCumul = int(config["MVPCumul"]);
    if (config["PlaymakerCumul"].is_number_unsigned())
        stat.PlaymakerCumul = int(config["PlaymakerCumul"]);
    if (config["TeamMVPCumul"].is_number_unsigned())
        stat.TeamMVPCumul = int(config["TeamMVPCumul"]);
    if (config["TeamSaviorCumul"].is_number_unsigned())
        stat.TeamSaviorCumul = int(config["TeamSaviorCumul"]);
    if (config["TeamPlaymakerCumul"].is_number_unsigned())
        stat.TeamPlaymakerCumul = int(config["TeamPlaymakerCumul"]);
    if (config["TotalMVPCumul"].is_number_unsigned())
        stat.TotalMVPCumul = int(config["TotalMVPCumul"]);
    if (config["TotalSaviorCumul"].is_number_unsigned())
        stat.TotalSaviorCumul = int(config["TotalSaviorCumul"]);
    if (config["TotalPlaymakerCumul"].is_number_unsigned())
        stat.TotalPlaymakerCumul = int(config["TotalPlaymakerCumul"]);
}

void RocketStats::WriteCertifications(Stats& stat, json& config)
{
    config["MVP"] = stat.MVP;
    config["Savior"] = stat.Savior;
    config["Playmaker"] = stat.Playmaker;
    config["TeamMVP"] = stat.TeamMVP;
    config["TeamSavior"] = stat.TeamSavior;
    config["TeamPlaymaker"] = stat.TeamPlaymaker;
    config["TotalMVP"] = stat.TotalMVP;
    config["TotalSavior"] = stat.TotalSavior;
    config["TotalPlaymaker"] = stat.TotalPlaymaker;

    config["SaviorCumul"] = stat.SaviorCumul;
    config["MVPCumul"] = stat.MVPCumul;
    config["PlaymakerCumul"] = stat.PlaymakerCumul;
    config["TeamMVPCumul"] = stat.TeamMVPCumul;
    config["TeamSaviorCumul"] = stat.TeamSaviorCumul;
    config["TeamPlaymakerCumul"] = stat.TeamPlaymakerCumul;
    config["TotalMVPCumul"] = stat.TotalMVPCumul;
    config["TotalSaviorCumul"] = stat.TotalSaviorCumul;
    config["TotalPlaymakerCumul"] = stat.TotalPlaymakerCumul;
}

void RocketStats::ReplaceCertifications(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["MVP"] = VarCertificationsMVP();
    vars["Savior"] = VarCertificationsSavior();
    vars["Playmaker"] = VarCertificationsPlaymaker();
    vars["TeamMVP"] = VarCertificationsTeamMVP();
    vars["TeamSavior"] = VarCertificationsTeamSavior();
    vars["TeamPlaymaker"] = VarCertificationsTeamPlaymaker();
    vars["TotalMVP"] = VarCertificationsTotalMVP();
    vars["TotalSavior"] = VarCertificationsTotalSavior();
    vars["TotalPlaymaker"] = VarCertificationsTotalPlaymaker();

    /// Match
    vars["MVPMatch"] = VarCertificationsMVPMatch();
    vars["SaviorMatch"] = VarCertificationsSaviorMatch();
    vars["PlaymakerMatch"] = VarCertificationsPlaymakerMatch();
    vars["TeamMVPMatch"] = VarCertificationsTeamMVPMatch();
    vars["TeamSaviorMatch"] = VarCertificationsTeamSaviorMatch();
    vars["TeamPlaymakerMatch"] = VarCertificationsTeamPlaymakerMatch();
    vars["TotalMVPMatch"] = VarCertificationsTotalMVPMatch();
    vars["TotalSaviorMatch"] = VarCertificationsTotalSaviorMatch();
    vars["TotalPlaymakerMatch"] = VarCertificationsTotalPlaymakerMatch();

    /// Cumul
    vars["MVPCumul"] = VarCertificationsMVPCumul();
    vars["SaviorCumul"] = VarCertificationsSaviorCumul();
    vars["PlaymakerCumul"] = VarCertificationsPlaymakerCumul();
    vars["TeamMVPCumul"] = VarCertificationsTeamMVPCumul();
    vars["TeamSaviorCumul"] = VarCertificationsTeamSaviorCumul();
    vars["TeamPlaymakerCumul"] = VarCertificationsTeamPlaymakerCumul();
    vars["TotalMVPCumul"] = VarCertificationsTotalMVPCumul();
    vars["TotalSaviorCumul"] = VarCertificationsTotalSaviorCumul();
    vars["TotalPlaymakerCumul"] = VarCertificationsTotalPlaymakerCumul();
}

void RocketStats::SessionCertifications(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.MVP += stats[index].MVP;
        stat.Savior += stats[index].Savior;
        stat.Playmaker += stats[index].Playmaker;
        stat.TeamMVP += stats[index].TeamMVP;
        stat.TeamSavior += stats[index].TeamSavior;
        stat.TeamPlaymaker += stats[index].TeamPlaymaker;
        stat.TotalMVP += stats[index].TotalMVP;
        stat.TotalSavior += stats[index].TotalSavior;
        stat.TotalPlaymaker += stats[index].TotalPlaymaker;
    }
    else
    {
        session.MVPCumul = stat.MVP;
        session.SaviorCumul = stat.Savior;
        session.PlaymakerCumul = stat.Playmaker;
        session.TeamMVPCumul = stat.TeamMVP;
        session.TeamSaviorCumul = stat.TeamSavior;
        session.TeamPlaymakerCumul = stat.TeamPlaymaker;
        session.TotalMVPCumul = stat.TotalMVP;
        session.TotalSaviorCumul = stat.TotalSavior;
        session.TotalPlaymakerCumul = stat.TotalPlaymaker;
    }
}

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