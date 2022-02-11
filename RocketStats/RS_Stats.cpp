#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    void RocketStats::UpdateMMR(UniqueIDWrapper id)
    {
        cvarManager->log("===== updateMMR =====");

        if (id.GetIdString() != gameWrapper->GetUniqueID().GetIdString()) {
            cvarManager->log("not the user");
            return;
        }

        if (currentPlaylist == 0)
        {
            cvarManager->log("Invalid playlist id. Have you just opened the game ?");
            return;
        }

        MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
        float mmr = mmrw.GetPlayerMMR(id, currentPlaylist);
        SkillRank playerRank = mmrw.GetPlayerRank(id, currentPlaylist);

        if (stats[currentPlaylist].isInit == false)
        {
            stats[currentPlaylist].myMMR = mmr;
            stats[currentPlaylist].isInit = true;
        }
        stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (mmr - stats[currentPlaylist].myMMR);
        stats[currentPlaylist].myMMR = mmr;

        MajRank(currentPlaylist, mmrw.IsRanked(currentPlaylist), stats[currentPlaylist].myMMR, playerRank);
        SessionStats();
        writeMMR();
        writeMMRChange();
    }

    void RocketStats::SessionStats()
    {
        Stats tmp;

        for (auto it = playlistName.begin(); it != playlistName.end(); it++)
        {
            tmp.MMRChange += stats[it->first].MMRChange;
            tmp.win += stats[it->first].win;
            tmp.losses += stats[it->first].losses;
        }

        session.myMMR = stats[currentPlaylist].myMMR;
        session.MMRChange = tmp.MMRChange;
        session.win = tmp.win;
        session.losses = tmp.losses;
    }

    void RocketStats::ResetStats()
    {
        for (auto& kv : stats)
        {
            kv.second = Stats();
        }
        session = Stats();
        WriteInFile("RocketStats_Win.txt", std::to_string(0));
        WriteInFile("RocketStats_Streak.txt", std::to_string(0));
        WriteInFile("RocketStats_Loose.txt", std::to_string(0));
        WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));
        WriteInFile("RocketStats_MMR.txt", std::to_string(0));
        WriteInFile("RocketStats_Rank.txt", "");
        WriteInFile("RocketStats_Div.txt", "");
        WriteInFile("RocketStats_GameMode.txt", "");

        InitRank();
    }
}