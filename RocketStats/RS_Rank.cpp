#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    void RocketStats::InitRank()
    {
        lastGameMode = 0;
        currentGameMode = 0;
        currentMMR = 0;
        currentRank = "norank";
        currentDivision = "nodiv";
        lastRank = "norank";

        // std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

        // WriteInFile("RocketStats_images/rank.html", _value);
    }

    void RocketStats::MajRank(int _gameMode, bool isRanked, float _currentMMR, SkillRank playerRank)
    {
        currentGameMode = _gameMode;
        currentMMR = _currentMMR;
        currentTier = playerRank.Tier;

        if (isRanked)
        {
            if (currentGameMode != 34 && playerRank.MatchesPlayed < 10)
            {
                currentRank = "Placement: " + std::to_string(playerRank.MatchesPlayed) + "/10";
                currentDivision = "";
            }
            else
            {
                currentRank = GetRank(playerRank.Tier);
                currentDivision = "Div. " + std::to_string(playerRank.Division + 1);
                WriteInFile("RocketStats_Div.txt", currentDivision);
            }

            if (currentRank != lastRank)
            {
                // std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"" + currentRank + ".png" + "\" width = \"100\" height = \"100\" />";

                // WriteInFile("RocketStats_images/rank.html", _value);
                WriteInFile("RocketStats_Rank.txt", currentRank);
            }
        }
        else
        {
            currentRank = GetPlaylistName(currentGameMode);
            currentDivision = "";

            // std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

            // WriteInFile("RocketStats_images/rank.html", _value);
            WriteInFile("RocketStats_Rank.txt", currentRank);
        }
    }
}