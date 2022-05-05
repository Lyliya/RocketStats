#include "../RocketStats.h"

void RocketStats::VarsReplace(std::map<std::string, std::string>& vars)
{
    ReplaceOther(vars);
    ReplaceShots(vars);
    ReplaceSaves(vars);
    ReplaceGoals(vars);
    ReplaceDropshot(vars);
    ReplaceKnockout(vars);
    ReplaceMiscs(vars);
    ReplaceAccolades(vars);
}

void RocketStats::VarsSession(Stats& stat, int index, bool playlists)
{
    SessionOther(stat, index, playlists);
    SessionShots(stat, index, playlists);
    SessionSaves(stat, index, playlists);
    SessionGoals(stat, index, playlists);
    SessionDropshot(stat, index, playlists);
    SessionKnockout(stat, index, playlists);
    SessionMiscs(stat, index, playlists);
    SessionAccolades(stat, index, playlists);
}

void RocketStats::VarsRead(Stats& stat, json& config)
{
    ReadOther(stat, config);
    ReadShots(stat, config);
    ReadSaves(stat, config);
    ReadGoals(stat, config);
    ReadDropshot(stat, config);
    ReadKnockout(stat, config);
    ReadMiscs(stat, config);
    ReadAccolades(stat, config);
}

void RocketStats::VarsWrite(Stats& stat, json& config)
{
    WriteOther(stat, config);
    WriteShots(stat, config);
    WriteSaves(stat, config);
    WriteGoals(stat, config);
    WriteDropshot(stat, config);
    WriteKnockout(stat, config);
    WriteMiscs(stat, config);
    WriteAccolades(stat, config);
}

#pragma region Other
void RocketStats::AllOther(bool force, bool default_value)
{
    VarGames(true, force, default_value);
    VarGameMode(true, force, default_value);
    VarRank(true, force, default_value);
    VarDiv(true, force, default_value);
    VarMMR(true, force, default_value);
    VarMMRChange(true, force, default_value);
    VarMMRCumulChange(true, force, default_value);
    VarWin(true, force, default_value);
    VarLoss(true, force, default_value);
    VarStreak(true, force, default_value);
    VarWinRatio(true, force, default_value);
    VarWinPercentage(true, force, default_value);
    VarBoost(true, force, (!is_game_started || is_game_ended), false);
}
#pragma endregion

#pragma region Shots
void RocketStats::AllShots(bool force, bool default_value)
{
    AllShotsClear(force, default_value);
    AllShotsAssist(force, default_value);
    AllShotsCenter(force, default_value);
    AllShotsAerialHit(force, default_value);
    AllShotsBicycleHit(force, default_value);
    AllShotsShotOnGoal(force, default_value);
}

void RocketStats::AllShotsClear(bool force, bool default_value)
{
    VarShotsClear(true, force, default_value);
    VarShotsClearMatch(true, force, default_value);
    VarShotsClearCumul(true, force, default_value);
}

void RocketStats::AllShotsAssist(bool force, bool default_value)
{
    VarShotsAssist(true, force, default_value);
    VarShotsTeamAssist(true, force, default_value);
    VarShotsTotalAssist(true, force, default_value);

    VarShotsAssistMatch(true, force, default_value);
    VarShotsTeamAssistMatch(true, force, default_value);
    VarShotsTotalAssistMatch(true, force, default_value);

    VarShotsAssistCumul(true, force, default_value);
    VarShotsTeamAssistCumul(true, force, default_value);
    VarShotsTotalAssistCumul(true, force, default_value);
}

void RocketStats::AllShotsCenter(bool force, bool default_value)
{
    VarShotsCenter(true, force, default_value);
    VarShotsCenterMatch(true, force, default_value);
    VarShotsCenterCumul(true, force, default_value);
}

void RocketStats::AllShotsAerialHit(bool force, bool default_value)
{
    VarShotsAerialHit(true, force, default_value);
    VarShotsAerialHitMatch(true, force, default_value);
    VarShotsAerialHitCumul(true, force, default_value);
}

void RocketStats::AllShotsBicycleHit(bool force, bool default_value)
{
    VarShotsBicycleHit(true, force, default_value);
    VarShotsTeamBicycleHit(true, force, default_value);
    VarShotsTotalBicycleHit(true, force, default_value);

    VarShotsBicycleHitMatch(true, force, default_value);
    VarShotsTeamBicycleHitMatch(true, force, default_value);
    VarShotsTotalBicycleHitMatch(true, force, default_value);

    VarShotsBicycleHitCumul(true, force, default_value);
    VarShotsTeamBicycleHitCumul(true, force, default_value);
    VarShotsTotalBicycleHitCumul(true, force, default_value);
}

