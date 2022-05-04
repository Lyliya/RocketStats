#include "../RocketStats.h"

bool RocketStats::isPrimaryPlayer(PriWrapper PRI)
{
    bool check = !is_online_game;
    ServerWrapper server = gameWrapper->GetOnlineGame();
    PlayerControllerWrapper player = server.GetLocalPrimaryPlayer();
    PriWrapper playerPRI = player.GetPRI();

    check = (check || PRI.IsNull()); // null PRI
    check = (check || server.IsNull()); // null server

    check = (check || player.IsNull()); // null controller
    check = (check || playerPRI.IsNull()); // null player PRI

    check = (check || PRI.GetUniqueIdWrapper().GetUID() != playerPRI.GetUniqueIdWrapper().GetUID());

    return !check;
}

void RocketStats::onStatEvent(ServerWrapper caller, void* params)
{
    StatEventParams* pstats = (StatEventParams*)params;
    if (!is_online_game)
        return;

    StatEventWrapper event = StatEventWrapper(pstats->StatEvent);

    bool refresh = true;
    std::string name = event.GetEventName();
    if (name == "Clear")
    {
        ++always.Clear;
        ++current.stats.Clear;
        ++session.Clear;
        ++stats[current.playlist].Clear;
        ++always_gm[current.playlist].Clear;

        ++always.ClearCumul;
        ++current.stats.ClearCumul;
        ++session.ClearCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].ClearCumul;
            ++always_gm[it->first].ClearCumul;
        }

        AllShotsClear(true);
    }
    else if (name == "Center")
    {
        ++always.Center;
        ++current.stats.Center;
        ++session.Center;
        ++stats[current.playlist].Center;
        ++always_gm[current.playlist].Center;

        ++always.CenterCumul;
        ++current.stats.CenterCumul;
        ++session.CenterCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].CenterCumul;
            ++always_gm[it->first].CenterCumul;
        }

        AllShotsCenter(true);
    }
    else if (name == "AerialHit")
    {
        ++always.AerialHit;
        ++current.stats.AerialHit;
        ++session.AerialHit;
        ++stats[current.playlist].AerialHit;
        ++always_gm[current.playlist].AerialHit;

        ++always.AerialHitCumul;
        ++current.stats.AerialHitCumul;
        ++session.AerialHitCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].AerialHitCumul;
            ++always_gm[it->first].AerialHitCumul;
        }

        AllShotsAerialHit(true);
    }
    else if (name == "FirstTouch")
    {
        ++always.FirstTouch;
        ++current.stats.FirstTouch;
        ++session.FirstTouch;
        ++stats[current.playlist].FirstTouch;
        ++always_gm[current.playlist].FirstTouch;

        ++always.FirstTouchCumul;
        ++current.stats.FirstTouchCumul;
        ++session.FirstTouchCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].FirstTouchCumul;
            ++always_gm[it->first].FirstTouchCumul;
        }

        AllMiscsFirstTouch(true);
    }
    else if (name == "OwnGoal")
    {
        ++always.OwnGoal;
        ++current.stats.OwnGoal;
        ++session.OwnGoal;
        ++stats[current.playlist].OwnGoal;
        ++always_gm[current.playlist].OwnGoal;

        ++always.OwnGoalCumul;
        ++current.stats.OwnGoalCumul;
        ++session.OwnGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].OwnGoalCumul;
            ++always_gm[it->first].OwnGoalCumul;
        }

        AllGoalsOwnGoal(true);
    }
    else if (name == "KO_Thrown")
    {
        ++always.KnockoutThrown;
        ++current.stats.KnockoutThrown;
        ++session.KnockoutThrown;
        ++stats[current.playlist].KnockoutThrown;
        ++always_gm[current.playlist].KnockoutThrown;

        ++always.KnockoutThrownCumul;
        ++current.stats.KnockoutThrownCumul;
        ++session.KnockoutThrownCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutThrownCumul;
            ++always_gm[it->first].KnockoutThrownCumul;
        }

        AllKnockoutThrown(true);
    }
    else if (name == "KO_Grabbed")
    {
        ++always.KnockoutGrabbed;
        ++current.stats.KnockoutGrabbed;
        ++session.KnockoutGrabbed;
        ++stats[current.playlist].KnockoutGrabbed;
        ++always_gm[current.playlist].KnockoutGrabbed;

        ++always.KnockoutGrabbedCumul;
        ++current.stats.KnockoutGrabbedCumul;
        ++session.KnockoutGrabbedCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutGrabbedCumul;
            ++always_gm[it->first].KnockoutGrabbedCumul;
        }

        AllKnockoutGrabbed(true);
    }
    else if (name == "KO_HitTaken")
    {
        ++always.KnockoutHitTaken;
        ++current.stats.KnockoutHitTaken;
        ++session.KnockoutHitTaken;
        ++stats[current.playlist].KnockoutHitTaken;
        ++always_gm[current.playlist].KnockoutHitTaken;

        ++always.KnockoutHitTakenCumul;
        ++current.stats.KnockoutHitTakenCumul;
        ++session.KnockoutHitTakenCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutHitTakenCumul;
            ++always_gm[it->first].KnockoutHitTakenCumul;
        }

        AllKnockoutHitTaken(true);
    }
    else if (name == "KO_LightHit")
    {
        ++always.KnockoutLightHit;
        ++current.stats.KnockoutLightHit;
        ++session.KnockoutLightHit;
        ++stats[current.playlist].KnockoutLightHit;
        ++always_gm[current.playlist].KnockoutLightHit;

        ++always.KnockoutLightHitCumul;
        ++current.stats.KnockoutLightHitCumul;
        ++session.KnockoutLightHitCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutLightHitCumul;
            ++always_gm[it->first].KnockoutLightHitCumul;
        }

        AllKnockoutLightHit(true);
    }
    else if (name == "KO_BlockTaken")
    {
        ++always.KnockoutBlockTaken;
        ++current.stats.KnockoutBlockTaken;
        ++session.KnockoutBlockTaken;
        ++stats[current.playlist].KnockoutBlockTaken;
        ++always_gm[current.playlist].KnockoutBlockTaken;

        ++always.KnockoutBlockTakenCumul;
        ++current.stats.KnockoutBlockTakenCumul;
        ++session.KnockoutBlockTakenCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutBlockTakenCumul;
            ++always_gm[it->first].KnockoutBlockTakenCumul;
        }

        AllKnockoutBlockTaken(true);
    }
    else if (name == "KO_LightBlock")
    {
        ++always.KnockoutLightBlock;
        ++current.stats.KnockoutLightBlock;
        ++session.KnockoutLightBlock;
        ++stats[current.playlist].KnockoutLightBlock;
        ++always_gm[current.playlist].KnockoutLightBlock;

        ++always.KnockoutLightBlockCumul;
        ++current.stats.KnockoutLightBlockCumul;
        ++session.KnockoutLightBlockCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutLightBlockCumul;
            ++always_gm[it->first].KnockoutLightBlockCumul;
        }

        AllKnockoutLightBlock(true);
    }
    else if (name == "KO_PlayerThrown")
    {
        ++always.KnockoutPlayerThrown;
        ++current.stats.KnockoutPlayerThrown;
        ++session.KnockoutPlayerThrown;
        ++stats[current.playlist].KnockoutPlayerThrown;
        ++always_gm[current.playlist].KnockoutPlayerThrown;

        ++always.KnockoutPlayerThrownCumul;
        ++current.stats.KnockoutPlayerThrownCumul;
        ++session.KnockoutPlayerThrownCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutPlayerThrownCumul;
            ++always_gm[it->first].KnockoutPlayerThrownCumul;
        }

        AllKnockoutPlayerThrown(true);
    }
    else if (name == "KO_PlayerGrabbed")
    {
        ++always.KnockoutPlayerGrabbed;
        ++current.stats.KnockoutPlayerGrabbed;
        ++session.KnockoutPlayerGrabbed;
        ++stats[current.playlist].KnockoutPlayerGrabbed;
        ++always_gm[current.playlist].KnockoutPlayerGrabbed;

        ++always.KnockoutPlayerGrabbedCumul;
        ++current.stats.KnockoutPlayerGrabbedCumul;
        ++session.KnockoutPlayerGrabbedCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutPlayerGrabbedCumul;
            ++always_gm[it->first].KnockoutPlayerGrabbedCumul;
        }

        AllKnockoutPlayerGrabbed(true);
    }
    else
    {
        if (name == "Demolish" || name == "Shot" || name == "Goal" || name == "LongGoal" || name == "HatTrick" || name == "BackwardsGoal" || name == "HoopsSwishGoal" || name == "BreakoutDamage" || name == "BreakoutDamageLarge" || name == "OvertimeGoal" || name == "Playmaker" || name == "AerialGoal" || name == "Assist" || name == "Save" || name == "EpicSave" || name == "Savior" || name == "MVP" || name == "BicycleHit" || name == "TurtleGoal")
            return;

        refresh = false;
        cvarManager->log("onStatEvent e:" + name + "=" + std::to_string(event.GetPoints()));
    }

    if (refresh)
        SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::onStatTickerMessage(ServerWrapper caller, void* params)
{
    StatTickerParams* pstats = (StatTickerParams*)params;
    if (!is_online_game)
        return;

    CarWrapper me = gameWrapper->GetLocalCar();
    PriWrapper receiver = PriWrapper(pstats->Receiver);
    PriWrapper victim = PriWrapper(pstats->Victim);
    StatEventWrapper event = StatEventWrapper(pstats->StatEvent);

    bool iam_receiver = (receiver.IsNull() ? false : isPrimaryPlayer(receiver));
    bool iam_victim = (victim.IsNull() ? false : isPrimaryPlayer(victim));
    bool team_receiver = (!me.IsNull() && !receiver.IsNull() && me.GetTeamNum2() == receiver.GetTeamNum2());
    bool team_victim = (!me.IsNull() && !victim.IsNull() && me.GetTeamNum2() == victim.GetTeamNum2());

    bool refresh = true;
    std::string name = event.GetEventName();
    if (name == "BicycleHit")
    {
        ++always.TotalBicycleHit;
        ++current.stats.TotalBicycleHit;
        ++session.TotalBicycleHit;
        ++stats[current.playlist].TotalBicycleHit;
        ++always_gm[current.playlist].TotalBicycleHit;

        ++(iam_receiver ? always.BicycleHit : always.TeamBicycleHit);
        ++(iam_receiver ? current.stats.BicycleHit : current.stats.TeamBicycleHit);
        ++(iam_receiver ? session.BicycleHit : session.TeamBicycleHit);
        ++(iam_receiver ? stats[current.playlist].BicycleHit : stats[current.playlist].TeamBicycleHit);
        ++(iam_receiver ? always_gm[current.playlist].BicycleHit : always_gm[current.playlist].TeamBicycleHit);

        ++always.TotalBicycleHitCumul;
        ++current.stats.TotalBicycleHitCumul;
        ++session.TotalBicycleHitCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalBicycleHitCumul;
            ++always_gm[it->first].TotalBicycleHitCumul;

            ++(iam_receiver ? stats[it->first].BicycleHitCumul : stats[it->first].TeamBicycleHitCumul);
            ++(iam_receiver ? always_gm[it->first].BicycleHitCumul : always_gm[it->first].TeamBicycleHitCumul);
        }

        AllShotsBicycleHit(true);
    }
    else if (name == "Shot")
    {
        ++always.TotalShotOnGoal;
        ++current.stats.TotalShotOnGoal;
        ++session.TotalShotOnGoal;
        ++stats[current.playlist].TotalShotOnGoal;
        ++always_gm[current.playlist].TotalShotOnGoal;

        ++(iam_receiver ? always.ShotOnGoal : always.TeamShotOnGoal);
        ++(iam_receiver ? current.stats.ShotOnGoal : current.stats.TeamShotOnGoal);
        ++(iam_receiver ? session.ShotOnGoal : session.TeamShotOnGoal);
        ++(iam_receiver ? stats[current.playlist].ShotOnGoal : stats[current.playlist].TeamShotOnGoal);
        ++(iam_receiver ? always_gm[current.playlist].ShotOnGoal : always_gm[current.playlist].TeamShotOnGoal);

        ++always.TotalShotOnGoalCumul;
        ++current.stats.TotalShotOnGoalCumul;
        ++session.TotalShotOnGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalShotOnGoalCumul;
            ++always_gm[it->first].TotalShotOnGoalCumul;

            ++(iam_receiver ? stats[it->first].ShotOnGoalCumul : stats[it->first].TeamShotOnGoalCumul);
            ++(iam_receiver ? always_gm[it->first].ShotOnGoalCumul : always_gm[it->first].TeamShotOnGoalCumul);
        }

        AllShotsShotOnGoal(true);
    }
    else if (name == "Assist")
    {
        ++always.TotalAssist;
        ++current.stats.TotalAssist;
        ++session.TotalAssist;
        ++stats[current.playlist].TotalAssist;
        ++always_gm[current.playlist].TotalAssist;

        ++(iam_receiver ? always.Assist : always.TeamAssist);
        ++(iam_receiver ? current.stats.Assist : current.stats.TeamAssist);
        ++(iam_receiver ? session.Assist : session.TeamAssist);
        ++(iam_receiver ? stats[current.playlist].Assist : stats[current.playlist].TeamAssist);
        ++(iam_receiver ? always_gm[current.playlist].Assist : always_gm[current.playlist].TeamAssist);

        ++always.TotalAssistCumul;
        ++current.stats.TotalAssistCumul;
        ++session.TotalAssistCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalAssistCumul;
            ++always_gm[it->first].TotalAssistCumul;

            ++(iam_receiver ? stats[it->first].AssistCumul : stats[it->first].TeamAssistCumul);
            ++(iam_receiver ? always_gm[it->first].AssistCumul : always_gm[it->first].TeamAssistCumul);
        }

        AllShotsAssist(true);
    }
    else if (name == "Save")
    {
        ++always.TotalSave;
        ++current.stats.TotalSave;
        ++session.TotalSave;
        ++stats[current.playlist].TotalSave;
        ++always_gm[current.playlist].TotalSave;

        ++(iam_receiver ? always.Save : always.TeamSave);
        ++(iam_receiver ? current.stats.Save : current.stats.TeamSave);
        ++(iam_receiver ? session.Save : session.TeamSave);
        ++(iam_receiver ? stats[current.playlist].Save : stats[current.playlist].TeamSave);
        ++(iam_receiver ? always_gm[current.playlist].Save : always_gm[current.playlist].TeamSave);

        ++always.TotalSaveCumul;
        ++current.stats.TotalSaveCumul;
        ++session.TotalSaveCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalSaveCumul;
            ++always_gm[it->first].TotalSaveCumul;

            ++(iam_receiver ? stats[it->first].SaveCumul : stats[it->first].TeamSaveCumul);
            ++(iam_receiver ? always_gm[it->first].SaveCumul : always_gm[it->first].TeamSaveCumul);
        }

        AllSavesSave(true);
    }
    else if (name == "EpicSave")
    {
        ++always.TotalEpicSave;
        ++current.stats.TotalEpicSave;
        ++session.TotalEpicSave;
        ++stats[current.playlist].TotalEpicSave;
        ++always_gm[current.playlist].TotalEpicSave;

        ++(iam_receiver ? always.EpicSave : always.TeamEpicSave);
        ++(iam_receiver ? current.stats.EpicSave : current.stats.TeamEpicSave);
        ++(iam_receiver ? session.EpicSave : session.TeamEpicSave);
        ++(iam_receiver ? stats[current.playlist].EpicSave : stats[current.playlist].TeamEpicSave);
        ++(iam_receiver ? always_gm[current.playlist].EpicSave : always_gm[current.playlist].TeamEpicSave);

        ++always.TotalEpicSaveCumul;
        ++current.stats.TotalEpicSaveCumul;
        ++session.TotalEpicSaveCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalEpicSaveCumul;
            ++always_gm[it->first].TotalEpicSaveCumul;

            ++(iam_receiver ? stats[it->first].EpicSaveCumul : stats[it->first].TeamEpicSaveCumul);
            ++(iam_receiver ? always_gm[it->first].EpicSaveCumul : always_gm[it->first].TeamEpicSaveCumul);
        }

        AllSavesEpicSave(true);
    }
    else if (name == "Goal")
    {
        ++always.TotalGoal;
        ++current.stats.TotalGoal;
        ++session.TotalGoal;
        ++stats[current.playlist].TotalGoal;
        ++always_gm[current.playlist].TotalGoal;

        ++(iam_receiver ? always.Goal : always.TeamGoal);
        ++(iam_receiver ? current.stats.Goal : current.stats.TeamGoal);
        ++(iam_receiver ? session.Goal : session.TeamGoal);
        ++(iam_receiver ? stats[current.playlist].Goal : stats[current.playlist].TeamGoal);
        ++(iam_receiver ? always_gm[current.playlist].Goal : always_gm[current.playlist].TeamGoal);

        ++always.TotalGoalCumul;
        ++current.stats.TotalGoalCumul;
        ++session.TotalGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalGoalCumul;
            ++always_gm[it->first].TotalGoalCumul;

            ++(iam_receiver ? stats[it->first].GoalCumul : stats[it->first].TeamGoalCumul);
            ++(iam_receiver ? always_gm[it->first].GoalCumul : always_gm[it->first].TeamGoalCumul);
        }

        AllGoalsGoal(true);
    }
    else if (name == "AerialGoal")
    {
        ++always.TotalAerialGoal;
        ++current.stats.TotalAerialGoal;
        ++session.TotalAerialGoal;
        ++stats[current.playlist].TotalAerialGoal;
        ++always_gm[current.playlist].TotalAerialGoal;

        ++(iam_receiver ? always.AerialGoal : always.TeamAerialGoal);
        ++(iam_receiver ? current.stats.AerialGoal : current.stats.TeamAerialGoal);
        ++(iam_receiver ? session.AerialGoal : session.TeamAerialGoal);
        ++(iam_receiver ? stats[current.playlist].AerialGoal : stats[current.playlist].TeamAerialGoal);
        ++(iam_receiver ? always_gm[current.playlist].AerialGoal : always_gm[current.playlist].TeamAerialGoal);

        ++always.TotalAerialGoalCumul;
        ++current.stats.TotalAerialGoalCumul;
        ++session.TotalAerialGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalAerialGoalCumul;
            ++always_gm[it->first].TotalAerialGoalCumul;

            ++(iam_receiver ? stats[it->first].AerialGoalCumul : stats[it->first].TeamAerialGoalCumul);
            ++(iam_receiver ? always_gm[it->first].AerialGoalCumul : always_gm[it->first].TeamAerialGoalCumul);
        }

        AllGoalsAerialGoal(true);
    }
    else if (name == "BackwardsGoal")
    {
        ++always.TotalBackwardsGoal;
        ++current.stats.TotalBackwardsGoal;
        ++session.TotalBackwardsGoal;
        ++stats[current.playlist].TotalBackwardsGoal;
        ++always_gm[current.playlist].TotalBackwardsGoal;

        ++(iam_receiver ? always.BackwardsGoal : always.TeamBackwardsGoal);
        ++(iam_receiver ? current.stats.BackwardsGoal : current.stats.TeamBackwardsGoal);
        ++(iam_receiver ? session.BackwardsGoal : session.TeamBackwardsGoal);
        ++(iam_receiver ? stats[current.playlist].BackwardsGoal : stats[current.playlist].TeamBackwardsGoal);
        ++(iam_receiver ? always_gm[current.playlist].BackwardsGoal : always_gm[current.playlist].TeamBackwardsGoal);

        ++always.TotalBackwardsGoalCumul;
        ++current.stats.TotalBackwardsGoalCumul;
        ++session.TotalBackwardsGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalBackwardsGoalCumul;
            ++always_gm[it->first].TotalBackwardsGoalCumul;

            ++(iam_receiver ? stats[it->first].BackwardsGoalCumul : stats[it->first].TeamBackwardsGoalCumul);
            ++(iam_receiver ? always_gm[it->first].BackwardsGoalCumul : always_gm[it->first].TeamBackwardsGoalCumul);
        }

        AllGoalsBackwardsGoal(true);
    }
    else if (name == "BicycleGoal")
    {
        cvarManager->log(" --> BicycleGoal " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.TotalBicycleGoal;
        ++current.stats.TotalBicycleGoal;
        ++session.TotalBicycleGoal;
        ++stats[current.playlist].TotalBicycleGoal;
        ++always_gm[current.playlist].TotalBicycleGoal;

        ++(iam_receiver ? always.BicycleGoal : always.TeamBicycleGoal);
        ++(iam_receiver ? current.stats.BicycleGoal : current.stats.TeamBicycleGoal);
        ++(iam_receiver ? session.BicycleGoal : session.TeamBicycleGoal);
        ++(iam_receiver ? stats[current.playlist].BicycleGoal : stats[current.playlist].TeamBicycleGoal);
        ++(iam_receiver ? always_gm[current.playlist].BicycleGoal : always_gm[current.playlist].TeamBicycleGoal);

        ++always.TotalBicycleGoalCumul;
        ++current.stats.TotalBicycleGoalCumul;
        ++session.TotalBicycleGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalBicycleGoalCumul;
            ++always_gm[it->first].TotalBicycleGoalCumul;

            ++(iam_receiver ? stats[it->first].BicycleGoalCumul : stats[it->first].TeamBicycleGoalCumul);
            ++(iam_receiver ? always_gm[it->first].BicycleGoalCumul : always_gm[it->first].TeamBicycleGoalCumul);
        }

        AllGoalsBicycleGoal(true);
    }
    else if (name == "LongGoal")
    {
        ++always.TotalLongGoal;
        ++current.stats.TotalLongGoal;
        ++session.TotalLongGoal;
        ++stats[current.playlist].TotalLongGoal;
        ++always_gm[current.playlist].TotalLongGoal;

        ++(iam_receiver ? always.LongGoal : always.TeamLongGoal);
        ++(iam_receiver ? current.stats.LongGoal : current.stats.TeamLongGoal);
        ++(iam_receiver ? session.LongGoal : session.TeamLongGoal);
        ++(iam_receiver ? stats[current.playlist].LongGoal : stats[current.playlist].TeamLongGoal);
        ++(iam_receiver ? always_gm[current.playlist].LongGoal : always_gm[current.playlist].TeamLongGoal);

        ++always.TotalLongGoalCumul;
        ++current.stats.TotalLongGoalCumul;
        ++session.TotalLongGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalLongGoalCumul;
            ++always_gm[it->first].TotalLongGoalCumul;

            ++(iam_receiver ? stats[it->first].LongGoalCumul : stats[it->first].TeamLongGoalCumul);
            ++(iam_receiver ? always_gm[it->first].LongGoalCumul : always_gm[it->first].TeamLongGoalCumul);
        }

        AllGoalsLongGoal(true);
    }
    else if (name == "TurtleGoal")
    {
        ++always.TotalTurtleGoal;
        ++current.stats.TotalTurtleGoal;
        ++session.TotalTurtleGoal;
        ++stats[current.playlist].TotalTurtleGoal;
        ++always_gm[current.playlist].TotalTurtleGoal;

        ++(iam_receiver ? always.TurtleGoal : always.TeamTurtleGoal);
        ++(iam_receiver ? current.stats.TurtleGoal : current.stats.TeamTurtleGoal);
        ++(iam_receiver ? session.TurtleGoal : session.TeamTurtleGoal);
        ++(iam_receiver ? stats[current.playlist].TurtleGoal : stats[current.playlist].TeamTurtleGoal);
        ++(iam_receiver ? always_gm[current.playlist].TurtleGoal : always_gm[current.playlist].TeamTurtleGoal);

        ++always.TotalTurtleGoalCumul;
        ++current.stats.TotalTurtleGoalCumul;
        ++session.TotalTurtleGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalTurtleGoalCumul;
            ++always_gm[it->first].TotalTurtleGoalCumul;

            ++(iam_receiver ? stats[it->first].TurtleGoalCumul : stats[it->first].TeamTurtleGoalCumul);
            ++(iam_receiver ? always_gm[it->first].TurtleGoalCumul : always_gm[it->first].TeamTurtleGoalCumul);
        }

        AllGoalsTurtleGoal(true);
    }
    else if (name == "OvertimeGoal")
    {
        ++always.TotalOvertimeGoal;
        ++current.stats.TotalOvertimeGoal;
        ++session.TotalOvertimeGoal;
        ++stats[current.playlist].TotalOvertimeGoal;
        ++always_gm[current.playlist].TotalOvertimeGoal;

        ++(iam_receiver ? always.OvertimeGoal : always.TeamOvertimeGoal);
        ++(iam_receiver ? current.stats.OvertimeGoal : current.stats.TeamOvertimeGoal);
        ++(iam_receiver ? session.OvertimeGoal : session.TeamOvertimeGoal);
        ++(iam_receiver ? stats[current.playlist].OvertimeGoal : stats[current.playlist].TeamOvertimeGoal);
        ++(iam_receiver ? always_gm[current.playlist].OvertimeGoal : always_gm[current.playlist].TeamOvertimeGoal);

        ++always.TotalOvertimeGoalCumul;
        ++current.stats.TotalOvertimeGoalCumul;
        ++session.TotalOvertimeGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalOvertimeGoalCumul;
            ++always_gm[it->first].TotalOvertimeGoalCumul;

            ++(iam_receiver ? stats[it->first].OvertimeGoalCumul : stats[it->first].TeamOvertimeGoalCumul);
            ++(iam_receiver ? always_gm[it->first].OvertimeGoalCumul : always_gm[it->first].TeamOvertimeGoalCumul);
        }

        AllGoalsOvertimeGoal(true);
    }
    else if (name == "HoopsSwishGoal")
    {
        ++always.TotalHoopsSwishGoal;
        ++current.stats.TotalHoopsSwishGoal;
        ++session.TotalHoopsSwishGoal;
        ++stats[current.playlist].TotalHoopsSwishGoal;
        ++always_gm[current.playlist].TotalHoopsSwishGoal;

        ++(iam_receiver ? always.HoopsSwishGoal : always.TeamHoopsSwishGoal);
        ++(iam_receiver ? current.stats.HoopsSwishGoal : current.stats.TeamHoopsSwishGoal);
        ++(iam_receiver ? session.HoopsSwishGoal : session.TeamHoopsSwishGoal);
        ++(iam_receiver ? stats[current.playlist].HoopsSwishGoal : stats[current.playlist].TeamHoopsSwishGoal);
        ++(iam_receiver ? always_gm[current.playlist].HoopsSwishGoal : always_gm[current.playlist].TeamHoopsSwishGoal);

        ++always.TotalHoopsSwishGoalCumul;
        ++current.stats.TotalHoopsSwishGoalCumul;
        ++session.TotalHoopsSwishGoalCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalHoopsSwishGoalCumul;
            ++always_gm[it->first].TotalHoopsSwishGoalCumul;

            ++(iam_receiver ? stats[it->first].HoopsSwishGoalCumul : stats[it->first].TeamHoopsSwishGoalCumul);
            ++(iam_receiver ? always_gm[it->first].HoopsSwishGoalCumul : always_gm[it->first].TeamHoopsSwishGoalCumul);
        }

        AllGoalsHoopsSwishGoal(true);
    }
    else if (name == "PoolShot")
    {
        cvarManager->log(" --> PoolShot " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.TotalPoolShot;
        ++current.stats.TotalPoolShot;
        ++session.TotalPoolShot;
        ++stats[current.playlist].TotalPoolShot;
        ++always_gm[current.playlist].TotalPoolShot;

        ++(iam_receiver ? always.PoolShot : always.TeamPoolShot);
        ++(iam_receiver ? current.stats.PoolShot : current.stats.TeamPoolShot);
        ++(iam_receiver ? session.PoolShot : session.TeamPoolShot);
        ++(iam_receiver ? stats[current.playlist].PoolShot : stats[current.playlist].TeamPoolShot);
        ++(iam_receiver ? always_gm[current.playlist].PoolShot : always_gm[current.playlist].TeamPoolShot);

        ++always.TotalPoolShotCumul;
        ++current.stats.TotalPoolShotCumul;
        ++session.TotalPoolShotCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalPoolShotCumul;
            ++always_gm[it->first].TotalPoolShotCumul;

            ++(iam_receiver ? stats[it->first].PoolShotCumul : stats[it->first].TeamPoolShotCumul);
            ++(iam_receiver ? always_gm[it->first].PoolShotCumul : always_gm[it->first].TeamPoolShotCumul);
        }

        AllGoalsPoolShot(true);
    }
    else if (name == "FirstTouch")
    {
        ++always.FirstTouch;
        ++current.stats.FirstTouch;
        ++session.FirstTouch;
        ++stats[current.playlist].FirstTouch;
        ++always_gm[current.playlist].FirstTouch;

        ++always.FirstTouchCumul;
        ++current.stats.FirstTouchCumul;
        ++session.FirstTouchCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].FirstTouchCumul;
            ++always_gm[it->first].FirstTouchCumul;
        }

        AllMiscsFirstTouch(true);
    }
    else if (name == "Savior")
    {
        ++always.TotalSavior;
        ++current.stats.TotalSavior;
        ++session.TotalSavior;
        ++stats[current.playlist].TotalSavior;
        ++always_gm[current.playlist].TotalSavior;

        ++(iam_receiver ? always.Savior : always.TeamSavior);
        ++(iam_receiver ? current.stats.Savior : current.stats.TeamSavior);
        ++(iam_receiver ? session.Savior : session.TeamSavior);
        ++(iam_receiver ? stats[current.playlist].Savior : stats[current.playlist].TeamSavior);
        ++(iam_receiver ? always_gm[current.playlist].Savior : always_gm[current.playlist].TeamSavior);

        ++always.TotalSaviorCumul;
        ++current.stats.TotalSaviorCumul;
        ++session.TotalSaviorCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalSaviorCumul;
            ++always_gm[it->first].TotalSaviorCumul;

            ++(iam_receiver ? stats[it->first].SaviorCumul : stats[it->first].TeamSaviorCumul);
            ++(iam_receiver ? always_gm[it->first].SaviorCumul : always_gm[it->first].TeamSaviorCumul);
        }

        AllMiscsSavior(true);
    }
    else if (name == "LowFive")
    {
        cvarManager->log(" --> LowFive " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.TotalLowFive;
        ++current.stats.TotalLowFive;
        ++session.TotalLowFive;
        ++stats[current.playlist].TotalLowFive;
        ++always_gm[current.playlist].TotalLowFive;

        ++(iam_receiver ? always.LowFive : always.TeamLowFive);
        ++(iam_receiver ? current.stats.LowFive : current.stats.TeamLowFive);
        ++(iam_receiver ? session.LowFive : session.TeamLowFive);
        ++(iam_receiver ? stats[current.playlist].LowFive : stats[current.playlist].TeamLowFive);
        ++(iam_receiver ? always_gm[current.playlist].LowFive : always_gm[current.playlist].TeamLowFive);

        ++always.TotalLowFiveCumul;
        ++current.stats.TotalLowFiveCumul;
        ++session.TotalLowFiveCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalLowFiveCumul;
            ++always_gm[it->first].TotalLowFiveCumul;

            ++(iam_receiver ? stats[it->first].LowFiveCumul : stats[it->first].TeamLowFiveCumul);
            ++(iam_receiver ? always_gm[it->first].LowFiveCumul : always_gm[it->first].TeamLowFiveCumul);
        }

        AllMiscsLowFive(true);
    }
    else if (name == "HatTrick")
    {
        ++always.TotalHatTrick;
        ++current.stats.TotalHatTrick;
        ++session.TotalHatTrick;
        ++stats[current.playlist].TotalHatTrick;
        ++always_gm[current.playlist].TotalHatTrick;

        ++(iam_receiver ? always.HatTrick : always.TeamHatTrick);
        ++(iam_receiver ? current.stats.HatTrick : current.stats.TeamHatTrick);
        ++(iam_receiver ? session.HatTrick : session.TeamHatTrick);
        ++(iam_receiver ? stats[current.playlist].HatTrick : stats[current.playlist].TeamHatTrick);
        ++(iam_receiver ? always_gm[current.playlist].HatTrick : always_gm[current.playlist].TeamHatTrick);

        ++always.TotalHatTrickCumul;
        ++current.stats.TotalHatTrickCumul;
        ++session.TotalHatTrickCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalHatTrickCumul;
            ++always_gm[it->first].TotalHatTrickCumul;

            ++(iam_receiver ? stats[it->first].HatTrickCumul : stats[it->first].TeamHatTrickCumul);
            ++(iam_receiver ? always_gm[it->first].HatTrickCumul : always_gm[it->first].TeamHatTrickCumul);
        }

        AllMiscsHatTrick(true);
    }
    else if (name == "HighFive")
    {
        cvarManager->log(" --> HighFive " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.TotalHighFive;
        ++current.stats.TotalHighFive;
        ++session.TotalHighFive;
        ++stats[current.playlist].TotalHighFive;
        ++always_gm[current.playlist].TotalHighFive;

        ++(iam_receiver ? always.HighFive : always.TeamHighFive);
        ++(iam_receiver ? current.stats.HighFive : current.stats.TeamHighFive);
        ++(iam_receiver ? session.HighFive : session.TeamHighFive);
        ++(iam_receiver ? stats[current.playlist].HighFive : stats[current.playlist].TeamHighFive);
        ++(iam_receiver ? always_gm[current.playlist].HighFive : always_gm[current.playlist].TeamHighFive);

        ++always.TotalHighFiveCumul;
        ++current.stats.TotalHighFiveCumul;
        ++session.TotalHighFiveCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalHighFiveCumul;
            ++always_gm[it->first].TotalHighFiveCumul;

            ++(iam_receiver ? stats[it->first].HighFiveCumul : stats[it->first].TeamHighFiveCumul);
            ++(iam_receiver ? always_gm[it->first].HighFiveCumul : always_gm[it->first].TeamHighFiveCumul);
        }

        AllMiscsHighFive(true);
    }
    else if (name == "Playmaker")
    {
        ++always.TotalPlaymaker;
        ++current.stats.TotalPlaymaker;
        ++session.TotalPlaymaker;
        ++stats[current.playlist].TotalPlaymaker;
        ++always_gm[current.playlist].TotalPlaymaker;

        ++(iam_receiver ? always.Playmaker : always.TeamPlaymaker);
        ++(iam_receiver ? current.stats.Playmaker : current.stats.TeamPlaymaker);
        ++(iam_receiver ? session.Playmaker : session.TeamPlaymaker);
        ++(iam_receiver ? stats[current.playlist].Playmaker : stats[current.playlist].TeamPlaymaker);
        ++(iam_receiver ? always_gm[current.playlist].Playmaker : always_gm[current.playlist].TeamPlaymaker);

        ++always.TotalPlaymakerCumul;
        ++current.stats.TotalPlaymakerCumul;
        ++session.TotalPlaymakerCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalPlaymakerCumul;
            ++always_gm[it->first].TotalPlaymakerCumul;

            ++(iam_receiver ? stats[it->first].PlaymakerCumul : stats[it->first].TeamPlaymakerCumul);
            ++(iam_receiver ? always_gm[it->first].PlaymakerCumul : always_gm[it->first].TeamPlaymakerCumul);
        }

        AllMiscsPlaymaker(true);
    }
    else if (name == "Demolish")
    {
        cvarManager->log(" --> Demolish " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));
        if (iam_receiver || iam_victim || team_receiver || team_victim)
        {
            ++((iam_receiver || team_receiver) ? always.TotalDemolitions : always.TotalDeath);
            ++((iam_receiver || team_receiver) ? current.stats.TotalDemolitions : current.stats.TotalDeath);
            ++((iam_receiver || team_receiver) ? session.TotalDemolitions : session.TotalDeath);
            ++((iam_receiver || team_receiver) ? stats[current.playlist].TotalDemolitions : stats[current.playlist].TotalDeath);
            ++((iam_receiver || team_receiver) ? always_gm[current.playlist].TotalDemolitions : always_gm[current.playlist].TotalDeath);

            ++((iam_receiver || team_receiver) ? always.TotalDemolitionsCumul : always.TotalDeathCumul);
            ++((iam_receiver || team_receiver) ? current.stats.TotalDemolitionsCumul : current.stats.TotalDeathCumul);
            ++((iam_receiver || team_receiver) ? session.TotalDemolitionsCumul : session.TotalDeathCumul);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++((iam_receiver || team_receiver) ? stats[it->first].TotalDemolitionsCumul : stats[it->first].TotalDeathCumul);
                ++((iam_receiver || team_receiver) ? always_gm[it->first].TotalDemolitionsCumul : always_gm[it->first].TotalDeathCumul);
            }
        }

        if (iam_receiver || iam_victim)
        {
            ++(iam_receiver ? always.Demolitions : always.Death);
            ++(iam_receiver ? current.stats.Demolitions : current.stats.Death);
            ++(iam_receiver ? session.Demolitions : session.Death);
            ++(iam_receiver ? stats[current.playlist].Demolitions : stats[current.playlist].Death);
            ++(iam_receiver ? always_gm[current.playlist].Demolitions : always_gm[current.playlist].Death);

            ++(iam_receiver ? always.DemolitionsCumul : always.DeathCumul);
            ++(iam_receiver ? current.stats.DemolitionsCumul : current.stats.DeathCumul);
            ++(iam_receiver ? session.DemolitionsCumul : session.DeathCumul);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++(iam_receiver ? stats[it->first].DemolitionsCumul : stats[it->first].DeathCumul);
                ++(iam_receiver ? always_gm[it->first].DemolitionsCumul : always_gm[it->first].DeathCumul);
            }

            if (iam_receiver)
                AllMiscsDemolitions(true);
            else
                AllMiscsDeath(true);
        }
        else if (team_receiver || team_victim)
        {
            ++(team_receiver ? always.TeamDemolitions : always.TeamDeath);
            ++(team_receiver ? current.stats.TeamDemolitions : current.stats.TeamDeath);
            ++(team_receiver ? session.TeamDemolitions : session.TeamDeath);
            ++(team_receiver ? stats[current.playlist].TeamDemolitions : stats[current.playlist].TeamDeath);
            ++(team_receiver ? always_gm[current.playlist].TeamDemolitions : always_gm[current.playlist].TeamDeath);

            ++(team_receiver ? always.TeamDemolitionsCumul : always.TeamDeathCumul);
            ++(team_receiver ? current.stats.TeamDemolitionsCumul : current.stats.TeamDeathCumul);
            ++(team_receiver ? session.TeamDemolitionsCumul : session.TeamDeathCumul);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++(team_receiver ? stats[it->first].TeamDemolitionsCumul : stats[it->first].TeamDeathCumul);
                ++(team_receiver ? always_gm[it->first].TeamDemolitionsCumul : always_gm[it->first].TeamDeathCumul);
            }

            if (team_receiver)
                AllMiscsDemolitions(true);
            else
                AllMiscsDeath(true);
        }
    }
    else if (name == "BreakoutDamage")
    {
        ++always.TotalBreakoutDamage;
        ++current.stats.TotalBreakoutDamage;
        ++session.TotalBreakoutDamage;
        ++stats[current.playlist].TotalBreakoutDamage;
        ++always_gm[current.playlist].TotalBreakoutDamage;

        ++(iam_receiver ? always.BreakoutDamage : always.TeamBreakoutDamage);
        ++(iam_receiver ? current.stats.BreakoutDamage : current.stats.TeamBreakoutDamage);
        ++(iam_receiver ? session.BreakoutDamage : session.TeamBreakoutDamage);
        ++(iam_receiver ? stats[current.playlist].BreakoutDamage : stats[current.playlist].TeamBreakoutDamage);
        ++(iam_receiver ? always_gm[current.playlist].BreakoutDamage : always_gm[current.playlist].TeamBreakoutDamage);

        ++always.TotalBreakoutDamageCumul;
        ++current.stats.TotalBreakoutDamageCumul;
        ++session.TotalBreakoutDamageCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalBreakoutDamageCumul;
            ++always_gm[it->first].TotalBreakoutDamageCumul;

            ++(iam_receiver ? stats[it->first].BreakoutDamageCumul : stats[it->first].TeamBreakoutDamageCumul);
            ++(iam_receiver ? always_gm[it->first].BreakoutDamageCumul : always_gm[it->first].TeamBreakoutDamageCumul);
        }

        AllDropshotBreakoutDamage(true);
    }
    else if (name == "BreakoutDamageLarge")
    {
        ++always.TotalBreakoutDamageLarge;
        ++current.stats.TotalBreakoutDamageLarge;
        ++session.TotalBreakoutDamageLarge;
        ++stats[current.playlist].TotalBreakoutDamageLarge;
        ++always_gm[current.playlist].TotalBreakoutDamageLarge;

        ++(iam_receiver ? always.BreakoutDamageLarge : always.TeamBreakoutDamageLarge);
        ++(iam_receiver ? current.stats.BreakoutDamageLarge : current.stats.TeamBreakoutDamageLarge);
        ++(iam_receiver ? session.BreakoutDamageLarge : session.TeamBreakoutDamageLarge);
        ++(iam_receiver ? stats[current.playlist].BreakoutDamageLarge : stats[current.playlist].TeamBreakoutDamageLarge);
        ++(iam_receiver ? always_gm[current.playlist].BreakoutDamageLarge : always_gm[current.playlist].TeamBreakoutDamageLarge);

        ++always.TotalBreakoutDamageLargeCumul;
        ++current.stats.TotalBreakoutDamageLargeCumul;
        ++session.TotalBreakoutDamageLargeCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalBreakoutDamageLargeCumul;
            ++always_gm[it->first].TotalBreakoutDamageLargeCumul;

            ++(iam_receiver ? stats[it->first].BreakoutDamageLargeCumul : stats[it->first].TeamBreakoutDamageLargeCumul);
            ++(iam_receiver ? always_gm[it->first].BreakoutDamageLargeCumul : always_gm[it->first].TeamBreakoutDamageLargeCumul);
        }

        AllDropshotBreakoutDamageLarge(true);
    }
    else if (name == "KO_Knockout" && (iam_receiver || iam_victim)) // KO_Death
    {
        cvarManager->log(" --> " + name + " " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++(iam_receiver ? always.KnockoutDemolitions : always.Death);
        ++(iam_receiver ? current.stats.KnockoutDemolitions : current.stats.Death);
        ++(iam_receiver ? session.KnockoutDemolitions : session.Death);
        ++(iam_receiver ? stats[current.playlist].KnockoutDemolitions : stats[current.playlist].Death);
        ++(iam_receiver ? always_gm[current.playlist].KnockoutDemolitions : always_gm[current.playlist].Death);

        ++(iam_receiver ? always.KnockoutDemolitionsCumul : always.DeathCumul);
        ++(iam_receiver ? current.stats.KnockoutDemolitionsCumul : current.stats.DeathCumul);
        ++(iam_receiver ? session.KnockoutDemolitionsCumul : session.DeathCumul);

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++(iam_receiver ? stats[it->first].KnockoutDemolitionsCumul : stats[it->first].DeathCumul);
            ++(iam_receiver ? always_gm[it->first].KnockoutDemolitionsCumul : always_gm[it->first].DeathCumul);
        }

        AllKnockoutDeath(true);
    }
    else if (name == "KO_KnockoutAssist")
    {
        cvarManager->log(" --> KnockoutAssist " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.KnockoutAssist;
        ++current.stats.KnockoutAssist;
        ++session.KnockoutAssist;
        ++stats[current.playlist].KnockoutAssist;
        ++always_gm[current.playlist].KnockoutAssist;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutAssistCumul;
            ++always_gm[it->first].KnockoutAssistCumul;
        }

        AllKnockoutAssist(true);
    }
    else if (name == "KO_DoubleKO" && iam_receiver)
    {
        cvarManager->log(" --> KnockoutDoubleKO " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.KnockoutDoubleKO;
        ++current.stats.KnockoutDoubleKO;
        ++session.KnockoutDoubleKO;
        ++stats[current.playlist].KnockoutDoubleKO;
        ++always_gm[current.playlist].KnockoutDoubleKO;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutDoubleKOCumul;
            ++always_gm[it->first].KnockoutDoubleKOCumul;
        }

        AllKnockoutDoubleKO(true);
    }
    else if (name == "KO_HeavyHit")
    {
        cvarManager->log(" --> KnockoutHeavyHit " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.KnockoutHeavyHit;
        ++current.stats.KnockoutHeavyHit;
        ++session.KnockoutHeavyHit;
        ++stats[current.playlist].KnockoutHeavyHit;
        ++always_gm[current.playlist].KnockoutHeavyHit;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutHeavyHitCumul;
            ++always_gm[it->first].KnockoutHeavyHitCumul;
        }

        AllKnockoutHeavyHit(true);
    }
    else if (name == "KO_TripleKO")
    {
        cvarManager->log(" --> KnockoutTripleKO " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.KnockoutTripleKO;
        ++current.stats.KnockoutTripleKO;
        ++session.KnockoutTripleKO;
        ++stats[current.playlist].KnockoutTripleKO;
        ++always_gm[current.playlist].KnockoutTripleKO;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutTripleKOCumul;
            ++always_gm[it->first].KnockoutTripleKOCumul;
        }

        AllKnockoutTripleKO(true);
    }
    else if (name == "KO_HeavyBlock")
    {
        cvarManager->log(" --> KnockoutHeavyBlock " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.KnockoutHeavyBlock;
        ++current.stats.KnockoutHeavyBlock;
        ++session.KnockoutHeavyBlock;
        ++stats[current.playlist].KnockoutHeavyBlock;
        ++always_gm[current.playlist].KnockoutHeavyBlock;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutHeavyBlockCumul;
            ++always_gm[it->first].KnockoutHeavyBlockCumul;
        }

        AllKnockoutHeavyBlock(true);
    }
    else if (name == "KO_AerialHeavyHit")
    {
        cvarManager->log(" --> KnockoutAerialHeavyHit " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.KnockoutAerialHeavyHit;
        ++current.stats.KnockoutAerialHeavyHit;
        ++session.KnockoutAerialHeavyHit;
        ++stats[current.playlist].KnockoutAerialHeavyHit;
        ++always_gm[current.playlist].KnockoutAerialHeavyHit;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutAerialHeavyHitCumul;
            ++always_gm[it->first].KnockoutAerialHeavyHitCumul;
        }

        AllKnockoutAerialHeavyHit(true);
    }
    else if (name == "KO_AerialLightHit")
    {
        cvarManager->log(" --> KnockoutAerialLightHit " + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));

        ++always.KnockoutAerialLightHit;
        ++current.stats.KnockoutAerialLightHit;
        ++session.KnockoutAerialLightHit;
        ++stats[current.playlist].KnockoutAerialLightHit;
        ++always_gm[current.playlist].KnockoutAerialLightHit;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].KnockoutAerialLightHitCumul;
            ++always_gm[it->first].KnockoutAerialLightHitCumul;
        }

        AllKnockoutAerialLightHit(true);
    }
    else if (name == "MVP")
    {
        ++always.TotalMVP;
        ++current.stats.TotalMVP;
        ++session.TotalMVP;
        ++stats[current.playlist].TotalMVP;
        ++always_gm[current.playlist].TotalMVP;

        ++(iam_receiver ? always.MVP : always.TeamMVP);
        ++(iam_receiver ? current.stats.MVP : current.stats.TeamMVP);
        ++(iam_receiver ? session.MVP : session.TeamMVP);
        ++(iam_receiver ? stats[current.playlist].MVP : stats[current.playlist].TeamMVP);
        ++(iam_receiver ? always_gm[current.playlist].MVP : always_gm[current.playlist].TeamMVP);

        ++always.TotalMVPCumul;
        ++current.stats.TotalMVPCumul;
        ++session.TotalMVPCumul;

        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            ++stats[it->first].TotalMVPCumul;
            ++always_gm[it->first].TotalMVPCumul;

            ++(iam_receiver ? stats[it->first].MVPCumul : stats[it->first].TeamMVPCumul);
            ++(iam_receiver ? always_gm[it->first].MVPCumul : always_gm[it->first].TeamMVPCumul);
        }

        AllCertificationsMVP(true);
    }
    else
    {
        refresh = false;
        cvarManager->log("onStatTickerMessage " + name + "=" + std::to_string(event.GetPoints()) + std::string(iam_receiver ? "iam_receiver" : (iam_victim ? "iam_victim" : "-")) + " " + std::string(team_receiver ? "team_receiver" : (team_victim ? "team_victim" : "-")));
    }

    if (refresh)
        SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::onGoalScore(std::string eventName)
{
    TeamWrapper player = GetTeam(false);
    TeamWrapper opposite = GetTeam(true);

    //if (!player.IsNull())
    //    cvarManager->log(" --> Score Player: " + std::to_string(player.GetScore()));
    //if (!opposite.IsNull())
    //    cvarManager->log(" --> Score Opposite: " + std::to_string(opposite.GetScore()));
}

