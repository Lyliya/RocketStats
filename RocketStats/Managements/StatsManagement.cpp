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

    std::string name = event.GetEventName(); // error
    //cvarManager->log("onStatEvent e:" + name + "=" + std::to_string(event.GetPoints()));
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
    cvarManager->log("onStatTickerMessage receiver:" + std::string(isPrimaryPlayer(receiver) ? "1" : "0") + " victim:" + std::string(isPrimaryPlayer(victim) ? "1" : "0") + " e:" + name + "=" + std::to_string(event.GetPoints()));
    if (name == "Demolish" && receiver && victim)
    {
        bool demo = isPrimaryPlayer(receiver);
        if (demo && current.playlist)
        {
            ++always.demo;
            ++current.demo;
            ++session.demo;
            ++always.demoCumul;
            ++session.demoCumul;
            ++stats[current.playlist].demo;
            ++always_gm[current.playlist].demo;

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
            ++current.death;
            ++session.death;
            ++always.deathCumul;
            ++session.deathCumul;
            ++stats[current.playlist].death;
            ++always_gm[current.playlist].death;

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
        if (name == "Shot")
        {
            cvarManager->log(" --> Shot " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalShot;
            ++current.TotalShot;
            ++session.TotalShot;
            ++always.TotalShotCumul;
            ++session.TotalShotCumul;
            ++stats[current.playlist].TotalShot;
            ++always_gm[current.playlist].TotalShot;

            ++(me ? always.Shot : always.TeamShot);
            ++(me ? current.Shot : current.TeamShot);
            ++(me ? session.Shot : session.TeamShot);
            ++(me ? stats[current.playlist].Shot : stats[current.playlist].TeamShot);
            ++(me ? always_gm[current.playlist].Shot : always_gm[current.playlist].TeamShot);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalShotCumul;
                ++always_gm[it->first].TotalShotCumul;
            }

            AllShotsShot(true);
        }
        else if (name == "CenterBall")
        {
            cvarManager->log(" --> CenterBall " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalCenterBall;
            ++current.TotalCenterBall;
            ++session.TotalCenterBall;
            ++always.TotalCenterBallCumul;
            ++session.TotalCenterBallCumul;
            ++stats[current.playlist].TotalCenterBall;
            ++always_gm[current.playlist].TotalCenterBall;

            ++(me ? always.CenterBall : always.TeamCenterBall);
            ++(me ? current.CenterBall : current.TeamCenterBall);
            ++(me ? session.CenterBall : session.TeamCenterBall);
            ++(me ? stats[current.playlist].CenterBall : stats[current.playlist].TeamCenterBall);
            ++(me ? always_gm[current.playlist].CenterBall : always_gm[current.playlist].TeamCenterBall);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalCenterBallCumul;
                ++always_gm[it->first].TotalCenterBallCumul;
            }

            AllShotsCenterBall(true);
        }
        else if (name == "ClearBall")
        {
            cvarManager->log(" --> ClearBall " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalClearBall;
            ++current.TotalClearBall;
            ++session.TotalClearBall;
            ++always.TotalClearBallCumul;
            ++session.TotalClearBallCumul;
            ++stats[current.playlist].TotalClearBall;
            ++always_gm[current.playlist].TotalClearBall;

            ++(me ? always.ClearBall : always.TeamClearBall);
            ++(me ? current.ClearBall : current.TeamClearBall);
            ++(me ? session.ClearBall : session.TeamClearBall);
            ++(me ? stats[current.playlist].ClearBall : stats[current.playlist].TeamClearBall);
            ++(me ? always_gm[current.playlist].ClearBall : always_gm[current.playlist].TeamClearBall);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalClearBallCumul;
                ++always_gm[it->first].TotalClearBallCumul;
            }

            AllShotsClearBall(true);
        }
        else if (name == "FirstTouch")
        {
            cvarManager->log(" --> FirstTouch " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalFirstTouch;
            ++current.TotalFirstTouch;
            ++session.TotalFirstTouch;
            ++always.TotalFirstTouchCumul;
            ++session.TotalFirstTouchCumul;
            ++stats[current.playlist].TotalFirstTouch;
            ++always_gm[current.playlist].TotalFirstTouch;

            ++(me ? always.FirstTouch : always.TeamFirstTouch);
            ++(me ? current.FirstTouch : current.TeamFirstTouch);
            ++(me ? session.FirstTouch : session.TeamFirstTouch);
            ++(me ? stats[current.playlist].FirstTouch : stats[current.playlist].TeamFirstTouch);
            ++(me ? always_gm[current.playlist].FirstTouch : always_gm[current.playlist].TeamFirstTouch);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalFirstTouchCumul;
                ++always_gm[it->first].TotalFirstTouchCumul;
            }

            AllShotsFirstTouch(true);
        }
        else if (name == "ShotonGoal")
        {
            cvarManager->log(" --> ShotOnGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalShotOnGoal;
            ++current.TotalShotOnGoal;
            ++session.TotalShotOnGoal;
            ++always.TotalShotOnGoalCumul;
            ++session.TotalShotOnGoalCumul;
            ++stats[current.playlist].TotalShotOnGoal;
            ++always_gm[current.playlist].TotalShotOnGoal;

            ++(me ? always.ShotOnGoal : always.TeamShotOnGoal);
            ++(me ? current.ShotOnGoal : current.TeamShotOnGoal);
            ++(me ? session.ShotOnGoal : session.TeamShotOnGoal);
            ++(me ? stats[current.playlist].ShotOnGoal : stats[current.playlist].TeamShotOnGoal);
            ++(me ? always_gm[current.playlist].ShotOnGoal : always_gm[current.playlist].TeamShotOnGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalShotOnGoalCumul;
                ++always_gm[it->first].TotalShotOnGoalCumul;
            }

            AllShotsShotOnGoal(true);
        }
        else if (name == "BicycleHit")
        {
            cvarManager->log(" --> BicycleHit " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalBicycleHit;
            ++current.TotalBicycleHit;
            ++session.TotalBicycleHit;
            ++always.TotalBicycleHitCumul;
            ++session.TotalBicycleHitCumul;
            ++stats[current.playlist].TotalBicycleHit;
            ++always_gm[current.playlist].TotalBicycleHit;

            ++(me ? always.BicycleHit : always.TeamBicycleHit);
            ++(me ? current.BicycleHit : current.TeamBicycleHit);
            ++(me ? session.BicycleHit : session.TeamBicycleHit);
            ++(me ? stats[current.playlist].BicycleHit : stats[current.playlist].TeamBicycleHit);
            ++(me ? always_gm[current.playlist].BicycleHit : always_gm[current.playlist].TeamBicycleHit);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBicycleHitCumul;
                ++always_gm[it->first].TotalBicycleHitCumul;
            }

            AllShotsBicycleHit(true);
        }
        else if (name == "Assist")
        {
            cvarManager->log(" --> Assist " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalAssist;
            ++current.TotalAssist;
            ++session.TotalAssist;
            ++always.TotalAssistCumul;
            ++session.TotalAssistCumul;
            ++stats[current.playlist].TotalAssist;
            ++always_gm[current.playlist].TotalAssist;

            ++(me ? always.Assist : always.TeamAssist);
            ++(me ? current.Assist : current.TeamAssist);
            ++(me ? session.Assist : session.TeamAssist);
            ++(me ? stats[current.playlist].Assist : stats[current.playlist].TeamAssist);
            ++(me ? always_gm[current.playlist].Assist : always_gm[current.playlist].TeamAssist);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalAssistCumul;
                ++always_gm[it->first].TotalAssistCumul;
            }

            AllAssistsAssist(true);
        }
        else if (name == "Playmaker")
        {
            cvarManager->log(" --> Playmaker " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalPlaymaker;
            ++current.TotalPlaymaker;
            ++session.TotalPlaymaker;
            ++always.TotalPlaymakerCumul;
            ++session.TotalPlaymakerCumul;
            ++stats[current.playlist].TotalPlaymaker;
            ++always_gm[current.playlist].TotalPlaymaker;

            ++(me ? always.Playmaker : always.TeamPlaymaker);
            ++(me ? current.Playmaker : current.TeamPlaymaker);
            ++(me ? session.Playmaker : session.TeamPlaymaker);
            ++(me ? stats[current.playlist].Playmaker : stats[current.playlist].TeamPlaymaker);
            ++(me ? always_gm[current.playlist].Playmaker : always_gm[current.playlist].TeamPlaymaker);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalPlaymakerCumul;
                ++always_gm[it->first].TotalPlaymakerCumul;
            }

            AllAssistsPlaymaker(true);
        }
        else if (name == "Goal")
        {
            cvarManager->log(" --> Goal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalGoal;
            ++current.TotalGoal;
            ++session.TotalGoal;
            ++always.TotalGoalCumul;
            ++session.TotalGoalCumul;
            ++stats[current.playlist].TotalGoal;
            ++always_gm[current.playlist].TotalGoal;

            ++(me ? always.Goal : always.TeamGoal);
            ++(me ? current.Goal : current.TeamGoal);
            ++(me ? session.Goal : session.TeamGoal);
            ++(me ? stats[current.playlist].Goal : stats[current.playlist].TeamGoal);
            ++(me ? always_gm[current.playlist].Goal : always_gm[current.playlist].TeamGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalGoalCumul;
                ++always_gm[it->first].TotalGoalCumul;
            }

            AllGoalsGoal(true);
        }
        else if (name == "AerialGoal")
        {
            cvarManager->log(" --> AerialGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalAerialGoal;
            ++current.TotalAerialGoal;
            ++session.TotalAerialGoal;
            ++always.TotalAerialGoalCumul;
            ++session.TotalAerialGoalCumul;
            ++stats[current.playlist].TotalAerialGoal;
            ++always_gm[current.playlist].TotalAerialGoal;

            ++(me ? always.AerialGoal : always.TeamAerialGoal);
            ++(me ? current.AerialGoal : current.TeamAerialGoal);
            ++(me ? session.AerialGoal : session.TeamAerialGoal);
            ++(me ? stats[current.playlist].AerialGoal : stats[current.playlist].TeamAerialGoal);
            ++(me ? always_gm[current.playlist].AerialGoal : always_gm[current.playlist].TeamAerialGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalAerialGoalCumul;
                ++always_gm[it->first].TotalAerialGoalCumul;
            }

            AllGoalsAerialGoal(true);
        }
        else if (name == "BackwardsGoal")
        {
            cvarManager->log(" --> BackwardsGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalBackwardsGoal;
            ++current.TotalBackwardsGoal;
            ++session.TotalBackwardsGoal;
            ++always.TotalBackwardsGoalCumul;
            ++session.TotalBackwardsGoalCumul;
            ++stats[current.playlist].TotalBackwardsGoal;
            ++always_gm[current.playlist].TotalBackwardsGoal;

            ++(me ? always.BackwardsGoal : always.TeamBackwardsGoal);
            ++(me ? current.BackwardsGoal : current.TeamBackwardsGoal);
            ++(me ? session.BackwardsGoal : session.TeamBackwardsGoal);
            ++(me ? stats[current.playlist].BackwardsGoal : stats[current.playlist].TeamBackwardsGoal);
            ++(me ? always_gm[current.playlist].BackwardsGoal : always_gm[current.playlist].TeamBackwardsGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBackwardsGoalCumul;
                ++always_gm[it->first].TotalBackwardsGoalCumul;
            }

            AllGoalsBackwardsGoal(true);
        }
        else if (name == "BicycleGoal")
        {
            cvarManager->log(" --> BicycleGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalBicycleGoal;
            ++current.TotalBicycleGoal;
            ++session.TotalBicycleGoal;
            ++always.TotalBicycleGoalCumul;
            ++session.TotalBicycleGoalCumul;
            ++stats[current.playlist].TotalBicycleGoal;
            ++always_gm[current.playlist].TotalBicycleGoal;

            ++(me ? always.BicycleGoal : always.TeamBicycleGoal);
            ++(me ? current.BicycleGoal : current.TeamBicycleGoal);
            ++(me ? session.BicycleGoal : session.TeamBicycleGoal);
            ++(me ? stats[current.playlist].BicycleGoal : stats[current.playlist].TeamBicycleGoal);
            ++(me ? always_gm[current.playlist].BicycleGoal : always_gm[current.playlist].TeamBicycleGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalBicycleGoalCumul;
                ++always_gm[it->first].TotalBicycleGoalCumul;
            }

            AllGoalsBicycleGoal(true);
        }
        else if (name == "LongGoal")
        {
            cvarManager->log(" --> LongGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalLongGoal;
            ++current.TotalLongGoal;
            ++session.TotalLongGoal;
            ++always.TotalLongGoalCumul;
            ++session.TotalLongGoalCumul;
            ++stats[current.playlist].TotalLongGoal;
            ++always_gm[current.playlist].TotalLongGoal;

            ++(me ? always.LongGoal : always.TeamLongGoal);
            ++(me ? current.LongGoal : current.TeamLongGoal);
            ++(me ? session.LongGoal : session.TeamLongGoal);
            ++(me ? stats[current.playlist].LongGoal : stats[current.playlist].TeamLongGoal);
            ++(me ? always_gm[current.playlist].LongGoal : always_gm[current.playlist].TeamLongGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalLongGoalCumul;
                ++always_gm[it->first].TotalLongGoalCumul;
            }

            AllGoalsLongGoal(true);
        }
        else if (name == "TurtleGoal")
        {
            cvarManager->log(" --> TurtleGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalTurtleGoal;
            ++current.TotalTurtleGoal;
            ++session.TotalTurtleGoal;
            ++always.TotalTurtleGoalCumul;
            ++session.TotalTurtleGoalCumul;
            ++stats[current.playlist].TotalTurtleGoal;
            ++always_gm[current.playlist].TotalTurtleGoal;

            ++(me ? always.TurtleGoal : always.TeamTurtleGoal);
            ++(me ? current.TurtleGoal : current.TeamTurtleGoal);
            ++(me ? session.TurtleGoal : session.TeamTurtleGoal);
            ++(me ? stats[current.playlist].TurtleGoal : stats[current.playlist].TeamTurtleGoal);
            ++(me ? always_gm[current.playlist].TurtleGoal : always_gm[current.playlist].TeamTurtleGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalTurtleGoalCumul;
                ++always_gm[it->first].TotalTurtleGoalCumul;
            }

            AllGoalsTurtleGoal(true);
        }
        else if (name == "OvertimeGoal")
        {
            cvarManager->log(" --> OvertimeGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalOvertimeGoal;
            ++current.TotalOvertimeGoal;
            ++session.TotalOvertimeGoal;
            ++always.TotalOvertimeGoalCumul;
            ++session.TotalOvertimeGoalCumul;
            ++stats[current.playlist].TotalOvertimeGoal;
            ++always_gm[current.playlist].TotalOvertimeGoal;

            ++(me ? always.OvertimeGoal : always.TeamOvertimeGoal);
            ++(me ? current.OvertimeGoal : current.TeamOvertimeGoal);
            ++(me ? session.OvertimeGoal : session.TeamOvertimeGoal);
            ++(me ? stats[current.playlist].OvertimeGoal : stats[current.playlist].TeamOvertimeGoal);
            ++(me ? always_gm[current.playlist].OvertimeGoal : always_gm[current.playlist].TeamOvertimeGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalOvertimeGoalCumul;
                ++always_gm[it->first].TotalOvertimeGoalCumul;
            }

            AllGoalsOvertimeGoal(true);
        }
        else if (name == "SwishGoal")
        {
            cvarManager->log(" --> SwishGoal " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalSwishGoal;
            ++current.TotalSwishGoal;
            ++session.TotalSwishGoal;
            ++always.TotalSwishGoalCumul;
            ++session.TotalSwishGoalCumul;
            ++stats[current.playlist].TotalSwishGoal;
            ++always_gm[current.playlist].TotalSwishGoal;

            ++(me ? always.SwishGoal : always.TeamSwishGoal);
            ++(me ? current.SwishGoal : current.TeamSwishGoal);
            ++(me ? session.SwishGoal : session.TeamSwishGoal);
            ++(me ? stats[current.playlist].SwishGoal : stats[current.playlist].TeamSwishGoal);
            ++(me ? always_gm[current.playlist].SwishGoal : always_gm[current.playlist].TeamSwishGoal);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalSwishGoalCumul;
                ++always_gm[it->first].TotalSwishGoalCumul;
            }

            AllGoalsSwishGoal(true);
        }
        else if (name == "PoolShot")
        {
            cvarManager->log(" --> PoolShot " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalPoolShot;
            ++current.TotalPoolShot;
            ++session.TotalPoolShot;
            ++always.TotalPoolShotCumul;
            ++session.TotalPoolShotCumul;
            ++stats[current.playlist].TotalPoolShot;
            ++always_gm[current.playlist].TotalPoolShot;

            ++(me ? always.PoolShot : always.TeamPoolShot);
            ++(me ? current.PoolShot : current.TeamPoolShot);
            ++(me ? session.PoolShot : session.TeamPoolShot);
            ++(me ? stats[current.playlist].PoolShot : stats[current.playlist].TeamPoolShot);
            ++(me ? always_gm[current.playlist].PoolShot : always_gm[current.playlist].TeamPoolShot);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalPoolShotCumul;
                ++always_gm[it->first].TotalPoolShotCumul;
            }

            AllGoalsPoolShot(true);
        }
        else if (name == "HatTrick")
        {
            cvarManager->log(" --> HatTrick " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalHatTrick;
            ++current.TotalHatTrick;
            ++session.TotalHatTrick;
            ++always.TotalHatTrickCumul;
            ++session.TotalHatTrickCumul;
            ++stats[current.playlist].TotalHatTrick;
            ++always_gm[current.playlist].TotalHatTrick;

            ++(me ? always.HatTrick : always.TeamHatTrick);
            ++(me ? current.HatTrick : current.TeamHatTrick);
            ++(me ? session.HatTrick : session.TeamHatTrick);
            ++(me ? stats[current.playlist].HatTrick : stats[current.playlist].TeamHatTrick);
            ++(me ? always_gm[current.playlist].HatTrick : always_gm[current.playlist].TeamHatTrick);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalHatTrickCumul;
                ++always_gm[it->first].TotalHatTrickCumul;
            }

            AllMiscsHatTrick(true);
        }
        else if (name == "LowFive")
        {
            cvarManager->log(" --> LowFive " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalLowFive;
            ++current.TotalLowFive;
            ++session.TotalLowFive;
            ++always.TotalLowFiveCumul;
            ++session.TotalLowFiveCumul;
            ++stats[current.playlist].TotalLowFive;
            ++always_gm[current.playlist].TotalLowFive;

            ++(me ? always.LowFive : always.TeamLowFive);
            ++(me ? current.LowFive : current.TeamLowFive);
            ++(me ? session.LowFive : session.TeamLowFive);
            ++(me ? stats[current.playlist].LowFive : stats[current.playlist].TeamLowFive);
            ++(me ? always_gm[current.playlist].LowFive : always_gm[current.playlist].TeamLowFive);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalLowFiveCumul;
                ++always_gm[it->first].TotalLowFiveCumul;
            }

            AllMiscsLowFive(true);
        }
        else if (name == "HighFive")
        {
            cvarManager->log(" --> HighFive " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalHighFive;
            ++current.TotalHighFive;
            ++session.TotalHighFive;
            ++always.TotalHighFiveCumul;
            ++session.TotalHighFiveCumul;
            ++stats[current.playlist].TotalHighFive;
            ++always_gm[current.playlist].TotalHighFive;

            ++(me ? always.HighFive : always.TeamHighFive);
            ++(me ? current.HighFive : current.TeamHighFive);
            ++(me ? session.HighFive : session.TeamHighFive);
            ++(me ? stats[current.playlist].HighFive : stats[current.playlist].TeamHighFive);
            ++(me ? always_gm[current.playlist].HighFive : always_gm[current.playlist].TeamHighFive);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalHighFiveCumul;
                ++always_gm[it->first].TotalHighFiveCumul;
            }

            AllMiscsHighFive(true);
        }
        else if (name == "MVP")
        {
            cvarManager->log(" --> MVP " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalMVP;
            ++current.TotalMVP;
            ++session.TotalMVP;
            ++always.TotalMVPCumul;
            ++session.TotalMVPCumul;
            ++stats[current.playlist].TotalMVP;
            ++always_gm[current.playlist].TotalMVP;

            ++(me ? always.MVP : always.TeamMVP);
            ++(me ? current.MVP : current.TeamMVP);
            ++(me ? session.MVP : session.TeamMVP);
            ++(me ? stats[current.playlist].MVP : stats[current.playlist].TeamMVP);
            ++(me ? always_gm[current.playlist].MVP : always_gm[current.playlist].TeamMVP);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalMVPCumul;
                ++always_gm[it->first].TotalMVPCumul;
            }

            AllMiscsMVP(true);
        }
        else if (name == "Save")
        {
            cvarManager->log(" --> Save " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalSave;
            ++current.TotalSave;
            ++session.TotalSave;
            ++always.TotalSaveCumul;
            ++session.TotalSaveCumul;
            ++stats[current.playlist].TotalSave;
            ++always_gm[current.playlist].TotalSave;

            ++(me ? always.Save : always.TeamSave);
            ++(me ? current.Save : current.TeamSave);
            ++(me ? session.Save : session.TeamSave);
            ++(me ? stats[current.playlist].Save : stats[current.playlist].TeamSave);
            ++(me ? always_gm[current.playlist].Save : always_gm[current.playlist].TeamSave);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalSaveCumul;
                ++always_gm[it->first].TotalSaveCumul;
            }

            AllSavesSave(true);
        }
        else if (name == "EpicSave")
        {
            cvarManager->log(" --> EpicSave " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalEpicSave;
            ++current.TotalEpicSave;
            ++session.TotalEpicSave;
            ++always.TotalEpicSaveCumul;
            ++session.TotalEpicSaveCumul;
            ++stats[current.playlist].TotalEpicSave;
            ++always_gm[current.playlist].TotalEpicSave;

            ++(me ? always.EpicSave : always.TeamEpicSave);
            ++(me ? current.EpicSave : current.TeamEpicSave);
            ++(me ? session.EpicSave : session.TeamEpicSave);
            ++(me ? stats[current.playlist].EpicSave : stats[current.playlist].TeamEpicSave);
            ++(me ? always_gm[current.playlist].EpicSave : always_gm[current.playlist].TeamEpicSave);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalEpicSaveCumul;
                ++always_gm[it->first].TotalEpicSaveCumul;
            }

            AllSavesEpicSave(true);
        }
        else if (name == "Savior")
        {
            cvarManager->log(" --> Savior " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalSavior;
            ++current.TotalSavior;
            ++session.TotalSavior;
            ++always.TotalSaviorCumul;
            ++session.TotalSaviorCumul;
            ++stats[current.playlist].TotalSavior;
            ++always_gm[current.playlist].TotalSavior;

            ++(me ? always.Savior : always.TeamSavior);
            ++(me ? current.Savior : current.TeamSavior);
            ++(me ? session.Savior : session.TeamSavior);
            ++(me ? stats[current.playlist].Savior : stats[current.playlist].TeamSavior);
            ++(me ? always_gm[current.playlist].Savior : always_gm[current.playlist].TeamSavior);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalSaviorCumul;
                ++always_gm[it->first].TotalSaviorCumul;
            }

            AllSavesSavior(true);
        }
        else if (name == "Damage")
        {
            cvarManager->log(" --> Damage " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalDamage;
            ++current.TotalDamage;
            ++session.TotalDamage;
            ++always.TotalDamageCumul;
            ++session.TotalDamageCumul;
            ++stats[current.playlist].TotalDamage;
            ++always_gm[current.playlist].TotalDamage;

            ++(me ? always.Damage : always.TeamDamage);
            ++(me ? current.Damage : current.TeamDamage);
            ++(me ? session.Damage : session.TeamDamage);
            ++(me ? stats[current.playlist].Damage : stats[current.playlist].TeamDamage);
            ++(me ? always_gm[current.playlist].Damage : always_gm[current.playlist].TeamDamage);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalDamageCumul;
                ++always_gm[it->first].TotalDamageCumul;
            }

            AllDropshotDamage(true);
        }
        else if (name == "UltraDamage")
        {
            cvarManager->log(" --> UltraDamage " + std::string(me ? "PLAYER" : "TEAM"));

            ++always.TotalUltraDamage;
            ++current.TotalUltraDamage;
            ++session.TotalUltraDamage;
            ++always.TotalUltraDamageCumul;
            ++session.TotalUltraDamageCumul;
            ++stats[current.playlist].TotalUltraDamage;
            ++always_gm[current.playlist].TotalUltraDamage;

            ++(me ? always.UltraDamage : always.TeamUltraDamage);
            ++(me ? current.UltraDamage : current.TeamUltraDamage);
            ++(me ? session.UltraDamage : session.TeamUltraDamage);
            ++(me ? stats[current.playlist].UltraDamage : stats[current.playlist].TeamUltraDamage);
            ++(me ? always_gm[current.playlist].UltraDamage : always_gm[current.playlist].TeamUltraDamage);

            for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
            {
                ++stats[it->first].TotalUltraDamageCumul;
                ++always_gm[it->first].TotalUltraDamageCumul;
            }

            AllDropshotUltraDamage(true);
        }

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
        tmp.Shot += stats[it->first].Shot;
        tmp.CenterBall += stats[it->first].CenterBall;
        tmp.ClearBall += stats[it->first].ClearBall;
        tmp.FirstTouch += stats[it->first].FirstTouch;
        tmp.ShotOnGoal += stats[it->first].ShotOnGoal;
        tmp.BicycleHit += stats[it->first].BicycleHit;
        tmp.TeamShot += stats[it->first].TeamShot;
        tmp.TeamCenterBall += stats[it->first].TeamCenterBall;
        tmp.TeamClearBall += stats[it->first].TeamClearBall;
        tmp.TeamFirstTouch += stats[it->first].TeamFirstTouch;
        tmp.TeamShotOnGoal += stats[it->first].TeamShotOnGoal;
        tmp.TeamBicycleHit += stats[it->first].TeamBicycleHit;
        tmp.TotalShot += stats[it->first].TotalShot;
        tmp.TotalCenterBall += stats[it->first].TotalCenterBall;
        tmp.TotalClearBall += stats[it->first].TotalClearBall;
        tmp.TotalFirstTouch += stats[it->first].TotalFirstTouch;
        tmp.TotalShotOnGoal += stats[it->first].TotalShotOnGoal;
        tmp.TotalBicycleHit += stats[it->first].TotalBicycleHit;

        /// Miscs
        tmp.HatTrick += stats[it->first].HatTrick;
        tmp.LowFive += stats[it->first].LowFive;
        tmp.HighFive += stats[it->first].HighFive;
        tmp.MVP += stats[it->first].MVP;
        tmp.TeamHatTrick += stats[it->first].TeamHatTrick;
        tmp.TeamLowFive += stats[it->first].TeamLowFive;
        tmp.TeamHighFive += stats[it->first].TeamHighFive;
        tmp.TeamMVP += stats[it->first].TeamMVP;
        tmp.TotalHatTrick += stats[it->first].TotalHatTrick;
        tmp.TotalLowFive += stats[it->first].TotalLowFive;
        tmp.TotalHighFive += stats[it->first].TotalHighFive;
        tmp.TotalMVP += stats[it->first].TotalMVP;

        /// Assists
        tmp.Assist += stats[it->first].Assist;
        tmp.Playmaker += stats[it->first].Playmaker;
        tmp.TeamAssist += stats[it->first].TeamAssist;
        tmp.TeamPlaymaker += stats[it->first].TeamPlaymaker;
        tmp.TotalAssist += stats[it->first].TotalAssist;
        tmp.TotalPlaymaker += stats[it->first].TotalPlaymaker;

        /// Goals
        tmp.Goal += stats[it->first].Goal;
        tmp.AerialGoal += stats[it->first].AerialGoal;
        tmp.BackwardsGoal += stats[it->first].BackwardsGoal;
        tmp.BicycleGoal += stats[it->first].BicycleGoal;
        tmp.LongGoal += stats[it->first].LongGoal;
        tmp.TurtleGoal += stats[it->first].TurtleGoal;
        tmp.OvertimeGoal += stats[it->first].OvertimeGoal;
        tmp.SwishGoal += stats[it->first].SwishGoal;
        tmp.PoolShot += stats[it->first].PoolShot;
        tmp.TeamGoal += stats[it->first].TeamGoal;
        tmp.TeamAerialGoal += stats[it->first].TeamAerialGoal;
        tmp.TeamBackwardsGoal += stats[it->first].TeamBackwardsGoal;
        tmp.TeamBicycleGoal += stats[it->first].TeamBicycleGoal;
        tmp.TeamLongGoal += stats[it->first].TeamLongGoal;
        tmp.TeamTurtleGoal += stats[it->first].TeamTurtleGoal;
        tmp.TeamOvertimeGoal += stats[it->first].TeamOvertimeGoal;
        tmp.TeamSwishGoal += stats[it->first].TeamSwishGoal;
        tmp.TeamPoolShot += stats[it->first].TeamPoolShot;
        tmp.TotalGoal += stats[it->first].TotalGoal;
        tmp.TotalAerialGoal += stats[it->first].TotalAerialGoal;
        tmp.TotalBackwardsGoal += stats[it->first].TotalBackwardsGoal;
        tmp.TotalBicycleGoal += stats[it->first].TotalBicycleGoal;
        tmp.TotalLongGoal += stats[it->first].TotalLongGoal;
        tmp.TotalTurtleGoal += stats[it->first].TotalTurtleGoal;
        tmp.TotalOvertimeGoal += stats[it->first].TotalOvertimeGoal;
        tmp.TotalSwishGoal += stats[it->first].TotalSwishGoal;
        tmp.TotalPoolShot += stats[it->first].TotalPoolShot;

        /// Saves
        tmp.Save += stats[it->first].Save;
        tmp.EpicSave += stats[it->first].EpicSave;
        tmp.Savior += stats[it->first].Savior;
        tmp.TeamSave += stats[it->first].TeamSave;
        tmp.TeamEpicSave += stats[it->first].TeamEpicSave;
        tmp.TeamSavior += stats[it->first].TeamSavior;
        tmp.TotalSave += stats[it->first].TotalSave;
        tmp.TotalEpicSave += stats[it->first].TotalEpicSave;
        tmp.TotalSavior += stats[it->first].TotalSavior;

        /// Dropshot
        tmp.Damage += stats[it->first].Damage;
        tmp.UltraDamage += stats[it->first].UltraDamage;
        tmp.TeamDamage += stats[it->first].TeamDamage;
        tmp.TeamUltraDamage += stats[it->first].TeamUltraDamage;
        tmp.TotalDamage += stats[it->first].TotalDamage;
        tmp.TotalUltraDamage += stats[it->first].TotalUltraDamage;
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
    session.ShotCumul = tmp.Shot;
    session.CenterBallCumul = tmp.CenterBall;
    session.ClearBallCumul = tmp.ClearBall;
    session.FirstTouchCumul = tmp.FirstTouch;
    session.ShotOnGoalCumul = tmp.ShotOnGoal;
    session.BicycleHitCumul = tmp.BicycleHit;
    session.TeamShotCumul = tmp.TeamShot;
    session.TeamCenterBallCumul = tmp.TeamCenterBall;
    session.TeamClearBallCumul = tmp.TeamClearBall;
    session.TeamFirstTouchCumul = tmp.TeamFirstTouch;
    session.TeamShotOnGoalCumul = tmp.TeamShotOnGoal;
    session.TeamBicycleHitCumul = tmp.TeamBicycleHit;
    session.TotalShotCumul = tmp.TotalShot;
    session.TotalCenterBallCumul = tmp.TotalCenterBall;
    session.TotalClearBallCumul = tmp.TotalClearBall;
    session.TotalFirstTouchCumul = tmp.TotalFirstTouch;
    session.TotalShotOnGoalCumul = tmp.TotalShotOnGoal;
    session.TotalBicycleHitCumul = tmp.TotalBicycleHit;

    /// Miscs
    session.HatTrickCumul = tmp.HatTrick;
    session.LowFiveCumul = tmp.LowFive;
    session.HighFiveCumul = tmp.HighFive;
    session.MVPCumul = tmp.MVP;
    session.TeamHatTrickCumul = tmp.TeamHatTrick;
    session.TeamLowFiveCumul = tmp.TeamLowFive;
    session.TeamHighFiveCumul = tmp.TeamHighFive;
    session.TeamMVPCumul = tmp.TeamMVP;
    session.TotalHatTrickCumul = tmp.TotalHatTrick;
    session.TotalLowFiveCumul = tmp.TotalLowFive;
    session.TotalHighFiveCumul = tmp.TotalHighFive;
    session.TotalMVPCumul = tmp.TotalMVP;

    /// Assists
    session.AssistCumul = tmp.Assist;
    session.PlaymakerCumul = tmp.Playmaker;
    session.TeamAssistCumul = tmp.TeamAssist;
    session.TeamPlaymakerCumul = tmp.TeamPlaymaker;
    session.TotalAssistCumul = tmp.TotalAssist;
    session.TotalPlaymakerCumul = tmp.TotalPlaymaker;

    /// Goals
    session.GoalCumul = tmp.Goal;
    session.AerialGoalCumul = tmp.AerialGoal;
    session.BackwardsGoalCumul = tmp.BackwardsGoal;
    session.BicycleGoalCumul = tmp.BicycleGoal;
    session.LongGoalCumul = tmp.LongGoal;
    session.TurtleGoalCumul = tmp.TurtleGoal;
    session.OvertimeGoalCumul = tmp.OvertimeGoal;
    session.SwishGoalCumul = tmp.SwishGoal;
    session.PoolShotCumul = tmp.PoolShot;
    session.TeamGoalCumul = tmp.TeamGoal;
    session.TeamAerialGoalCumul = tmp.TeamAerialGoal;
    session.TeamBackwardsGoalCumul = tmp.TeamBackwardsGoal;
    session.TeamBicycleGoalCumul = tmp.TeamBicycleGoal;
    session.TeamLongGoalCumul = tmp.TeamLongGoal;
    session.TeamTurtleGoalCumul = tmp.TeamTurtleGoal;
    session.TeamOvertimeGoalCumul = tmp.TeamOvertimeGoal;
    session.TeamSwishGoalCumul = tmp.TeamSwishGoal;
    session.TeamPoolShotCumul = tmp.TeamPoolShot;
    session.TotalGoalCumul = tmp.TotalGoal;
    session.TotalAerialGoalCumul = tmp.TotalAerialGoal;
    session.TotalBackwardsGoalCumul = tmp.TotalBackwardsGoal;
    session.TotalBicycleGoalCumul = tmp.TotalBicycleGoal;
    session.TotalLongGoalCumul = tmp.TotalLongGoal;
    session.TotalTurtleGoalCumul = tmp.TotalTurtleGoal;
    session.TotalOvertimeGoalCumul = tmp.TotalOvertimeGoal;
    session.TotalSwishGoalCumul = tmp.TotalSwishGoal;
    session.TotalPoolShotCumul = tmp.TotalPoolShot;

    /// Saves
    session.SaveCumul = tmp.Save;
    session.EpicSaveCumul = tmp.EpicSave;
    session.SaviorCumul = tmp.Savior;
    session.TeamSaveCumul = tmp.TeamSave;
    session.TeamEpicSaveCumul = tmp.TeamEpicSave;
    session.TeamSaviorCumul = tmp.TeamSavior;
    session.TotalSaveCumul = tmp.TotalSave;
    session.TotalEpicSaveCumul = tmp.TotalEpicSave;
    session.TotalSaviorCumul = tmp.TotalSavior;

    /// Dropshot
    session.DamageCumul = tmp.Damage;
    session.UltraDamageCumul = tmp.UltraDamage;
    session.TeamDamageCumul = tmp.TeamDamage;
    session.TeamUltraDamageCumul = tmp.TeamUltraDamage;
    session.TotalDamageCumul = tmp.TotalDamage;
    session.TotalUltraDamageCumul = tmp.TotalUltraDamage;

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
    current.demo = 0;
    current.death = 0;

    /// Shots
    current.CenterBall = 0;
    current.ClearBall = 0;
    current.FirstTouch = 0;
    current.ShotOnGoal = 0;
    current.BicycleHit = 0;

    current.TeamCenterBall = 0;
    current.TeamClearBall = 0;
    current.TeamFirstTouch = 0;
    current.TeamShotOnGoal = 0;
    current.TeamBicycleHit = 0;

    current.TotalCenterBall = 0;
    current.TotalClearBall = 0;
    current.TotalFirstTouch = 0;
    current.TotalShotOnGoal = 0;
    current.TotalBicycleHit = 0;

    /// Miscs
    current.HatTrick = 0;
    current.LowFive = 0;
    current.HighFive = 0;
    current.MVP = 0;

    current.TeamHatTrick = 0;
    current.TeamLowFive = 0;
    current.TeamHighFive = 0;
    current.TeamMVP = 0;

    current.TotalHatTrick = 0;
    current.TotalLowFive = 0;
    current.TotalHighFive = 0;
    current.TotalMVP = 0;

    /// Assists
    current.Assist = 0;
    current.Playmaker = 0;

    current.TeamAssist = 0;
    current.TeamPlaymaker = 0;

    current.TotalAssist = 0;
    current.TotalPlaymaker = 0;

    /// Goals
    current.Goal = 0;
    current.AerialGoal = 0;
    current.BackwardsGoal = 0;
    current.BicycleGoal = 0;
    current.LongGoal = 0;
    current.TurtleGoal = 0;
    current.OvertimeGoal = 0;
    current.SwishGoal = 0;
    current.PoolShot = 0;

    current.TeamGoal = 0;
    current.TeamAerialGoal = 0;
    current.TeamBackwardsGoal = 0;
    current.TeamBicycleGoal = 0;
    current.TeamLongGoal = 0;
    current.TeamTurtleGoal = 0;
    current.TeamOvertimeGoal = 0;
    current.TeamSwishGoal = 0;
    current.TeamPoolShot = 0;

    current.TotalGoal = 0;
    current.TotalAerialGoal = 0;
    current.TotalBackwardsGoal = 0;
    current.TotalBicycleGoal = 0;
    current.TotalLongGoal = 0;
    current.TotalTurtleGoal = 0;
    current.TotalOvertimeGoal = 0;
    current.TotalSwishGoal = 0;
    current.TotalPoolShot = 0;

    /// Saves
    current.Save = 0;
    current.EpicSave = 0;
    current.Savior = 0;

    current.TeamSave = 0;
    current.TeamEpicSave = 0;
    current.TeamSavior = 0;

    current.TotalSave = 0;
    current.TotalEpicSave = 0;
    current.TotalSavior = 0;

    /// DropShot
    current.Save = 0;
    current.EpicSave = 0;
    current.Savior = 0;

    current.TeamSave = 0;
    current.TeamEpicSave = 0;
    current.TeamSavior = 0;

    current.TotalSave = 0;
    current.TotalEpicSave = 0;
    current.TotalSavior = 0;
}
