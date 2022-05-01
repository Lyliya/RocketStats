#include "../RocketStats.h"

#pragma region Base
std::string RocketStats::VarKnockout(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().Knockout)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_Knockout.txt", tmp);

    return tmp;
}

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


std::string RocketStats::VarKnockoutTeam(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeam)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeam.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamAssist)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAssist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDoubleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDoubleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamTripleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamTripleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamTripleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyBlock(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyBlock.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAerialHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamAerialHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAerialHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAerialLightHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamAerialLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAerialLightHit.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTotal(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotal)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_TotalKnockout.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDeath(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDeath.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAssist(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalAssist)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAssist.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDoubleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDoubleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalTripleKO(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalTripleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalTripleKO.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyBlock(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyBlock.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAerialHeavyHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalAerialHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAerialHeavyHit.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAerialLightHit(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalAerialLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAerialLightHit.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Match
std::string RocketStats::VarKnockoutMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.Knockout)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutMatch.txt", tmp);

    return tmp;
}

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


std::string RocketStats::VarKnockoutTeamMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeam)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamAssist)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDoubleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDoubleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamTripleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamTripleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamTripleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyBlockMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyBlockMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAerialHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamAerialHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAerialHeavyHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAerialLightHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTeamAerialLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAerialLightHitMatch.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTotalMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotal)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDeathMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalDeath)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDeathMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAssistMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalAssist)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAssistMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDoubleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalDoubleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDoubleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalTripleKOMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalTripleKO)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalTripleKOMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyBlockMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalHeavyBlock)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyBlockMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAerialHeavyHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalAerialHeavyHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAerialHeavyHitMatch.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAerialLightHitMatch(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(current.stats.KnockoutTotalAerialLightHit)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAerialLightHitMatch.txt", tmp);

    return tmp;
}
#pragma endregion

#pragma region Cumul
std::string RocketStats::VarKnockoutCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutCumul.txt", tmp);

    return tmp;
}

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


std::string RocketStats::VarKnockoutTeamCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamAssistCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamDoubleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamDoubleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamDoubleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamTripleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamTripleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamTripleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamHeavyBlockCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamHeavyBlockCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamHeavyBlockCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAerialHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamAerialHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAerialHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTeamAerialLightHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTeamAerialLightHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTeamAerialLightHitCumul.txt", tmp);

    return tmp;
}


std::string RocketStats::VarKnockoutTotalCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDeathCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDeathCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDeathCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAssistCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalAssistCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAssistCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalDoubleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalDoubleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalDoubleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalTripleKOCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalTripleKOCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalTripleKOCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalHeavyBlockCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalHeavyBlockCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalHeavyBlockCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAerialHeavyHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalAerialHeavyHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAerialHeavyHitCumul.txt", tmp);

    return tmp;
}

std::string RocketStats::VarKnockoutTotalAerialLightHitCumul(bool write, bool force, bool default_value)
{
    std::string tmp = (rs_hide_knockout ? theme_hide_value : (default_value ? "0" : std::to_string(GetStats().KnockoutTotalAerialLightHitCumul)));

    if (write && (force || (rs_in_file && rs_file_knockout)))
        WriteInFile("RocketStats_KnockoutTotalAerialLightHitCumul.txt", tmp);

    return tmp;
}
#pragma endregion