void RocketStats::AllShotsShotOnGoal(bool force, bool default_value)
{
    VarShotsShotOnGoal(true, force, default_value);
    VarShotsTeamShotOnGoal(true, force, default_value);
    VarShotsTotalShotOnGoal(true, force, default_value);

    VarShotsShotOnGoalMatch(true, force, default_value);
    VarShotsTeamShotOnGoalMatch(true, force, default_value);
    VarShotsTotalShotOnGoalMatch(true, force, default_value);

    VarShotsShotOnGoalCumul(true, force, default_value);
    VarShotsTeamShotOnGoalCumul(true, force, default_value);
    VarShotsTotalShotOnGoalCumul(true, force, default_value);
}
#pragma endregion

#pragma region Saves
void RocketStats::AllSaves(bool force, bool default_value)
{
    AllSavesSave(force, default_value);
    AllSavesEpicSave(force, default_value);
}

void RocketStats::AllSavesSave(bool force, bool default_value)
{
    VarSavesSave(true, force, default_value);
    VarSavesTeamSave(true, force, default_value);
    VarSavesTotalSave(true, force, default_value);

    VarSavesSaveMatch(true, force, default_value);
    VarSavesTeamSaveMatch(true, force, default_value);
    VarSavesTotalSaveMatch(true, force, default_value);

    VarSavesSaveCumul(true, force, default_value);
    VarSavesTeamSaveCumul(true, force, default_value);
    VarSavesTotalSaveCumul(true, force, default_value);
}

void RocketStats::AllSavesEpicSave(bool force, bool default_value)
{
    VarSavesEpicSave(true, force, default_value);
    VarSavesTeamEpicSave(true, force, default_value);
    VarSavesTotalEpicSave(true, force, default_value);

    VarSavesEpicSaveMatch(true, force, default_value);
    VarSavesTeamEpicSaveMatch(true, force, default_value);
    VarSavesTotalEpicSaveMatch(true, force, default_value);

    VarSavesEpicSaveCumul(true, force, default_value);
    VarSavesTeamEpicSaveCumul(true, force, default_value);
    VarSavesTotalEpicSaveCumul(true, force, default_value);
}
#pragma endregion

#pragma region Goals
void RocketStats::AllGoals(bool force, bool default_value)
{
    AllGoalsGoal(force, default_value);
    AllGoalsOwnGoal(force, default_value);
    AllGoalsLongGoal(force, default_value);
    AllGoalsPoolShot(force, default_value);
    AllGoalsAerialGoal(force, default_value);
    AllGoalsTurtleGoal(force, default_value);
    AllGoalsBicycleGoal(force, default_value);
    AllGoalsOvertimeGoal(force, default_value);
    AllGoalsBackwardsGoal(force, default_value);
    AllGoalsHoopsSwishGoal(force, default_value);
}

