#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    void RocketStats::GameStart(std::string eventName)
    {
        if (!gameWrapper->IsInOnlineGame() || isGameStarted)
            return;

        cvarManager->log("===== GameStart =====");
        CarWrapper me = gameWrapper->GetLocalCar();
        if (me.IsNull())
            return;

        PriWrapper mePRI = me.GetPRI();
        if (mePRI.IsNull())
            return;

        TeamInfoWrapper myTeam = mePRI.GetTeam();
        if (myTeam.IsNull())
            return;

        MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
        currentPlaylist = mmrw.GetCurrentPlaylist();
        SkillRank playerRank = mmrw.GetPlayerRank(gameWrapper->GetUniqueID(), currentPlaylist);
        cvarManager->log(std::to_string(currentPlaylist) + " -> " + GetPlaylistName(currentPlaylist));

        writeGameMode();
        writeMMRChange();
        writeWin();
        writeStreak();
        writeLosses();
        writeMMR();

        // Get TeamNum
        myTeamNum = myTeam.GetTeamNum();

        // Set Game Started
        isGameStarted = true;
        isGameEnded = false;

        UpdateMMR(gameWrapper->GetUniqueID());
        WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));
    }

    void RocketStats::GameEnd(std::string eventName)
    {
        if (gameWrapper->IsInOnlineGame() && myTeamNum != -1)
        {
            cvarManager->log("===== GameEnd =====");
            ServerWrapper server = gameWrapper->GetOnlineGame();
            TeamWrapper winningTeam = server.GetGameWinner();
            if (winningTeam.IsNull())
                return;

            int teamnum = winningTeam.GetTeamNum();

            // Game as ended
            isGameEnded = true;

            MMRWrapper mw = gameWrapper->GetMMRWrapper();

            if (myTeamNum == winningTeam.GetTeamNum())
            {
                cvarManager->log("===== Game Won =====");
                // On Win, Increase streak and Win Number
                stats[currentPlaylist].win++;
                session.win++;

                if (stats[currentPlaylist].streak < 0)
                {
                    session.streak = 1;
                    stats[currentPlaylist].streak = 1;
                }
                else
                {
                    session.streak += 1;
                    stats[currentPlaylist].streak++;
                }

                writeWin();
            }
            else
            {
                cvarManager->log("===== Game Lost =====");
                // On Loose, Increase loose Number and decrease streak
                stats[currentPlaylist].losses++;
                session.losses++;
                if (stats[currentPlaylist].streak > 0)
                {
                    session.streak = -1;
                    stats[currentPlaylist].streak = -1;
                }
                else
                {
                    session.streak--;
                    stats[currentPlaylist].streak--;
                }

                writeLosses();
            }

            writeStreak();

            // Reset myTeamNum security
            myTeamNum = -1;

            WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));

            gameWrapper->SetTimeout([&](GameWrapper* gameWrapper)
                { UpdateMMR(gameWrapper->GetUniqueID()); },
                3.0F);
        }
    }

    void RocketStats::GameDestroyed(std::string eventName)
    {
        cvarManager->log("===== GameDestroyed =====");
        // Check if Game Ended, if not, RAGE QUIT or disconnect
        if (isGameStarted == true && isGameEnded == false)
        {
            session.losses++;
            stats[currentPlaylist].losses++;
            if (stats[currentPlaylist].streak > 0)
            {
                session.streak = 0;
                stats[currentPlaylist].streak = -1;
            }
            else
            {
                session.streak--;
                stats[currentPlaylist].streak--;
            }

            writeStreak();
            writeLosses();
        }
        isGameEnded = true;
        isGameStarted = false;
        WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
    }
}