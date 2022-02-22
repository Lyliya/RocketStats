/* ===========================================================
 *   Developped by @Lyliya, @NuSa_yt, @Arubinu42 & @Larsluph
 * =========================================================== */

#include "RocketStats.h"

BAKKESMOD_PLUGIN(RocketStats, "RocketStats", "4.0", PERMISSION_ALL)

#pragma region Utils
Stats RocketStats::GetStats()
{
    Stats result;

    switch (RS_mode)
    {
        case 1: result = stats[currentPlaylist]; break;
        case 2: result = always; break;
        case 3: result = always_gm[currentPlaylist]; break;
        default: result = session;
    }

    return result;
}

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

void RocketStats::LogImageLoadStatus(bool status, std::string imageName)
{
    if (status)
        cvarManager->log(imageName + ": image load");
    else
        cvarManager->log(imageName + ": failed to load");
}

std::shared_ptr<ImageWrapper> RocketStats::LoadImg(const std::string& _filename)
{
    fs::path _path = GetPath(_filename);
    return LoadImg(_path);
}

std::shared_ptr<ImageWrapper> RocketStats::LoadImg(fs::path& _path)
{
    return std::make_shared<ImageWrapper>(_path, false, true);
}

void RocketStats::LoadImgs()
{
    int load_check = 0;

    for (int i = 0; i < rank_nb; i++)
    {
        rank[i].image = LoadImg("RocketStats_images/" + rank[i].name + ".png");
        load_check += (int)rank[i].image->IsLoadedForImGui();
        LogImageLoadStatus(rank[i].image->IsLoadedForImGui(), rank[i].name);
    }
    cvarManager->log(std::to_string(load_check) + "/" + std::to_string(rank_nb) + " images were loaded successfully");
}

void RocketStats::RecoveryOldVars()
{
    cvarManager->log("Recovery old vars !");

    CVarWrapper RS_session = cvarManager->getCvar("RS_session");
    if (!RS_session.IsNull())
        RS_mode = (RS_session.getBoolValue() ? 1 : 0);

    CVarWrapper RS_Use_v1 = cvarManager->getCvar("RS_Use_v1");
    CVarWrapper RS_Use_v2 = cvarManager->getCvar("RS_Use_v2");
    if (!RS_Use_v1.IsNull() && !RS_Use_v1.IsNull())
        SetTheme((RS_Use_v1.getBoolValue() == RS_Use_v1.getBoolValue()) ? "Arubinu42" : (RS_Use_v1.getBoolValue() ? "Default" : "Redesigned"));

    CVarWrapper RS_x_position = cvarManager->getCvar("RS_x_position");
    if (!RS_x_position.IsNull())
        RS_x = RS_x_position.getFloatValue();

    CVarWrapper RS_y_position = cvarManager->getCvar("RS_y_position");
    if (!RS_y_position.IsNull())
        RS_y = RS_y_position.getFloatValue();

    CVarWrapper RS_disp_ig = cvarManager->getCvar("RS_disp_ig");
    if (!RS_disp_ig.IsNull())
        RS_disp_overlay = (RS_disp_ig.getBoolValue() ? 1 : 0);

    CVarWrapper RS_hide_overlay_ig = cvarManager->getCvar("RS_hide_overlay_ig");
    if (!RS_hide_overlay_ig.IsNull())
        RS_enable_ingame = (RS_hide_overlay_ig.getBoolValue() ? 0 : 1);

    CVarWrapper RS_disp_gamemode = cvarManager->getCvar("RS_disp_gamemode");
    if (!RS_disp_gamemode.IsNull())
        RS_hide_gm = (RS_disp_gamemode.getBoolValue() ? 0 : 1);

    CVarWrapper RS_disp_rank = cvarManager->getCvar("RS_disp_rank");
    if (!RS_disp_rank.IsNull())
        RS_hide_rank = (RS_disp_rank.getBoolValue() ? 0 : 1);

    CVarWrapper RS_disp_mmr = cvarManager->getCvar("RS_disp_mmr");
    if (!RS_disp_mmr.IsNull())
        RS_hide_mmr = (RS_disp_mmr.getBoolValue() ? 0 : 1);

    CVarWrapper RS_disp_wins = cvarManager->getCvar("RS_disp_wins");
    if (!RS_disp_wins.IsNull())
        RS_hide_win = (RS_disp_wins.getBoolValue() ? 0 : 1);

    CVarWrapper RS_disp_losses = cvarManager->getCvar("RS_disp_losses");
    if (!RS_disp_losses.IsNull())
        RS_hide_loss = (RS_disp_losses.getBoolValue() ? 0 : 1);

    CVarWrapper RS_disp_streak = cvarManager->getCvar("RS_disp_streak");
    if (!RS_disp_streak.IsNull())
        RS_hide_streak = (RS_disp_streak.getBoolValue() ? 0 : 1);

    CVarWrapper RocketStats_stop_boost = cvarManager->getCvar("RocketStats_stop_boost");
    if (!RocketStats_stop_boost.IsNull())
        RS_file_boost = (RocketStats_stop_boost.getBoolValue() ? 0 : 1);
}
#pragma endregion

#pragma region PluginLoadRoutines
void RocketStats::onLoad()
{
    // notifierToken = gameWrapper->GetMMRWrapper().RegisterMMRNotifier(std::bind(&RocketStats::UpdateMMR, this, std::placeholders::_1));

    SetDefaultFolder();
    rs_title = LoadImg("RocketStats_images/title.png");

    LoadImgs();
    LoadThemes();

    InitRank();
    InitStats();
    bool recovery = !ReadConfig();
    ChangeTheme(RS_theme);

    // Can be used from the console or in bindings
    cvarManager->registerNotifier("RS_toggle_menu", [this](std::vector<std::string> params) {
            ToggleSettings("RS_toggle_menu");
    }, "Toggle menu", PERMISSION_ALL);

    // Hook on Event
    gameWrapper->HookEvent("Function TAGame.GFxData_StartMenu_TA.EventTitleScreenClicked", bind(&RocketStats::ShowPlugin, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&RocketStats::GameStart, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&RocketStats::GameEnd, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", bind(&RocketStats::OnBoostStart, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Destroyed", bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));

    gameWrapper->HookEventWithCallerPost<ServerWrapper>("Function TAGame.GFxHUD_TA.HandleStatEvent", std::bind(&RocketStats::onStatEvent, this, std::placeholders::_1, std::placeholders::_2));
    gameWrapper->HookEventWithCallerPost<ServerWrapper>("Function TAGame.GFxHUD_TA.HandleStatTickerMessage", std::bind(&RocketStats::onStatTickerMessage, this, std::placeholders::_1, std::placeholders::_2));

    ResetFiles(); // Reset all files (and create them if they don't exist)
    RemoveFile("RocketStats_Loose.txt"); // Delete the old file
    RemoveFile("RocketStats_images/BoostState.txt"); // Delete the old file
    RemoveFile("plugins/settings/rocketstats.set", true); // Delete the old file

    // Register Cvars
    if (recovery)
        RecoveryOldVars();

    cvarManager->registerCvar("cl_rocketstats_settings", (isSettingsOpen_ ? "1" : "0"), "Display RocketStats settings", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper now) {
        isSettingsOpen_ = now.getBoolValue();

        cvarManager->log("cl_rocketstats_settings: " + std::string(isSettingsOpen_ ? "true" : "false"));
        if (!isSettingsOpen_)
            WriteConfig();
    });

    cvarManager->registerCvar("RS_mode", std::to_string(RS_mode), "Mode", true, true, 0, true, float(modes.size() - 1), false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_theme", std::to_string(RS_theme), "Theme", true, true, 0, false, 99, false).addOnValueChanged([this](std::string old, CVarWrapper now) {
        if (!ChangeTheme(now.getIntValue()))
            now.setValue(old);
    });

    cvarManager->registerCvar("RS_x", std::to_string(RS_x), "X", true, true, 0.f, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_y", std::to_string(RS_y), "Y", true, true, 0.f, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_scale", std::to_string(RS_scale), "Scale", true, true, 0.f, true, 10.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_rotate", std::to_string(RS_rotate), "Rotate", true, true, -180.f, true, 180.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_opacity", std::to_string(RS_opacity), "Opacity", true, true, 0.f, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("RS_disp_overlay", (RS_disp_overlay ? "1" : "0"), "Overlay", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("RS_disp_obs", (RS_disp_obs ? "1" : "0"), "Show on OBS", true, true, 0, true, 1, false);
    cvarManager->registerCvar("RS_enable_inmenu", (RS_enable_inmenu ? "1" : "0"), "Show in menu", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_enable_ingame", (RS_enable_ingame ? "1" : "0"), "Show while in-game", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_enable_float", (RS_enable_float ? "1" : "0"), "Enable floating point", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_onchange_scale", (RS_onchange_scale ? "1" : "0"), "Reset scale on change", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_onchange_rotate", (RS_onchange_rotate ? "1" : "0"), "Reset rotate on change", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_onchange_opacity", (RS_onchange_opacity ? "1" : "0"), "Reset opacity on change", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_onchange_position", (RS_onchange_position ? "1" : "0"), "Reset position on change", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("RS_in_file", std::to_string(RS_in_file), "Informations", true, true, 0, true, 1, true).addOnValueChanged([this](std::string old, CVarWrapper now) {
        if (!now.getBoolValue())
            return;

        WriteGameMode();
        WriteRank();
        WriteDiv();
        WriteMMR();
        WriteMMRChange();
        WriteMMRCumulChange();
        WriteWin();
        WriteLoss();
        WriteStreak();
        WriteDemo();
        WriteDeath();
        WriteBoost();
    });
    cvarManager->registerCvar("RS_file_gm", (RS_file_gm ? "1" : "0"), "Write GameMode in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_rank", (RS_file_rank ? "1" : "0"), "Write Rank in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_div", (RS_file_div ? "1" : "0"), "Write Division in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_mmr", (RS_file_mmr ? "1" : "0"), "Write MMR in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_mmrc", (RS_file_mmrc ? "1" : "0"), "Write MMRChange in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_mmrcc", (RS_file_mmrcc ? "1" : "0"), "Write MMRChangeCumul in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_win", (RS_file_win ? "1" : "0"), "Write Wins in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_loss", (RS_file_loss ? "1" : "0"), "Write Losses in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_streak", (RS_file_streak ? "1" : "0"), "Write Streaks in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_demo", (RS_file_demo ? "1" : "0"), "Write Demolitions in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_death", (RS_file_death ? "1" : "0"), "Write Deaths in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_file_boost", (RS_file_boost ? "1" : "0"), "Write Boost in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("RS_hide_gm", (RS_hide_div ? "1" : "0"), "Hide GameMode", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_rank", (RS_hide_rank ? "1" : "0"), "Hide Rank", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_div", (RS_hide_div ? "1" : "0"), "Hide Division", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_mmr", (RS_hide_mmr ? "1" : "0"), "Hide MMR", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_mmrc", (RS_hide_mmrc ? "1" : "0"), "Hide MMRChange", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_mmrcc", (RS_hide_mmrcc ? "1" : "0"), "Hide MMRChangeCumul", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_win", (RS_hide_win ? "1" : "0"), "Hide Wins", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_loss", (RS_hide_loss ? "1" : "0"), "Hide Losses", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_streak", (RS_hide_streak ? "1" : "0"), "Hide Streaks", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_demo", (RS_hide_demo ? "1" : "0"), "Hide Demolitions", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_death", (RS_hide_death ? "1" : "0"), "Hide Deaths", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_replace_mmr", (RS_replace_mmr ? "1" : "0"), "Replace MMR with MMRChange", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    // Displays the plugin shortly after initialization
    gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
        TogglePlugin("onLoad", ToggleFlags_Show);
    }, 0.2F);
}

void RocketStats::onUnload()
{
    WriteConfig(); // Save settings (if not already done)

    gameWrapper->UnhookEvent("Function TAGame.GFxData_StartMenu_TA.EventTitleScreenClicked");
    gameWrapper->UnhookEvent("Function GameEvent_TA.Countdown.BeginState");
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded");
    gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.BeginState");
    gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.EndState");
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_TA.Destroyed");

    //gameWrapper->UnhookEventPost("Function TAGame.GFxHUD_TA.HandleStatEvent");
    //gameWrapper->UnhookEventPost("Function TAGame.GFxHUD_TA.HandleStatTickerMessage");

    TogglePlugin("onUnload", ToggleFlags_Hide); // Hide the plugin before unloading it
}

void RocketStats::SetDefaultFolder()
{
    rs_path = "RocketStats";
    rs_fonts = "../../";

    // If the old folder does not exist, targets the new one in data
    if (!ExistsPath(rs_path, true))
    {
        rs_fonts = "../";
        rs_path = "data/" + rs_path;
    }
    rs_fonts += "RocketStats";

    cvarManager->log("RS_path: " + GetPath());
    cvarManager->log("RS_fonts: " + GetPath("", true) + "data/fonts/" + rs_fonts);
}

void RocketStats::ShowPlugin(std::string eventName)
{
    TogglePlugin(eventName, ToggleFlags_Show);
}

void RocketStats::TogglePlugin(std::string eventName, ToggleFlags mode)
{
    if (mode == ToggleFlags_Toggle || (mode == ToggleFlags_Show && !isPluginOpen_) || (mode == ToggleFlags_Hide && isPluginOpen_))
    {
        isPluginOpen_ = !isPluginOpen_;
        cvarManager->executeCommand("togglemenu " + GetMenuName());
    }
}

void RocketStats::ToggleSettings(std::string eventName, ToggleFlags mode)
{
    if (mode == ToggleFlags_Toggle || (mode == ToggleFlags_Show && !isSettingsOpen_) || (mode == ToggleFlags_Hide && isSettingsOpen_))
    {
        isSettingsOpen_ = !isSettingsOpen_;
        cvarManager->getCvar("cl_rocketstats_settings").setValue(isSettingsOpen_);

        cvarManager->log("ToggleSettings: " + std::string(isSettingsOpen_ ? "true" : "false"));
        if (!isSettingsOpen_)
            WriteConfig(); // Saves settings when closing the menu
    }
}
#pragma endregion

#pragma region GameMgmt
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

    WriteGameMode();
    WriteRank();
    WriteDiv();
    WriteMMR();
    WriteMMRChange();
    WriteMMRCumulChange();
    WriteWin();
    WriteLoss();
    WriteStreak();
    WriteDemo();
    WriteDeath();
    WriteBoost();

    // Get TeamNum
    myTeamNum = myTeam.GetTeamNum();

    // Set Game Started
    isGameStarted = true;
    isGameEnded = false;

    UpdateMMR(gameWrapper->GetUniqueID());
    WriteConfig();
    if (RS_in_file && RS_file_boost)
        WriteInFile("RocketStats_BoostState.txt", std::to_string(0));

    cvarManager->log("===== !GameStart =====");
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
            always.win++;
            session.win++;
            stats[currentPlaylist].win++;
            always_gm[currentPlaylist].win++;

            if (stats[currentPlaylist].streak < 0)
            {
                always.streak = 1;
                session.streak = 1;
                stats[currentPlaylist].streak = 1;
                always_gm[currentPlaylist].streak = 1;
            }
            else
            {
                always.streak++;
                session.streak++;
                stats[currentPlaylist].streak++;
                always_gm[currentPlaylist].streak++;
            }

            theme_refresh = 1;
            WriteWin();
        }
        else
        {
            cvarManager->log("===== Game Lost =====");
            // On Loose, Increase loose Number and decrease streak
            always.loss++;
            session.loss++;
            stats[currentPlaylist].loss++;
            always_gm[currentPlaylist].loss++;

            if (stats[currentPlaylist].streak > 0)
            {
                always.streak = -1;
                session.streak = -1;
                stats[currentPlaylist].streak = -1;
                always_gm[currentPlaylist].streak = -1;
            }
            else
            {
                always.streak--;
                session.streak--;
                stats[currentPlaylist].streak--;
                always_gm[currentPlaylist].streak--;
            }

            theme_refresh = 1;
            WriteLoss();
        }

        WriteStreak();
        WriteConfig();

        // Reset myTeamNum security
        myTeamNum = -1;

        if (RS_in_file && RS_file_boost)
            WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));

        gameWrapper->SetTimeout([&](GameWrapper *gameWrapper) { UpdateMMR(gameWrapper->GetUniqueID()); }, 3.0F);

        cvarManager->log("===== !GameEnd =====");
    }
}

