#include "pch.h"
#include "RocketStats.h"


namespace NS_RS {
	BAKKESMOD_PLUGIN(RocketStats, "Tracks matches results", plugin_version, 0)

    void RocketStats::onLoad()
    {
        // notifierToken = gameWrapper->GetMMRWrapper().RegisterMMRNotifier(std::bind(&RocketStats::UpdateMMR, this, std::placeholders::_1));

        LoadImgs();

        cvarManager->registerNotifier(
            "RocketStats_reset_stats",
            [this](std::vector<std::string> params)
            { ResetStats(); },
            "Reset Stats",
            PERMISSION_ALL);

        cvarManager->registerNotifier(
            "RocketStats_reload_images",
            [this](std::vector<std::string> params)
            { LoadImgs(); },
            "Reload images",
            PERMISSION_ALL);

        // Register drawable
        gameWrapper->RegisterDrawable(std::bind(&RocketStats::Render, this, std::placeholders::_1));

        // Hook on Event
        gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&RocketStats::GameStart, this, std::placeholders::_1));
        gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&RocketStats::GameEnd, this, std::placeholders::_1));
        gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", bind(&RocketStats::OnBoostStart, this, std::placeholders::_1));
        gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
        gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Destroyed", bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));

        WriteInFile("RocketStats_Div.txt", "");
        WriteInFile("RocketStats_Win.txt", "0");
        WriteInFile("RocketStats_Streak.txt", "0");
        WriteInFile("RocketStats_Loose.txt", "0");
        WriteInFile("RocketStats_MMRChange.txt", "0");
        WriteInFile("RocketStats_MMR.txt", "0");
        WriteInFile("RocketStats_Rank.txt", "");
        WriteInFile("RocketStats_GameMode.txt", "");
        WriteInFile("RocketStats_images/BoostState.txt", "-1");

        InitRank();

        // Register Cvars
        cvarManager->registerCvar("RS_Use_v1", "0", "Use the v1 overlay", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_Use_v2", "0", "Use the v2 overlay", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_disp_ig", "1", "Display information panel", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_hide_overlay_ig", "0", "Hide overlay while in-game", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_disp_mmr", "1", "Display the current MMR", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_disp_wins", "1", "Display the wins on the current game mode", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_disp_losses", "1", "Display the losses on the current game mode", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_disp_streak", "1", "Display the streak on the current game mode", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_disp_rank", "1", "Display the rank on the current game mode", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_disp_gamemode", "1", "Display the current game mode", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_enable_float", "0", "Enable floating point for MMR (OBS only)", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_x_position", "0.700", "Overlay X position", true, true, 0, true, 1.0f);
        cvarManager->registerCvar("RS_y_position", "0.575", "Overlay Y position", true, true, 0, true, 1.0f);
        cvarManager->registerCvar("RS_scale", "1", "Overlay scale", true, true, 0, true, 10);
        cvarManager->registerCvar("RocketStats_stop_boost", "1", "Stop Boost animation", true, true, 0, true, 1);
        cvarManager->registerCvar("RS_session", "0", "Display session information instead of game mode", true, true, 0, true, 1, true);
    }

    void RocketStats::onUnload() {}
}