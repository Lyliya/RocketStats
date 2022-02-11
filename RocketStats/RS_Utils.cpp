#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    std::string RocketStats::GetRank(int tierID)
    {
        cvarManager->log("tier: " + std::to_string(tierID));
        if (tierID < rank_nb)
            return rank[tierID].name;
        else
            return "Unranked";
    }

    std::string RocketStats::GetPlaylistName(int playlistID)
    {
        if (playlistName.find(playlistID) != playlistName.end())
            return playlistName.at(playlistID);
        else
            return "Unknown Game Mode";
    }

    void RocketStats::LoadImgs()
    {
        int load_check = 0;

        crown = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath() / "RocketStats" / "RocketStats_images" / "crown.png", true);
        load_check += (int)crown->LoadForCanvas();
        LogImageLoadStatus(crown->LoadForCanvas(), "crown");

        win = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath() / "RocketStats" / "RocketStats_images" / "win.png", true);
        load_check += (int)win->LoadForCanvas();
        LogImageLoadStatus(win->LoadForCanvas(), "win");

        loose = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath() / "RocketStats" / "RocketStats_images" / "loose.png", true);
        load_check += (int)loose->LoadForCanvas();
        LogImageLoadStatus(loose->LoadForCanvas(), "loose");

        streak = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath() / "RocketStats" / "RocketStats_images" / "streak.png", true);
        load_check += (int)streak->LoadForCanvas();
        LogImageLoadStatus(streak->LoadForCanvas(), "streak");

        for (int i = 0; i < rank_nb; i++)
        {
            rank[i].image = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath() / "RocketStats" / "RocketStats_images" / (rank[i].name + ".png"), true);
            load_check += (int)rank[i].image->LoadForCanvas();
            LogImageLoadStatus(rank[i].image->LoadForCanvas(), rank[i].name);
        }
        cvarManager->log(std::to_string(load_check) + "/27 images were loaded successfully");
    }

    void RocketStats::LogImageLoadStatus(bool status, std::string imageName)
    {
        if (status)
            cvarManager->log(imageName + ": image load");
        else
            cvarManager->log(imageName + ": failed to load");
    }
}