void RocketStats::GameDestroyed(std::string eventName)
{
    cvarManager->log("===== GameDestroyed =====");

    // Check if Game Ended, if not, RAGE QUIT or disconnect
    if (isGameStarted == true && isGameEnded == false)
    {
        always.loss++;
        session.loss++;
        stats[currentPlaylist].loss++;
        always_gm[currentPlaylist].loss++;

        if (stats[currentPlaylist].streak > 0)
        {
            always.streak = 0;
            session.streak = 0;
            stats[currentPlaylist].streak = -1;
            always_gm[currentPlaylist].streak = -1;
        }
        else
        {
            always.streak--;
            session.streak--;
            stats[currentPlaylist].streak--;
            always_gm[currentPlaylist].streak--;
        }

        WriteStreak();
        WriteLoss();
        WriteConfig();
    }

    isGameEnded = true;
    isGameStarted = false;
    if (RS_in_file && RS_file_boost)
        WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));

    theme_refresh = 1;
    cvarManager->log("===== !GameDestroyed =====");
}
#pragma endregion

#pragma region StatsMgmt
bool RocketStats::isPrimaryPlayer(PriWrapper PRI)
{
    bool check = !gameWrapper->IsInOnlineGame();
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
    if (!gameWrapper->IsInOnlineGame())
        return;

    StatEventWrapper event = StatEventWrapper(pstats->StatEvent);

    std::string name = event.GetEventName(); // error
    //cvarManager->log("onStatEvent e:" + name + "=" + std::to_string(event.GetPoints()));
}

void RocketStats::onStatTickerMessage(ServerWrapper caller, void* params)
{
    StatTickerParams* pstats = (StatTickerParams*)params;
    if (!gameWrapper->IsInOnlineGame())
        return;

    PriWrapper receiver = PriWrapper(pstats->Receiver);
    PriWrapper victim = PriWrapper(pstats->Victim);
    StatEventWrapper event = StatEventWrapper(pstats->StatEvent);

    std::string name = event.GetEventName();
    //cvarManager->log("onStatTickerMessage receiver:" + std::string(isPrimaryPlayer(receiver) ? "1" : "0") + " victim:" + std::string(isPrimaryPlayer(victim) ? "1" : "0") + " e:" + name + "=" + std::to_string(event.GetPoints()));
    if (name == "Demolish" && receiver && victim)
    {
        bool demo = isPrimaryPlayer(receiver);
        if (demo && currentPlaylist)
        {
            ++session.demo;
            ++stats[currentPlaylist].demo;
            ++always_gm[currentPlaylist].demo;
            theme_refresh = 1;

            if (RS_file_demo)
                WriteInFile("RocketStats_Demolition.txt", std::to_string(0));
        }

        bool death = isPrimaryPlayer(victim);
        if (death && currentPlaylist)
        {
            ++session.death;
            ++stats[currentPlaylist].death;
            ++always_gm[currentPlaylist].death;
            theme_refresh = 1;

            if (RS_file_death)
                WriteInFile("RocketStats_Death.txt", std::to_string(0));
        }
    }
}

void RocketStats::UpdateMMR(UniqueIDWrapper id)
{
    cvarManager->log("===== UpdateMMR =====");
    /*
    if (id.GetIdString() != gameWrapper->GetUniqueID().GetIdString()) {
        cvarManager->log("not the user");
        return;
    }
    cvarManager->log("user match");
    */

    if (currentPlaylist == 0)
    {
        cvarManager->log("Invalid playlist id. Have you just opened the game ?");
        return;
    }

    MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
    float mmr = mmrw.GetPlayerMMR(id, currentPlaylist);
    SkillRank playerRank = mmrw.GetPlayerRank(id, currentPlaylist);

    if (stats[currentPlaylist].isInit)
    {
        float MMRChange = (mmr - stats[currentPlaylist].myMMR);

        always.MMRChange += MMRChange;
        stats[currentPlaylist].MMRChange = MMRChange;
        always_gm[currentPlaylist].MMRChange = MMRChange;

        always.MMRCumulChange += MMRChange;
        for (auto it = playlistName.begin(); it != playlistName.end(); it++)
        {
            stats[it->first].MMRCumulChange += MMRChange;
            always_gm[it->first].MMRCumulChange += MMRChange;
        }
    }
    else
        stats[currentPlaylist].isInit = true;

    always.myMMR = mmr;
    session.myMMR = mmr;
    stats[currentPlaylist].myMMR = mmr;
    always_gm[currentPlaylist].myMMR = mmr;

    MajRank(currentPlaylist, mmrw.IsRanked(currentPlaylist), stats[currentPlaylist].myMMR, playerRank);
    SessionStats();
    WriteMMR();
    WriteMMRChange();
    WriteMMRCumulChange();

    theme_refresh = 1;
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

    for (auto it = playlistName.begin(); it != playlistName.end(); it++)
    {
        tmp.MMRChange += stats[it->first].MMRChange;
        tmp.MMRCumulChange += stats[it->first].MMRChange;
        tmp.win += stats[it->first].win;
        tmp.loss += stats[it->first].loss;
        tmp.demo += stats[it->first].demo;
        tmp.death += stats[it->first].death;
    }

    session.myMMR = stats[currentPlaylist].myMMR;
    session.MMRChange = tmp.MMRChange;
    session.MMRCumulChange = tmp.MMRCumulChange;
    session.win = tmp.win;
    session.loss = tmp.loss;
    session.demo = tmp.demo;
    session.death = tmp.death;
    session.isInit = true;

    always.myMMR = session.myMMR;
    always.MMRChange = session.MMRChange;
    always.isInit = true;

    theme_refresh = 1;
}

