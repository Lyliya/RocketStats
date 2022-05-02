#include "../RocketStats.h"

void RocketStats::ReadKnockout(Stats& stat, json& config)
{
    if (config["Knockout"].is_number_unsigned())
        stat.Knockout = int(config["Knockout"]);
    if (config["KnockoutDeath"].is_number_unsigned())
        stat.KnockoutDeath = int(config["KnockoutDeath"]);
    if (config["KnockoutAssist"].is_number_unsigned())
        stat.KnockoutAssist = int(config["KnockoutAssist"]);
    if (config["KnockoutThrown"].is_number_unsigned())
        stat.KnockoutThrown = int(config["KnockoutThrown"]);
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
    if (config["KnockoutPlayerThrown"].is_number_unsigned())
        stat.KnockoutPlayerThrown = int(config["KnockoutPlayerThrown"]);
    if (config["KnockoutPlayerGrabbed"].is_number_unsigned())
        stat.KnockoutPlayerGrabbed = int(config["KnockoutPlayerGrabbed"]);
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
    if (config["KnockoutThrownCumul"].is_number_unsigned())
        stat.KnockoutThrownCumul = int(config["KnockoutThrownCumul"]);
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
    if (config["KnockoutPlayerThrownCumul"].is_number_unsigned())
        stat.KnockoutPlayerThrownCumul = int(config["KnockoutPlayerThrownCumul"]);
    if (config["KnockoutPlayerGrabbedCumul"].is_number_unsigned())
        stat.KnockoutPlayerGrabbedCumul = int(config["KnockoutPlayerGrabbedCumul"]);
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

void RocketStats::WriteKnockout(Stats& stat, json& config)
{
    config["Knockout"] = stat.Knockout;
    config["KnockoutDeath"] = stat.KnockoutDeath;
    config["KnockoutAssist"] = stat.KnockoutAssist;
    config["KnockoutThrown"] = stat.KnockoutThrown;
    config["KnockoutGrabbed"] = stat.KnockoutGrabbed;
    config["KnockoutDoubleKO"] = stat.KnockoutDoubleKO;
    config["KnockoutHeavyHit"] = stat.KnockoutHeavyHit;
    config["KnockoutHitTaken"] = stat.KnockoutHitTaken;
    config["KnockoutLightHit"] = stat.KnockoutLightHit;
    config["KnockoutTripleKO"] = stat.KnockoutTripleKO;
    config["KnockoutBlockTaken"] = stat.KnockoutBlockTaken;
    config["KnockoutHeavyBlock"] = stat.KnockoutHeavyBlock;
    config["KnockoutLightBlock"] = stat.KnockoutLightBlock;
    config["KnockoutPlayerThrown"] = stat.KnockoutPlayerThrown;
    config["KnockoutPlayerGrabbed"] = stat.KnockoutPlayerGrabbed;
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
    config["KnockoutThrownCumul"] = stat.KnockoutThrownCumul;
    config["KnockoutGrabbedCumul"] = stat.KnockoutGrabbedCumul;
    config["KnockoutDoubleKOCumul"] = stat.KnockoutDoubleKOCumul;
    config["KnockoutHeavyHitCumul"] = stat.KnockoutHeavyHitCumul;
    config["KnockoutHitTakenCumul"] = stat.KnockoutHitTakenCumul;
    config["KnockoutLightHitCumul"] = stat.KnockoutLightHitCumul;
    config["KnockoutTripleKOCumul"] = stat.KnockoutTripleKOCumul;
    config["KnockoutBlockTakenCumul"] = stat.KnockoutBlockTakenCumul;
    config["KnockoutHeavyBlockCumul"] = stat.KnockoutHeavyBlockCumul;
    config["KnockoutLightBlockCumul"] = stat.KnockoutLightBlockCumul;
    config["KnockoutPlayerThrownCumul"] = stat.KnockoutPlayerThrownCumul;
    config["KnockoutPlayerGrabbedCumul"] = stat.KnockoutPlayerGrabbedCumul;
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

void RocketStats::ReplaceKnockout(std::map<std::string, std::string>& vars)
{
    /// Base
    vars["Knockout"] = VarKnockout();
    vars["KnockoutDeath"] = VarKnockoutDeath();
    vars["KnockoutAssist"] = VarKnockoutAssist();
    vars["KnockoutThrown"] = VarKnockoutThrown();
    vars["KnockoutGrabbed"] = VarKnockoutGrabbed();
    vars["KnockoutDoubleKO"] = VarKnockoutDoubleKO();
    vars["KnockoutHeavyHit"] = VarKnockoutHeavyHit();
    vars["KnockoutHitTaken"] = VarKnockoutHitTaken();
    vars["KnockoutLightHit"] = VarKnockoutLightHit();
    vars["KnockoutTripleKO"] = VarKnockoutTripleKO();
    vars["KnockoutBlockTaken"] = VarKnockoutBlockTaken();
    vars["KnockoutHeavyBlock"] = VarKnockoutHeavyBlock();
    vars["KnockoutLightBlock"] = VarKnockoutLightBlock();
    vars["KnockoutPlayerThrown"] = VarKnockoutPlayerThrown();
    vars["KnockoutPlayerGrabbed"] = VarKnockoutPlayerGrabbed();
    vars["KnockoutAerialHeavyHit"] = VarKnockoutAerialHeavyHit();
    vars["KnockoutAerialLightHit"] = VarKnockoutAerialLightHit();
    vars["KnockoutTeam"] = VarKnockoutTeam();
    vars["KnockoutTeamDeath"] = VarKnockoutTeamDeath();
    vars["KnockoutTeamAssist"] = VarKnockoutTeamAssist();
    vars["KnockoutTeamDoubleKO"] = VarKnockoutTeamDoubleKO();
    vars["KnockoutTeamHeavyHit"] = VarKnockoutTeamHeavyHit();
    vars["KnockoutTeamTripleKO"] = VarKnockoutTeamTripleKO();
    vars["KnockoutTeamHeavyBlock"] = VarKnockoutTeamHeavyBlock();
    vars["KnockoutTeamAerialHeavyHit"] = VarKnockoutAerialHeavyHit();
    vars["KnockoutTeamAerialLightHit"] = VarKnockoutAerialLightHit();
    vars["KnockoutTotal"] = VarKnockoutTotal();
    vars["KnockoutTotalDeath"] = VarKnockoutTotalDeath();
    vars["KnockoutTotalAssist"] = VarKnockoutTotalAssist();
    vars["KnockoutTotalDoubleKO"] = VarKnockoutTotalDoubleKO();
    vars["KnockoutTotalHeavyHit"] = VarKnockoutTotalHeavyHit();
    vars["KnockoutTotalTripleKO"] = VarKnockoutTotalTripleKO();
    vars["KnockoutTotalHeavyBlock"] = VarKnockoutTotalHeavyBlock();
    vars["KnockoutTotalAerialHeavyHit"] = VarKnockoutAerialHeavyHit();
    vars["KnockoutTotalAerialLightHit"] = VarKnockoutAerialLightHit();

    /// Match
    vars["KnockoutMatch"] = VarKnockoutMatch();
    vars["KnockoutDeathMatch"] = VarKnockoutDeathMatch();
    vars["KnockoutAssistMatch"] = VarKnockoutAssistMatch();
    vars["KnockoutThrownMatch"] = VarKnockoutThrownMatch();
    vars["KnockoutGrabbedMatch"] = VarKnockoutGrabbedMatch();
    vars["KnockoutDoubleKOMatch"] = VarKnockoutDoubleKOMatch();
    vars["KnockoutHeavyHitMatch"] = VarKnockoutHeavyHitMatch();
    vars["KnockoutHitTakenMatch"] = VarKnockoutHitTakenMatch();
    vars["KnockoutLightHitMatch"] = VarKnockoutLightHitMatch();
    vars["KnockoutTripleKOMatch"] = VarKnockoutTripleKOMatch();
    vars["KnockoutBlockTakenMatch"] = VarKnockoutBlockTakenMatch();
    vars["KnockoutHeavyBlockMatch"] = VarKnockoutHeavyBlockMatch();
    vars["KnockoutLightBlockMatch"] = VarKnockoutLightBlock();
    vars["KnockoutPlayerThrownMatch"] = VarKnockoutPlayerThrown();
    vars["KnockoutPlayerGrabbedMatch"] = VarKnockoutPlayerGrabbed();
    vars["KnockoutAerialHeavyHitMatch"] = VarKnockoutAerialHeavyHitMatch();
    vars["KnockoutAerialLightHitMatch"] = VarKnockoutAerialLightHitMatch();
    vars["KnockoutTeamMatch"] = VarKnockoutTeamMatch();
    vars["KnockoutTeamDeathMatch"] = VarKnockoutTeamDeathMatch();
    vars["KnockoutTeamAssistMatch"] = VarKnockoutTeamAssistMatch();
    vars["KnockoutTeamDoubleKOMatch"] = VarKnockoutTeamDoubleKOMatch();
    vars["KnockoutTeamHeavyHitMatch"] = VarKnockoutTeamHeavyHitMatch();
    vars["KnockoutTeamTripleKOMatch"] = VarKnockoutTeamTripleKOMatch();
    vars["KnockoutTeamHeavyBlockMatch"] = VarKnockoutTeamHeavyBlockMatch();
    vars["KnockoutTeamAerialHeavyHitMatch"] = VarKnockoutAerialHeavyHitMatch();
    vars["KnockoutTeamAerialLightHitMatch"] = VarKnockoutAerialLightHitMatch();
    vars["KnockoutTotalMatch"] = VarKnockoutTotalMatch();
    vars["KnockoutTotalDeathMatch"] = VarKnockoutTotalDeathMatch();
    vars["KnockoutTotalAssistMatch"] = VarKnockoutTotalAssistMatch();
    vars["KnockoutTotalDoubleKOMatch"] = VarKnockoutTotalDoubleKOMatch();
    vars["KnockoutTotalHeavyHitMatch"] = VarKnockoutTotalHeavyHitMatch();
    vars["KnockoutTotalTripleKOMatch"] = VarKnockoutTotalTripleKOMatch();
    vars["KnockoutTotalHeavyBlockMatch"] = VarKnockoutTotalHeavyBlockMatch();
    vars["KnockoutTotalAerialHeavyHitMatch"] = VarKnockoutAerialHeavyHitMatch();
    vars["KnockoutTotalAerialLightHitMatch"] = VarKnockoutAerialLightHitMatch();

    /// Cumul
    vars["KnockoutCumul"] = VarKnockoutCumul();
    vars["KnockoutDeathCumul"] = VarKnockoutDeathCumul();
    vars["KnockoutAssistCumul"] = VarKnockoutAssistCumul();
    vars["KnockoutThrownCumul"] = VarKnockoutThrownCumul();
    vars["KnockoutGrabbedCumul"] = VarKnockoutGrabbedCumul();
    vars["KnockoutDoubleKOCumul"] = VarKnockoutDoubleKOCumul();
    vars["KnockoutHeavyHitCumul"] = VarKnockoutHeavyHitCumul();
    vars["KnockoutHitTakenCumul"] = VarKnockoutHitTakenCumul();
    vars["KnockoutLightHitCumul"] = VarKnockoutLightHitCumul();
    vars["KnockoutTripleKOCumul"] = VarKnockoutTripleKOCumul();
    vars["KnockoutBlockTakenCumul"] = VarKnockoutBlockTakenCumul();
    vars["KnockoutHeavyBlockCumul"] = VarKnockoutHeavyBlockCumul();
    vars["KnockoutLightBlockCumul"] = VarKnockoutLightBlock();
    vars["KnockoutPlayerThrownCumul"] = VarKnockoutPlayerThrown();
    vars["KnockoutPlayerGrabbedCumul"] = VarKnockoutPlayerGrabbed();
    vars["KnockoutAerialHeavyHitCumul"] = VarKnockoutAerialHeavyHitCumul();
    vars["KnockoutAerialLightHitCumul"] = VarKnockoutAerialLightHitCumul();
    vars["KnockoutTeamCumul"] = VarKnockoutTeamCumul();
    vars["KnockoutTeamDeathCumul"] = VarKnockoutTeamDeathCumul();
    vars["KnockoutTeamAssistCumul"] = VarKnockoutTeamAssistCumul();
    vars["KnockoutTeamDoubleKOCumul"] = VarKnockoutTeamDoubleKOCumul();
    vars["KnockoutTeamHeavyHitCumul"] = VarKnockoutTeamHeavyHitCumul();
    vars["KnockoutTeamTripleKOCumul"] = VarKnockoutTeamTripleKOCumul();
    vars["KnockoutTeamHeavyBlockCumul"] = VarKnockoutTeamHeavyBlockCumul();
    vars["KnockoutTeamAerialHeavyHitCumul"] = VarKnockoutAerialHeavyHitCumul();
    vars["KnockoutTeamAerialLightHitCumul"] = VarKnockoutAerialLightHitCumul();
    vars["KnockoutTotalCumul"] = VarKnockoutTotalCumul();
    vars["KnockoutTotalDeathCumul"] = VarKnockoutTotalDeathCumul();
    vars["KnockoutTotalAssistCumul"] = VarKnockoutTotalAssistCumul();
    vars["KnockoutTotalDoubleKOCumul"] = VarKnockoutTotalDoubleKOCumul();
    vars["KnockoutTotalHeavyHitCumul"] = VarKnockoutTotalHeavyHitCumul();
    vars["KnockoutTotalTripleKOCumul"] = VarKnockoutTotalTripleKOCumul();
    vars["KnockoutTotalHeavyBlockCumul"] = VarKnockoutTotalHeavyBlockCumul();
    vars["KnockoutTotalAerialHeavyHitCumul"] = VarKnockoutAerialHeavyHitCumul();
    vars["KnockoutTotalAerialLightHitCumul"] = VarKnockoutAerialLightHitCumul();
}

void RocketStats::SessionKnockout(Stats& stat, int index, bool playlists)
{
    if (playlists)
    {
        stat.Knockout += stats[index].Knockout;
        stat.KnockoutDeath += stats[index].KnockoutDeath;
        stat.KnockoutAssist += stats[index].KnockoutAssist;
        stat.KnockoutThrown += stats[index].KnockoutThrown;
        stat.KnockoutGrabbed += stats[index].KnockoutGrabbed;
        stat.KnockoutDoubleKO += stats[index].KnockoutDoubleKO;
        stat.KnockoutHeavyHit += stats[index].KnockoutHeavyHit;
        stat.KnockoutHitTaken += stats[index].KnockoutHitTaken;
        stat.KnockoutLightHit += stats[index].KnockoutLightHit;
        stat.KnockoutTripleKO += stats[index].KnockoutTripleKO;
        stat.KnockoutBlockTaken += stats[index].KnockoutBlockTaken;
        stat.KnockoutHeavyBlock += stats[index].KnockoutHeavyBlock;
        stat.KnockoutLightBlock += stats[index].KnockoutLightBlock;
        stat.KnockoutPlayerThrown += stats[index].KnockoutPlayerThrown;
        stat.KnockoutPlayerGrabbed += stats[index].KnockoutPlayerGrabbed;
        stat.KnockoutAerialHeavyHit += stats[index].KnockoutAerialHeavyHit;
        stat.KnockoutAerialLightHit += stats[index].KnockoutAerialLightHit;
        stat.KnockoutTeam += stats[index].KnockoutTeam;
        stat.KnockoutTeamDeath += stats[index].KnockoutTeamDeath;
        stat.KnockoutTeamDoubleKO += stats[index].KnockoutTeamDoubleKO;
        stat.KnockoutTeamHeavyHit += stats[index].KnockoutTeamHeavyHit;
        stat.KnockoutTeamTripleKO += stats[index].KnockoutTeamTripleKO;
        stat.KnockoutTeamHeavyBlock += stats[index].KnockoutTeamHeavyBlock;
        stat.KnockoutTeamAerialHeavyHit += stats[index].KnockoutTeamAerialHeavyHit;
        stat.KnockoutTeamAerialLightHit += stats[index].KnockoutTeamAerialLightHit;
        stat.KnockoutTotal += stats[index].KnockoutTotal;
        stat.KnockoutTotalDeath += stats[index].KnockoutTotalDeath;
        stat.KnockoutTotalDoubleKO += stats[index].KnockoutTotalDoubleKO;
        stat.KnockoutTotalHeavyHit += stats[index].KnockoutTotalHeavyHit;
        stat.KnockoutTotalTripleKO += stats[index].KnockoutTotalTripleKO;
        stat.KnockoutTotalHeavyBlock += stats[index].KnockoutTotalHeavyBlock;
        stat.KnockoutTotalAerialHeavyHit += stats[index].KnockoutTotalAerialHeavyHit;
        stat.KnockoutTotalAerialLightHit += stats[index].KnockoutTotalAerialLightHit;
    }
    else
    {
        session.KnockoutCumul = stat.Knockout;
        session.KnockoutDeathCumul = stat.KnockoutDeath;
        session.KnockoutAssistCumul = stat.KnockoutAssist;
        session.KnockoutThrownCumul = stat.KnockoutThrown;
        session.KnockoutGrabbedCumul = stat.KnockoutGrabbed;
        session.KnockoutDoubleKOCumul = stat.KnockoutDoubleKO;
        session.KnockoutHeavyHitCumul = stat.KnockoutHeavyHit;
        session.KnockoutHitTakenCumul = stat.KnockoutHitTaken;
        session.KnockoutLightHitCumul = stat.KnockoutLightHit;
        session.KnockoutTripleKOCumul = stat.KnockoutTripleKO;
        session.KnockoutBlockTakenCumul = stat.KnockoutBlockTaken;
        session.KnockoutHeavyBlockCumul = stat.KnockoutHeavyBlock;
        session.KnockoutLightBlockCumul = stat.KnockoutLightBlock;
        session.KnockoutPlayerThrownCumul = stat.KnockoutPlayerThrown;
        session.KnockoutPlayerGrabbedCumul = stat.KnockoutPlayerGrabbed;
        session.KnockoutAerialHeavyHitCumul = stat.KnockoutAerialHeavyHit;
        session.KnockoutAerialLightHitCumul = stat.KnockoutAerialLightHit;
        session.KnockoutTeamCumul = stat.KnockoutTeam;
        session.KnockoutTeamDeathCumul = stat.KnockoutTeamDeath;
        session.KnockoutTeamDoubleKOCumul = stat.KnockoutTeamDoubleKO;
        session.KnockoutTeamHeavyHitCumul = stat.KnockoutTeamHeavyHit;
        session.KnockoutTeamTripleKOCumul = stat.KnockoutTeamTripleKO;
        session.KnockoutTeamHeavyBlockCumul = stat.KnockoutTeamHeavyBlock;
        session.KnockoutTeamAerialHeavyHitCumul = stat.KnockoutTeamAerialHeavyHit;
        session.KnockoutTeamAerialLightHitCumul = stat.KnockoutTeamAerialLightHit;
        session.KnockoutTotalCumul = stat.KnockoutTotal;
        session.KnockoutTotalDeathCumul = stat.KnockoutTotalDeath;
        session.KnockoutTotalDoubleKOCumul = stat.KnockoutTotalDoubleKO;
        session.KnockoutTotalHeavyHitCumul = stat.KnockoutTotalHeavyHit;
        session.KnockoutTotalTripleKOCumul = stat.KnockoutTotalTripleKO;
        session.KnockoutTotalHeavyBlockCumul = stat.KnockoutTotalHeavyBlock;
        session.KnockoutTotalAerialHeavyHitCumul = stat.KnockoutTotalAerialHeavyHit;
        session.KnockoutTotalAerialLightHitCumul = stat.KnockoutTotalAerialLightHit;
    }
}

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