void RocketStats::AllGoalsGoal(bool force, bool default_value)
{
    VarGoalsGoal(true, force, default_value);
    VarGoalsTeamGoal(true, force, default_value);
    VarGoalsTotalGoal(true, force, default_value);

    VarGoalsGoalMatch(true, force, default_value);
    VarGoalsTeamGoalMatch(true, force, default_value);
    VarGoalsTotalGoalMatch(true, force, default_value);

    VarGoalsGoalCumul(true, force, default_value);
    VarGoalsTeamGoalCumul(true, force, default_value);
    VarGoalsTotalGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsOwnGoal(bool force, bool default_value)
{
    VarGoalsOwnGoal(true, force, default_value);
    VarGoalsOwnGoalMatch(true, force, default_value);
    VarGoalsOwnGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsLongGoal(bool force, bool default_value)
{
    VarGoalsLongGoal(true, force, default_value);
    VarGoalsTeamLongGoal(true, force, default_value);
    VarGoalsTotalLongGoal(true, force, default_value);

    VarGoalsLongGoalMatch(true, force, default_value);
    VarGoalsTeamLongGoalMatch(true, force, default_value);
    VarGoalsTotalLongGoalMatch(true, force, default_value);

    VarGoalsLongGoalCumul(true, force, default_value);
    VarGoalsTeamLongGoalCumul(true, force, default_value);
    VarGoalsTotalLongGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsPoolShot(bool force, bool default_value)
{
    VarGoalsPoolShot(true, force, default_value);
    VarGoalsTeamPoolShot(true, force, default_value);
    VarGoalsTotalPoolShot(true, force, default_value);

    VarGoalsPoolShotMatch(true, force, default_value);
    VarGoalsTeamPoolShotMatch(true, force, default_value);
    VarGoalsTotalPoolShotMatch(true, force, default_value);

    VarGoalsPoolShotCumul(true, force, default_value);
    VarGoalsTeamPoolShotCumul(true, force, default_value);
    VarGoalsTotalPoolShotCumul(true, force, default_value);
}

void RocketStats::AllGoalsAerialGoal(bool force, bool default_value)
{
    VarGoalsAerialGoal(true, force, default_value);
    VarGoalsTeamAerialGoal(true, force, default_value);
    VarGoalsTotalAerialGoal(true, force, default_value);

    VarGoalsAerialGoalMatch(true, force, default_value);
    VarGoalsTeamAerialGoalMatch(true, force, default_value);
    VarGoalsTotalAerialGoalMatch(true, force, default_value);

    VarGoalsAerialGoalCumul(true, force, default_value);
    VarGoalsTeamAerialGoalCumul(true, force, default_value);
    VarGoalsTotalAerialGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsTurtleGoal(bool force, bool default_value)
{
    VarGoalsTurtleGoal(true, force, default_value);
    VarGoalsTeamTurtleGoal(true, force, default_value);
    VarGoalsTotalTurtleGoal(true, force, default_value);

    VarGoalsTurtleGoalMatch(true, force, default_value);
    VarGoalsTeamTurtleGoalMatch(true, force, default_value);
    VarGoalsTotalTurtleGoalMatch(true, force, default_value);

    VarGoalsTurtleGoalCumul(true, force, default_value);
    VarGoalsTeamTurtleGoalCumul(true, force, default_value);
    VarGoalsTotalTurtleGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsBicycleGoal(bool force, bool default_value)
{
    VarGoalsBicycleGoal(true, force, default_value);
    VarGoalsTeamBicycleGoal(true, force, default_value);
    VarGoalsTotalBicycleGoal(true, force, default_value);

    VarGoalsBicycleGoalMatch(true, force, default_value);
    VarGoalsTeamBicycleGoalMatch(true, force, default_value);
    VarGoalsTotalBicycleGoalMatch(true, force, default_value);

    VarGoalsBicycleGoalCumul(true, force, default_value);
    VarGoalsTeamBicycleGoalCumul(true, force, default_value);
    VarGoalsTotalBicycleGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsOvertimeGoal(bool force, bool default_value)
{
    VarGoalsOvertimeGoal(true, force, default_value);
    VarGoalsTeamOvertimeGoal(true, force, default_value);
    VarGoalsTotalOvertimeGoal(true, force, default_value);

    VarGoalsOvertimeGoalMatch(true, force, default_value);
    VarGoalsTeamOvertimeGoalMatch(true, force, default_value);
    VarGoalsTotalOvertimeGoalMatch(true, force, default_value);

    VarGoalsOvertimeGoalCumul(true, force, default_value);
    VarGoalsTeamOvertimeGoalCumul(true, force, default_value);
    VarGoalsTotalOvertimeGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsBackwardsGoal(bool force, bool default_value)
{
    VarGoalsBackwardsGoal(true, force, default_value);
    VarGoalsTeamBackwardsGoal(true, force, default_value);
    VarGoalsTotalBackwardsGoal(true, force, default_value);

    VarGoalsBackwardsGoalMatch(true, force, default_value);
    VarGoalsTeamBackwardsGoalMatch(true, force, default_value);
    VarGoalsTotalBackwardsGoalMatch(true, force, default_value);

    VarGoalsBackwardsGoalCumul(true, force, default_value);
    VarGoalsTeamBackwardsGoalCumul(true, force, default_value);
    VarGoalsTotalBackwardsGoalCumul(true, force, default_value);
}

void RocketStats::AllGoalsHoopsSwishGoal(bool force, bool default_value)
{
    VarGoalsHoopsSwishGoal(true, force, default_value);
    VarGoalsTeamHoopsSwishGoal(true, force, default_value);
    VarGoalsTotalHoopsSwishGoal(true, force, default_value);

    VarGoalsHoopsSwishGoalMatch(true, force, default_value);
    VarGoalsTeamHoopsSwishGoalMatch(true, force, default_value);
    VarGoalsTotalHoopsSwishGoalMatch(true, force, default_value);

    VarGoalsHoopsSwishGoalCumul(true, force, default_value);
    VarGoalsTeamHoopsSwishGoalCumul(true, force, default_value);
    VarGoalsTotalHoopsSwishGoalCumul(true, force, default_value);
}
#pragma endregion

#pragma region Dropshot
void RocketStats::AllDropshot(bool force, bool default_value)
{
    AllDropshotBreakoutDamage(force, default_value);
    AllDropshotBreakoutDamageLarge(force, default_value);
}

void RocketStats::AllDropshotBreakoutDamage(bool force, bool default_value)
{
    VarDropshotBreakoutDamage(true, force, default_value);
    VarDropshotTeamBreakoutDamage(true, force, default_value);
    VarDropshotTotalBreakoutDamage(true, force, default_value);

    VarDropshotBreakoutDamageMatch(true, force, default_value);
    VarDropshotTeamBreakoutDamageMatch(true, force, default_value);
    VarDropshotTotalBreakoutDamageMatch(true, force, default_value);

    VarDropshotBreakoutDamageCumul(true, force, default_value);
    VarDropshotTeamBreakoutDamageCumul(true, force, default_value);
    VarDropshotTotalBreakoutDamageCumul(true, force, default_value);
}

void RocketStats::AllDropshotBreakoutDamageLarge(bool force, bool default_value)
{
    VarDropshotBreakoutDamageLarge(true, force, default_value);
    VarDropshotTeamBreakoutDamageLarge(true, force, default_value);
    VarDropshotTotalBreakoutDamageLarge(true, force, default_value);

    VarDropshotBreakoutDamageLargeMatch(true, force, default_value);
    VarDropshotTeamBreakoutDamageLargeMatch(true, force, default_value);
    VarDropshotTotalBreakoutDamageLargeMatch(true, force, default_value);

    VarDropshotBreakoutDamageLargeCumul(true, force, default_value);
    VarDropshotTeamBreakoutDamageLargeCumul(true, force, default_value);
    VarDropshotTotalBreakoutDamageLargeCumul(true, force, default_value);
}
#pragma endregion

#pragma region Knockout
void RocketStats::AllKnockout(bool force, bool default_value)
{
    AllKnockoutKO(force, default_value);
    AllKnockoutDeath(force, default_value);
    AllKnockoutAssist(force, default_value);
    AllKnockoutThrown(force, default_value);
    AllKnockoutWinner(force, default_value);
    AllKnockoutGrabbed(force, default_value);
    AllKnockoutDoubleKO(force, default_value);
    AllKnockoutHeavyHit(force, default_value);
    AllKnockoutHitTaken(force, default_value);
    AllKnockoutLightHit(force, default_value);
    AllKnockoutTripleKO(force, default_value);
    AllKnockoutBlockTaken(force, default_value);
    AllKnockoutHeavyBlock(force, default_value);
    AllKnockoutLightBlock(force, default_value);
    AllKnockoutPlayerThrown(force, default_value);
    AllKnockoutPlayerGrabbed(force, default_value);
    AllKnockoutAerialHeavyHit(force, default_value);
    AllKnockoutAerialLightHit(force, default_value);
}

void RocketStats::AllKnockoutKO(bool force, bool default_value)
{
    VarKnockoutKO(true, force, default_value);
    VarKnockoutKOMatch(true, force, default_value);
    VarKnockoutKOCumul(true, force, default_value);
}

void RocketStats::AllKnockoutDeath(bool force, bool default_value)
{
    VarKnockoutDeath(true, force, default_value);
    VarKnockoutDeathMatch(true, force, default_value);
    VarKnockoutDeathCumul(true, force, default_value);
}

void RocketStats::AllKnockoutAssist(bool force, bool default_value)
{
    VarKnockoutAssist(true, force, default_value);
    VarKnockoutAssistMatch(true, force, default_value);
    VarKnockoutAssistCumul(true, force, default_value);
}

void RocketStats::AllKnockoutThrown(bool force, bool default_value)
{
    VarKnockoutThrown(true, force, default_value);
    VarKnockoutThrownMatch(true, force, default_value);
    VarKnockoutThrownCumul(true, force, default_value);
}

void RocketStats::AllKnockoutWinner(bool force, bool default_value)
{
    VarKnockoutWinner(true, force, default_value);
    VarKnockoutWinnerMatch(true, force, default_value);
    VarKnockoutWinnerCumul(true, force, default_value);
}

void RocketStats::AllKnockoutGrabbed(bool force, bool default_value)
{
    VarKnockoutGrabbed(true, force, default_value);
    VarKnockoutGrabbedMatch(true, force, default_value);
    VarKnockoutGrabbedCumul(true, force, default_value);
}

void RocketStats::AllKnockoutDoubleKO(bool force, bool default_value)
{
    VarKnockoutDoubleKO(true, force, default_value);
    VarKnockoutDoubleKOMatch(true, force, default_value);
    VarKnockoutDoubleKOCumul(true, force, default_value);
}

void RocketStats::AllKnockoutHeavyHit(bool force, bool default_value)
{
    VarKnockoutHeavyHit(true, force, default_value);
    VarKnockoutHeavyHitMatch(true, force, default_value);
    VarKnockoutHeavyHitCumul(true, force, default_value);
}

void RocketStats::AllKnockoutHitTaken(bool force, bool default_value)
{
    VarKnockoutHitTaken(true, force, default_value);
    VarKnockoutHitTakenMatch(true, force, default_value);
    VarKnockoutHitTakenCumul(true, force, default_value);
}

void RocketStats::AllKnockoutLightHit(bool force, bool default_value)
{
    VarKnockoutLightHit(true, force, default_value);
    VarKnockoutLightHitMatch(true, force, default_value);
    VarKnockoutLightHitCumul(true, force, default_value);
}

void RocketStats::AllKnockoutTripleKO(bool force, bool default_value)
{
    VarKnockoutTripleKO(true, force, default_value);
    VarKnockoutTripleKOMatch(true, force, default_value);
    VarKnockoutTripleKOCumul(true, force, default_value);
}

void RocketStats::AllKnockoutBlockTaken(bool force, bool default_value)
{
    VarKnockoutBlockTaken(true, force, default_value);
    VarKnockoutBlockTakenMatch(true, force, default_value);
    VarKnockoutBlockTakenCumul(true, force, default_value);
}

void RocketStats::AllKnockoutHeavyBlock(bool force, bool default_value)
{
    VarKnockoutHeavyBlock(true, force, default_value);
    VarKnockoutHeavyBlockMatch(true, force, default_value);
    VarKnockoutHeavyBlockCumul(true, force, default_value);
}

void RocketStats::AllKnockoutLightBlock(bool force, bool default_value)
{
    VarKnockoutLightBlock(true, force, default_value);
    VarKnockoutLightBlockMatch(true, force, default_value);
    VarKnockoutLightBlockCumul(true, force, default_value);
}

void RocketStats::AllKnockoutPlayerThrown(bool force, bool default_value)
{
    VarKnockoutPlayerThrown(true, force, default_value);
    VarKnockoutPlayerThrownMatch(true, force, default_value);
    VarKnockoutPlayerThrownCumul(true, force, default_value);
}

void RocketStats::AllKnockoutPlayerGrabbed(bool force, bool default_value)
{
    VarKnockoutPlayerGrabbed(true, force, default_value);
    VarKnockoutPlayerGrabbedMatch(true, force, default_value);
    VarKnockoutPlayerGrabbedCumul(true, force, default_value);
}

void RocketStats::AllKnockoutAerialHeavyHit(bool force, bool default_value)
{
    VarKnockoutAerialHeavyHit(true, force, default_value);
    VarKnockoutAerialHeavyHitMatch(true, force, default_value);
    VarKnockoutAerialHeavyHitCumul(true, force, default_value);
}

void RocketStats::AllKnockoutAerialLightHit(bool force, bool default_value)
{
    VarKnockoutAerialLightHit(true, force, default_value);
    VarKnockoutAerialLightHitMatch(true, force, default_value);
    VarKnockoutAerialLightHitCumul(true, force, default_value);
}
#pragma endregion

#pragma region Miscs
void RocketStats::AllMiscs(bool force, bool default_value)
{
    AllMiscsDeath(force, default_value);
    AllMiscsSavior(force, default_value);
    AllMiscsLowFive(force, default_value);
    AllMiscsHatTrick(force, default_value);
    AllMiscsHighFive(force, default_value);
    AllMiscsPlaymaker(force, default_value);
    AllMiscsFirstTouch(force, default_value);
    AllMiscsDemolitions(force, default_value);
}

void RocketStats::AllMiscsDeath(bool force, bool default_value)
{
    VarMiscsDeath(true, force, default_value);
    VarMiscsTeamDeath(true, force, default_value);
    VarMiscsTotalDeath(true, force, default_value);

    VarMiscsDeathMatch(true, force, default_value);
    VarMiscsTeamDeathMatch(true, force, default_value);
    VarMiscsTotalDeathMatch(true, force, default_value);

    VarMiscsDeathCumul(true, force, default_value);
    VarMiscsTeamDeathCumul(true, force, default_value);
    VarMiscsTotalDeathCumul(true, force, default_value);
}

void RocketStats::AllMiscsSavior(bool force, bool default_value)
{
    VarMiscsSavior(true, force, default_value);
    VarMiscsTeamSavior(true, force, default_value);
    VarMiscsTotalSavior(true, force, default_value);

    VarMiscsSaviorMatch(true, force, default_value);
    VarMiscsTeamSaviorMatch(true, force, default_value);
    VarMiscsTotalSaviorMatch(true, force, default_value);

    VarMiscsSaviorCumul(true, force, default_value);
    VarMiscsTeamSaviorCumul(true, force, default_value);
    VarMiscsTotalSaviorCumul(true, force, default_value);
}

void RocketStats::AllMiscsLowFive(bool force, bool default_value)
{
    VarMiscsLowFive(true, force, default_value);
    VarMiscsTeamLowFive(true, force, default_value);
    VarMiscsTotalLowFive(true, force, default_value);

    VarMiscsLowFiveMatch(true, force, default_value);
    VarMiscsTeamLowFiveMatch(true, force, default_value);
    VarMiscsTotalLowFiveMatch(true, force, default_value);

    VarMiscsLowFiveCumul(true, force, default_value);
    VarMiscsTeamLowFiveCumul(true, force, default_value);
    VarMiscsTotalLowFiveCumul(true, force, default_value);
}

void RocketStats::AllMiscsHatTrick(bool force, bool default_value)
{
    VarMiscsHatTrick(true, force, default_value);
    VarMiscsTeamHatTrick(true, force, default_value);
    VarMiscsTotalHatTrick(true, force, default_value);

    VarMiscsHatTrickMatch(true, force, default_value);
    VarMiscsTeamHatTrickMatch(true, force, default_value);
    VarMiscsTotalHatTrickMatch(true, force, default_value);

    VarMiscsHatTrickCumul(true, force, default_value);
    VarMiscsTeamHatTrickCumul(true, force, default_value);
    VarMiscsTotalHatTrickCumul(true, force, default_value);
}

void RocketStats::AllMiscsHighFive(bool force, bool default_value)
{
    VarMiscsHighFive(true, force, default_value);
    VarMiscsTeamHighFive(true, force, default_value);
    VarMiscsTotalHighFive(true, force, default_value);

    VarMiscsHighFiveMatch(true, force, default_value);
    VarMiscsTeamHighFiveMatch(true, force, default_value);
    VarMiscsTotalHighFiveMatch(true, force, default_value);

    VarMiscsHighFiveCumul(true, force, default_value);
    VarMiscsTeamHighFiveCumul(true, force, default_value);
    VarMiscsTotalHighFiveCumul(true, force, default_value);
}

void RocketStats::AllMiscsPlaymaker(bool force, bool default_value)
{
    VarMiscsPlaymaker(true, force, default_value);
    VarMiscsTeamPlaymaker(true, force, default_value);
    VarMiscsTotalPlaymaker(true, force, default_value);

    VarMiscsPlaymakerMatch(true, force, default_value);
    VarMiscsTeamPlaymakerMatch(true, force, default_value);
    VarMiscsTotalPlaymakerMatch(true, force, default_value);

    VarMiscsPlaymakerCumul(true, force, default_value);
    VarMiscsTeamPlaymakerCumul(true, force, default_value);
    VarMiscsTotalPlaymakerCumul(true, force, default_value);
}

void RocketStats::AllMiscsFirstTouch(bool force, bool default_value)
{
    VarMiscsFirstTouch(true, force, default_value);
    VarMiscsFirstTouchMatch(true, force, default_value);
    VarMiscsFirstTouchCumul(true, force, default_value);
}

void RocketStats::AllMiscsDemolitions(bool force, bool default_value)
{
    VarMiscsDemolitions(true, force, default_value);
    VarMiscsTeamDemolitions(true, force, default_value);
    VarMiscsTotalDemolitions(true, force, default_value);

    VarMiscsDemolitionsMatch(true, force, default_value);
    VarMiscsTeamDemolitionsMatch(true, force, default_value);
    VarMiscsTotalDemolitionsMatch(true, force, default_value);

    VarMiscsDemolitionsCumul(true, force, default_value);
    VarMiscsTeamDemolitionsCumul(true, force, default_value);
    VarMiscsTotalDemolitionsCumul(true, force, default_value);
}
#pragma endregion

#pragma region Accolades
void RocketStats::AllAccolades(bool force, bool default_value)
{
    AllAccoladesMVP(force, default_value);
    AllAccoladesCarTouches(force, default_value);
    AllAccoladesFastestGoal(force, default_value);
    AllAccoladesSlowestGoal(force, default_value);
    AllAccoladesBoostPickups(force, default_value);
    AllAccoladesFurthestGoal(force, default_value);
    AllAccoladesMostBallTouches(force, default_value);
    AllAccoladesMostBoostPickups(force, default_value);
    AllAccoladesFewestBallTouches(force, default_value);
}

void RocketStats::AllAccoladesMVP(bool force, bool default_value)
{
    VarAccoladesMVP(true, force, default_value);
    VarAccoladesTeamMVP(true, force, default_value);
    VarAccoladesTotalMVP(true, force, default_value);

    VarAccoladesMVPMatch(true, force, default_value);
    VarAccoladesTeamMVPMatch(true, force, default_value);
    VarAccoladesTotalMVPMatch(true, force, default_value);

    VarAccoladesMVPCumul(true, force, default_value);
    VarAccoladesTeamMVPCumul(true, force, default_value);
    VarAccoladesTotalMVPCumul(true, force, default_value);
}

void RocketStats::AllAccoladesCarTouches(bool force, bool default_value)
{
    VarAccoladesCarTouches(true, force, default_value);
    VarAccoladesCarTouchesMatch(true, force, default_value);
    VarAccoladesCarTouchesCumul(true, force, default_value);
}

void RocketStats::AllAccoladesFastestGoal(bool force, bool default_value)
{
    VarAccoladesFastestGoal(true, force, default_value);
    VarAccoladesFastestGoalMatch(true, force, default_value);
    VarAccoladesFastestGoalCumul(true, force, default_value);
}

void RocketStats::AllAccoladesSlowestGoal(bool force, bool default_value)
{
    VarAccoladesSlowestGoal(true, force, default_value);
    VarAccoladesSlowestGoalMatch(true, force, default_value);
    VarAccoladesSlowestGoalCumul(true, force, default_value);
}

void RocketStats::AllAccoladesBoostPickups(bool force, bool default_value)
{
    VarAccoladesBoostPickups(true, force, default_value);
    VarAccoladesBoostPickupsMatch(true, force, default_value);
    VarAccoladesBoostPickupsCumul(true, force, default_value);
}

void RocketStats::AllAccoladesFurthestGoal(bool force, bool default_value)
{
    VarAccoladesFurthestGoal(true, force, default_value);
    VarAccoladesFurthestGoalMatch(true, force, default_value);
    VarAccoladesFurthestGoalCumul(true, force, default_value);
}

void RocketStats::AllAccoladesMostBallTouches(bool force, bool default_value)
{
    VarAccoladesMostBallTouches(true, force, default_value);
    VarAccoladesMostBallTouchesMatch(true, force, default_value);
    VarAccoladesMostBallTouchesCumul(true, force, default_value);
}

void RocketStats::AllAccoladesMostBoostPickups(bool force, bool default_value)
{
    VarAccoladesMostBoostPickups(true, force, default_value);
    VarAccoladesMostBoostPickupsMatch(true, force, default_value);
    VarAccoladesMostBoostPickupsCumul(true, force, default_value);
}

void RocketStats::AllAccoladesFewestBallTouches(bool force, bool default_value)
{
    VarAccoladesFewestBallTouches(true, force, default_value);
    VarAccoladesFewestBallTouchesMatch(true, force, default_value);
    VarAccoladesFewestBallTouchesCumul(true, force, default_value);
}
#pragma endregion