void RocketStats::ResetStats()
{
    InitStats();

    WriteConfig();
    ResetFiles();

    InitRank();
    theme_refresh = 1;
}
#pragma endregion

#pragma region BoostMgmt
void RocketStats::OnBoostStart(std::string eventName)
{
    // Check if boost enabled in options
    if (!RS_file_boost || gameWrapper->IsInReplay() || isBoosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        // Check that the boosting car is ours
        if (!bWrap.IsNull() && bWrap.GetbActive() == 1 && !isBoosting)
        {
            isBoosting = true;
            theme_refresh = 1;
            if (RS_in_file)
                WriteInFile("RocketStats_BoostState.txt", std::to_string(1));
        }
    }
}

void RocketStats::OnBoostEnd(std::string eventName)
{
    // Check if boost enabled in options
    if (!RS_file_boost || gameWrapper->IsInReplay() || !isBoosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        // Check that the boosting car is ours
        if (!bWrap.IsNull() && bWrap.GetbActive() == 0 && isBoosting)
        {
            isBoosting = false;
            theme_refresh = 1;
            if (RS_in_file)
                WriteInFile("RocketStats_BoostState.txt", std::to_string(0));
        }
    }
}

// Act as toggle
// void RocketStats::StopBoost() {}
#pragma endregion

#pragma region Rank / Div
void RocketStats::InitRank()
{
    lastGameMode = 0;
    currentGameMode = 0;
    currentMMR = 0;
    currentRank = "norank";
    currentDivision = "nodiv";
    lastRank = "norank";
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

            if (RS_file_div)
                WriteInFile("RocketStats_Div.txt", currentDivision);
        }

        if (RS_file_rank && currentRank != lastRank)
            WriteInFile("RocketStats_Rank.txt", currentRank);
    }
    else
    {
        currentRank = GetPlaylistName(currentGameMode);
        currentDivision = "";

        if (RS_file_rank)
            WriteInFile("RocketStats_Rank.txt", currentRank);
    }

    theme_refresh = 1;
}
#pragma endregion

#pragma region OverlayMgmt
void RocketStats::LoadThemes()
{
    cvarManager->log("===== LoadThemes =====");

    themes = {};
    std::string theme_base = GetPath("RocketStats_themes");
    if (fs::exists(theme_base))
    {
        // List the themes (taking the name of the folder)
        for (const auto& entry : fs::directory_iterator(theme_base))
        {
            std::string theme_path = entry.path().u8string();
            if (entry.is_directory() && fs::exists(theme_path + "/config.json"))
            {
                struct Theme theme;
                theme.name = theme_path.substr(theme_path.find_last_of("/\\") + 1);
                cvarManager->log("Theme: " + theme.name);

                // Puts the "Default" theme in the first position and "Redesign" in the second position
                if (theme.name == "Default" || theme.name == "Redesigned")
                {
                    size_t pos = ((theme.name == "Redesigned" && themes.at(0).name == "Default") ? 1 : 0);
                    themes.insert((themes.begin() + pos), theme);
                }
                else
                    themes.push_back(theme);
            }
        }
    }

    cvarManager->log("===== !LoadThemes =====");
}

bool RocketStats::ChangeTheme(int idx)
{
    cvarManager->log("===== ChangeTheme =====");

    // Stores current theme variables on error
    Theme old = {
        theme_render.name,
        theme_render.author,
        theme_render.version,
        theme_render.date,
        theme_render.font_size,
        theme_render.font_name
    };

    try
    {
        // If the index of the theme does not fit in the list of themes, we do nothing
        if (themes.size() <= idx)
            return true;

        Theme& theme = themes.at(idx);

        // Read the JSON file including the settings of the chosen theme
        theme_config = json::parse(ReadFile("RocketStats_themes/" + theme.name + "/config.json"));
        cvarManager->log(nlohmann::to_string(theme_config));

        if (theme_config.is_object())
        {
            theme_render.name = theme.name;

            if (theme_config.contains("author") && theme_config["author"].size())
                theme_render.author = theme_config["author"];

            if (theme_config.contains("version"))
            {
                std::string version = theme_config["version"];
                if (version.size() >= 2 && version[0] == 'v')
                    theme_render.version = version;
            }

            if (theme_config.contains("date"))
            {
                std::string date = theme_config["date"];
                if (date.size() == 10 && date[2] == '/' && date[5] == '/')
                    theme_render.date = date;
            }

            // Add theme font to system
            theme_render.font_name = "";
            if (theme_config.contains("font") && theme_config["font"].is_array() && theme_config["font"].size() == 2)
            {
                if (theme_config["font"][0].is_string() && theme_config["font"][1].is_number_unsigned())
                {
                    int font_size = theme_config["font"][1];
                    std::string font_file = theme_config["font"][0];

                    std::string font_prefix = "rs_";
                    std::string font_path = ("RocketStats_themes/" + theme_render.name + "/fonts/" + font_file);
                    std::string font_dest = (rs_fonts + "/" + font_path);

                    if (font_file.size() && font_size > 0 && ExistsPath(font_path))
                    {
                        theme_render.font_size = font_size;
                        theme_render.font_name = font_prefix + (font_file.substr(0, font_file.find_last_of('.'))) + "_" + std::to_string(font_size);

                        GuiManagerWrapper gui = gameWrapper->GetGUIManager();
                        gui.LoadFont(theme_render.font_name, font_dest, font_size);
                        cvarManager->log("Load font: " + theme_render.font_name);
                    }
                }
            }

            cvarManager->log("Theme changed: " + theme.name + " (old: " + theme_render.name + ")");
            RS_theme = idx;
            theme_refresh = 2;
        }
        else
            cvarManager->log("Theme config: " + theme.name + " bad JSON");
    }
    catch (json::parse_error& e)
    {
        cvarManager->log("Theme config: " + std::to_string(idx) + " bad JSON -> " + std::string(e.what()));

        // Returns the variables as they were before the process
        theme_render.name = old.name;
        theme_render.author = old.author;
        theme_render.version = old.version;
        theme_render.date = old.date;
        theme_render.font_size = old.font_size;
        theme_render.font_name = old.font_name;
    }

    cvarManager->log("===== !ChangeTheme =====");
    return (RS_theme == idx);
}

void RocketStats::SetTheme(std::string name)
{
    // Search the index of a theme with its name (changes current theme if found)
    for (int i = 0; i < themes.size(); ++i)
    {
        if (themes.at(i).name == name)
        {
            RS_theme = i;
            break;
        }
    }
}

void RocketStats::RefreshTheme(std::string old, CVarWrapper now)
{
    theme_refresh = 1;
}

struct Element RocketStats::CalculateElement(json& element, Options& options, bool& check)
{
    check = false;
    struct Element calculated;

    if (!element.contains("visible") || element["visible"])
    {
        try
        {
            Vector2D element_2d;
            std::vector<ImVec2> positions;

            if (element.contains("name") && element["name"].size())
                calculated.name = element["name"];

            if (element.contains("x"))
                element_2d.x = int(float(element["x"].is_string() ? Utils::EvaluateExpression(element["x"], options.width) : int(element["x"])) * options.scale);

            if (element.contains("y"))
                element_2d.y = int(float(element["y"].is_string() ? Utils::EvaluateExpression(element["y"], options.height) : int(element["y"])) * options.scale);

            if (element.contains("width"))
                element_2d.width = int(float(element["width"].is_string() ? Utils::EvaluateExpression(element["width"], options.width) : int(element["width"])) * options.scale);

            if (element.contains("height"))
                element_2d.height = int(float(element["height"].is_string() ? Utils::EvaluateExpression(element["height"], options.height) : int(element["height"])) * options.scale);

            ImVec2 element_pos = { float(options.x + element_2d.x), float(options.y + element_2d.y) };
            ImVec2 element_size = { float(element_2d.width), float(element_2d.height) };
            const float element_scale = (element.contains("scale") ? float(element["scale"]) : 1.f);
            const float element_rotate = (element.contains("rotate") ? float(element["rotate"]) : 0.f);
            const float element_opacity = (options.opacity * (element.contains("opacity") ? float(element["opacity"]) : 1.f));

            calculated.scale = (element_scale * options.scale);

            calculated.color.enable = true;
            if (element.contains("color") && element["color"].is_array())
                calculated.color = { true, Utils::GetImColor(element["color"], element_opacity) };

            if (element.contains("fill") && element["fill"].is_array())
                calculated.fill = { true, Utils::GetImColor(element["fill"], element_opacity) };

            if (element.contains("stroke") && element["stroke"].is_array())
                calculated.stroke = { true, Utils::GetImColor(element["stroke"], element_opacity) };

            if (element["type"] == "text" && element["value"].size())
            {
                calculated.scale *= 2.0f;
                calculated.value = element["value"];

                Utils::ReplaceVars(calculated.value, theme_vars, [this, &element, &options, &calculated, &element_opacity](const std::string &key, std::string &value) {
                    if (element.contains("sign") && element["sign"] == key && value != hide_value)
                    {
                        bool positive = (value.at(0) != '-');
                        if (positive)
                            value = ("+" + value);
                    }

                    if (element.contains("chameleon") && element["chameleon"] == key)
                    {
                        bool positive = (value.at(0) != '-');
                        calculated.color.color = Utils::GetImColor({ float(positive ? 30 : 224), float(positive ? 224 : 24), float(positive ? 24 : 24) }, element_opacity);
                    }
                });

                if (!calculated.value.size())
                    return calculated;

                ImVec2 string_size;
                ImGui::SetWindowFontScale(1.f);
                if (theme_render.font_name.size())
                {
                    calculated.scale *= theme_render.font_size;

                    GuiManagerWrapper gui = gameWrapper->GetGUIManager();
                    string_size = gui.GetFont(theme_render.font_name)->CalcTextSizeA(calculated.scale, FLT_MAX, 0.f, calculated.value.c_str());
                }
                else
                {
                    ImGui::SetWindowFontScale(calculated.scale);
                    string_size = ImGui::CalcTextSize(calculated.value.c_str());
                }

                if (element.contains("align") && element["align"].is_string())
                {
                    if (element["align"] == "right")
                        element_pos.x -= string_size.x;
                    else if (element["align"] == "center")
                        element_pos.x -= std::round(string_size.x / 2.0f);
                }

                if (element.contains("valign") && element["valign"].is_string())
                {
                    if (element["valign"] == "bottom")
                        element_pos.y -= string_size.y;
                    else if (element["valign"] == "middle")
                        element_pos.y -= std::round(string_size.y / 2.0f);
                }
            }
            else if (element["type"] == "line")
            {
                element_pos.x = float(options.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(element["x1"], options.width) : int(element["x1"])) * options.scale);
                element_pos.y = float(options.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(element["y1"], options.height) : int(element["y1"])) * options.scale);
                const float element_width = (element.contains("scale") ? (float)element["scale"] : 1);

                element_size.x = element_width;
                calculated.scale = (element_width * options.scale);

                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(element["x2"], options.width) : int(element["x2"])) * options.scale),
                    float(options.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(element["y2"], options.height) : int(element["y2"])) * options.scale)
                });
            }
            else if (element["type"] == "rectangle")
            {
                element_size.x = (element.contains("rounding") ? float(element["rounding"]) : 0.f);

                positions.push_back(ImVec2{
                    element_pos.x + element_2d.width,
                    element_pos.y + element_2d.height
                });
            }
            else if (element["type"] == "triangle")
            {
                element_pos.x = float(options.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(element["x1"], options.width) : int(element["x1"])) * options.scale);
                element_pos.y = float(options.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(element["y1"], options.height) : int(element["y1"])) * options.scale);

                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(element["x2"], options.width) : int(element["x2"])) * options.scale),
                    float(options.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(element["y2"], options.height) : int(element["y2"])) * options.scale)
                });
                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x3"].is_string() ? Utils::EvaluateExpression(element["x3"], options.width) : int(element["x3"])) * options.scale),
                    float(options.y) + (float(element["y3"].is_string() ? Utils::EvaluateExpression(element["y3"], options.height) : int(element["y3"])) * options.scale)
                });
            }
            else if (element["type"] == "circle")
            {
                element_size.x = (float(element["radius"].is_string() ? Utils::EvaluateExpression(element["radius"], options.width) : int(element["radius"])) * options.scale);
                element_size.y = float(element.contains("segments") ? int(element["segments"]) : 0);
            }
            else if (element["type"] == "image")
            {
                calculated.scale *= 0.5f;
                calculated.value = element["file"];

                if (!element.contains("color"))
                    calculated.color = { true, Utils::GetImColor({ 255.f, 255.f, 255.f }, element_opacity) };

                if (calculated.value == "{{Rank}}")
                {
                    // Returns the image of the current rank
                    theme_images[calculated.value] = rank[(!RS_hide_rank && currentTier < rank_nb) ? currentTier : 0].image;
                }
                else if (!theme_images[calculated.value])
                {
                    // Get the requested image
                    element_size = { 0, 0 };
                    std::string image_path = "RocketStats_themes/" + themes.at(RS_theme).name + "/images/" + calculated.value;

                    cvarManager->log("load image: " + image_path);
                    theme_images[calculated.value] = LoadImg(image_path);
                }

                // Calculate the image only if it is loaded (request for recalculation later if needed)
                if (theme_images[calculated.value]->IsLoadedForImGui())
                {
                    Vector2F image_size = theme_images[calculated.value]->GetSizeF();
                    element_size = {
                        (image_size.X * calculated.scale),
                        (image_size.Y * calculated.scale)
                    };

                    if (element.contains("align") && element["align"].is_string())
                    {
                        if (element["align"] == "right")
                            element_pos.x -= element_size.x;
                        else if (element["align"] == "center")
                            element_pos.x -= (element_size.x / 2.0f);
                    }

                    if (element.contains("valign") && element["valign"].is_string())
                    {
                        if (element["valign"] == "bottom")
                            element_pos.y -= element_size.y;
                        else if (element["valign"] == "middle")
                            element_pos.y -= (element_size.y / 2.0f);
                    }

                    element_size.x += element_pos.x;
                    element_size.y += element_pos.y;
                }
            }

            positions.emplace(positions.begin(), element_pos);

            calculated.type = element["type"];
            calculated.positions = positions;
            calculated.size = element_size;
            if (element_rotate)
            {
                calculated.rotate_enable = true;
                calculated.rotate = ((90.f - element_rotate) * (float(M_PI) / 180.f)); // Convert degrees to radians
            }

            check = true;
        }
        catch (const std::exception& e)
        {
            cvarManager->log("CalculateElement error: " + std::string(e.what()));
        }
    }

    return calculated;
}

