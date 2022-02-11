#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    void RocketStats::WriteInFile(std::string _filename, std::string _value)
    {
        std::ofstream stream(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\" + _filename, std::ios::out | std::ios::trunc);

        if (stream.is_open())
        {
            stream << _value;
            stream.close();
        }
        else
        {
            cvarManager->log("Can't write to file: " + _filename);
            cvarManager->log("Value to write was: " + _value);
        }
    }

    void RocketStats::writeGameMode()
    {
        WriteInFile("RocketStats_GameMode.txt", GetPlaylistName(currentPlaylist));
    }

    void RocketStats::writeMMR()
    {
        std::string tmp;
        if (cvarManager->getCvar("RS_enable_float").getBoolValue())
            tmp = to_string_with_precision(stats[currentPlaylist].myMMR, 2);
        else
            tmp = std::to_string(int(stats[currentPlaylist].myMMR));
        WriteInFile("RocketStats_MMR.txt", tmp);
    }
    void RocketStats::writeMMRChange()
    {
        bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
        Stats current = (RS_session == true) ? session : stats[currentPlaylist];

        std::string tmp;
        if (cvarManager->getCvar("RS_enable_float").getBoolValue())
            tmp = to_string_with_precision(current.MMRChange, 2);
        else
            tmp = std::to_string(int(current.MMRChange));

        if (current.MMRChange > 0)
            WriteInFile("RocketStats_MMRChange.txt", "+" + tmp);
        else
            WriteInFile("RocketStats_MMRChange.txt", tmp);
    }

    void RocketStats::writeStreak()
    {
        bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
        Stats current = (RS_session == true) ? session : stats[currentPlaylist];

        if (current.streak > 0)
            WriteInFile("RocketStats_Streak.txt", "+" + std::to_string(current.streak));
        else
            WriteInFile("RocketStats_Streak.txt", std::to_string(current.streak));
    }

    void RocketStats::writeWin()
    {
        bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
        Stats current = (RS_session == true) ? session : stats[currentPlaylist];
        WriteInFile("RocketStats_Win.txt", std::to_string(current.win));
    }

    void RocketStats::writeLosses()
    {
        bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
        Stats current = (RS_session == true) ? session : stats[currentPlaylist];
        WriteInFile("RocketStats_Loose.txt", std::to_string(current.losses));
    }
}