void RocketStats::InitRank()
{
    int tier = current.tier;
    bool ranked = current.ranked;
    int playlist = current.playlist;

    last_rank = "";
    last_division = "";
    current = t_current();

    current.tier = tier;
    current.ranked = ranked;
    current.playlist = playlist;
}

void RocketStats::MajRank(bool isRanked, float _currentMMR, SkillRank playerRank)
{
    current.tier = playerRank.Tier;
    current.ranked = isRanked;

    if (isRanked)
    {
        current.preview_rank = GetRankName(playerRank.Tier, current.preview_rank_number);
        if (current.preview_rank_number)
            current.preview_rank += " {{Number}}";

        current.preview_division = "Div. {{Number}}";
        current.preview_division_number = (playerRank.Division + 1);

        if (current.playlist != 34 && playerRank.MatchesPlayed < 10)
        {
            current.rank = "Placement: " + std::to_string(playerRank.MatchesPlayed) + "/10";
            current.rank_number = 0;
            current.division = "";
            current.division_number = 0;
        }
        else
        {
            current.rank = current.preview_rank;
            current.rank_number = current.preview_rank_number;
            current.division = current.preview_division;
            current.division_number = current.preview_division_number;
        }
    }
    else
    {
        current.rank = GetPlaylistName(current.playlist);
        current.rank_number = 0;
        current.division = "";
        current.division_number = 0;

        current.preview_rank = current.rank;
        current.preview_rank_number = current.rank_number;
        current.preview_division = current.division;
        current.preview_division_number = current.division_number;
    }

    VarRank(true);
    VarDiv(true);

    SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::UpdateMMR(UniqueIDWrapper id)
{
    cvarManager->log("===== UpdateMMR =====");
    /*
    if (id.GetIdString() != gameWrapper->GetUniqueID().GetIdString()) {
        cvarManager->log("Not the user");
        return;
    }
    cvarManager->log("User match");
    */

    if (current.playlist == 0)
    {
        cvarManager->log("Invalid playlist id. Have you just opened the game ?");
        return;
    }

    MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
    float mmr = mmrw.GetPlayerMMR(id, current.playlist);
    SkillRank playerRank = mmrw.GetPlayerRank(id, current.playlist);

    if (stats[current.playlist].isInit)
    {
        float MMRChange = (mmr - stats[current.playlist].myMMR);

        always.MMRChange = MMRChange;
        session.MMRChange = MMRChange;
        stats[current.playlist].MMRChange = MMRChange;
        always_gm[current.playlist].MMRChange = MMRChange;

        always.MMRCumulChange += MMRChange;
        session.MMRCumulChange += MMRChange;
        stats[current.playlist].MMRCumulChange += MMRChange;
        always_gm[current.playlist].MMRCumulChange += MMRChange;
    }
    else
        stats[current.playlist].isInit = true;

    always.myMMR = mmr;
    session.myMMR = mmr;
    stats[current.playlist].myMMR = mmr;
    always_gm[current.playlist].myMMR = mmr;

    MajRank(mmrw.IsRanked(current.playlist), stats[current.playlist].myMMR, playerRank);
    SessionStats();
    VarMMR(true);
    VarMMRChange(true);

    SetRefresh(RefreshFlags_Refresh);
    cvarManager->log("===== !UpdateMMR =====");
}

void RocketStats::InitStats()
{
    session = Stats();
    for (auto& kv : stats)
        kv.second = Stats();

    always = Stats();
    always.isInit = true;
    for (auto& kv : always_gm)
    {
        kv.second = Stats();
        kv.second.isInit = true;
    }
}

void RocketStats::SessionStats()
{
    Stats tmp;

    for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        VarsSession(tmp, it->first, true);

    VarsSession(tmp);
    session.isInit = true;

    always.myMMR = session.myMMR;
    always.MMRChange = session.MMRChange;
    always.isInit = true;

    SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::ResetStats()
{
    InitStats();

    WriteConfig();
    ResetFiles();

    InitRank();
    SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::ResetBasicStats()
{
    current.stats = Stats();
}