void RocketStats::RenderElement(ImDrawList* drawlist, Element& element)
{
    try
    {
        if (element.rotate_enable)
            ImRotateStart(drawlist); // Saves the position of the vertex array for future rotation

        if (element.fill.enable)
        {
            if (element.type == "triangle")
                drawlist->AddTriangleFilled(element.positions.at(0), element.positions.at(1), element.positions.at(2), element.fill.color);
            else if (element.type == "rectangle")
                drawlist->AddRectFilled(element.positions.at(0), element.positions.at(1), element.fill.color, element.size.x, ImDrawCornerFlags_All);
            else if (element.type == "circle")
                drawlist->AddCircleFilled(element.positions.at(0), element.size.x, element.fill.color, int(element.size.y ? element.size.y : 12));
        }

        if (element.stroke.enable)
        {
            if (element.type == "triangle")
                drawlist->AddTriangle(element.positions.at(0), element.positions.at(1), element.positions.at(2), element.stroke.color, element.scale);
            else if (element.type == "rectangle")
                drawlist->AddRect(element.positions.at(0), element.positions.at(1), element.stroke.color, element.size.x, ImDrawCornerFlags_All, element.scale);
            else if (element.type == "circle")
                drawlist->AddCircle(element.positions.at(0), element.size.x, element.stroke.color, int(element.size.y ? element.size.y : 12), element.scale);
        }

        if (element.type == "image")
        {
            std::shared_ptr<ImageWrapper> image = theme_images[element.value];
            if (image->IsLoadedForImGui())
            {
                if (element.size.x && element.size.y)
                    drawlist->AddImage(image->GetImGuiTex(), element.positions.at(0), element.size, ImVec2{ 0, 0 }, ImVec2{ 1, 1 }, element.color.color);
                else
                    theme_refresh = 1;
            }
        }
        else if (element.type == "text")
        {
            ImGui::SetWindowFontScale(1);
            if (theme_render.font_name.size())
            {
                GuiManagerWrapper gui = gameWrapper->GetGUIManager();
                ImFont* font = gui.GetFont(theme_render.font_name);

                // Display text if font is loaded
                if (font && font->IsLoaded())
                    drawlist->AddText(font, element.scale, element.positions.at(0), element.color.color, element.value.c_str());
            }
            else
            {
                // Displays text without font
                ImGui::SetWindowFontScale(element.scale);
                drawlist->AddText(element.positions.at(0), element.color.color, element.value.c_str());
            }
        }
        else if (element.type == "line")
            drawlist->AddLine(element.positions.at(0), element.positions.at(1), element.color.color, element.size.x);

        if (element.rotate_enable)
            ImRotateEnd(element.rotate); // Applies the rotation to the vertices of the current element
    }
    catch (const std::exception&) {}
}
#pragma endregion

#pragma region File I / O
std::string RocketStats::GetPath(std::string _path, bool root)
{
    std::string _return = gameWrapper->GetBakkesModPath().string() + "/";

    if (root)
        _return += _path;
    else
        _return += rs_path + "/" + _path;

    return _return;
}

bool RocketStats::ExistsPath(std::string _filename, bool root)
{
    return fs::exists(GetPath(_filename, root));
}

bool RocketStats::RemoveFile(std::string _filename, bool root)
{
    if (!ExistsPath(_filename, root))
        return true;

    try
    {
        return fs::remove(GetPath(_filename, root));
    }
    catch (const std::exception&) {}

    return false;
}

std::string RocketStats::ReadFile(std::string _filename, bool root)
{
    std::string _value = "";
    std::string _path = GetPath(_filename, root);
    if (fs::exists(_path) && fs::is_regular_file(_path) && (fs::status(_path).permissions() & fs::perms::owner_read) == fs::perms::owner_read)
    {
        std::ifstream stream(_path, std::ios::in | std::ios::binary);

        if (stream.is_open())
        {
            std::ostringstream os;
            os << stream.rdbuf();
            _value = os.str();
            stream.close();
        }
        else
            cvarManager->log("Can't read this file: " + _filename);
    }
    else
        cvarManager->log("Bad path: " + _filename);

    return _value;
}

void RocketStats::WriteInFile(std::string _filename, std::string _value, bool root)
{
    std::string _path = GetPath(_filename, root);
    if (!fs::exists(_path) || fs::is_regular_file(_path))
    {
        std::ofstream stream(_path, std::ios::out | std::ios::trunc);

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
}

void RocketStats::ResetFiles()
{
    WriteInFile("RocketStats_GameMode.txt", "");
    WriteInFile("RocketStats_Rank.txt", "");
    WriteInFile("RocketStats_Div.txt", "");
    WriteInFile("RocketStats_MMR.txt", std::to_string(0));
    WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));
    WriteInFile("RocketStats_MMRCumulChange.txt", std::to_string(0));
    WriteInFile("RocketStats_Win.txt", std::to_string(0));
    WriteInFile("RocketStats_Loss.txt", std::to_string(0));
    WriteInFile("RocketStats_Streak.txt", std::to_string(0));
    WriteInFile("RocketStats_Demolition.txt", std::to_string(0));
    WriteInFile("RocketStats_Death.txt", std::to_string(0));
    WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));
}

