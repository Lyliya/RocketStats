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

        AllShotsFirstTouch(true);
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
    else
    {
        if (name == "Shot" || name == "Goal" || name == "LongGoal" || name == "HatTrick" || name == "BackwardsGoal" || name == "HoopsSwishGoal" || name == "BreakoutDamage" || name == "BreakoutDamageLarge" || name == "OvertimeGoal" || name == "Playmaker" || name == "AerialGoal" || name == "Assist" || name == "Save" || name == "EpicSave" || name == "Savior" || name == "MVP" || name == "BicycleHit" || name == "" || name == "" || name == "" || name == "")
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

    PriWrapper receiver = PriWrapper(pstats->Receiver);
    PriWrapper victim = PriWrapper(pstats->Victim);
    StatEventWrapper event = StatEventWrapper(pstats->StatEvent);

    bool me = isPrimaryPlayer(receiver);
    std::string name = event.GetEventName();
    if (name == "Demolish" && !receiver.IsNull() && !victim.IsNull())
    {
        bool demo = isPrimaryPlayer(receiver);
        if (demo && current.playlist)
        {
            ++always.demo;
            ++current.stats.demo;
            ++session.demo;
            ++stats[current.playlist].demo;
            ++always_gm[current.playlist].demo;

            ++always.demoCumul;
            ++current.stats.demoCumul;
            ++session.demoCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].demoCumul;
                ++always_gm[it->first].demoCumul;
            }

            SetRefresh(RefreshFlags_Refresh);
            VarDemolitions(true);
        }

        bool death = isPrimaryPlayer(victim);
        if (death && current.playlist)
        {
            ++always.death;
            ++current.stats.death;
            ++session.death;
            ++stats[current.playlist].death;
            ++always_gm[current.playlist].death;

            ++always.deathCumul;
            ++current.stats.deathCumul;
            ++session.deathCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].deathCumul;
                ++always_gm[it->first].deathCumul;
            }

            SetRefresh(RefreshFlags_Refresh);
            VarDeath(true);
        }
    }
    else
    {
        bool refresh = true;
        if (name == "BicycleHit")
        {
            ++always.TotalBicycleHit;
            ++current.stats.TotalBicycleHit;
            ++session.TotalBicycleHit;
            ++stats[current.playlist].TotalBicycleHit;
            ++always_gm[current.playlist].TotalBicycleHit;

            ++(me ? always.BicycleHit : always.TeamBicycleHit);
            ++(me ? current.stats.BicycleHit : current.stats.TeamBicycleHit);
            ++(me ? session.BicycleHit : session.TeamBicycleHit);
            ++(me ? stats[current.playlist].BicycleHit : stats[current.playlist].TeamBicycleHit);
            ++(me ? always_gm[current.playlist].BicycleHit : always_gm[current.playlist].TeamBicycleHit);

            ++always.TotalBicycleHitCumul;
            ++current.stats.TotalBicycleHitCumul;
            ++session.TotalBicycleHitCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBicycleHitCumul;
                ++always_gm[it->first].TotalBicycleHitCumul;

                ++(me ? stats[it->first].BicycleHitCumul : stats[it->first].TeamBicycleHitCumul);
                ++(me ? always_gm[it->first].BicycleHitCumul : always_gm[it->first].TeamBicycleHitCumul);
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

            ++(me ? always.ShotOnGoal : always.TeamShotOnGoal);
            ++(me ? current.stats.ShotOnGoal : current.stats.TeamShotOnGoal);
            ++(me ? session.ShotOnGoal : session.TeamShotOnGoal);
            ++(me ? stats[current.playlist].ShotOnGoal : stats[current.playlist].TeamShotOnGoal);
            ++(me ? always_gm[current.playlist].ShotOnGoal : always_gm[current.playlist].TeamShotOnGoal);

            ++always.TotalShotOnGoalCumul;
            ++current.stats.TotalShotOnGoalCumul;
            ++session.TotalShotOnGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalShotOnGoalCumul;
                ++always_gm[it->first].TotalShotOnGoalCumul;

                ++(me ? stats[it->first].ShotOnGoalCumul : stats[it->first].TeamShotOnGoalCumul);
                ++(me ? always_gm[it->first].ShotOnGoalCumul : always_gm[it->first].TeamShotOnGoalCumul);
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

            ++(me ? always.Assist : always.TeamAssist);
            ++(me ? current.stats.Assist : current.stats.TeamAssist);
            ++(me ? session.Assist : session.TeamAssist);
            ++(me ? stats[current.playlist].Assist : stats[current.playlist].TeamAssist);
            ++(me ? always_gm[current.playlist].Assist : always_gm[current.playlist].TeamAssist);

            ++always.TotalAssistCumul;
            ++current.stats.TotalAssistCumul;
            ++session.TotalAssistCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalAssistCumul;
                ++always_gm[it->first].TotalAssistCumul;

                ++(me ? stats[it->first].AssistCumul : stats[it->first].TeamAssistCumul);
                ++(me ? always_gm[it->first].AssistCumul : always_gm[it->first].TeamAssistCumul);
            }

            AllShotsAssist(true);
        }
        else if (name == "Goal")
        {
            ++always.TotalGoal;
            ++current.stats.TotalGoal;
            ++session.TotalGoal;
            ++stats[current.playlist].TotalGoal;
            ++always_gm[current.playlist].TotalGoal;

            ++(me ? always.Goal : always.TeamGoal);
            ++(me ? current.stats.Goal : current.stats.TeamGoal);
            ++(me ? session.Goal : session.TeamGoal);
            ++(me ? stats[current.playlist].Goal : stats[current.playlist].TeamGoal);
            ++(me ? always_gm[current.playlist].Goal : always_gm[current.playlist].TeamGoal);

            ++always.TotalGoalCumul;
            ++current.stats.TotalGoalCumul;
            ++session.TotalGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalGoalCumul;
                ++always_gm[it->first].TotalGoalCumul;

                ++(me ? stats[it->first].GoalCumul : stats[it->first].TeamGoalCumul);
                ++(me ? always_gm[it->first].GoalCumul : always_gm[it->first].TeamGoalCumul);
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

            ++(me ? always.AerialGoal : always.TeamAerialGoal);
            ++(me ? current.stats.AerialGoal : current.stats.TeamAerialGoal);
            ++(me ? session.AerialGoal : session.TeamAerialGoal);
            ++(me ? stats[current.playlist].AerialGoal : stats[current.playlist].TeamAerialGoal);
            ++(me ? always_gm[current.playlist].AerialGoal : always_gm[current.playlist].TeamAerialGoal);

            ++always.TotalAerialGoalCumul;
            ++current.stats.TotalAerialGoalCumul;
            ++session.TotalAerialGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalAerialGoalCumul;
                ++always_gm[it->first].TotalAerialGoalCumul;

                ++(me ? stats[it->first].AerialGoalCumul : stats[it->first].TeamAerialGoalCumul);
                ++(me ? always_gm[it->first].AerialGoalCumul : always_gm[it->first].TeamAerialGoalCumul);
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

            ++(me ? always.BackwardsGoal : always.TeamBackwardsGoal);
            ++(me ? current.stats.BackwardsGoal : current.stats.TeamBackwardsGoal);
            ++(me ? session.BackwardsGoal : session.TeamBackwardsGoal);
            ++(me ? stats[current.playlist].BackwardsGoal : stats[current.playlist].TeamBackwardsGoal);
            ++(me ? always_gm[current.playlist].BackwardsGoal : always_gm[current.playlist].TeamBackwardsGoal);

            ++always.TotalBackwardsGoalCumul;
            ++current.stats.TotalBackwardsGoalCumul;
            ++session.TotalBackwardsGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBackwardsGoalCumul;
                ++always_gm[it->first].TotalBackwardsGoalCumul;

                ++(me ? stats[it->first].BackwardsGoalCumul : stats[it->first].TeamBackwardsGoalCumul);
                ++(me ? always_gm[it->first].BackwardsGoalCumul : always_gm[it->first].TeamBackwardsGoalCumul);
            }

            AllGoalsBackwardsGoal(true);
        }
        else if (name == "BicycleGoal")
        {
            cvarManager->log(" --> BicycleGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalBicycleGoal;
            ++current.stats.TotalBicycleGoal;
            ++session.TotalBicycleGoal;
            ++stats[current.playlist].TotalBicycleGoal;
            ++always_gm[current.playlist].TotalBicycleGoal;

            ++(me ? always.BicycleGoal : always.TeamBicycleGoal);
            ++(me ? current.stats.BicycleGoal : current.stats.TeamBicycleGoal);
            ++(me ? session.BicycleGoal : session.TeamBicycleGoal);
            ++(me ? stats[current.playlist].BicycleGoal : stats[current.playlist].TeamBicycleGoal);
            ++(me ? always_gm[current.playlist].BicycleGoal : always_gm[current.playlist].TeamBicycleGoal);

            ++always.TotalBicycleGoalCumul;
            ++current.stats.TotalBicycleGoalCumul;
            ++session.TotalBicycleGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBicycleGoalCumul;
                ++always_gm[it->first].TotalBicycleGoalCumul;

                ++(me ? stats[it->first].BicycleGoalCumul : stats[it->first].TeamBicycleGoalCumul);
                ++(me ? always_gm[it->first].BicycleGoalCumul : always_gm[it->first].TeamBicycleGoalCumul);
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

            ++(me ? always.LongGoal : always.TeamLongGoal);
            ++(me ? current.stats.LongGoal : current.stats.TeamLongGoal);
            ++(me ? session.LongGoal : session.TeamLongGoal);
            ++(me ? stats[current.playlist].LongGoal : stats[current.playlist].TeamLongGoal);
            ++(me ? always_gm[current.playlist].LongGoal : always_gm[current.playlist].TeamLongGoal);

            ++always.TotalLongGoalCumul;
            ++current.stats.TotalLongGoalCumul;
            ++session.TotalLongGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalLongGoalCumul;
                ++always_gm[it->first].TotalLongGoalCumul;

                ++(me ? stats[it->first].LongGoalCumul : stats[it->first].TeamLongGoalCumul);
                ++(me ? always_gm[it->first].LongGoalCumul : always_gm[it->first].TeamLongGoalCumul);
            }

            AllGoalsLongGoal(true);
        }
        else if (name == "TurtleGoal")
        {
            cvarManager->log(" --> TurtleGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalTurtleGoal;
            ++current.stats.TotalTurtleGoal;
            ++session.TotalTurtleGoal;
            ++stats[current.playlist].TotalTurtleGoal;
            ++always_gm[current.playlist].TotalTurtleGoal;

            ++(me ? always.TurtleGoal : always.TeamTurtleGoal);
            ++(me ? current.stats.TurtleGoal : current.stats.TeamTurtleGoal);
            ++(me ? session.TurtleGoal : session.TeamTurtleGoal);
            ++(me ? stats[current.playlist].TurtleGoal : stats[current.playlist].TeamTurtleGoal);
            ++(me ? always_gm[current.playlist].TurtleGoal : always_gm[current.playlist].TeamTurtleGoal);

            ++always.TotalTurtleGoalCumul;
            ++current.stats.TotalTurtleGoalCumul;
            ++session.TotalTurtleGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalTurtleGoalCumul;
                ++always_gm[it->first].TotalTurtleGoalCumul;

                ++(me ? stats[it->first].TurtleGoalCumul : stats[it->first].TeamTurtleGoalCumul);
                ++(me ? always_gm[it->first].TurtleGoalCumul : always_gm[it->first].TeamTurtleGoalCumul);
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

            ++(me ? always.OvertimeGoal : always.TeamOvertimeGoal);
            ++(me ? current.stats.OvertimeGoal : current.stats.TeamOvertimeGoal);
            ++(me ? session.OvertimeGoal : session.TeamOvertimeGoal);
            ++(me ? stats[current.playlist].OvertimeGoal : stats[current.playlist].TeamOvertimeGoal);
            ++(me ? always_gm[current.playlist].OvertimeGoal : always_gm[current.playlist].TeamOvertimeGoal);

            ++always.TotalOvertimeGoalCumul;
            ++current.stats.TotalOvertimeGoalCumul;
            ++session.TotalOvertimeGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalOvertimeGoalCumul;
                ++always_gm[it->first].TotalOvertimeGoalCumul;

                ++(me ? stats[it->first].OvertimeGoalCumul : stats[it->first].TeamOvertimeGoalCumul);
                ++(me ? always_gm[it->first].OvertimeGoalCumul : always_gm[it->first].TeamOvertimeGoalCumul);
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

            ++(me ? always.HoopsSwishGoal : always.TeamHoopsSwishGoal);
            ++(me ? current.stats.HoopsSwishGoal : current.stats.TeamHoopsSwishGoal);
            ++(me ? session.HoopsSwishGoal : session.TeamHoopsSwishGoal);
            ++(me ? stats[current.playlist].HoopsSwishGoal : stats[current.playlist].TeamHoopsSwishGoal);
            ++(me ? always_gm[current.playlist].HoopsSwishGoal : always_gm[current.playlist].TeamHoopsSwishGoal);

            ++always.TotalHoopsSwishGoalCumul;
            ++current.stats.TotalHoopsSwishGoalCumul;
            ++session.TotalHoopsSwishGoalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalHoopsSwishGoalCumul;
                ++always_gm[it->first].TotalHoopsSwishGoalCumul;

                ++(me ? stats[it->first].HoopsSwishGoalCumul : stats[it->first].TeamHoopsSwishGoalCumul);
                ++(me ? always_gm[it->first].HoopsSwishGoalCumul : always_gm[it->first].TeamHoopsSwishGoalCumul);
            }

            AllGoalsHoopsSwishGoal(true);
        }
        else if (name == "PoolShot")
        {
            cvarManager->log(" --> PoolShot " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalPoolShot;
            ++current.stats.TotalPoolShot;
            ++session.TotalPoolShot;
            ++stats[current.playlist].TotalPoolShot;
            ++always_gm[current.playlist].TotalPoolShot;

            ++(me ? always.PoolShot : always.TeamPoolShot);
            ++(me ? current.stats.PoolShot : current.stats.TeamPoolShot);
            ++(me ? session.PoolShot : session.TeamPoolShot);
            ++(me ? stats[current.playlist].PoolShot : stats[current.playlist].TeamPoolShot);
            ++(me ? always_gm[current.playlist].PoolShot : always_gm[current.playlist].TeamPoolShot);

            ++always.TotalPoolShotCumul;
            ++current.stats.TotalPoolShotCumul;
            ++session.TotalPoolShotCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalPoolShotCumul;
                ++always_gm[it->first].TotalPoolShotCumul;

                ++(me ? stats[it->first].PoolShotCumul : stats[it->first].TeamPoolShotCumul);
                ++(me ? always_gm[it->first].PoolShotCumul : always_gm[it->first].TeamPoolShotCumul);
            }

            AllGoalsPoolShot(true);
        }
        else if (name == "HatTrick")
        {
            ++always.TotalHatTrick;
            ++current.stats.TotalHatTrick;
            ++session.TotalHatTrick;
            ++stats[current.playlist].TotalHatTrick;
            ++always_gm[current.playlist].TotalHatTrick;

            ++(me ? always.HatTrick : always.TeamHatTrick);
            ++(me ? current.stats.HatTrick : current.stats.TeamHatTrick);
            ++(me ? session.HatTrick : session.TeamHatTrick);
            ++(me ? stats[current.playlist].HatTrick : stats[current.playlist].TeamHatTrick);
            ++(me ? always_gm[current.playlist].HatTrick : always_gm[current.playlist].TeamHatTrick);

            ++always.TotalHatTrickCumul;
            ++current.stats.TotalHatTrickCumul;
            ++session.TotalHatTrickCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalHatTrickCumul;
                ++always_gm[it->first].TotalHatTrickCumul;

                ++(me ? stats[it->first].HatTrickCumul : stats[it->first].TeamHatTrickCumul);
                ++(me ? always_gm[it->first].HatTrickCumul : always_gm[it->first].TeamHatTrickCumul);
            }

            AllMiscsHatTrick(true);
        }
        else if (name == "LowFive")
        {
            cvarManager->log(" --> LowFive " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalLowFive;
            ++current.stats.TotalLowFive;
            ++session.TotalLowFive;
            ++stats[current.playlist].TotalLowFive;
            ++always_gm[current.playlist].TotalLowFive;

            ++(me ? always.LowFive : always.TeamLowFive);
            ++(me ? current.stats.LowFive : current.stats.TeamLowFive);
            ++(me ? session.LowFive : session.TeamLowFive);
            ++(me ? stats[current.playlist].LowFive : stats[current.playlist].TeamLowFive);
            ++(me ? always_gm[current.playlist].LowFive : always_gm[current.playlist].TeamLowFive);

            ++always.TotalLowFiveCumul;
            ++current.stats.TotalLowFiveCumul;
            ++session.TotalLowFiveCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalLowFiveCumul;
                ++always_gm[it->first].TotalLowFiveCumul;

                ++(me ? stats[it->first].LowFiveCumul : stats[it->first].TeamLowFiveCumul);
                ++(me ? always_gm[it->first].LowFiveCumul : always_gm[it->first].TeamLowFiveCumul);
            }

            AllMiscsLowFive(true);
        }
        else if (name == "HighFive")
        {
            cvarManager->log(" --> HighFive " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalHighFive;
            ++current.stats.TotalHighFive;
            ++session.TotalHighFive;
            ++stats[current.playlist].TotalHighFive;
            ++always_gm[current.playlist].TotalHighFive;

            ++(me ? always.HighFive : always.TeamHighFive);
            ++(me ? current.stats.HighFive : current.stats.TeamHighFive);
            ++(me ? session.HighFive : session.TeamHighFive);
            ++(me ? stats[current.playlist].HighFive : stats[current.playlist].TeamHighFive);
            ++(me ? always_gm[current.playlist].HighFive : always_gm[current.playlist].TeamHighFive);

            ++always.TotalHighFiveCumul;
            ++current.stats.TotalHighFiveCumul;
            ++session.TotalHighFiveCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalHighFiveCumul;
                ++always_gm[it->first].TotalHighFiveCumul;

                ++(me ? stats[it->first].HighFiveCumul : stats[it->first].TeamHighFiveCumul);
                ++(me ? always_gm[it->first].HighFiveCumul : always_gm[it->first].TeamHighFiveCumul);
            }

            AllMiscsHighFive(true);
        }
        else if (name == "BreakoutDamage")
        {
            ++always.TotalBreakoutDamage;
            ++current.stats.TotalBreakoutDamage;
            ++session.TotalBreakoutDamage;
            ++stats[current.playlist].TotalBreakoutDamage;
            ++always_gm[current.playlist].TotalBreakoutDamage;

            ++(me ? always.BreakoutDamage : always.TeamBreakoutDamage);
            ++(me ? current.stats.BreakoutDamage : current.stats.TeamBreakoutDamage);
            ++(me ? session.BreakoutDamage : session.TeamBreakoutDamage);
            ++(me ? stats[current.playlist].BreakoutDamage : stats[current.playlist].TeamBreakoutDamage);
            ++(me ? always_gm[current.playlist].BreakoutDamage : always_gm[current.playlist].TeamBreakoutDamage);

            ++always.TotalBreakoutDamageCumul;
            ++current.stats.TotalBreakoutDamageCumul;
            ++session.TotalBreakoutDamageCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBreakoutDamageCumul;
                ++always_gm[it->first].TotalBreakoutDamageCumul;

                ++(me ? stats[it->first].BreakoutDamageCumul : stats[it->first].TeamBreakoutDamageCumul);
                ++(me ? always_gm[it->first].BreakoutDamageCumul : always_gm[it->first].TeamBreakoutDamageCumul);
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

            ++(me ? always.BreakoutDamageLarge : always.TeamBreakoutDamageLarge);
            ++(me ? current.stats.BreakoutDamageLarge : current.stats.TeamBreakoutDamageLarge);
            ++(me ? session.BreakoutDamageLarge : session.TeamBreakoutDamageLarge);
            ++(me ? stats[current.playlist].BreakoutDamageLarge : stats[current.playlist].TeamBreakoutDamageLarge);
            ++(me ? always_gm[current.playlist].BreakoutDamageLarge : always_gm[current.playlist].TeamBreakoutDamageLarge);

            ++always.TotalBreakoutDamageLargeCumul;
            ++current.stats.TotalBreakoutDamageLargeCumul;
            ++session.TotalBreakoutDamageLargeCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBreakoutDamageLargeCumul;
                ++always_gm[it->first].TotalBreakoutDamageLargeCumul;

                ++(me ? stats[it->first].BreakoutDamageLargeCumul : stats[it->first].TeamBreakoutDamageLargeCumul);
                ++(me ? always_gm[it->first].BreakoutDamageLargeCumul : always_gm[it->first].TeamBreakoutDamageLargeCumul);
            }

            AllDropshotBreakoutDamageLarge(true);
        }
        else if (name == "KO_Death")
        {
            cvarManager->log(" --> KnockoutDeath " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.KnockoutTotalDeath;
            ++current.stats.KnockoutTotalDeath;
            ++session.KnockoutTotalDeath;
            ++stats[current.playlist].KnockoutTotalDeath;
            ++always_gm[current.playlist].KnockoutTotalDeath;

            ++(me ? always.KnockoutDeath : always.KnockoutTeamDeath);
            ++(me ? current.stats.KnockoutDeath : current.stats.KnockoutTeamDeath);
            ++(me ? session.KnockoutDeath : session.KnockoutTeamDeath);
            ++(me ? stats[current.playlist].KnockoutDeath : stats[current.playlist].KnockoutTeamDeath);
            ++(me ? always_gm[current.playlist].KnockoutDeath : always_gm[current.playlist].KnockoutTeamDeath);

            ++always.KnockoutTotalDeathCumul;
            ++current.stats.KnockoutTotalDeathCumul;
            ++session.KnockoutTotalDeathCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].KnockoutTotalDeathCumul;
                ++always_gm[it->first].KnockoutTotalDeathCumul;

                ++(me ? stats[it->first].KnockoutDeathCumul : stats[it->first].KnockoutTeamDeathCumul);
                ++(me ? always_gm[it->first].KnockoutDeathCumul : always_gm[it->first].KnockoutTeamDeathCumul);
            }

            AllKnockoutDeath(true);
        }
        else if (name == "KO_DoubleKO")
        {
            cvarManager->log(" --> KnockoutDoubleKO " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.KnockoutTotalDoubleKO;
            ++current.stats.KnockoutTotalDoubleKO;
            ++session.KnockoutTotalDoubleKO;
            ++stats[current.playlist].KnockoutTotalDoubleKO;
            ++always_gm[current.playlist].KnockoutTotalDoubleKO;

            ++(me ? always.KnockoutDoubleKO : always.KnockoutTeamDoubleKO);
            ++(me ? current.stats.KnockoutDoubleKO : current.stats.KnockoutTeamDoubleKO);
            ++(me ? session.KnockoutDoubleKO : session.KnockoutTeamDoubleKO);
            ++(me ? stats[current.playlist].KnockoutDoubleKO : stats[current.playlist].KnockoutTeamDoubleKO);
            ++(me ? always_gm[current.playlist].KnockoutDoubleKO : always_gm[current.playlist].KnockoutTeamDoubleKO);

            ++always.KnockoutTotalDoubleKOCumul;
            ++current.stats.KnockoutTotalDoubleKOCumul;
            ++session.KnockoutTotalDoubleKOCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].KnockoutTotalDoubleKOCumul;
                ++always_gm[it->first].KnockoutTotalDoubleKOCumul;

                ++(me ? stats[it->first].KnockoutDoubleKOCumul : stats[it->first].KnockoutTeamDoubleKOCumul);
                ++(me ? always_gm[it->first].KnockoutDoubleKOCumul : always_gm[it->first].KnockoutTeamDoubleKOCumul);
            }

            AllKnockoutDoubleKO(true);
        }
        else if (name == "KO_HeavyHit")
        {
            cvarManager->log(" --> KnockoutHeavyHit " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.KnockoutTotalHeavyHit;
            ++current.stats.KnockoutTotalHeavyHit;
            ++session.KnockoutTotalHeavyHit;
            ++stats[current.playlist].KnockoutTotalHeavyHit;
            ++always_gm[current.playlist].KnockoutTotalHeavyHit;

            ++(me ? always.KnockoutHeavyHit : always.KnockoutTeamHeavyHit);
            ++(me ? current.stats.KnockoutHeavyHit : current.stats.KnockoutTeamHeavyHit);
            ++(me ? session.KnockoutHeavyHit : session.KnockoutTeamHeavyHit);
            ++(me ? stats[current.playlist].KnockoutHeavyHit : stats[current.playlist].KnockoutTeamHeavyHit);
            ++(me ? always_gm[current.playlist].KnockoutHeavyHit : always_gm[current.playlist].KnockoutTeamHeavyHit);

            ++always.KnockoutTotalHeavyHitCumul;
            ++current.stats.KnockoutTotalHeavyHitCumul;
            ++session.KnockoutTotalHeavyHitCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].KnockoutTotalHeavyHitCumul;
                ++always_gm[it->first].KnockoutTotalHeavyHitCumul;

                ++(me ? stats[it->first].KnockoutHeavyHitCumul : stats[it->first].KnockoutTeamHeavyHitCumul);
                ++(me ? always_gm[it->first].KnockoutHeavyHitCumul : always_gm[it->first].KnockoutTeamHeavyHitCumul);
            }

            AllKnockoutHeavyHit(true);
        }
        else if (name == "KO_Knockout")
        {
            cvarManager->log(" --> Knockout " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.KnockoutTotal;
            ++current.stats.KnockoutTotal;
            ++session.KnockoutTotal;
            ++stats[current.playlist].KnockoutTotal;
            ++always_gm[current.playlist].KnockoutTotal;

            ++(me ? always.Knockout : always.KnockoutTeam);
            ++(me ? current.stats.Knockout : current.stats.KnockoutTeam);
            ++(me ? session.Knockout : session.KnockoutTeam);
            ++(me ? stats[current.playlist].Knockout : stats[current.playlist].KnockoutTeam);
            ++(me ? always_gm[current.playlist].Knockout : always_gm[current.playlist].KnockoutTeam);

            ++always.KnockoutTotalCumul;
            ++current.stats.KnockoutTotalCumul;
            ++session.KnockoutTotalCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].KnockoutTotalCumul;
                ++always_gm[it->first].KnockoutTotalCumul;

                ++(me ? stats[it->first].KnockoutCumul : stats[it->first].KnockoutTeamCumul);
                ++(me ? always_gm[it->first].KnockoutCumul : always_gm[it->first].KnockoutTeamCumul);
            }

            AllKnockoutBase(true);
        }
        else if (name == "KO_HeavyBlock")
        {
            cvarManager->log(" --> KnockoutHeavyBlock " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.KnockoutTotalHeavyBlock;
            ++current.stats.KnockoutTotalHeavyBlock;
            ++session.KnockoutTotalHeavyBlock;
            ++stats[current.playlist].KnockoutTotalHeavyBlock;
            ++always_gm[current.playlist].KnockoutTotalHeavyBlock;

            ++(me ? always.KnockoutHeavyBlock : always.KnockoutTeamHeavyBlock);
            ++(me ? current.stats.KnockoutHeavyBlock : current.stats.KnockoutTeamHeavyBlock);
            ++(me ? session.KnockoutHeavyBlock : session.KnockoutTeamHeavyBlock);
            ++(me ? stats[current.playlist].KnockoutHeavyBlock : stats[current.playlist].KnockoutTeamHeavyBlock);
            ++(me ? always_gm[current.playlist].KnockoutHeavyBlock : always_gm[current.playlist].KnockoutTeamHeavyBlock);

            ++always.KnockoutTotalHeavyBlockCumul;
            ++current.stats.KnockoutTotalHeavyBlockCumul;
            ++session.KnockoutTotalHeavyBlockCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].KnockoutTotalHeavyBlockCumul;
                ++always_gm[it->first].KnockoutTotalHeavyBlockCumul;

                ++(me ? stats[it->first].KnockoutHeavyBlockCumul : stats[it->first].KnockoutTeamHeavyBlockCumul);
                ++(me ? always_gm[it->first].KnockoutHeavyBlockCumul : always_gm[it->first].KnockoutTeamHeavyBlockCumul);
            }

            AllKnockoutHeavyBlock(true);
        }
        else if (name == "MVP")
        {
            ++always.TotalMVP;
            ++current.stats.TotalMVP;
            ++session.TotalMVP;
            ++stats[current.playlist].TotalMVP;
            ++always_gm[current.playlist].TotalMVP;

            ++(me ? always.MVP : always.TeamMVP);
            ++(me ? current.stats.MVP : current.stats.TeamMVP);
            ++(me ? session.MVP : session.TeamMVP);
            ++(me ? stats[current.playlist].MVP : stats[current.playlist].TeamMVP);
            ++(me ? always_gm[current.playlist].MVP : always_gm[current.playlist].TeamMVP);

            ++always.TotalMVPCumul;
            ++current.stats.TotalMVPCumul;
            ++session.TotalMVPCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalMVPCumul;
                ++always_gm[it->first].TotalMVPCumul;

                ++(me ? stats[it->first].MVPCumul : stats[it->first].TeamMVPCumul);
                ++(me ? always_gm[it->first].MVPCumul : always_gm[it->first].TeamMVPCumul);
            }

            AllCertificationsMVP(true);
        }
        else if (name == "Savior")
        {
            ++always.TotalSavior;
            ++current.stats.TotalSavior;
            ++session.TotalSavior;
            ++stats[current.playlist].TotalSavior;
            ++always_gm[current.playlist].TotalSavior;

            ++(me ? always.Savior : always.TeamSavior);
            ++(me ? current.stats.Savior : current.stats.TeamSavior);
            ++(me ? session.Savior : session.TeamSavior);
            ++(me ? stats[current.playlist].Savior : stats[current.playlist].TeamSavior);
            ++(me ? always_gm[current.playlist].Savior : always_gm[current.playlist].TeamSavior);

            ++always.TotalSaviorCumul;
            ++current.stats.TotalSaviorCumul;
            ++session.TotalSaviorCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalSaviorCumul;
                ++always_gm[it->first].TotalSaviorCumul;

                ++(me ? stats[it->first].SaviorCumul : stats[it->first].TeamSaviorCumul);
                ++(me ? always_gm[it->first].SaviorCumul : always_gm[it->first].TeamSaviorCumul);
            }

            AllCertificationsSavior(true);
        }
        else if (name == "Playmaker")
        {
            ++always.TotalPlaymaker;
            ++current.stats.TotalPlaymaker;
            ++session.TotalPlaymaker;
            ++stats[current.playlist].TotalPlaymaker;
            ++always_gm[current.playlist].TotalPlaymaker;

            ++(me ? always.Playmaker : always.TeamPlaymaker);
            ++(me ? current.stats.Playmaker : current.stats.TeamPlaymaker);
            ++(me ? session.Playmaker : session.TeamPlaymaker);
            ++(me ? stats[current.playlist].Playmaker : stats[current.playlist].TeamPlaymaker);
            ++(me ? always_gm[current.playlist].Playmaker : always_gm[current.playlist].TeamPlaymaker);

            ++always.TotalPlaymakerCumul;
            ++current.stats.TotalPlaymakerCumul;
            ++session.TotalPlaymakerCumul;

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalPlaymakerCumul;
                ++always_gm[it->first].TotalPlaymakerCumul;

                ++(me ? stats[it->first].PlaymakerCumul : stats[it->first].TeamPlaymakerCumul);
                ++(me ? always_gm[it->first].PlaymakerCumul : always_gm[it->first].TeamPlaymakerCumul);
            }

            AllCertificationsPlaymaker(true);
        }
        else
        {
            refresh = false;
            cvarManager->log("onStatTickerMessage receiver:" + std::string(isPrimaryPlayer(receiver) ? "1" : "0") + " victim:" + std::string(isPrimaryPlayer(victim) ? "1" : "0") + " e:" + name + "=" + std::to_string(event.GetPoints()));
        }

        if (refresh)
            SetRefresh(RefreshFlags_Refresh);
    }
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
    {
        tmp.games += stats[it->first].games;
        tmp.MMRCumulChange += stats[it->first].MMRChange;
        tmp.win += stats[it->first].win;
        tmp.loss += stats[it->first].loss;
        tmp.demo += stats[it->first].demo;
        tmp.death += stats[it->first].death;

        /// Shots
        tmp.Clear += stats[it->first].Clear;
        tmp.Assist += stats[it->first].Assist;
        tmp.Center += stats[it->first].Center;
        tmp.AerialHit += stats[it->first].AerialHit;
        tmp.BicycleHit += stats[it->first].BicycleHit;
        tmp.FirstTouch += stats[it->first].FirstTouch;
        tmp.ShotOnGoal += stats[it->first].ShotOnGoal;
        tmp.TeamAssist += stats[it->first].TeamAssist;
        tmp.TeamBicycleHit += stats[it->first].TeamBicycleHit;
        tmp.TeamShotOnGoal += stats[it->first].TeamShotOnGoal;
        tmp.TotalAssist += stats[it->first].TotalAssist;
        tmp.TotalBicycleHit += stats[it->first].TotalBicycleHit;
        tmp.TotalShotOnGoal += stats[it->first].TotalShotOnGoal;

        /// Saves
        tmp.Save += stats[it->first].Save;
        tmp.EpicSave += stats[it->first].EpicSave;
        tmp.TeamSave += stats[it->first].TeamSave;
        tmp.TeamEpicSave += stats[it->first].TeamEpicSave;
        tmp.TotalSave += stats[it->first].TotalSave;
        tmp.TotalEpicSave += stats[it->first].TotalEpicSave;

        /// Goals
        tmp.Goal += stats[it->first].Goal;
        tmp.LongGoal += stats[it->first].LongGoal;
        tmp.PoolShot += stats[it->first].PoolShot;
        tmp.AerialGoal += stats[it->first].AerialGoal;
        tmp.TurtleGoal += stats[it->first].TurtleGoal;
        tmp.BicycleGoal += stats[it->first].BicycleGoal;
        tmp.OvertimeGoal += stats[it->first].OvertimeGoal;
        tmp.BackwardsGoal += stats[it->first].BackwardsGoal;
        tmp.HoopsSwishGoal += stats[it->first].HoopsSwishGoal;
        tmp.TeamGoal += stats[it->first].TeamGoal;
        tmp.TeamLongGoal += stats[it->first].TeamLongGoal;
        tmp.TeamPoolShot += stats[it->first].TeamPoolShot;
        tmp.TeamAerialGoal += stats[it->first].TeamAerialGoal;
        tmp.TeamTurtleGoal += stats[it->first].TeamTurtleGoal;
        tmp.TeamBicycleGoal += stats[it->first].TeamBicycleGoal;
        tmp.TeamOvertimeGoal += stats[it->first].TeamOvertimeGoal;
        tmp.TeamBackwardsGoal += stats[it->first].TeamBackwardsGoal;
        tmp.TeamHoopsSwishGoal += stats[it->first].TeamHoopsSwishGoal;
        tmp.TotalGoal += stats[it->first].TotalGoal;
        tmp.TotalLongGoal += stats[it->first].TotalLongGoal;
        tmp.TotalPoolShot += stats[it->first].TotalPoolShot;
        tmp.TotalAerialGoal += stats[it->first].TotalAerialGoal;
        tmp.TotalTurtleGoal += stats[it->first].TotalTurtleGoal;
        tmp.TotalBicycleGoal += stats[it->first].TotalBicycleGoal;
        tmp.TotalOvertimeGoal += stats[it->first].TotalOvertimeGoal;
        tmp.TotalBackwardsGoal += stats[it->first].TotalBackwardsGoal;
        tmp.TotalHoopsSwishGoal += stats[it->first].TotalHoopsSwishGoal;

        /// Dropshot
        tmp.BreakoutDamage += stats[it->first].BreakoutDamage;
        tmp.BreakoutDamageLarge += stats[it->first].BreakoutDamageLarge;
        tmp.TeamBreakoutDamage += stats[it->first].TeamBreakoutDamage;
        tmp.TeamBreakoutDamageLarge += stats[it->first].TeamBreakoutDamageLarge;
        tmp.TotalBreakoutDamage += stats[it->first].TotalBreakoutDamage;
        tmp.TotalBreakoutDamageLarge += stats[it->first].TotalBreakoutDamageLarge;

        /// Knockout
        tmp.Knockout += stats[it->first].Knockout;
        tmp.KnockoutDeath += stats[it->first].KnockoutDeath;
        tmp.KnockoutThrown += stats[it->first].KnockoutThrown;
        tmp.KnockoutGrabbed += stats[it->first].KnockoutGrabbed;
        tmp.KnockoutDoubleKO += stats[it->first].KnockoutDoubleKO;
        tmp.KnockoutHeavyHit += stats[it->first].KnockoutHeavyHit;
        tmp.KnockoutHitTaken += stats[it->first].KnockoutHitTaken;
        tmp.KnockoutLightHit += stats[it->first].KnockoutLightHit;
        tmp.KnockoutBlockTaken += stats[it->first].KnockoutBlockTaken;
        tmp.KnockoutHeavyBlock += stats[it->first].KnockoutHeavyBlock;
        tmp.KnockoutTeam += stats[it->first].KnockoutTeam;
        tmp.KnockoutTeamDeath += stats[it->first].KnockoutTeamDeath;
        tmp.KnockoutTeamDoubleKO += stats[it->first].KnockoutTeamDoubleKO;
        tmp.KnockoutTeamHeavyHit += stats[it->first].KnockoutTeamHeavyHit;
        tmp.KnockoutTeamHeavyBlock += stats[it->first].KnockoutTeamHeavyBlock;
        tmp.KnockoutTotal += stats[it->first].KnockoutTotal;
        tmp.KnockoutTotalDeath += stats[it->first].KnockoutTotalDeath;
        tmp.KnockoutTotalDoubleKO += stats[it->first].KnockoutTotalDoubleKO;
        tmp.KnockoutTotalHeavyHit += stats[it->first].KnockoutTotalHeavyHit;
        tmp.KnockoutTotalHeavyBlock += stats[it->first].KnockoutTotalHeavyBlock;

        /// Miscs
        tmp.LowFive += stats[it->first].LowFive;
        tmp.HatTrick += stats[it->first].HatTrick;
        tmp.HighFive += stats[it->first].HighFive;
        tmp.TeamLowFive += stats[it->first].TeamLowFive;
        tmp.TeamHatTrick += stats[it->first].TeamHatTrick;
        tmp.TeamHighFive += stats[it->first].TeamHighFive;
        tmp.TotalLowFive += stats[it->first].TotalLowFive;
        tmp.TotalHatTrick += stats[it->first].TotalHatTrick;
        tmp.TotalHighFive += stats[it->first].TotalHighFive;

        /// Certifications
        tmp.MVP += stats[it->first].MVP;
        tmp.Savior += stats[it->first].Savior;
        tmp.Playmaker += stats[it->first].Playmaker;
        tmp.TeamMVP += stats[it->first].TeamMVP;
        tmp.TeamSavior += stats[it->first].TeamSavior;
        tmp.TeamPlaymaker += stats[it->first].TeamPlaymaker;
        tmp.TotalMVP += stats[it->first].TotalMVP;
        tmp.TotalSavior += stats[it->first].TotalSavior;
        tmp.TotalPlaymaker += stats[it->first].TotalPlaymaker;
    }

    session.games = tmp.games;
    session.myMMR = stats[current.playlist].myMMR;
    session.MMRChange = stats[current.playlist].MMRChange;
    session.win = tmp.win;
    session.loss = tmp.loss;
    session.demo = tmp.demo;
    session.demoCumul = tmp.demo;
    session.death = tmp.death;
    session.deathCumul = tmp.death;

    /// Shots
    session.ClearCumul = tmp.Clear;
    session.CenterCumul = tmp.Center;
    session.AssistCumul = tmp.Assist;
    session.FirstTouchCumul = tmp.FirstTouch;
    session.ShotOnGoalCumul = tmp.ShotOnGoal;
    session.AerialHitCumul = tmp.AerialHit;
    session.BicycleHitCumul = tmp.BicycleHit;
    session.TeamAssistCumul = tmp.TeamAssist;
    session.TeamShotOnGoalCumul = tmp.TeamShotOnGoal;
    session.TeamBicycleHitCumul = tmp.TeamBicycleHit;
    session.TotalAssistCumul = tmp.TotalAssist;
    session.TotalShotOnGoalCumul = tmp.TotalShotOnGoal;
    session.TotalBicycleHitCumul = tmp.TotalBicycleHit;

    /// Saves
    session.SaveCumul = tmp.Save;
    session.EpicSaveCumul = tmp.EpicSave;
    session.TeamSaveCumul = tmp.TeamSave;
    session.TeamEpicSaveCumul = tmp.TeamEpicSave;
    session.TotalSaveCumul = tmp.TotalSave;
    session.TotalEpicSaveCumul = tmp.TotalEpicSave;

    /// Goals
    session.GoalCumul = tmp.Goal;
    session.AerialGoalCumul = tmp.AerialGoal;
    session.BackwardsGoalCumul = tmp.BackwardsGoal;
    session.BicycleGoalCumul = tmp.BicycleGoal;
    session.LongGoalCumul = tmp.LongGoal;
    session.TurtleGoalCumul = tmp.TurtleGoal;
    session.OvertimeGoalCumul = tmp.OvertimeGoal;
    session.HoopsSwishGoalCumul = tmp.HoopsSwishGoal;
    session.PoolShotCumul = tmp.PoolShot;
    session.TeamGoalCumul = tmp.TeamGoal;
    session.TeamAerialGoalCumul = tmp.TeamAerialGoal;
    session.TeamBackwardsGoalCumul = tmp.TeamBackwardsGoal;
    session.TeamBicycleGoalCumul = tmp.TeamBicycleGoal;
    session.TeamLongGoalCumul = tmp.TeamLongGoal;
    session.TeamTurtleGoalCumul = tmp.TeamTurtleGoal;
    session.TeamOvertimeGoalCumul = tmp.TeamOvertimeGoal;
    session.TeamHoopsSwishGoalCumul = tmp.TeamHoopsSwishGoal;
    session.TeamPoolShotCumul = tmp.TeamPoolShot;
    session.TotalGoalCumul = tmp.TotalGoal;
    session.TotalAerialGoalCumul = tmp.TotalAerialGoal;
    session.TotalBackwardsGoalCumul = tmp.TotalBackwardsGoal;
    session.TotalBicycleGoalCumul = tmp.TotalBicycleGoal;
    session.TotalLongGoalCumul = tmp.TotalLongGoal;
    session.TotalTurtleGoalCumul = tmp.TotalTurtleGoal;
    session.TotalOvertimeGoalCumul = tmp.TotalOvertimeGoal;
    session.TotalHoopsSwishGoalCumul = tmp.TotalHoopsSwishGoal;
    session.TotalPoolShotCumul = tmp.TotalPoolShot;

    /// Dropshot
    session.BreakoutDamageCumul = tmp.BreakoutDamage;
    session.BreakoutDamageLargeCumul = tmp.BreakoutDamageLarge;
    session.TeamBreakoutDamageCumul = tmp.TeamBreakoutDamage;
    session.TeamBreakoutDamageLargeCumul = tmp.TeamBreakoutDamageLarge;
    session.TotalBreakoutDamageCumul = tmp.TotalBreakoutDamage;
    session.TotalBreakoutDamageLargeCumul = tmp.TotalBreakoutDamageLarge;

    /// Knockout
    tmp.KnockoutCumul += tmp.Knockout;
    tmp.KnockoutDeathCumul += tmp.KnockoutDeath;
    tmp.KnockoutThrownCumul += tmp.KnockoutThrown;
    tmp.KnockoutGrabbedCumul += tmp.KnockoutGrabbed;
    tmp.KnockoutDoubleKOCumul += tmp.KnockoutDoubleKO;
    tmp.KnockoutHeavyHitCumul += tmp.KnockoutHeavyHit;
    tmp.KnockoutHitTakenCumul += tmp.KnockoutHitTaken;
    tmp.KnockoutLightHitCumul += tmp.KnockoutLightHit;
    tmp.KnockoutBlockTakenCumul += tmp.KnockoutBlockTaken;
    tmp.KnockoutHeavyBlockCumul += tmp.KnockoutHeavyBlock;
    tmp.KnockoutTeamCumul += tmp.KnockoutTeam;
    tmp.KnockoutTeamDeathCumul += tmp.KnockoutTeamDeath;
    tmp.KnockoutTeamDoubleKOCumul += tmp.KnockoutTeamDoubleKO;
    tmp.KnockoutTeamHeavyHitCumul += tmp.KnockoutTeamHeavyHit;
    tmp.KnockoutTeamHeavyBlockCumul += tmp.KnockoutTeamHeavyBlock;
    tmp.KnockoutTotalDeathCumul += tmp.KnockoutTotalDeath;
    tmp.KnockoutTotalDoubleKOCumul += tmp.KnockoutTotalDoubleKO;
    tmp.KnockoutTotalHeavyHitCumul += tmp.KnockoutTotalHeavyHit;
    tmp.KnockoutTotalCumul += tmp.KnockoutTotal;
    tmp.KnockoutTotalHeavyBlockCumul += tmp.KnockoutTotalHeavyBlock;

    /// Miscs
    session.LowFiveCumul = tmp.LowFive;
    session.HatTrickCumul = tmp.HatTrick;
    session.HighFiveCumul = tmp.HighFive;
    session.TeamLowFiveCumul = tmp.TeamLowFive;
    session.TeamHatTrickCumul = tmp.TeamHatTrick;
    session.TeamHighFiveCumul = tmp.TeamHighFive;
    session.TotalLowFiveCumul = tmp.TotalLowFive;
    session.TotalHatTrickCumul = tmp.TotalHatTrick;
    session.TotalHighFiveCumul = tmp.TotalHighFive;

    /// Certifications
    session.MVPCumul = tmp.MVP;
    session.SaviorCumul = tmp.Savior;
    session.PlaymakerCumul = tmp.Playmaker;
    session.TeamMVPCumul = tmp.TeamMVP;
    session.TeamSaviorCumul = tmp.TeamSavior;
    session.TeamPlaymakerCumul = tmp.TeamPlaymaker;
    session.TotalMVPCumul = tmp.TotalMVP;
    session.TotalSaviorCumul = tmp.TotalSavior;
    session.TotalPlaymakerCumul = tmp.TotalPlaymaker;

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
