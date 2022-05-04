#include "../RocketStats.h"

void RocketStats::ReadKnockout(Stats& stat, json& config)
{
    if (config["KnockoutDeath"].is_number_unsigned())
        stat.KnockoutDeath = int(config["KnockoutDeath"]);
    if (config["KnockoutAssist"].is_number_unsigned())
        stat.KnockoutAssist = int(config["KnockoutAssist"]);
    if (config["KnockoutThrown"].is_number_unsigned())
        stat.KnockoutThrown = int(config["KnockoutThrown"]);
    if (config["KnockoutWinner"].is_number_unsigned())
        stat.KnockoutWinner = int(config["KnockoutWinner"]);
    if (config["KnockoutGrabbed"].is_number_unsigned())
        stat.KnockoutGrabbed = int(config["KnockoutGrabbed"]);
    if (config["KnockoutDoubleKO"].is_number_unsigned())
        stat.KnockoutDoubleKO = int(config["KnockoutDoubleKO"]);
    if (config["KnockoutHeavyHit"].is_number_unsigned())
        stat.KnockoutHeavyHit = int(config["KnockoutHeavyHit"]);
    if (config["KnockoutHitTaken"].is_number_unsigned())
        stat.KnockoutHitTaken = int(config["KnockoutHitTaken"]);
    if (config["KnockoutLightHit"].is_number_unsigned())
        stat.KnockoutLightHit = int(config["KnockoutLightHit"]);
    if (config["KnockoutTripleKO"].is_number_unsigned())
        stat.KnockoutTripleKO = int(config["KnockoutTripleKO"]);
    if (config["KnockoutBlockTaken"].is_number_unsigned())
        stat.KnockoutBlockTaken = int(config["KnockoutBlockTaken"]);
    if (config["KnockoutHeavyBlock"].is_number_unsigned())
        stat.KnockoutHeavyBlock = int(config["KnockoutHeavyBlock"]);
    if (config["KnockoutLightBlock"].is_number_unsigned())
        stat.KnockoutLightBlock = int(config["KnockoutLightBlock"]);
    if (config["KnockoutDemolitions"].is_number_unsigned())
        stat.KnockoutDemolitions = int(config["KnockoutDemolitions"]);
    if (config["KnockoutPlayerThrown"].is_number_unsigned())
        stat.KnockoutPlayerThrown = int(config["KnockoutPlayerThrown"]);
    if (config["KnockoutPlayerGrabbed"].is_number_unsigned())
        stat.KnockoutPlayerGrabbed = int(config["KnockoutPlayerGrabbed"]);
    if (config["KnockoutAerialHeavyHit"].is_number_unsigned())
        stat.KnockoutAerialHeavyHit = int(config["KnockoutAerialHeavyHit"]);
    if (config["KnockoutAerialLightHit"].is_number_unsigned())
        stat.KnockoutAerialLightHit = int(config["KnockoutAerialLightHit"]);

    if (config["KnockoutDeathCumul"].is_number_unsigned())
        stat.KnockoutDeathCumul = int(config["KnockoutDeathCumul"]);
    if (config["KnockoutAssistCumul"].is_number_unsigned())
        stat.KnockoutAssistCumul = int(config["KnockoutAssistCumul"]);
    if (config["KnockoutThrownCumul"].is_number_unsigned())
        stat.KnockoutThrownCumul = int(config["KnockoutThrownCumul"]);
    if (config["KnockoutWinnerCumul"].is_number_unsigned())
        stat.KnockoutWinnerCumul = int(config["KnockoutWinnerCumul"]);
    if (config["KnockoutGrabbedCumul"].is_number_unsigned())
        stat.KnockoutGrabbedCumul = int(config["KnockoutGrabbedCumul"]);
    if (config["KnockoutDoubleKOCumul"].is_number_unsigned())
        stat.KnockoutDoubleKOCumul = int(config["KnockoutDoubleKOCumul"]);
    if (config["KnockoutHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutHeavyHitCumul = int(config["KnockoutHeavyHitCumul"]);
    if (config["KnockoutHitTakenCumul"].is_number_unsigned())
        stat.KnockoutHitTakenCumul = int(config["KnockoutHitTakenCumul"]);
    if (config["KnockoutLightHitCumul"].is_number_unsigned())
        stat.KnockoutLightHitCumul = int(config["KnockoutLightHitCumul"]);
    if (config["KnockoutTripleKOCumul"].is_number_unsigned())
        stat.KnockoutTripleKOCumul = int(config["KnockoutTripleKOCumul"]);
    if (config["KnockoutBlockTakenCumul"].is_number_unsigned())
        stat.KnockoutBlockTakenCumul = int(config["KnockoutBlockTakenCumul"]);
    if (config["KnockoutHeavyBlockCumul"].is_number_unsigned())
        stat.KnockoutHeavyBlockCumul = int(config["KnockoutHeavyBlockCumul"]);
    if (config["KnockoutLightBlockCumul"].is_number_unsigned())
        stat.KnockoutLightBlockCumul = int(config["KnockoutLightBlockCumul"]);
    if (config["KnockoutDemolitionsCumul"].is_number_unsigned())
        stat.KnockoutDemolitionsCumul = int(config["KnockoutDemolitionsCumul"]);
    if (config["KnockoutPlayerThrownCumul"].is_number_unsigned())
        stat.KnockoutPlayerThrownCumul = int(config["KnockoutPlayerThrownCumul"]);
    if (config["KnockoutPlayerGrabbedCumul"].is_number_unsigned())
        stat.KnockoutPlayerGrabbedCumul = int(config["KnockoutPlayerGrabbedCumul"]);
    if (config["KnockoutAerialHeavyHitCumul"].is_number_unsigned())
        stat.KnockoutAerialHeavyHitCumul = int(config["KnockoutAerialHeavyHitCumul"]);
    if (config["KnockoutAerialLightHitCumul"].is_number_unsigned())
        stat.KnockoutAerialLightHitCumul = int(config["KnockoutAerialLightHitCumul"]);
}

void RocketStats::WriteKnockout(Stats& stat, json& config)
{
    config["KnockoutDeath"] = stat.KnockoutDeath;
    config["KnockoutAssist"] = stat.KnockoutAssist;
    config["KnockoutThrown"] = stat.KnockoutThrown;
    config["KnockoutWinner"] = stat.KnockoutWinner;
    config["KnockoutGrabbed"] = stat.KnockoutGrabbed;
    config["KnockoutDoubleKO"] = stat.KnockoutDoubleKO;
    config["KnockoutHeavyHit"] = stat.KnockoutHeavyHit;
    config["KnockoutHitTaken"] = stat.KnockoutHitTaken;
    config["KnockoutLightHit"] = stat.KnockoutLightHit;
    config["KnockoutTripleKO"] = stat.KnockoutTripleKO;
    config["KnockoutBlockTaken"] = stat.KnockoutBlockTaken;
    config["KnockoutHeavyBlock"] = stat.KnockoutHeavyBlock;
    config["KnockoutLightBlock"] = stat.KnockoutLightBlock;
    config["KnockoutDemolitions"] = stat.KnockoutDemolitions;
    config["KnockoutPlayerThrown"] = stat.KnockoutPlayerThrown;
    config["KnockoutPlayerGrabbed"] = stat.KnockoutPlayerGrabbed;
    config["KnockoutAerialHeavyHit"] = stat.KnockoutAerialHeavyHit;
    config["KnockoutAerialLightHit"] = stat.KnockoutAerialLightHit;

    config["KnockoutDeathCumul"] = stat.KnockoutDeathCumul;
    config["KnockoutAssistCumul"] = stat.KnockoutAssistCumul;
    config["KnockoutThrownCumul"] = stat.KnockoutThrownCumul;
    config["KnockoutWinnerCumul"] = stat.KnockoutWinnerCumul;
    config["KnockoutGrabbedCumul"] = stat.KnockoutGrabbedCumul;
    config["KnockoutDoubleKOCumul"] = stat.KnockoutDoubleKOCumul;
    config["KnockoutHeavyHitCumul"] = stat.KnockoutHeavyHitCumul;
    config["KnockoutHitTakenCumul"] = stat.KnockoutHitTakenCumul;
    config["KnockoutLightHitCumul"] = stat.KnockoutLightHitCumul;
    config["KnockoutTripleKOCumul"] = stat.KnockoutTripleKOCumul;
    config["KnockoutBlockTakenCumul"] = stat.KnockoutBlockTakenCumul;
    config["KnockoutHeavyBlockCumul"] = stat.KnockoutHeavyBlockCumul;
    config["KnockoutLightBlockCumul"] = stat.KnockoutLightBlockCumul;
    config["KnockoutDemolitionsCumul"] = stat.KnockoutDemolitionsCumul;
    config["KnockoutPlayerThrownCumul"] = stat.KnockoutPlayerThrownCumul;
    config["KnockoutPlayerGrabbedCumul"] = stat.KnockoutPlayerGrabbedCumul;
    config["KnockoutAerialHeavyHitCumul"] = stat.KnockoutAerialHeavyHitCumul;
    config["KnockoutAerialLightHitCumul"] = stat.KnockoutAerialLightHitCumul;
}

void RocketStats::ReplaceKnockout(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["KnockoutDeath"] = VarKnockoutDeath();
    vars["KnockoutAssist"] = VarKnockoutAssist();
    vars["KnockoutThrown"] = VarKnockoutThrown();
    vars["KnockoutWinner"] = VarKnockoutWinner();
    vars["KnockoutGrabbed"] = VarKnockoutGrabbed();
    vars["KnockoutDoubleKO"] = VarKnockoutDoubleKO();
    vars["KnockoutHeavyHit"] = VarKnockoutHeavyHit();
    vars["KnockoutHitTaken"] = VarKnockoutHitTaken();
    vars["KnockoutLightHit"] = VarKnockoutLightHit();
    vars["KnockoutTripleKO"] = VarKnockoutTripleKO();
    vars["KnockoutBlockTaken"] = VarKnockoutBlockTaken();
    vars["KnockoutHeavyBlock"] = VarKnockoutHeavyBlock();
    vars["KnockoutLightBlock"] = VarKnockoutLightBlock();
    vars["KnockoutDemolitions"] = VarKnockoutDemolitions();
    vars["KnockoutPlayerThrown"] = VarKnockoutPlayerThrown();
    vars["KnockoutPlayerGrabbed"] = VarKnockoutPlayerGrabbed();
    vars["KnockoutAerialHeavyHit"] = VarKnockoutAerialHeavyHit();
    vars["KnockoutAerialLightHit"] = VarKnockoutAerialLightHit();

    /// Match
    vars["KnockoutDeathMatch"] = VarKnockoutDeathMatch();
    vars["KnockoutAssistMatch"] = VarKnockoutAssistMatch();
    vars["KnockoutThrownMatch"] = VarKnockoutThrownMatch();
    vars["KnockoutWinnerMatch"] = VarKnockoutWinnerMatch();
    vars["KnockoutGrabbedMatch"] = VarKnockoutGrabbedMatch();
    vars["KnockoutDoubleKOMatch"] = VarKnockoutDoubleKOMatch();
    vars["KnockoutHeavyHitMatch"] = VarKnockoutHeavyHitMatch();
    vars["KnockoutHitTakenMatch"] = VarKnockoutHitTakenMatch();
    vars["KnockoutLightHitMatch"] = VarKnockoutLightHitMatch();
    vars["KnockoutTripleKOMatch"] = VarKnockoutTripleKOMatch();
    vars["KnockoutBlockTakenMatch"] = VarKnockoutBlockTakenMatch();
    vars["KnockoutHeavyBlockMatch"] = VarKnockoutHeavyBlockMatch();
    vars["KnockoutLightBlockMatch"] = VarKnockoutLightBlockMatch();
    vars["KnockoutDemolitionsMatch"] = VarKnockoutDemolitionsMatch();
    vars["KnockoutPlayerThrownMatch"] = VarKnockoutPlayerThrownMatch();
    vars["KnockoutPlayerGrabbedMatch"] = VarKnockoutPlayerGrabbedMatch();
    vars["KnockoutAerialHeavyHitMatch"] = VarKnockoutAerialHeavyHitMatch();
    vars["KnockoutAerialLightHitMatch"] = VarKnockoutAerialLightHitMatch();

    /// Cumul
    vars["KnockoutDeathCumul"] = VarKnockoutDeathCumul();
    vars["KnockoutAssistCumul"] = VarKnockoutAssistCumul();
    vars["KnockoutThrownCumul"] = VarKnockoutThrownCumul();
    vars["KnockoutWinnerCumul"] = VarKnockoutWinnerCumul();
    vars["KnockoutGrabbedCumul"] = VarKnockoutGrabbedCumul();
    vars["KnockoutDoubleKOCumul"] = VarKnockoutDoubleKOCumul();
    vars["KnockoutHeavyHitCumul"] = VarKnockoutHeavyHitCumul();
    vars["KnockoutHitTakenCumul"] = VarKnockoutHitTakenCumul();
    vars["KnockoutLightHitCumul"] = VarKnockoutLightHitCumul();
    vars["KnockoutTripleKOCumul"] = VarKnockoutTripleKOCumul();
    vars["KnockoutBlockTakenCumul"] = VarKnockoutBlockTakenCumul();
    vars["KnockoutHeavyBlockCumul"] = VarKnockoutHeavyBlockCumul();
    vars["KnockoutLightBlockCumul"] = VarKnockoutLightBlockCumul();
    vars["KnockoutDemolitionsCumul"] = VarKnockoutDemolitionsCumul();
    vars["KnockoutPlayerThrownCumul"] = VarKnockoutPlayerThrownCumul();
    vars["KnockoutPlayerGrabbedCumul"] = VarKnockoutPlayerGrabbedCumul();
    vars["KnockoutAerialHeavyHitCumul"] = VarKnockoutAerialHeavyHitCumul();
    vars["KnockoutAerialLightHitCumul"] = VarKnockoutAerialLightHitCumul();
}

void RocketStats::SessionKnockout(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.KnockoutDeath += stats[index].KnockoutDeath;
        stat.KnockoutAssist += stats[index].KnockoutAssist;
        stat.KnockoutThrown += stats[index].KnockoutThrown;
        stat.KnockoutWinner += stats[index].KnockoutWinner;
        stat.KnockoutGrabbed += stats[index].KnockoutGrabbed;
        stat.KnockoutDoubleKO += stats[index].KnockoutDoubleKO;
        stat.KnockoutHeavyHit += stats[index].KnockoutHeavyHit;
        stat.KnockoutHitTaken += stats[index].KnockoutHitTaken;
        stat.KnockoutLightHit += stats[index].KnockoutLightHit;
        stat.KnockoutTripleKO += stats[index].KnockoutTripleKO;
        stat.KnockoutBlockTaken += stats[index].KnockoutBlockTaken;
        stat.KnockoutHeavyBlock += stats[index].KnockoutHeavyBlock;
        stat.KnockoutLightBlock += stats[index].KnockoutLightBlock;
        stat.KnockoutDemolitions += stats[index].KnockoutDemolitions;
        stat.KnockoutPlayerThrown += stats[index].KnockoutPlayerThrown;
        stat.KnockoutPlayerGrabbed += stats[index].KnockoutPlayerGrabbed;
        stat.KnockoutAerialHeavyHit += stats[index].KnockoutAerialHeavyHit;
        stat.KnockoutAerialLightHit += stats[index].KnockoutAerialLightHit;
    }
    else
    {
        session.KnockoutDeathCumul = stat.KnockoutDeath;
        session.KnockoutAssistCumul = stat.KnockoutAssist;
        session.KnockoutThrownCumul = stat.KnockoutThrown;
        session.KnockoutWinnerCumul = stat.KnockoutWinner;
        session.KnockoutGrabbedCumul = stat.KnockoutGrabbed;
        session.KnockoutDoubleKOCumul = stat.KnockoutDoubleKO;
        session.KnockoutHeavyHitCumul = stat.KnockoutHeavyHit;
        session.KnockoutHitTakenCumul = stat.KnockoutHitTaken;
        session.KnockoutLightHitCumul = stat.KnockoutLightHit;
        session.KnockoutTripleKOCumul = stat.KnockoutTripleKO;
        session.KnockoutBlockTakenCumul = stat.KnockoutBlockTaken;
        session.KnockoutHeavyBlockCumul = stat.KnockoutHeavyBlock;
        session.KnockoutLightBlockCumul = stat.KnockoutLightBlock;
        session.KnockoutDemolitionsCumul = stat.KnockoutDemolitions;
        session.KnockoutPlayerThrownCumul = stat.KnockoutPlayerThrown;
        session.KnockoutPlayerGrabbedCumul = stat.KnockoutPlayerGrabbed;
        session.KnockoutAerialHeavyHitCumul = stat.KnockoutAerialHeavyHit;
        session.KnockoutAerialLightHitCumul = stat.KnockoutAerialLightHit;
    }
}

#pragma region Base
std::string RocketStats::VarKnockoutDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutAssist)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAssist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutThrown(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutThrown)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutThrown.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutWinner(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutWinner)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutWinner.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutGrabbed(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutGrabbed)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutGrabbed.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDoubleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDoubleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHitTaken(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHitTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHitTaken.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTripleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTripleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTripleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutBlockTaken(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutBlockTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutBlockTaken.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyBlock(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyBlock.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightBlock(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutLightBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightBlock.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDemolitions(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDemolitions)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDemolitions.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutPlayerThrown(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutPlayerThrown)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutPlayerThrown.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutPlayerGrabbed(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutPlayerGrabbed)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutPlayerGrabbed.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAerialHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutAerialHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAerialHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAerialLightHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutAerialLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAerialLightHit.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Match
std::string RocketStats::VarKnockoutDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutAssist)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutThrownMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutThrown)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutThrownMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutWinnerMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutWinner)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutWinnerMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutGrabbedMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutGrabbed)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutGrabbedMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDoubleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDoubleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHitTakenMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutHitTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHitTakenMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTripleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTripleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTripleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutBlockTakenMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutBlockTaken)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutBlockTakenMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyBlockMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyBlockMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightBlockMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutLightBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightBlockMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDemolitionsMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutDemolitions)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDemolitionsMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutPlayerThrownMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutPlayerThrown)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutPlayerThrownMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutPlayerGrabbedMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutPlayerGrabbed)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutPlayerGrabbedMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAerialHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutAerialHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAerialHeavyHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAerialLightHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutAerialLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAerialLightHitMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Cumul
std::string RocketStats::VarKnockoutDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutAssistCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutThrownCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutThrownCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutThrownCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutWinnerCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutWinnerCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutWinnerCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutGrabbedCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutGrabbedCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutGrabbedCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDoubleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDoubleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDoubleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHitTakenCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHitTakenCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHitTakenCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutLightHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTripleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTripleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTripleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutBlockTakenCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutBlockTakenCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutBlockTakenCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutHeavyBlockCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutHeavyBlockCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutHeavyBlockCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutLightBlockCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutLightBlockCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutLightBlockCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutDemolitionsCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutDemolitionsCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutDemolitionsCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutPlayerThrownCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutPlayerThrownCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutPlayerThrownCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutPlayerGrabbedCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutPlayerGrabbedCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutPlayerGrabbedCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAerialHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutAerialHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAerialHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutAerialLightHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutAerialLightHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutAerialLightHitCumul.txt", tmp);

    return tmp;
}
#pragma endregion