bool RocketStats::ReadConfig()
{
    cvarManager->log("===== ReadConfig =====");

    std::string file = "data/rocketstats.json";
    bool exists = ExistsPath(file, true);
    if (exists)
    {
        try
        {
            // Read the plugin settings JSON file
            json config = json::parse(ReadFile(file, true));
            cvarManager->log(nlohmann::to_string(config));

            if (config.is_object())
            {
                if (config["settings"].is_object())
                {
                    if (config["settings"]["mode"].is_number_unsigned())
                        RS_mode = config["settings"]["mode"];

                    if (config["settings"]["theme"].is_string())
                        SetTheme(config["settings"]["theme"]);

                    if (config["settings"]["position"].is_array() && config["settings"]["position"].size() == 2)
                    {
                        if (config["settings"]["position"][0].is_number_unsigned() || config["settings"]["position"][0].is_number_integer() || config["settings"]["position"][0].is_number_float())
                            RS_x = config["settings"]["position"][0];

                        if (config["settings"]["position"][1].is_number_unsigned() || config["settings"]["position"][1].is_number_integer() || config["settings"]["position"][1].is_number_float())
                            RS_y = config["settings"]["position"][1];
                    }
                    if (config["settings"]["scale"].is_number_unsigned() || config["settings"]["scale"].is_number_integer() || config["settings"]["scale"].is_number_float())
                        RS_scale = config["settings"]["scale"];
                    if (config["settings"]["rotate"].is_number_unsigned() || config["settings"]["rotate"].is_number_integer() || config["settings"]["rotate"].is_number_float())
                        RS_rotate = config["settings"]["rotate"];
                    if (config["settings"]["opacity"].is_number_unsigned() || config["settings"]["opacity"].is_number_integer() || config["settings"]["opacity"].is_number_float())
                        RS_opacity = config["settings"]["opacity"];

                    if (config["settings"]["overlay"].is_boolean())
                        RS_disp_overlay = config["settings"]["overlay"];

                    if (config["settings"]["obs"].is_boolean())
                        RS_disp_obs = config["settings"]["obs"];
                    if (config["settings"]["inmenu"].is_boolean())
                        RS_enable_inmenu = config["settings"]["inmenu"];
                    if (config["settings"]["ingame"].is_number_unsigned())
                        RS_enable_ingame = config["settings"]["ingame"];
                    if (config["settings"]["float"].is_boolean())
                        RS_enable_float = config["settings"]["float"];
                    if (config["settings"]["onchange_scale"].is_boolean())
                        RS_onchange_scale = config["settings"]["onchange_scale"];
                    if (config["settings"]["onchange_rotate"].is_boolean())
                        RS_onchange_rotate = config["settings"]["onchange_rotate"];
                    if (config["settings"]["onchange_opacity"].is_boolean())
                        RS_onchange_opacity = config["settings"]["onchange_opacity"];
                    if (config["settings"]["onchange_position"].is_boolean())
                        RS_onchange_position = config["settings"]["onchange_position"];

                    if (config["settings"]["files"].is_object())
                    {
                        if (config["settings"]["files"]["on"].is_boolean())
                            RS_in_file = config["settings"]["files"]["on"];
                        if (config["settings"]["files"]["gm"].is_boolean())
                            RS_hide_gm = config["settings"]["files"]["gm"];
                        if (config["settings"]["files"]["rank"].is_boolean())
                            RS_hide_rank = config["settings"]["files"]["rank"];
                        if (config["settings"]["files"]["div"].is_boolean())
                            RS_hide_div = config["settings"]["files"]["div"];
                        if (config["settings"]["files"]["mmr"].is_boolean())
                            RS_hide_mmr = config["settings"]["files"]["mmr"];
                        if (config["settings"]["files"]["mmrc"].is_boolean())
                            RS_hide_mmrc = config["settings"]["files"]["mmrc"];
                        if (config["settings"]["files"]["mmrcc"].is_boolean())
                            RS_hide_mmrcc = config["settings"]["files"]["mmrcc"];
                        if (config["settings"]["files"]["win"].is_boolean())
                            RS_hide_win = config["settings"]["files"]["win"];
                        if (config["settings"]["files"]["loss"].is_boolean())
                            RS_hide_loss = config["settings"]["files"]["loss"];
                        if (config["settings"]["files"]["streak"].is_boolean())
                            RS_hide_streak = config["settings"]["files"]["streak"];
                        if (config["settings"]["files"]["demo"].is_boolean())
                            RS_hide_demo = config["settings"]["files"]["demo"];
                        if (config["settings"]["files"]["death"].is_boolean())
                            RS_hide_death = config["settings"]["files"]["death"];
                        if (config["settings"]["files"]["boost"].is_boolean())
                            RS_file_boost = config["settings"]["files"]["boost"];
                    }

                    if (config["settings"]["hides"].is_object())
                    {
                        if (config["settings"]["hides"]["gm"].is_boolean())
                            RS_hide_gm = config["settings"]["hides"]["gm"];
                        if (config["settings"]["hides"]["rank"].is_boolean())
                            RS_hide_rank = config["settings"]["hides"]["rank"];
                        if (config["settings"]["hides"]["div"].is_boolean())
                            RS_hide_div = config["settings"]["hides"]["div"];
                        if (config["settings"]["hides"]["mmr"].is_boolean())
                            RS_hide_mmr = config["settings"]["hides"]["mmr"];
                        if (config["settings"]["hides"]["mmrc"].is_boolean())
                            RS_hide_mmrc = config["settings"]["hides"]["mmrc"];
                        if (config["settings"]["hides"]["mmrcc"].is_boolean())
                            RS_hide_mmrcc = config["settings"]["hides"]["mmrcc"];
                        if (config["settings"]["hides"]["win"].is_boolean())
                            RS_hide_win = config["settings"]["hides"]["win"];
                        if (config["settings"]["hides"]["loss"].is_boolean())
                            RS_hide_loss = config["settings"]["hides"]["loss"];
                        if (config["settings"]["hides"]["streak"].is_boolean())
                            RS_hide_streak = config["settings"]["hides"]["streak"];
                        if (config["settings"]["hides"]["demo"].is_boolean())
                            RS_hide_demo = config["settings"]["hides"]["demo"];
                        if (config["settings"]["hides"]["death"].is_boolean())
                            RS_hide_death = config["settings"]["hides"]["death"];

                        cvarManager->log("Config: hides loaded");
                    }
                    if (config["settings"]["replace_mmr"].is_boolean())
                        RS_replace_mmr = config["settings"]["replace_mmr"];

                    cvarManager->log("Config: settings loaded");
                }

                if (config["always"].is_object())
                {
                    if (config["always"]["MMRCumulChange"].is_number_unsigned() || config["always"]["MMRCumulChange"].is_number_integer() || config["always"]["MMRCumulChange"].is_number_float())
                        always.MMRCumulChange = float(config["always"]["MMRCumulChange"]);

                    if (config["always"]["Win"].is_number_unsigned())
                        always.win = int(config["always"]["Win"]);

                    if (config["always"]["Loss"].is_number_unsigned())
                        always.loss = int(config["always"]["Loss"]);

                    if (config["always"]["Streak"].is_number_unsigned() || config["always"]["Streak"].is_number_integer())
                        always.streak = int(config["always"]["Streak"]);

                    if (config["always"]["Demo"].is_number_unsigned())
                        always.demo = int(config["always"]["Demo"]);

                    if (config["always"]["Death"].is_number_unsigned())
                        always.death = int(config["always"]["Death"]);

                    cvarManager->log("Config: stats loaded");
                    always.isInit = true;
                }

                if (config["always_gm_idx"].is_number_unsigned() && int(config["always_gm_idx"]) < playlistName.size())
                    currentPlaylist = config["always_gm_idx"];

                if (config["always_gm"].is_array())
                {
                    for (int i = 0; i < config["always_gm"].size() && i < playlistName.size(); ++i)
                    {
                        if (config["always_gm"][i].is_object())
                        {
                            if (config["always_gm"][i]["MMRCumulChange"].is_number_unsigned() || config["always_gm"][i]["MMRCumulChange"].is_number_integer() || config["always_gm"][i]["MMRCumulChange"].is_number_float())
                                always_gm[i].MMRCumulChange = float(config["always_gm"][i]["MMRCumulChange"]);

                            if (config["always_gm"][i]["Win"].is_number_unsigned())
                                always_gm[i].win = int(config["always_gm"][i]["Win"]);

                            if (config["always_gm"][i]["Loss"].is_number_unsigned())
                                always_gm[i].loss = int(config["always_gm"][i]["Loss"]);

                            if (config["always_gm"][i]["Streak"].is_number_unsigned() || config["always_gm"][i]["Streak"].is_number_integer())
                                always_gm[i].streak = int(config["always_gm"][i]["Streak"]);

                            if (config["always_gm"][i]["Demo"].is_number_unsigned())
                                always_gm[i].demo = int(config["always_gm"][i]["Demo"]);

                            if (config["always_gm"][i]["Death"].is_number_unsigned())
                                always_gm[i].death = int(config["always_gm"][i]["Death"]);

                            always_gm[i].isInit = true;
                        }
                    }

                    cvarManager->log("Config: stats loaded");
                }

                theme_refresh = 1;
            }
            else
                cvarManager->log("Config: bad JSON");
        }
        catch (json::parse_error& e)
        {
            cvarManager->log("Config: bad JSON -> " + std::string(e.what()));
        }
    }

    cvarManager->log("===== !ReadConfig =====");
    return exists;
}

void RocketStats::WriteConfig()
{
    cvarManager->log("===== WriteConfig =====");

    json tmp = {};

    tmp["settings"] = {};
    tmp["settings"]["mode"] = RS_mode;
    tmp["settings"]["theme"] = theme_render.name;
    tmp["settings"]["position"] = { RS_x, RS_y };
    tmp["settings"]["scale"] = RS_scale;
    tmp["settings"]["rotate"] = RS_rotate;
    tmp["settings"]["opacity"] = RS_opacity;
    tmp["settings"]["overlay"] = RS_disp_overlay;
    tmp["settings"]["obs"] = RS_disp_obs;
    tmp["settings"]["inmeny"] = RS_enable_inmenu;
    tmp["settings"]["ingame"] = RS_enable_ingame;
    tmp["settings"]["float"] = RS_enable_float;
    tmp["settings"]["onchange_scale"] = RS_onchange_scale;
    tmp["settings"]["onchange_rotate"] = RS_onchange_rotate;
    tmp["settings"]["onchange_opacity"] = RS_onchange_opacity;
    tmp["settings"]["onchange_position"] = RS_onchange_position;

    tmp["settings"]["files"] = {};
    tmp["settings"]["files"]["on"] = RS_in_file;
    tmp["settings"]["files"]["gm"] = RS_file_gm;
    tmp["settings"]["files"]["rank"] = RS_file_rank;
    tmp["settings"]["files"]["div"] = RS_file_div;
    tmp["settings"]["files"]["mmr"] = RS_file_mmr;
    tmp["settings"]["files"]["mmr"] = RS_file_mmr;
    tmp["settings"]["files"]["mmrc"] = RS_file_mmrc;
    tmp["settings"]["files"]["mmrcc"] = RS_file_mmrcc;
    tmp["settings"]["files"]["win"] = RS_file_win;
    tmp["settings"]["files"]["loss"] = RS_file_loss;
    tmp["settings"]["files"]["streak"] = RS_file_streak;
    tmp["settings"]["files"]["demo"] = RS_file_demo;
    tmp["settings"]["files"]["death"] = RS_file_death;
    tmp["settings"]["files"]["boost"] = RS_file_boost;

    tmp["settings"]["hides"] = {};
    tmp["settings"]["hides"]["gm"] = RS_hide_gm;
    tmp["settings"]["hides"]["rank"] = RS_hide_rank;
    tmp["settings"]["hides"]["div"] = RS_hide_div;
    tmp["settings"]["hides"]["mmr"] = RS_hide_mmr;
    tmp["settings"]["hides"]["mmrc"] = RS_hide_mmrc;
    tmp["settings"]["hides"]["mmrcc"] = RS_hide_mmrcc;
    tmp["settings"]["hides"]["win"] = RS_hide_win;
    tmp["settings"]["hides"]["loss"] = RS_hide_loss;
    tmp["settings"]["hides"]["streak"] = RS_hide_streak;
    tmp["settings"]["hides"]["demo"] = RS_hide_demo;
    tmp["settings"]["hides"]["death"] = RS_hide_death;
    tmp["settings"]["replace_mmr"] = RS_replace_mmr;

    tmp["always"] = {};
    tmp["always"]["MMRCumulChange"] = always.MMRCumulChange;
    tmp["always"]["Win"] = always.win;
    tmp["always"]["Loss"] = always.loss;
    tmp["always"]["Streak"] = always.streak;
    tmp["always"]["Demo"] = always.demo;
    tmp["always"]["Death"] = always.death;

    tmp["always_gm_idx"] = currentPlaylist;
    tmp["always_gm"] = {};
    for (int i = 0; i < always_gm.size(); ++i)
    {
        tmp["always_gm"][i] = {};
        tmp["always_gm"][i]["MMRCumulChange"] = always_gm[i].MMRCumulChange;
        tmp["always_gm"][i]["Win"] = always_gm[i].win;
        tmp["always_gm"][i]["Loss"] = always_gm[i].loss;
        tmp["always_gm"][i]["Streak"] = always_gm[i].streak;
        tmp["always_gm"][i]["Demo"] = always_gm[i].demo;
        tmp["always_gm"][i]["Death"] = always_gm[i].death;
    }

    WriteInFile("data/rocketstats.json", nlohmann::to_string(tmp), true); // Save plugin settings in JSON format

    cvarManager->log("===== !WriteConfig =====");
}

void RocketStats::WriteGameMode()
{
    if (RS_in_file && RS_file_gm)
        WriteInFile("RocketStats_GameMode.txt", GetPlaylistName(currentPlaylist));
}

void RocketStats::WriteRank()
{
    if (RS_in_file && RS_file_rank)
        WriteInFile("RocketStats_Div.txt", currentRank);
}

void RocketStats::WriteDiv()
{
    if (RS_in_file && RS_file_div)
        WriteInFile("RocketStats_Div.txt", currentDivision);
}

void RocketStats::WriteMMR()
{
    if (!RS_in_file || !RS_file_mmr)
        return;

    std::string tmp = Utils::FloatFixer(stats[currentPlaylist].myMMR, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMR.txt", tmp);
}

void RocketStats::WriteMMRChange()
{
    if (!RS_in_file || !RS_file_mmrc)
        return;

    Stats current = GetStats();
    std::string tmp = Utils::FloatFixer(current.MMRChange, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRChange.txt", (((current.MMRChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteMMRCumulChange()
{
    if (!RS_in_file || !RS_file_mmrcc)
        return;

    Stats current = GetStats();
    std::string tmp = Utils::FloatFixer(current.MMRCumulChange, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRCumulChange.txt", (((current.MMRCumulChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteWin()
{
    if (RS_in_file && RS_file_win)
        WriteInFile("RocketStats_Win.txt", std::to_string(GetStats().win));
}

void RocketStats::WriteLoss()
{
    if (RS_in_file && RS_file_loss)
        WriteInFile("RocketStats_Loss.txt", std::to_string(GetStats().loss));
}

void RocketStats::WriteStreak()
{
    if (!RS_in_file || !RS_file_streak)
        return;

    Stats current = GetStats();
    std::string tmp = std::to_string(current.streak);

    WriteInFile("RocketStats_Streak.txt", (((current.streak > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteDemo()
{
    if (RS_in_file && RS_file_demo)
        WriteInFile("RocketStats_Demo.txt", std::to_string(GetStats().demo));
}

void RocketStats::WriteDeath()
{
    if (RS_in_file && RS_file_death)
        WriteInFile("RocketStats_Death.txt", std::to_string(GetStats().death));
}

void RocketStats::WriteBoost()
{
    if (RS_in_file && RS_file_gm)
        WriteInFile("RocketStats_BoostState.txt", std::to_string(gameWrapper->IsInGame() ? 0 : -1));
}
#pragma endregion

#pragma region PluginWindow
void RocketStats::Render()
{
    isInGame = (gameWrapper->IsInGame() || gameWrapper->IsInOnlineGame());

    RenderIcon();
    RenderOverlay();

    if (isSettingsOpen_)
        RenderSettings();

    // Capture of the escape key, to prevent the plugin from disappearing
    int idx = ImGui::GetKeyIndex(ImGuiKey_Escape);
    if (ImGui::IsKeyDown(idx))
        escape_state = true;
    else if (ImGui::IsKeyReleased(idx))
        escape_state = false;
}

void RocketStats::RenderIcon()
{
    float margin = 20.f;
    float icon_size = 35.f;
    LPPOINT mouse_pos = new tagPOINT;
    bool mouse_click = GetAsyncKeyState(VK_LBUTTON);
    ImVec2 screen_size = ImGui::GetIO().DisplaySize;
    ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

    GetCursorPos(mouse_pos);
    ImVec2 icon_pos = { -10.f, (screen_size.y * 0.459f) };

    // Displays the button allowing the display and the hiding of the menu
    bool hover = (mouse_pos->x > (icon_pos.x - icon_size - margin) && mouse_pos->x < (icon_pos.x + icon_size + margin));
    hover = (hover && (mouse_pos->y > (icon_pos.y - icon_size - margin) && mouse_pos->y < (icon_pos.y + icon_size + margin)));
    if (!isInGame || hover)
    {
        drawlist->AddCircle({ icon_pos.x, icon_pos.y }, icon_size, ImColor{ 0.45f, 0.72f, 1.f, (hover ? 0.8f : 0.4f) }, 25, 4.f);
        drawlist->AddCircleFilled({ icon_pos.x, icon_pos.y }, icon_size, ImColor{ 0.04f, 0.52f, 0.89f, (hover ? 0.6f : 0.3f) }, 25);

        // When hovering over the button area
        if (hover)
        {
            // When clicking in the button area
            if (mouse_click)
            {
                // Send the event only once to the click (not to each image)
                if (!mouse_state)
                {
                    mouse_state = true;
                    ToggleSettings("MouseEvent");
                }
            }
            else
                mouse_state = false;
        }
    }
}

void RocketStats::RenderOverlay()
{
    bool show_overlay = ((RS_enable_ingame && isInGame) || (RS_enable_inmenu && !isInGame));
    if (!RS_disp_overlay || !show_overlay)
        return;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin(menuTitle_.c_str(), (bool*)1, (ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoFocusOnAppearing));

    try
    {
        // Calculation each element of the theme (only during a modification)
        if (theme_refresh || theme_render.name == "" || (themes.size() > RS_theme && theme_render.name != themes.at(RS_theme).name))
        {
            Stats current = GetStats();
            ImVec2 screen_size = ImGui::GetIO().DisplaySize;

            // Refresh all images
            if (theme_refresh == 2)
            {
                theme_images.clear();
                cvarManager->log("refresh all images");
            }

            // Reset the menu variables if you change the theme
            if (theme_prev.size() && theme_prev != theme_render.name)
            {
                if (RS_onchange_scale)
                    RS_scale = 1.f;

                if (RS_onchange_rotate)
                    RS_rotate = 0.f;

                if (RS_onchange_opacity)
                    RS_opacity = 1.f;

                if (RS_onchange_position && theme_config.contains("x") && theme_config.contains("y"))
                {
                    RS_x = theme_config["x"];
                    RS_y = theme_config["y"];
                }
            }
            theme_prev = theme_render.name;

            // Checks if there is a rotation to apply and converts degrees to radians
            RS_rotate_enabled = (theme_config.contains("rotate") && (RS_rotate + float(theme_config["rotate"])));
            if (RS_rotate)
            {
                RS_rotate_enabled = true;
                RS_crotate = ((90.f - RS_rotate) * (float(M_PI) / 180.f));
            }
            else if (RS_rotate_enabled)
                RS_crotate = ((90.f - RS_rotate + float(theme_config["rotate"])) * (float(M_PI) / 180.f));

            // Different global options used when calculating elements
            std::vector<struct Element> elements;
            Options options = {
                int(RS_x * screen_size.x),
                int(RS_y * screen_size.y),
                (theme_config.contains("width") ? int(theme_config["width"]) : 0),
                (theme_config.contains("height") ? int(theme_config["height"]) : 0),
                (RS_scale * (theme_config.contains("scale") ? float(theme_config["scale"]) : 1.f)),
                (rs_launch * RS_opacity * (theme_config.contains("opacity") ? float(theme_config["opacity"]) : 1.f))
            };

            // Creation of the different variables used in Text elements
            const size_t floating_length = (RS_enable_float ? 2 : 0);

            theme_vars["GameMode"] = (RS_hide_gm ? hide_value : GetPlaylistName(currentPlaylist));
            theme_vars["Rank"] = (RS_hide_rank ? hide_value : currentRank);
            theme_vars["Div"] = (RS_hide_div ? hide_value : currentDivision);
            theme_vars["MMR"] = (RS_hide_mmr ? hide_value : Utils::FloatFixer(current.myMMR, floating_length)); // Utils::PointFixer(current.myMMR, 6, floating_length)
            theme_vars["MMRChange"] = (RS_hide_mmrc ? hide_value : Utils::FloatFixer(current.MMRChange, floating_length)); // Utils::PointFixer(current.MMRChange, 6, floating_length)
            theme_vars["MMRCumulChange"] = (RS_hide_mmrcc ? hide_value : Utils::FloatFixer(current.MMRCumulChange, floating_length)); // Utils::PointFixer(current.MMRCumulChange, 6, floating_length)
            theme_vars["Win"] = (RS_hide_win ? hide_value : std::to_string(current.win));
            theme_vars["Loss"] = (RS_hide_loss ? hide_value : std::to_string(current.loss));
            theme_vars["Streak"] = (RS_hide_streak ? hide_value : std::to_string(current.streak));
            theme_vars["Demolition"] = (RS_hide_demo ? hide_value : std::to_string(current.demo));
            theme_vars["Death"] = (RS_hide_death ? hide_value : std::to_string(current.death));

            Utils::ReplaceAll(theme_vars["Rank"], "_", " ");

            // Replace MMR with MMRChange
            if (RS_replace_mmr)
                theme_vars["MMR"] = theme_vars["MMRChange"];

            // Calculation of each element composing the theme
            rs_vert.clear(); // Clear the array of vertices for the next step
            for (auto& element : theme_config["elements"])
            {
                bool check = false;
                struct Element calculated = CalculateElement(element, options, check);
                if (check)
                    elements.push_back(calculated);
            }

            theme_refresh = 0;
            theme_render.elements = elements;
        }

        // Used to display or not the overlay on a game capture (not functional)
        ImDrawList* drawlist;
        if (RS_disp_obs)
            drawlist = ImGui::GetBackgroundDrawList();
        else
            drawlist = ImGui::GetOverlayDrawList();

        if (rs_vert.empty())
        {
            // Generates the vertices of each element
            int start;
            if (RS_rotate_enabled)
                start = ImRotateStart(drawlist);

            for (auto& element : theme_render.elements)
                RenderElement(drawlist, element);

            if (RS_rotate_enabled)
                ImRotateEnd(RS_crotate, start, drawlist, ImRotationCenter(start, drawlist));
        }
        else
        {
            // Fill the DrawList with previously generated vertices
            auto& buf = drawlist->VtxBuffer;
            for (int i = 0; i < rs_vert.size(); ++i)
                buf.push_back(rs_vert[i]);
        }

        // Allows spawn transition
        if (rs_launch < 1.f)
        {
            rs_launch += 0.05f;
            theme_refresh = 1;
        }
    }
    catch (const std::exception&) {}

    ImGui::End();
}

void RocketStats::RenderSettings()
{
    ImVec2 settings_size = { 750, 0 };

    ImGui::SetNextWindowPos(ImVec2{ 128, 256 }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(settings_size);

    ImGui::Begin((menuTitle_ + " - Settings").c_str(), nullptr, (ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse));

    // Show menu only if menu image is loaded
    if (rs_title != nullptr && rs_title->IsLoadedForImGui())
    {
        float column_nb = 3;
        float column_space = 10.f;
        float column_start = 25.f;
        float column_width = ((settings_size.x - (column_start * 2) - (column_space * (column_nb - 1))) / column_nb);

        ImVec2 text_size;
        ImVec2 image_pos;
        ImVec2 win_pos = ImGui::GetWindowPos();
        ImVec2 win_size = ImGui::GetWindowSize();
        Vector2F image_size = rs_title->GetSizeF();
        ImDrawList* drawlist = ImGui::GetWindowDrawList();
        std::string developers = "Developped by @Lyliya, @NuSa_yt, @Arubinu42 & @Larsluph";

        ImVec2 p0 = win_pos;
        ImVec2 p1 = { (win_pos.x + win_size.x), (win_pos.y + win_size.y) };

        p0.x += 1;
        p1.x -= 1;
        drawlist->PushClipRect(p0, p1); // Allows you to delimit the area of the window (without internal borders)

        std::time(&current_time);
        const auto time_error = localtime_s(&local_time, &current_time);

        ImGui::SetCursorPos({ 0, 27 });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2) + image_pos.x, (image_size.Y / 2) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 23, 52 });
        ImGui::Checkbox("##in_file", &RS_in_file);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Updates RocketStats files with game information (usable in OBS)");

        ImGui::SetCursorPos({ 63, 54 });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(cvarManager->getCvar("RS_in_file").getDescription()).c_str());

        ImGui::SetWindowFontScale(1.3f);
        ImGui::SetCursorPos({ 355, 43 });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, cvarManager->getCvar("RS_mode").getDescription().c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ 295, 68 });
        ImGui::SetNextItemWidth(142);
        if (ImGui::BeginCombo("##modes_combo", modes.at(RS_mode).c_str(), ImGuiComboFlags_NoArrowButton))
        {
            int TRS_mode = RS_mode;
            for (int i = 0; i < modes.size(); ++i)
            {
                bool is_selected = (TRS_mode == i);
                if (ImGui::Selectable(modes.at(i).c_str(), is_selected))
                    RS_mode = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Restrict information to current game or keep longer");
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##modes_left", ImGuiDir_Left) && RS_mode > 0)
            --RS_mode;
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##modes_right", ImGuiDir_Right) && RS_mode < (modes.size() - 1))
            ++RS_mode;

        ImGui::SetWindowFontScale(1.3f);
        ImGui::SetCursorPos({ 585, 43 });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, cvarManager->getCvar("RS_theme").getDescription().c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ 525, 68 });
        ImGui::SetNextItemWidth(142);
        if (ImGui::BeginCombo("##themes_combo", theme_render.name.c_str(), ImGuiComboFlags_NoArrowButton))
        {
            int TRS_theme = RS_theme;
            for (int i = 0; i < themes.size(); ++i)
            {
                bool is_selected = (TRS_theme == i);
                if (ImGui::Selectable(themes.at(i).name.c_str(), is_selected))
                    RS_theme = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Themes available in RocketStats folders (fully customizable)");
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##themes_left", ImGuiDir_Left) && RS_theme > 0)
            --RS_theme;
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##themes_right", ImGuiDir_Right) && themes.size() && RS_theme < (themes.size() - 1))
            ++RS_theme;

        ImGui::SetCursorPos({ 113, 120 });
        if (ImGui::Button(cvarManager->getCvar("RS_x").getDescription().c_str(), { 65, 0 }))
            RS_x_edit = !RS_x_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the horizontal position of the overlay");
        ImGui::SetCursorPos({ 168, 120 });
        ImGui::SetNextItemWidth(150);
        if (RS_x_edit)
            ImGui::InputFloat("##x_position", &RS_x, 0.001f, 0.1f, "%.3f");
        else
            ImGui::SliderFloat("##x_position", &RS_x, 0.f, 1.f, "%.3f");

        ImGui::SetCursorPos({ 431, 120 });
        if (ImGui::Button(cvarManager->getCvar("RS_y").getDescription().c_str(), { 65, 0 }))
            RS_y_edit = !RS_y_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the vertical position of the overlay");
        ImGui::SetCursorPos({ 486, 120 });
        ImGui::SetNextItemWidth(150);
        if (RS_y_edit)
            ImGui::InputFloat("##y_position", &RS_y, 0.001f, 0.1f, "%.3f");
        else
            ImGui::SliderFloat("##y_position", &RS_y, 0.f, 1.f, "%.3f");

        ImGui::SetCursorPos({ 34, 165 });
        if (ImGui::Button(cvarManager->getCvar("RS_scale").getDescription().c_str(), { 65, 0 }))
            RS_scale_edit = !RS_scale_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the size of the overlay");
        ImGui::SetCursorPos({ 89, 165 });
        ImGui::SetNextItemWidth(150);
        if (RS_scale_edit)
            ImGui::InputFloat("##scale", &RS_scale, 0.01f, 0.1f, "%.3f");
        else
            ImGui::SliderFloat("##scale", &RS_scale, 0.f, 10.f, "%.3f");

        ImGui::SetCursorPos({ 273, 165 });
        if (ImGui::Button(cvarManager->getCvar("RS_rotate").getDescription().c_str(), { 65, 0 }))
            RS_rotate_edit = !RS_rotate_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the rotation of the overlay");
        ImGui::SetCursorPos({ 328, 165 });
        ImGui::SetNextItemWidth(150);
        if (RS_rotate_edit)
            ImGui::InputFloat("##rotate", &RS_rotate, 0.001f, 0.1f, "%.3f");
        else
            ImGui::SliderFloat("##rotate", &RS_rotate, -180.f, 180.f, "%.3f");

        ImGui::SetCursorPos({ 512, 165 });
        if (ImGui::Button(cvarManager->getCvar("RS_opacity").getDescription().c_str(), { 65, 0 }))
            RS_opacity_edit = !RS_opacity_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the opacity of the overlay");
        ImGui::SetCursorPos({ 567, 165 });
        ImGui::SetNextItemWidth(150);
        if (RS_opacity_edit)
            ImGui::InputFloat("##opacity", &RS_opacity, 0.001f, 0.1f, "%.3f");
        else
            ImGui::SliderFloat("##opacity", &RS_opacity, 0.f, 1.f, "%.3f");

        ImGui::SetCursorPosY(200);
        ImGui::Separator();

        ImGui::SetCursorPos({ 0, 210 });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2) + image_pos.x, (image_size.Y / 2) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 23, 235 });
        ImGui::Checkbox("##overlay", &RS_disp_overlay);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Displays the overlay on the game screen");

        ImGui::SetCursorPos({ 63, 237 });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(cvarManager->getCvar("RS_disp_overlay").getDescription()).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (settings_size.x - 120), 213 });
        if (ImGui::Button("Open folder", { 110, 0 }))
            system(("powershell -WindowStyle Hidden \"start \"\"" + GetPath() + "\"\"\"").c_str());
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Access theme folders or files for OBS");
        ImGui::SetCursorPos({ (settings_size.x - 120), 238 });
        if (ImGui::Button("Reload Theme", { 88, 0 }))
            ChangeTheme(RS_theme);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Refresh current theme information (JSON and images)");
        ImGui::SetCursorPos({ (settings_size.x - 27), 238 });
        if (ImGui::Button("A", { 17, 0 }))
        {
            LoadThemes();
            SetTheme(theme_render.name);
            ChangeTheme(RS_theme);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Reloads all the themes (adds or removes depending on the folders)");
        ImGui::SetCursorPos({ (settings_size.x - 120), 263 });
        if (ImGui::Button("Reset Stats", { 110, 0 }))
            ResetStats();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Resets all plugin information for all modes (MMR, Win, Loss, etc.)");

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 280, 230 });
        text_size = ImGui::CalcTextSize(theme_render.name.c_str());
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 1.f }, theme_render.name.c_str());
        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (285 + text_size.x), 237 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.5f }, (theme_render.version + (theme_render.date.size() ? (" - " + theme_render.date) : "")).c_str());
        ImGui::SetCursorPos({ 290, 254 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.8f }, ("Theme by " + theme_render.author).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ column_start, 300 });
        ImGui::BeginChild("##column1", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::Checkbox(cvarManager->getCvar("RS_disp_obs").getDescription().c_str(), &RS_disp_obs);
        ImGui::PopStyleVar();
        ImGui::Checkbox(cvarManager->getCvar("RS_enable_inmenu").getDescription().c_str(), &RS_enable_inmenu);
        ImGui::Checkbox(cvarManager->getCvar("RS_enable_ingame").getDescription().c_str(), &RS_enable_ingame);
        ImGui::Checkbox(cvarManager->getCvar("RS_enable_float").getDescription().c_str(), &RS_enable_float);
        ImGui::Checkbox(cvarManager->getCvar("RS_onchange_scale").getDescription().c_str(), &RS_onchange_scale);
        ImGui::Checkbox(cvarManager->getCvar("RS_onchange_rotate").getDescription().c_str(), &RS_onchange_rotate);
        ImGui::Checkbox(cvarManager->getCvar("RS_onchange_opacity").getDescription().c_str(), &RS_onchange_opacity);
        ImGui::Checkbox(cvarManager->getCvar("RS_onchange_position").getDescription().c_str(), &RS_onchange_position);
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::SetCursorPosX(column_start + column_space + column_width);
        ImGui::BeginChild("##column2", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        if (!RS_in_file)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_gm").getDescription().c_str(), &RS_file_gm);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_rank").getDescription().c_str(), &RS_file_rank);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_div").getDescription().c_str(), &RS_file_div);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_mmr").getDescription().c_str(), &RS_file_mmr);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_mmrc").getDescription().c_str(), &RS_file_mmrc);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_mmrcc").getDescription().c_str(), &RS_file_mmrcc);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_win").getDescription().c_str(), &RS_file_win);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_loss").getDescription().c_str(), &RS_file_loss);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_streak").getDescription().c_str(), &RS_file_streak);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_demo").getDescription().c_str(), &RS_file_demo);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_death").getDescription().c_str(), &RS_file_death);
        ImGui::Checkbox(cvarManager->getCvar("RS_file_boost").getDescription().c_str(), &RS_file_boost);
        if (!RS_in_file)
            ImGui::PopStyleVar();
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::SetCursorPosX(column_start + (column_space * 2) + (column_width * 2));
        ImGui::BeginChild("##column3", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_gm").getDescription().c_str(), &RS_hide_gm);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_rank").getDescription().c_str(), &RS_hide_rank);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_div").getDescription().c_str(), &RS_hide_div);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_mmr").getDescription().c_str(), &RS_hide_mmr);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_mmrc").getDescription().c_str(), &RS_hide_mmrc);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_mmrcc").getDescription().c_str(), &RS_hide_mmrcc);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_win").getDescription().c_str(), &RS_hide_win);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_loss").getDescription().c_str(), &RS_hide_loss);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_streak").getDescription().c_str(), &RS_hide_streak);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_demo").getDescription().c_str(), &RS_hide_demo);
        ImGui::Checkbox(cvarManager->getCvar("RS_hide_death").getDescription().c_str(), &RS_hide_death);
        ImGui::Checkbox(cvarManager->getCvar("RS_replace_mmr").getDescription().c_str(), &RS_replace_mmr);
        ImGui::EndChild();

        /* Variable to use to animate images
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        float fps = ImGui::GetIO().Framerate;
        ImGui::Text(("Framerate: " + std::to_string(fps)).c_str());
        */

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::Separator();

        ImGui::TextColored(((time_error || local_time.tm_sec % 2) ? ImVec4{ 0.04f, 0.52f, 0.89f, 1.f } : ImVec4{ 1.f, 1.f, 1.f, 0.5f }), "Donate");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::IsMouseClicked(0))
                system("powershell -WindowStyle Hidden \"start https://www.paypal.com/paypalme/rocketstats\"");
        }
        ImGui::SameLine();
        text_size = ImGui::CalcTextSize(developers.c_str());
        ImGui::SetCursorPosX((settings_size.x - text_size.x) / 2);
        ImGui::Text(developers.c_str());
        text_size = ImGui::CalcTextSize(menuVersion_.c_str());
        ImGui::SameLine();
        ImGui::SetCursorPosX(settings_size.x - text_size.x - 7);
        ImGui::Text(menuVersion_.c_str());

        drawlist->PopClipRect();
    }
    else
    {
        ImGui::SetWindowFontScale(1.5f);
        ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Bad Installation - Please move your old files to the folder: data/RocketStats");
        ImGui::SameLine();
        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPosX(settings_size.x - 80 - 7);
        if (ImGui::Button("Reload All", { 80, 0 }))
        {
            SetDefaultFolder();
            LoadThemes();
            ChangeTheme(RS_theme);
            rs_title = LoadImg("RocketStats_images/title.png");
        }
    }

    ImGui::End();

    // Delimits certain variables
    if (RS_scale < 0.f)
        RS_scale = 0.f;

    if (RS_rotate < -180.f)
        RS_rotate = -180.f;
    else if (RS_rotate > 180.f)
        RS_rotate = 180.f;

    if (RS_opacity < 0.f)
        RS_opacity = 0.f;
    else if (RS_opacity > 1.f)
        RS_opacity = 1.f;

    // Check for changes before modifying cvars
    if (RS_mode != cvarManager->getCvar("RS_mode").getIntValue())
        cvarManager->getCvar("RS_mode").setValue(RS_mode);
    if (RS_theme != cvarManager->getCvar("RS_theme").getIntValue())
        cvarManager->getCvar("RS_theme").setValue(RS_theme);

    if (RS_x != cvarManager->getCvar("RS_x").getFloatValue())
        cvarManager->getCvar("RS_x").setValue(RS_x);
    if (RS_y != cvarManager->getCvar("RS_y").getFloatValue())
        cvarManager->getCvar("RS_y").setValue(RS_y);
    if (RS_scale != cvarManager->getCvar("RS_scale").getFloatValue())
        cvarManager->getCvar("RS_scale").setValue(RS_scale);
    if (RS_rotate != cvarManager->getCvar("RS_rotate").getFloatValue())
        cvarManager->getCvar("RS_rotate").setValue(RS_rotate);
    if (RS_opacity != cvarManager->getCvar("RS_opacity").getFloatValue())
        cvarManager->getCvar("RS_opacity").setValue(RS_opacity);

    if (RS_disp_overlay != cvarManager->getCvar("RS_disp_overlay").getBoolValue())
        cvarManager->getCvar("RS_disp_overlay").setValue(RS_disp_overlay);
    if (RS_disp_obs != cvarManager->getCvar("RS_disp_obs").getBoolValue())
        cvarManager->getCvar("RS_disp_obs").setValue(RS_disp_obs);
    if (RS_enable_inmenu != cvarManager->getCvar("RS_enable_inmenu").getBoolValue())
    {
        cvarManager->getCvar("RS_enable_inmenu").setValue(RS_enable_inmenu);
        if (!RS_enable_inmenu && !RS_enable_ingame)
            RS_enable_ingame = true;
    }
    if (RS_enable_ingame != cvarManager->getCvar("RS_enable_ingame").getBoolValue())
    {
        cvarManager->getCvar("RS_enable_ingame").setValue(RS_enable_ingame);
        if (!RS_enable_ingame && !RS_enable_inmenu)
            RS_enable_inmenu = true;
    }
    if (RS_enable_float != cvarManager->getCvar("RS_enable_float").getBoolValue())
        cvarManager->getCvar("RS_enable_float").setValue(RS_enable_float);
    if (RS_onchange_scale != cvarManager->getCvar("RS_onchange_scale").getBoolValue())
        cvarManager->getCvar("RS_onchange_scale").setValue(RS_onchange_scale);
    if (RS_onchange_rotate != cvarManager->getCvar("RS_onchange_rotate").getBoolValue())
        cvarManager->getCvar("RS_onchange_rotate").setValue(RS_onchange_rotate);
    if (RS_onchange_opacity != cvarManager->getCvar("RS_onchange_opacity").getBoolValue())
        cvarManager->getCvar("RS_onchange_opacity").setValue(RS_onchange_opacity);
    if (RS_onchange_position != cvarManager->getCvar("RS_onchange_position").getBoolValue())
        cvarManager->getCvar("RS_onchange_position").setValue(RS_onchange_position);

    if (RS_file_gm != cvarManager->getCvar("RS_file_gm").getBoolValue())
        cvarManager->getCvar("RS_file_gm").setValue(RS_file_gm);
    if (RS_file_rank != cvarManager->getCvar("RS_file_rank").getBoolValue())
        cvarManager->getCvar("RS_file_rank").setValue(RS_file_rank);
    if (RS_file_div != cvarManager->getCvar("RS_file_div").getBoolValue())
        cvarManager->getCvar("RS_file_div").setValue(RS_file_div);
    if (RS_file_mmr != cvarManager->getCvar("RS_file_mmr").getBoolValue())
        cvarManager->getCvar("RS_file_mmr").setValue(RS_file_mmr);
    if (RS_file_mmrc != cvarManager->getCvar("RS_file_mmrc").getBoolValue())
        cvarManager->getCvar("RS_file_mmrc").setValue(RS_file_mmrc);
    if (RS_file_mmrcc != cvarManager->getCvar("RS_file_mmrcc").getBoolValue())
        cvarManager->getCvar("RS_file_mmrcc").setValue(RS_file_mmrcc);
    if (RS_file_win != cvarManager->getCvar("RS_file_win").getBoolValue())
        cvarManager->getCvar("RS_file_win").setValue(RS_file_win);
    if (RS_file_loss != cvarManager->getCvar("RS_file_loss").getBoolValue())
        cvarManager->getCvar("RS_file_loss").setValue(RS_file_loss);
    if (RS_file_streak != cvarManager->getCvar("RS_file_streak").getBoolValue())
        cvarManager->getCvar("RS_file_streak").setValue(RS_file_streak);
    if (RS_file_demo != cvarManager->getCvar("RS_file_demo").getBoolValue())
        cvarManager->getCvar("RS_file_demo").setValue(RS_file_demo);
    if (RS_file_death != cvarManager->getCvar("RS_file_death").getBoolValue())
        cvarManager->getCvar("RS_file_death").setValue(RS_file_death);
    if (RS_file_boost != cvarManager->getCvar("RS_file_boost").getBoolValue())
        cvarManager->getCvar("RS_file_boost").setValue(RS_file_boost);

    if (RS_hide_gm != cvarManager->getCvar("RS_hide_gm").getBoolValue())
        cvarManager->getCvar("RS_hide_gm").setValue(RS_hide_gm);
    if (RS_hide_rank != cvarManager->getCvar("RS_hide_rank").getBoolValue())
        cvarManager->getCvar("RS_hide_rank").setValue(RS_hide_rank);
    if (RS_hide_div != cvarManager->getCvar("RS_hide_div").getBoolValue())
        cvarManager->getCvar("RS_hide_div").setValue(RS_hide_div);
    if (RS_hide_mmr != cvarManager->getCvar("RS_hide_mmr").getBoolValue())
        cvarManager->getCvar("RS_hide_mmr").setValue(RS_hide_mmr);
    if (RS_hide_mmrc != cvarManager->getCvar("RS_hide_mmrc").getBoolValue())
        cvarManager->getCvar("RS_hide_mmrc").setValue(RS_hide_mmrc);
    if (RS_hide_mmrcc != cvarManager->getCvar("RS_hide_mmrcc").getBoolValue())
        cvarManager->getCvar("RS_hide_mmrcc").setValue(RS_hide_mmrcc);
    if (RS_hide_win != cvarManager->getCvar("RS_hide_win").getBoolValue())
        cvarManager->getCvar("RS_hide_win").setValue(RS_hide_win);
    if (RS_hide_loss != cvarManager->getCvar("RS_hide_loss").getBoolValue())
        cvarManager->getCvar("RS_hide_loss").setValue(RS_hide_loss);
    if (RS_hide_streak != cvarManager->getCvar("RS_hide_streak").getBoolValue())
        cvarManager->getCvar("RS_hide_streak").setValue(RS_hide_streak);
    if (RS_hide_demo != cvarManager->getCvar("RS_hide_demo").getBoolValue())
        cvarManager->getCvar("RS_hide_demo").setValue(RS_hide_demo);
    if (RS_hide_death != cvarManager->getCvar("RS_hide_death").getBoolValue())
        cvarManager->getCvar("RS_hide_death").setValue(RS_hide_death);
    if (RS_replace_mmr != cvarManager->getCvar("RS_replace_mmr").getBoolValue())
        cvarManager->getCvar("RS_replace_mmr").setValue(RS_replace_mmr);
}

// Name of the menu that is used to toggle the window.
std::string RocketStats::GetMenuName()
{
    return menuName_;
}

// Title to give the menu
std::string RocketStats::GetMenuTitle()
{
    return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void RocketStats::SetImGuiContext(uintptr_t ctx)
{
    ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool RocketStats::ShouldBlockInput()
{
    return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool RocketStats::IsActiveOverlay()
{
    return isSettingsOpen_;
}

void RocketStats::OnOpen()
{
    //ToggleSettings("OnOpen", ToggleFlags_Show);
}

void RocketStats::OnClose()
{
    // Displays the plugin immediately after pressing the escape key
    if (escape_state)
    {
        escape_state = false;
        gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
            cvarManager->executeCommand("togglemenu " + GetMenuName());
        }, 0.02F);
    }

    ToggleSettings("OnClose", ToggleFlags_Hide);
}
#pragma endregion
