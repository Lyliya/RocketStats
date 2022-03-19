/* ===========================================================
 *   Developped by @Lyliya, @NuSa_yt, @Arubinu42 & @Larsluph
 * =========================================================== */

#include "RocketStats.h"

BAKKESMOD_PLUGIN(RocketStats, "RocketStats", "4.0", PERMISSION_ALL)

#pragma region Utils
Stats RocketStats::GetStats()
{
    Stats result;

    switch (rs_mode)
    {
        case 1: result = stats[current.playlist]; break;
        case 2: result = always; break;
        case 3: result = always_gm[current.playlist]; break;
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
    if (playlist_name.find(playlistID) != playlist_name.end())
        return playlist_name.at(playlistID);
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

bool RocketStats::GetCVar(const char* name, int& value)
{
    if (themes_values[theme_render.name].is_object() && (themes_values[theme_render.name][name + 3].is_number_integer() || themes_values[theme_render.name][name + 3].is_number_unsigned()))
    {
        value = int(themes_values[theme_render.name][name + 3]);
        cvarManager->log("GetCVar: " + std::string(name) + " " + std::to_string(value));

        return true;
    }

    return false;
}

bool RocketStats::GetCVar(const char* name, bool& value)
{
    if (themes_values[theme_render.name].is_object() && themes_values[theme_render.name][name + 3].is_boolean())
    {
        value = bool(themes_values[theme_render.name][name + 3]);
        cvarManager->log("GetCVar: " + std::string(name) + " " + std::to_string(value));

        return true;
    }

    return false;
}

bool RocketStats::GetCVar(const char* name, float& value)
{
    if (themes_values[theme_render.name].is_object() && themes_values[theme_render.name][name + 3].is_number())
    {
        value = float(themes_values[theme_render.name][name + 3]);
        cvarManager->log("GetCVar: " + std::string(name) + " " + std::to_string(value));

        return true;
    }

    return false;
}

bool RocketStats::SetCVar(const char* name, int& value, bool save)
{
    if (value != cvarManager->getCvar(name).getIntValue())
    {
        cvarManager->log("SetCVar: " + std::string(name) + " " + std::to_string(value));
        cvarManager->getCvar(name).setValue(value);

        if (save)
        {
            if (!themes_values[theme_render.name].is_object())
                themes_values[theme_render.name] = {};

            themes_values[theme_render.name][name + 3] = value;
        }

        return true;
    }

    return false;
}

bool RocketStats::SetCVar(const char* name, bool& value, bool save)
{
    if (value != cvarManager->getCvar(name).getBoolValue())
    {
        cvarManager->log("SetCVar: " + std::string(name) + " " + std::to_string(value));
        cvarManager->getCvar(name).setValue(value);

        if (save)
        {
            if (!themes_values[theme_render.name].is_object())
                themes_values[theme_render.name] = {};

            themes_values[theme_render.name][name + 3] = value;
        }

        return true;
    }

    return false;
}

bool RocketStats::SetCVar(const char* name, float& value, bool save)
{
    value = (std::round(value * 1000.f) / 1000.f);
    if (value != cvarManager->getCvar(name).getFloatValue())
    {
        cvarManager->log("SetCVar: " + std::string(name) + " " + std::to_string(value));
        cvarManager->getCvar(name).setValue(value);

        if (save)
        {
            if (!themes_values[theme_render.name].is_object())
                themes_values[theme_render.name] = {};

            themes_values[theme_render.name][name + 3] = value;
        }

        return true;
    }

    return false;
}

void RocketStats::RecoveryOldVars()
{
    cvarManager->log("Recovery old vars !");

    CVarWrapper ors_session = cvarManager->getCvar("RS_session");
    if (!ors_session.IsNull())
        rs_mode = ors_session.getBoolValue();

    CVarWrapper ors_Use_v1 = cvarManager->getCvar("RS_Use_v1");
    CVarWrapper ors_Use_v2 = cvarManager->getCvar("RS_Use_v2");
    if (!ors_Use_v1.IsNull() && !ors_Use_v2.IsNull())
        SetTheme(ors_Use_v1.getBoolValue() ? "Default" : (ors_Use_v2.getBoolValue() ? "Redesigned" : "Arubinu42"));

    CVarWrapper ors_x_position = cvarManager->getCvar("RS_x_position");
    if (!ors_x_position.IsNull())
        rs_x = ors_x_position.getFloatValue();

    CVarWrapper ors_y_position = cvarManager->getCvar("RS_y_position");
    if (!ors_y_position.IsNull())
        rs_y = ors_y_position.getFloatValue();

    CVarWrapper ors_scale = cvarManager->getCvar("RS_scale");
    if (!ors_scale.IsNull())
        rs_scale = ors_scale.getFloatValue();

    CVarWrapper ors_disp_ig = cvarManager->getCvar("RS_disp_ig");
    if (!ors_disp_ig.IsNull())
        rs_disp_overlay = ors_disp_ig.getBoolValue();

    CVarWrapper ors_enable_float = cvarManager->getCvar("RS_enable_float");
    if (!ors_enable_float.IsNull())
        rs_enable_float = ors_enable_float.getBoolValue();

    CVarWrapper ors_hide_overlay_ig = cvarManager->getCvar("RS_hide_overlay_ig");
    if (!ors_hide_overlay_ig.IsNull())
        rs_enable_ingame = !ors_hide_overlay_ig.getBoolValue();

    CVarWrapper ors_disp_gamemode = cvarManager->getCvar("RS_disp_gamemode");
    if (!ors_disp_gamemode.IsNull())
        rs_hide_gm = !ors_disp_gamemode.getBoolValue();

    CVarWrapper ors_disp_rank = cvarManager->getCvar("RS_disp_rank");
    if (!ors_disp_rank.IsNull())
        rs_hide_rank = !ors_disp_rank.getBoolValue();

    CVarWrapper ors_disp_mmr = cvarManager->getCvar("RS_disp_mmr");
    if (!ors_disp_mmr.IsNull())
        rs_hide_mmr = !ors_disp_mmr.getBoolValue();

    CVarWrapper ors_disp_wins = cvarManager->getCvar("RS_disp_wins");
    if (!ors_disp_wins.IsNull())
        rs_hide_win = !ors_disp_wins.getBoolValue();

    CVarWrapper ors_disp_losses = cvarManager->getCvar("RS_disp_losses");
    if (!ors_disp_losses.IsNull())
        rs_hide_loss = !ors_disp_losses.getBoolValue();

    CVarWrapper ors_disp_streak = cvarManager->getCvar("RS_disp_streak");
    if (!ors_disp_streak.IsNull())
        rs_hide_streak = !ors_disp_streak.getBoolValue();

    CVarWrapper ors_stop_boost = cvarManager->getCvar("RocketStats_stop_boost");
    if (!ors_stop_boost.IsNull())
        rs_file_boost = ors_stop_boost.getBoolValue();

    ChangeTheme(rs_theme);
    WriteConfig();
}
#pragma endregion

#pragma region PluginLoadRoutines
void RocketStats::onLoad()
{
    // notifierToken = gameWrapper->GetMMRWrapper().RegisterMMRNotifier(std::bind(&RocketStats::UpdateMMR, this, std::placeholders::_1));

    SetDefaultFolder();
    SetCustomProtocol();
    rs_logo = LoadImg("RocketStats_images/logo.png");
    rs_title = LoadImg("RocketStats_images/title.png");

    LoadImgs();
    LoadThemes();

    InitRank();
    InitStats();
    rs_recovery = !ReadConfig();
    ChangeTheme(rs_theme);

    ResetFiles(); // Reset all files (and create them if they don't exist)
    RemoveFile("RocketStats_Loose.txt"); // Delete the old file
    RemoveFile("RocketStats_images/BoostState.txt"); // Delete the old file
    RemoveFile("plugins/settings/rocketstats.set", true); // Delete the old file

    // Can be used from the console or in bindings
    cvarManager->registerNotifier("rs_toggle_menu", [this](std::vector<std::string> params) {
            ToggleSettings("rs_toggle_menu");
    }, "Toggle menu", PERMISSION_ALL);

    // Hook on Event
    gameWrapper->HookEvent("Function TAGame.GFxData_StartMenu_TA.EventTitleScreenClicked", std::bind(&RocketStats::ShowPlugin, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameViewportClient_TA.SetUIScaleModifier", std::bind(&RocketStats::UpdateUIScale, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function Engine.GameViewportClient.IsFullScreenViewport", std::bind(&RocketStats::UpdateUIScale, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", std::bind(&RocketStats::GameStart, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", std::bind(&RocketStats::GameEnd, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", std::bind(&RocketStats::OnBoostStart, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", std::bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Destroyed", std::bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));

    gameWrapper->HookEventWithCallerPost<ServerWrapper>("Function TAGame.GFxHUD_TA.HandleStatEvent", std::bind(&RocketStats::onStatEvent, this, std::placeholders::_1, std::placeholders::_2));
    gameWrapper->HookEventWithCallerPost<ServerWrapper>("Function TAGame.GFxHUD_TA.HandleStatTickerMessage", std::bind(&RocketStats::onStatTickerMessage, this, std::placeholders::_1, std::placeholders::_2));

    // Register Cvars
    if (rs_recovery)
    {
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

    cvarManager->registerCvar("cl_rocketstats_settings", (settings_open ? "1" : "0"), "Display RocketStats settings", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper now) {
        settings_open = now.getBoolValue();

        cvarManager->log("cl_rocketstats_settings: " + std::string(settings_open ? "true" : "false"));
        if (!settings_open)
            WriteConfig();
    });

    cvarManager->registerCvar("rs_mode", std::to_string(rs_mode), "Mode", true, true, 0, true, float(modes.size() - 1), false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_theme", std::to_string(rs_theme), "Theme", true, true, 0, false, 99, false).addOnValueChanged([this](std::string old, CVarWrapper now) {
        if (!ChangeTheme(now.getIntValue()))
            now.setValue(old);
    });

    cvarManager->registerCvar("rs_x", std::to_string(rs_x), "X", true, true, 0.f, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_y", std::to_string(rs_y), "Y", true, true, 0.f, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_scale", std::to_string(rs_scale), "Scale", true, true, 0.001f, true, 10.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_rotate", std::to_string(rs_rotate), "Rotate", true, true, -180.f, true, 180.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_opacity", std::to_string(rs_opacity), "Opacity", true, true, 0.f, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("rs_disp_overlay", (rs_disp_overlay ? "1" : "0"), "Overlay", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("rs_enable_inmenu", (rs_enable_inmenu ? "1" : "0"), "Show in menu", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_enable_ingame", (rs_enable_ingame ? "1" : "0"), "Show while in-game", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_enable_float", (rs_enable_float ? "1" : "0"), "Enable floating point", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("rs_in_file", std::to_string(rs_in_file), "Informations", true, true, 0, true, 1, true).addOnValueChanged([this](std::string old, CVarWrapper now) {
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
    cvarManager->registerCvar("rs_file_gm", (rs_file_gm ? "1" : "0"), "Write GameMode in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_rank", (rs_file_rank ? "1" : "0"), "Write Rank in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_div", (rs_file_div ? "1" : "0"), "Write Division in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_mmr", (rs_file_mmr ? "1" : "0"), "Write MMR in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_mmrc", (rs_file_mmrc ? "1" : "0"), "Write MMRChange in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_mmrcc", (rs_file_mmrcc ? "1" : "0"), "Write MMRChangeCumul in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_win", (rs_file_win ? "1" : "0"), "Write Wins in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_loss", (rs_file_loss ? "1" : "0"), "Write Losses in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_streak", (rs_file_streak ? "1" : "0"), "Write Streaks in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_demo", (rs_file_demo ? "1" : "0"), "Write Demolitions in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_death", (rs_file_death ? "1" : "0"), "Write Deaths in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_file_boost", (rs_file_boost ? "1" : "0"), "Write Boost in file", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("rs_hide_gm", (rs_hide_gm ? "1" : "0"), "Hide GameMode", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_rank", (rs_hide_rank ? "1" : "0"), "Hide Rank", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_div", (rs_hide_div ? "1" : "0"), "Hide Division", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_mmr", (rs_hide_mmr ? "1" : "0"), "Hide MMR", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_mmrc", (rs_hide_mmrc ? "1" : "0"), "Hide MMRChange", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_mmrcc", (rs_hide_mmrcc ? "1" : "0"), "Hide MMRChangeCumul", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_win", (rs_hide_win ? "1" : "0"), "Hide Wins", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_loss", (rs_hide_loss ? "1" : "0"), "Hide Losses", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_streak", (rs_hide_streak ? "1" : "0"), "Hide Streaks", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_demo", (rs_hide_demo ? "1" : "0"), "Hide Demolitions", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_hide_death", (rs_hide_death ? "1" : "0"), "Hide Deaths", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_replace_mmr", (rs_replace_mmr ? "1" : "0"), "Replace MMR with MMRChange", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("rs_replace_mmrc", (rs_replace_mmrc ? "1" : "0"), "Replace MMRChange with MMR", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    // Displays the plugin shortly after initialization
    gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
        if (rs_recovery)
            RecoveryOldVars();

        UpdateUIScale("onLoad");
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
    // If the old folder exist, copy everything to the new path
    if (ExistsPath("RocketStats", true))
    {
        std::string old_path = GetPath("RocketStats", true);
        fs::copy(old_path, GetPath(), (fs::copy_options::recursive | fs::copy_options::update_existing));
        fs::remove_all(old_path);
    }
}

void RocketStats::SetCustomProtocol()
{
    std::string dir = GetPath();
    Utils::ReplaceAll(dir, "/", "\\");

    HKEY key;
    LPCTSTR value;
    DWORD dwDisposition;
    if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes\\RocketStats"), 0, NULL, 0, KEY_WRITE, NULL, &key, &dwDisposition) == ERROR_SUCCESS)
    {
        std::cout << "REGISTRY" << std::endl;

        value = TEXT("URL:RocketStats protocol");
        if (RegSetValueEx(key, TEXT(""), 0, REG_SZ, (const BYTE*)value, sizeof(TCHAR) * (lstrlen(value) + 1)) != ERROR_SUCCESS)
            std::cout << "set protocol failed!" << std::endl;

        value = TEXT("RocketStats");
        if (RegSetValueEx(key, TEXT("URL Protocol"), 0, REG_SZ, (const BYTE*)value, sizeof(TCHAR) * (lstrlen(value) + 1)) != ERROR_SUCCESS)
            std::cout << "set url failed!" << std::endl;

        RegCloseKey(key);

        /*if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes\\RocketStats\\DefaultIcon"), 0, NULL, 0, KEY_WRITE, NULL, &key, &dwDisposition) == ERROR_SUCCESS)
        {
            value = Utils::ConvertToLPSTR(installer + ", 1");
            if (RegSetValueEx(key, TEXT(""), 0, REG_SZ, (const BYTE*)value, sizeof(TCHAR) * (lstrlen(value) + 1)) != ERROR_SUCCESS)
                std::cout << "set icon failed!" << std::endl;

            RegCloseKey(key);
        }*/

        if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes\\RocketStats\\shell\\open\\command"), 0, NULL, 0, KEY_WRITE, NULL, &key, &dwDisposition) == ERROR_SUCCESS)
        {
            value = Utils::ConvertToLPSTR("rundll32 shell32.dll,ShellExec_RunDLL \"powershell\" \"try { $theme = \\\"%1\\\".split( '/' )[ 3 ]; $version = \\\"%1\\\".split( '/' )[ 4 ]; $dir = \\\"" + dir + "\"; $url = \\\"http://rocketstats.net/$theme/dl/$version\\\"; $zip = \\\"$dir\\toinstall.zip\\\"; $dest = \\\"$dir\\RocketStats_themes\\\"; if ( \\\"%1\\\".split( '/' )[ 2 ] -eq 'install' -and $theme -match '^\\d+$' -and $version -match '^\\d+$' ) { echo 'Theme being downloaded ...'; Invoke-WebRequest -Uri $url -OutFile $zip >$null 2>$null; try { echo 'Theme being installed ...'; Expand-Archive $zip -DestinationPath $dest -Force >$null 2>$null; echo 'Theme successfully installed.'; echo 'Click ''R'' to the right of the ''Reload Theme'' button in RocketStats to add the theme to the list.'; Remove-Item $zip >$null 2>$null; } catch { echo 'Install error!'; } } else { echo 'The requested theme could not be found!'; } } catch { echo 'Download error!'; } echo ''; echo 'Press Enter to continue ...'; Read-Host;\"");
            if (RegSetValueEx(key, TEXT(""), 0, REG_SZ, (const BYTE*)value, sizeof(TCHAR) * (lstrlen(value) + 1)) != ERROR_SUCCESS)
                std::cout << "set command failed!" << std::endl;

            RegCloseKey(key);
        }
    }
}

void RocketStats::ShowPlugin(std::string eventName)
{
    TogglePlugin(eventName, ToggleFlags_Show);
}

void RocketStats::UpdateUIScale(std::string eventName)
{
    rs_screen_scale[0] = gameWrapper->GetUIScale();
    rs_screen_scale[1] = gameWrapper->GetSafeZoneRatio();
    cvarManager->log("scale: " + std::to_string(rs_screen_scale[0]) + " " + std::to_string(rs_screen_scale[1]));
    SetRefresh(1);
}

void RocketStats::TogglePlugin(std::string eventName, ToggleFlags mode)
{
    if (mode == ToggleFlags_Toggle || (mode == ToggleFlags_Show && !plugin_open) || (mode == ToggleFlags_Hide && plugin_open))
    {
        plugin_open = !plugin_open;
        cvarManager->executeCommand("togglemenu " + GetMenuName());
    }
}

void RocketStats::ToggleSettings(std::string eventName, ToggleFlags mode)
{
    if (mode == ToggleFlags_Toggle || (mode == ToggleFlags_Show && !settings_open) || (mode == ToggleFlags_Hide && settings_open))
    {
        settings_open = !settings_open;
        cvarManager->getCvar("cl_rocketstats_settings").setValue(settings_open);

        cvarManager->log("ToggleSettings: " + std::string(settings_open ? "true" : "false"));
        if (!settings_open)
            WriteConfig(); // Saves settings when closing the menu
    }
}
#pragma endregion

#pragma region GameMgmt
void RocketStats::GameStart(std::string eventName)
{
    if (!gameWrapper->IsInOnlineGame() || is_game_started)
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
    current.playlist = mmrw.GetCurrentPlaylist();
    SkillRank playerRank = mmrw.GetPlayerRank(gameWrapper->GetUniqueID(), current.playlist);
    cvarManager->log(std::to_string(current.playlist) + " -> " + GetPlaylistName(current.playlist));

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
    my_team_num = myTeam.GetTeamNum();

    // Set Game Started
    is_game_started = true;
    is_game_ended = false;

    UpdateMMR(gameWrapper->GetUniqueID());
    WriteConfig();
    if (rs_in_file && rs_file_boost)
        WriteInFile("RocketStats_BoostState.txt", std::to_string(0));

    cvarManager->log("===== !GameStart =====");
}

void RocketStats::GameEnd(std::string eventName)
{
    if (gameWrapper->IsInOnlineGame() && my_team_num != -1)
    {
        cvarManager->log("===== GameEnd =====");
        ServerWrapper server = gameWrapper->GetOnlineGame();
        TeamWrapper winningTeam = server.GetGameWinner();
        if (winningTeam.IsNull())
            return;

        int teamnum = winningTeam.GetTeamNum();

        // Game as ended
        is_game_ended = true;

        MMRWrapper mw = gameWrapper->GetMMRWrapper();

        if (my_team_num == winningTeam.GetTeamNum())
        {
            cvarManager->log("===== Game Won =====");
            // On Win, Increase streak and Win Number
            always.win++;
            session.win++;
            stats[current.playlist].win++;
            always_gm[current.playlist].win++;

            if (stats[current.playlist].streak < 0)
            {
                always.streak = 1;
                session.streak = 1;
                stats[current.playlist].streak = 1;
                always_gm[current.playlist].streak = 1;
            }
            else
            {
                always.streak++;
                session.streak++;
                stats[current.playlist].streak++;
                always_gm[current.playlist].streak++;
            }

            SetRefresh(1);
            WriteWin();
        }
        else
        {
            cvarManager->log("===== Game Lost =====");
            // On Loose, Increase loose Number and decrease streak
            always.loss++;
            session.loss++;
            stats[current.playlist].loss++;
            always_gm[current.playlist].loss++;

            if (stats[current.playlist].streak > 0)
            {
                always.streak = -1;
                session.streak = -1;
                stats[current.playlist].streak = -1;
                always_gm[current.playlist].streak = -1;
            }
            else
            {
                always.streak--;
                session.streak--;
                stats[current.playlist].streak--;
                always_gm[current.playlist].streak--;
            }

            SetRefresh(1);
            WriteLoss();
        }

        WriteStreak();
        WriteConfig();

        // Reset myTeamNum security
        my_team_num = -1;

        if (rs_in_file && rs_file_boost)
            WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));

        gameWrapper->SetTimeout([&](GameWrapper *gameWrapper) { UpdateMMR(gameWrapper->GetUniqueID()); }, 3.0F);

        cvarManager->log("===== !GameEnd =====");
    }
}

void RocketStats::GameDestroyed(std::string eventName)
{
    cvarManager->log("===== GameDestroyed =====");

    // Check if Game Ended, if not, RAGE QUIT or disconnect
    if (is_game_started == true && is_game_ended == false)
    {
        always.loss++;
        session.loss++;
        stats[current.playlist].loss++;
        always_gm[current.playlist].loss++;

        if (stats[current.playlist].streak > 0)
        {
            always.streak = 0;
            session.streak = 0;
            stats[current.playlist].streak = -1;
            always_gm[current.playlist].streak = -1;
        }
        else
        {
            always.streak--;
            session.streak--;
            stats[current.playlist].streak--;
            always_gm[current.playlist].streak--;
        }

        WriteStreak();
        WriteLoss();
        WriteConfig();
    }

    is_game_ended = true;
    is_game_started = false;
    if (rs_in_file && rs_file_boost)
        WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));

    SetRefresh(1);
    cvarManager->log("===== !GameDestroyed =====");
}

int RocketStats::GetGameTime()
{
    ServerWrapper server = gameWrapper->GetGameEventAsServer();

    if (!is_in_game)
    {
        server = gameWrapper->GetOnlineGame();

        if (is_offline_game)
            return -1;
        else if (server.IsNull())
            return -1;

        return server.GetSecondsRemaining();
    }
    else if (server.IsNull())
        return -1;

    return server.GetSecondsRemaining(); // max game time: GetGameTime, seconds elapsed: GetSecondsElapsed
}

TeamWrapper RocketStats::GetTeam(bool opposing)
{
    if (is_in_game)
    {
        ServerWrapper server = (is_online_game ? gameWrapper->GetOnlineGame() : gameWrapper->GetGameEventAsServer());

        if (!server.IsNull())
        {
            ArrayWrapper<TeamWrapper> teams = server.GetTeams();
            PlayerControllerWrapper player = server.GetLocalPrimaryPlayer();

            if (!teams.IsNull() && !player.IsNull())
            {
                #pragma warning( push )
                #pragma warning( disable : 4267 )
                for (TeamWrapper team : teams)
                #pragma warning( pop )
                {
                    if (opposing == (player.GetTeamNum2() != team.GetTeamNum2()))
                        return team;
                }
            }
        }
    }
}

ImColor RocketStats::GetTeamColor(TeamWrapper team)
{
    if (!team.IsNull())
    {
        LinearColor color = team.GetCurrentColorList().Get(0);
        return ImColor{ (color.R / 255.f), (color.G / 255.f), (color.B / 255.f) };
    }
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
        if (demo && current.playlist)
        {
            ++session.demo;
            ++stats[current.playlist].demo;
            ++always_gm[current.playlist].demo;
            SetRefresh(1);

            if (rs_file_demo)
                WriteInFile("RocketStats_Demolition.txt", std::to_string(0));
        }

        bool death = isPrimaryPlayer(victim);
        if (death && current.playlist)
        {
            ++session.death;
            ++stats[current.playlist].death;
            ++always_gm[current.playlist].death;
            SetRefresh(1);

            if (rs_file_death)
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

        always.MMRChange += MMRChange;
        stats[current.playlist].MMRChange = MMRChange;
        always_gm[current.playlist].MMRChange = MMRChange;

        always.MMRCumulChange += MMRChange;
        for (auto it = playlist_name.begin(); it != playlist_name.end(); it++)
        {
            stats[it->first].MMRCumulChange += MMRChange;
            always_gm[it->first].MMRCumulChange += MMRChange;
        }
    }
    else
        stats[current.playlist].isInit = true;

    always.myMMR = mmr;
    session.myMMR = mmr;
    stats[current.playlist].myMMR = mmr;
    always_gm[current.playlist].myMMR = mmr;

    MajRank(mmrw.IsRanked(current.playlist), stats[current.playlist].myMMR, playerRank);
    SessionStats();
    WriteMMR();
    WriteMMRChange();
    WriteMMRCumulChange();

    SetRefresh(1);
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

    for (auto it = playlist_name.begin(); it != playlist_name.end(); it++)
    {
        tmp.MMRChange += stats[it->first].MMRChange;
        tmp.MMRCumulChange += stats[it->first].MMRChange;
        tmp.win += stats[it->first].win;
        tmp.loss += stats[it->first].loss;
        tmp.demo += stats[it->first].demo;
        tmp.death += stats[it->first].death;
    }

    session.myMMR = stats[current.playlist].myMMR;
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

    SetRefresh(1);
}

void RocketStats::ResetStats()
{
    InitStats();

    WriteConfig();
    ResetFiles();

    InitRank();
    SetRefresh(1);
}
#pragma endregion

#pragma region BoostMgmt
void RocketStats::OnBoostStart(std::string eventName)
{
    // Check if boost enabled in options
    if (!rs_file_boost || gameWrapper->IsInReplay() || is_boosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        // Check that the boosting car is ours
        if (!bWrap.IsNull() && bWrap.GetbActive() == 1 && !is_boosting)
        {
            is_boosting = true;
            SetRefresh(1);
            if (rs_in_file)
                WriteInFile("RocketStats_BoostState.txt", std::to_string(1));
        }
    }
}

void RocketStats::OnBoostEnd(std::string eventName)
{
    // Check if boost enabled in options
    if (!rs_file_boost || gameWrapper->IsInReplay() || !is_boosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        // Check that the boosting car is ours
        if (!bWrap.IsNull() && bWrap.GetbActive() == 0 && is_boosting)
        {
            is_boosting = false;
            SetRefresh(1);
            if (rs_in_file)
                WriteInFile("RocketStats_BoostState.txt", std::to_string(0));
        }
    }
}

int RocketStats::GetBoostAmount()
{
    CarWrapper me = gameWrapper->GetLocalCar();
    if (me.IsNull())
        return -1;

    BoostWrapper boost = me.GetBoostComponent();
    if (boost.IsNull())
        return -1;

    return int(boost.GetCurrentBoostAmount() * 100.f);
}

// Act as toggle
// void RocketStats::StopBoost() {}
#pragma endregion

#pragma region Rank / Div
void RocketStats::InitRank()
{
    int tier = current.tier;
    int playlist = current.playlist;

    current = t_current();

    last_rank = "norank";
    current.tier = tier;
    current.playlist = playlist;
}

void RocketStats::MajRank(bool isRanked, float _currentMMR, SkillRank playerRank)
{
    current.tier = playerRank.Tier;

    if (isRanked)
    {
        if (current.playlist != 34 && playerRank.MatchesPlayed < 10)
        {
            current.rank = "Placement: " + std::to_string(playerRank.MatchesPlayed) + "/10";
            current.division = "";
        }
        else
        {
            current.rank = GetRank(playerRank.Tier);
            current.division = "Div. " + std::to_string(playerRank.Division + 1);

            if (rs_file_div)
                WriteInFile("RocketStats_Div.txt", current.division);
        }

        if (rs_file_rank && current.rank != last_rank)
            WriteInFile("RocketStats_Rank.txt", current.rank);
    }
    else
    {
        current.rank = GetPlaylistName(current.playlist);
        current.division = "";

        if (rs_file_rank)
            WriteInFile("RocketStats_Rank.txt", current.rank);
    }

    SetRefresh(1);
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
                    std::string font_dest = ("../RocketStats/" + font_path);

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

            if (themes_values[theme_render.name].is_object())
            {
                if (themes_values[theme_render.name]["position"].is_array() && themes_values[theme_render.name]["position"].size() == 2)
                {
                    if (themes_values[theme_render.name]["position"][0].is_number())
                        rs_x = float(themes_values[theme_render.name]["position"][0]);

                    if (themes_values[theme_render.name]["position"][1].is_number())
                        rs_y = float(themes_values[theme_render.name]["position"][1]);
                }
                if (themes_values[theme_render.name]["scale"].is_number())
                    rs_scale = std::min(10.f, std::max(0.001f, float(themes_values[theme_render.name]["scale"])));
                if (themes_values[theme_render.name]["rotate"].is_number())
                    rs_rotate = std::min(180.f, std::max(-180.f, float(themes_values[theme_render.name]["rotate"])));
                if (themes_values[theme_render.name]["opacity"].is_number())
                    rs_opacity = std::min(1.f, std::max(0.f, float(themes_values[theme_render.name]["opacity"])));
            }

            cvarManager->log("Theme changed: " + theme.name + " (old: " + theme_render.name + ")");
            rs_theme = idx;
            SetRefresh(2);
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
    return (rs_theme == idx);
}

void RocketStats::SetTheme(std::string name)
{
    // Search the index of a theme with its name (changes current theme if found)
    for (int i = 0; i < themes.size(); ++i)
    {
        if (themes.at(i).name == name)
        {
            cvarManager->log("SetTheme: [" + std::to_string(i) + "] " + name);

            rs_theme = i;
            break;
        }
    }
}

void RocketStats::SetRefresh(unsigned char value)
{
    if (theme_refresh < value)
        theme_refresh = value;
}

void RocketStats::RefreshTheme(std::string old, CVarWrapper now)
{
    SetRefresh(1);
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
                    if (element.contains("sign") && element["sign"] == key && value != theme_hide_value)
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

                if (element.contains("transform") && element["transform"].is_string())
                {
                    std::string transform = element["transform"];
                    if (transform == "lower")
                        calculated.value = Utils::tolower(calculated.value);
                    else if (transform == "upper")
                        calculated.value = Utils::toupper(calculated.value);
                    else if (transform == "capitalize")
                        calculated.value = Utils::capitalize(calculated.value);
                }

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
                const float radius = float(element["radius"].is_string() ? Utils::EvaluateExpression(element["radius"], options.width) : int(element["radius"]));

                element_size.x = (radius * options.scale);
                element_size.y = float(element.contains("segments") ? int(element["segments"]) : 0);
            }
            else if (element["type"] == "pie_chart")
            {
                const float radius = float(element["radius"].is_string() ? Utils::EvaluateExpression(element["radius"], options.width) : int(element["radius"]));
                const float item_arc_span = (float(M_PI) * 2);
                const float angle_min = ((element.contains("angle-min") ? float(element["angle-min"]) : 0.f) - 90.f);
                const float angle_max = ((element.contains("angle-max") ? float(element["angle-max"]) : 0.f) - 90.f);
                const float radian_min = ((angle_min / 360.f) * item_arc_span);
                const float radian_max = ((angle_max / 360.f) * item_arc_span);

                element_size.x = (radius * options.scale);
                element_size.y = float(element.contains("segments") ? int(element["segments"]) : 0);

                positions.push_back(ImVec2{ radian_min, radian_max });

                if (element.contains("stroke"))
                {
                    positions.push_back(ImVec2{
                        (element_pos.x + ((element_size.x * cos(radian_min)))),
                        (element_pos.y + ((element_size.x * sin(radian_min))))
                    });
                }
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
                    theme_images[calculated.value] = rank[(!rs_hide_rank && current.tier < rank_nb) ? current.tier : 0].image;
                }
                else if (!theme_images[calculated.value])
                {
                    // Get the requested image
                    element_size = { 0, 0 };
                    std::string image_path = "RocketStats_themes/" + themes.at(rs_theme).name + "/images/" + calculated.value;

                    cvarManager->log("load image: " + image_path);
                    theme_images[calculated.value] = LoadImg(image_path);
                }

                // Calculate the image only if it is loaded (request for recalculation later if needed)
                if (theme_images[calculated.value]->GetImGuiTex() != nullptr)
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
            else if (element.type == "pie_chart")
            {
                drawlist->PathLineTo(element.positions.at(0));
                drawlist->PathArcTo(element.positions.at(0), element.size.x, element.positions.at(1).x, element.positions.at(1).y, int(element.size.y));
                drawlist->PathFillConvex(element.fill.color);
            }
        }

        if (element.stroke.enable)
        {
            if (element.type == "triangle")
                drawlist->AddTriangle(element.positions.at(0), element.positions.at(1), element.positions.at(2), element.stroke.color, element.scale);
            else if (element.type == "rectangle")
                drawlist->AddRect(element.positions.at(0), element.positions.at(1), element.stroke.color, element.size.x, ImDrawCornerFlags_All, element.scale);
            else if (element.type == "circle")
                drawlist->AddCircle(element.positions.at(0), element.size.x, element.stroke.color, int(element.size.y ? element.size.y : 12), element.scale);
            else if (element.type == "pie_chart")
            {
                drawlist->PathLineTo(element.positions.at(2));
                drawlist->PathArcTo(element.positions.at(0), element.size.x, element.positions.at(1).x, element.positions.at(1).y, int(element.size.y));
                drawlist->PathStroke(element.stroke.color, false, element.scale);
            }
        }

        if (element.type == "image")
        {
            std::shared_ptr<ImageWrapper> image = theme_images[element.value];
            if (image != nullptr && image->GetImGuiTex() != nullptr && element.size.x && element.size.y)
                drawlist->AddImage(image->GetImGuiTex(), element.positions.at(0), element.size, ImVec2{ 0, 0 }, ImVec2{ 1, 1 }, element.color.color);
            else
                SetRefresh(1);
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
        _return += "data/RocketStats/" + _path;

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
                if (config["settings"].is_object() && !config["settings"].is_null())
                {
                    if (config["settings"]["mode"].is_number_unsigned())
                        rs_mode = config["settings"]["mode"];

                    if (config["settings"]["theme"].is_string())
                        SetTheme(config["settings"]["theme"]);

                    if (config["settings"]["themes"].is_object() && !config["settings"]["themes"].is_null())
                        themes_values = config["settings"]["themes"];

                    if (config["settings"]["overlay"].is_boolean())
                        rs_disp_overlay = config["settings"]["overlay"];

                    if (config["settings"]["inmenu"].is_boolean())
                        rs_enable_inmenu = config["settings"]["inmenu"];
                    if (config["settings"]["ingame"].is_boolean())
                        rs_enable_ingame = config["settings"]["ingame"];
                    if (config["settings"]["float"].is_boolean())
                        rs_enable_float = config["settings"]["float"];

                    if (config["settings"]["files"].is_object() && !config["settings"]["files"].is_null())
                    {
                        if (config["settings"]["files"]["on"].is_boolean())
                            rs_in_file = config["settings"]["files"]["on"];
                        if (config["settings"]["files"]["gm"].is_boolean())
                            rs_hide_gm = config["settings"]["files"]["gm"];
                        if (config["settings"]["files"]["rank"].is_boolean())
                            rs_hide_rank = config["settings"]["files"]["rank"];
                        if (config["settings"]["files"]["div"].is_boolean())
                            rs_hide_div = config["settings"]["files"]["div"];
                        if (config["settings"]["files"]["mmr"].is_boolean())
                            rs_hide_mmr = config["settings"]["files"]["mmr"];
                        if (config["settings"]["files"]["mmrc"].is_boolean())
                            rs_hide_mmrc = config["settings"]["files"]["mmrc"];
                        if (config["settings"]["files"]["mmrcc"].is_boolean())
                            rs_hide_mmrcc = config["settings"]["files"]["mmrcc"];
                        if (config["settings"]["files"]["win"].is_boolean())
                            rs_hide_win = config["settings"]["files"]["win"];
                        if (config["settings"]["files"]["loss"].is_boolean())
                            rs_hide_loss = config["settings"]["files"]["loss"];
                        if (config["settings"]["files"]["streak"].is_boolean())
                            rs_hide_streak = config["settings"]["files"]["streak"];
                        if (config["settings"]["files"]["demo"].is_boolean())
                            rs_hide_demo = config["settings"]["files"]["demo"];
                        if (config["settings"]["files"]["death"].is_boolean())
                            rs_hide_death = config["settings"]["files"]["death"];
                        if (config["settings"]["files"]["boost"].is_boolean())
                            rs_file_boost = config["settings"]["files"]["boost"];
                    }

                    if (config["settings"]["hides"].is_object() && !config["settings"]["hides"].is_null())
                    {
                        if (config["settings"]["hides"]["gm"].is_boolean())
                            rs_hide_gm = config["settings"]["hides"]["gm"];
                        if (config["settings"]["hides"]["rank"].is_boolean())
                            rs_hide_rank = config["settings"]["hides"]["rank"];
                        if (config["settings"]["hides"]["div"].is_boolean())
                            rs_hide_div = config["settings"]["hides"]["div"];
                        if (config["settings"]["hides"]["mmr"].is_boolean())
                            rs_hide_mmr = config["settings"]["hides"]["mmr"];
                        if (config["settings"]["hides"]["mmrc"].is_boolean())
                            rs_hide_mmrc = config["settings"]["hides"]["mmrc"];
                        if (config["settings"]["hides"]["mmrcc"].is_boolean())
                            rs_hide_mmrcc = config["settings"]["hides"]["mmrcc"];
                        if (config["settings"]["hides"]["win"].is_boolean())
                            rs_hide_win = config["settings"]["hides"]["win"];
                        if (config["settings"]["hides"]["loss"].is_boolean())
                            rs_hide_loss = config["settings"]["hides"]["loss"];
                        if (config["settings"]["hides"]["streak"].is_boolean())
                            rs_hide_streak = config["settings"]["hides"]["streak"];
                        if (config["settings"]["hides"]["demo"].is_boolean())
                            rs_hide_demo = config["settings"]["hides"]["demo"];
                        if (config["settings"]["hides"]["death"].is_boolean())
                            rs_hide_death = config["settings"]["hides"]["death"];

                        cvarManager->log("Config: hides loaded");
                    }
                    if (config["settings"]["replace_mmr"].is_boolean())
                        rs_replace_mmr = config["settings"]["replace_mmr"];
                    if (config["settings"]["replace_mmrc"].is_boolean())
                        rs_replace_mmrc = config["settings"]["replace_mmrc"];

                    cvarManager->log("Config: settings loaded");
                }

                if (config["always"].is_object() && !config["always"].is_null())
                {
                    if (config["always"]["MMRCumulChange"].is_number())
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

                if (config["always_gm_idx"].is_number_unsigned() && int(config["always_gm_idx"]) < playlist_name.size())
                    current.playlist = config["always_gm_idx"];

                if (config["always_gm"].is_array())
                {
                    for (int i = 0; i < config["always_gm"].size() && i < playlist_name.size(); ++i)
                    {
                        if (config["always_gm"][i].is_object() && !config["always_gm"][i].is_null())
                        {
                            if (config["always_gm"][i]["MMRCumulChange"].is_number())
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

                SetRefresh(1);
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
    tmp["settings"]["mode"] = rs_mode;
    tmp["settings"]["theme"] = theme_render.name;
    tmp["settings"]["overlay"] = rs_disp_overlay;
    tmp["settings"]["inmeny"] = rs_enable_inmenu;
    tmp["settings"]["ingame"] = rs_enable_ingame;
    tmp["settings"]["float"] = rs_enable_float;

    // Save only existing themes
    tmp["settings"]["themes"] = {};
    for (int i = 0; i < themes.size(); ++i)
    {
        std::string name = themes.at(i).name;
        if (themes_values[name].is_object())
            tmp["settings"]["themes"][name] = themes_values[name];
    }

    tmp["settings"]["files"] = {};
    tmp["settings"]["files"]["on"] = rs_in_file;
    tmp["settings"]["files"]["gm"] = rs_file_gm;
    tmp["settings"]["files"]["rank"] = rs_file_rank;
    tmp["settings"]["files"]["div"] = rs_file_div;
    tmp["settings"]["files"]["mmr"] = rs_file_mmr;
    tmp["settings"]["files"]["mmr"] = rs_file_mmr;
    tmp["settings"]["files"]["mmrc"] = rs_file_mmrc;
    tmp["settings"]["files"]["mmrcc"] = rs_file_mmrcc;
    tmp["settings"]["files"]["win"] = rs_file_win;
    tmp["settings"]["files"]["loss"] = rs_file_loss;
    tmp["settings"]["files"]["streak"] = rs_file_streak;
    tmp["settings"]["files"]["demo"] = rs_file_demo;
    tmp["settings"]["files"]["death"] = rs_file_death;
    tmp["settings"]["files"]["boost"] = rs_file_boost;

    tmp["settings"]["hides"] = {};
    tmp["settings"]["hides"]["gm"] = rs_hide_gm;
    tmp["settings"]["hides"]["rank"] = rs_hide_rank;
    tmp["settings"]["hides"]["div"] = rs_hide_div;
    tmp["settings"]["hides"]["mmr"] = rs_hide_mmr;
    tmp["settings"]["hides"]["mmrc"] = rs_hide_mmrc;
    tmp["settings"]["hides"]["mmrcc"] = rs_hide_mmrcc;
    tmp["settings"]["hides"]["win"] = rs_hide_win;
    tmp["settings"]["hides"]["loss"] = rs_hide_loss;
    tmp["settings"]["hides"]["streak"] = rs_hide_streak;
    tmp["settings"]["hides"]["demo"] = rs_hide_demo;
    tmp["settings"]["hides"]["death"] = rs_hide_death;
    tmp["settings"]["replace_mmr"] = rs_replace_mmr;
    tmp["settings"]["replace_mmrc"] = rs_replace_mmrc;

    tmp["always"] = {};
    tmp["always"]["MMRCumulChange"] = always.MMRCumulChange;
    tmp["always"]["Win"] = always.win;
    tmp["always"]["Loss"] = always.loss;
    tmp["always"]["Streak"] = always.streak;
    tmp["always"]["Demo"] = always.demo;
    tmp["always"]["Death"] = always.death;

    tmp["always_gm_idx"] = current.playlist;
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
    if (rs_in_file && rs_file_gm)
        WriteInFile("RocketStats_GameMode.txt", GetPlaylistName(current.playlist));
}

void RocketStats::WriteRank()
{
    if (rs_in_file && rs_file_rank)
        WriteInFile("RocketStats_Div.txt", current.rank);
}

void RocketStats::WriteDiv()
{
    if (rs_in_file && rs_file_div)
        WriteInFile("RocketStats_Div.txt", current.division);
}

void RocketStats::WriteMMR()
{
    if (!rs_in_file || !rs_file_mmr)
        return;

    std::string tmp = Utils::FloatFixer(stats[current.playlist].myMMR, (rs_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMR.txt", tmp);
}

void RocketStats::WriteMMRChange()
{
    if (!rs_in_file || !rs_file_mmrc)
        return;

    Stats tstats = GetStats();
    std::string tmp = Utils::FloatFixer(tstats.MMRChange, (rs_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRChange.txt", (((tstats.MMRChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteMMRCumulChange()
{
    if (!rs_in_file || !rs_file_mmrcc)
        return;

    Stats tstats = GetStats();
    std::string tmp = Utils::FloatFixer(tstats.MMRCumulChange, (rs_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRCumulChange.txt", (((tstats.MMRCumulChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteWin()
{
    if (rs_in_file && rs_file_win)
        WriteInFile("RocketStats_Win.txt", std::to_string(GetStats().win));
}

void RocketStats::WriteLoss()
{
    if (rs_in_file && rs_file_loss)
        WriteInFile("RocketStats_Loss.txt", std::to_string(GetStats().loss));
}

void RocketStats::WriteStreak()
{
    if (!rs_in_file || !rs_file_streak)
        return;

    Stats tstats = GetStats();
    std::string tmp = std::to_string(tstats.streak);

    WriteInFile("RocketStats_Streak.txt", (((tstats.streak > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteDemo()
{
    if (rs_in_file && rs_file_demo)
        WriteInFile("RocketStats_Demo.txt", std::to_string(GetStats().demo));
}

void RocketStats::WriteDeath()
{
    if (rs_in_file && rs_file_death)
        WriteInFile("RocketStats_Death.txt", std::to_string(GetStats().death));
}

void RocketStats::WriteBoost()
{
    if (rs_in_file && rs_file_gm)
        WriteInFile("RocketStats_BoostState.txt", std::to_string(gameWrapper->IsInGame() ? 0 : -1));
}
#pragma endregion

#pragma region PluginWindow
void RocketStats::Render()
{
    is_online_game = gameWrapper->IsInOnlineGame();
    is_offline_game = gameWrapper->IsInGame();
    is_in_replay = gameWrapper->IsInReplay();
    is_in_game = (is_online_game || is_offline_game);
    is_in_pause = (is_in_game && gameWrapper->IsCursorVisible());

    RenderOverlay();
    RenderIcon();

    if (!overlay_move && settings_open)
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

    // Displays the button allowing the display and the hiding of the menu
    if (!overlay_move && (!is_in_game || is_in_pause))
    {
        float margin = 20.f;
        float icon_size = (42.f * rs_screen_scale[0]);
        float icon_scale = (1.f - rs_screen_scale[0]);
        ImVec2 screen_size = ImGui::GetIO().DisplaySize;
        ImVec2 icon_pos = { 0.f, (screen_size.y * 0.459f * (icon_scale + (icon_scale * (0.18f - (1.f - rs_screen_scale[1]))) + 1.f))};
        LPPOINT mouse_pos = new tagPOINT;
        bool mouse_click = GetAsyncKeyState(VK_LBUTTON);
        ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

        GetCursorPos(mouse_pos);

        bool hover = (mouse_pos->x > (icon_pos.x - icon_size - margin) && mouse_pos->x < (icon_pos.x + icon_size + margin));
        hover = (hover && (mouse_pos->y > (icon_pos.y - icon_size - margin) && mouse_pos->y < (icon_pos.y + icon_size + margin)));

        rs_logo_rotate += (rs_logo_mouv ? 0.15f : -0.15f);
        if (rs_logo_rotate < 0 || rs_logo_rotate >= 30.f)
            rs_logo_mouv = !rs_logo_mouv;

        Vector2F image_size = rs_logo->GetSizeF();
        float rotate = ((90.f - rs_logo_rotate) * (float(M_PI) / 180.f));
        ImRotateStart(drawlist);
        drawlist->AddImage(rs_logo->GetImGuiTex(), { icon_pos.x - icon_size, icon_pos.y - icon_size }, { icon_pos.x + icon_size, icon_pos.y + icon_size }, { 0, 0 }, { 1, 1 }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, rs_launch }));
        ImRotateEnd(rotate);

        // When hovering over the button area
        if (hover)
        {
            ImGui::SetTooltip("Show RocketStats menu");

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
    bool show_overlay = ((rs_enable_ingame && is_in_game) || (rs_enable_inmenu && !is_in_game));
    if (!rs_disp_overlay || !show_overlay)
        return;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin(menu_title.c_str(), (bool*)1, (ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoFocusOnAppearing));

    try
    {
        // Calculation each element of the theme (only during a modification)
        if (overlay_move || theme_refresh || theme_render.name == "" || (themes.size() > rs_theme && theme_render.name != themes.at(rs_theme).name))
        {
            Stats tstats = GetStats();
            ImVec2 screen_size = ImGui::GetIO().DisplaySize;

            // Refresh all images
            if (theme_refresh == 2)
            {
                theme_images.clear();
                cvarManager->log("refresh all images");
            }

            // Reset the menu variables if you change the theme
            if (theme_prev != theme_render.name)
            {
                if (!GetCVar("rs_x", rs_x))
                {
                    rs_x = 0.f;
                    if (theme_config["x"].is_number())
                        rs_x = float(theme_config["x"]);
                }

                if (!GetCVar("rs_y", rs_y))
                {
                    rs_y = 0.f;
                    if (theme_config["y"].is_number())
                        rs_y = float(theme_config["y"]);
                }

                if (!GetCVar("rs_scale", rs_scale))
                {
                    rs_scale = 1.f;
                    if (theme_config["scale"].is_number())
                        rs_scale = float(theme_config["scale"]);
                }

                if (!GetCVar("rs_rotate", rs_rotate))
                {
                    rs_rotate = 0.f;
                    if (theme_config["rotate"].is_number())
                        rs_rotate = float(theme_config["rotate"]);
                }

                if (!GetCVar("rs_opacity", rs_opacity))
                {
                    rs_opacity = 1.f;
                    if (theme_config["opacity"].is_number())
                        rs_opacity = float(theme_config["opacity"]);
                }
            }
            theme_prev = theme_render.name;

            // Checks if there is a rotation to apply and converts degrees to radians
            rs_rotate_enabled = (theme_config["rotate"].is_number() && (rs_rotate + float(theme_config["rotate"])));
            if (rs_rotate)
            {
                rs_rotate_enabled = true;
                rs_crotate = ((90.f - rs_rotate) * (float(M_PI) / 180.f));
            }
            else if (rs_rotate_enabled)
                rs_crotate = ((90.f - rs_rotate + float(theme_config["rotate"])) * (float(M_PI) / 180.f));

            // Different global options used when calculating elements
            std::vector<struct Element> elements;
            Options options = {
                int(rs_x * screen_size.x),
                int(rs_y * screen_size.y),
                (theme_config.contains("width") ? int(theme_config["width"]) : 0),
                (theme_config.contains("height") ? int(theme_config["height"]) : 0),
                (rs_scale * (theme_config.contains("scale") ? float(theme_config["scale"]) : 1.f)),
                (rs_launch * rs_opacity * (theme_config.contains("opacity") ? float(theme_config["opacity"]) : 1.f))
            };

            // Change the position of the overlay when moving with the mouse
            if (overlay_move)
            {
                options.x = int(overlay_cursor.x);
                options.y = int(overlay_cursor.y);
            }

            // Creation of the different variables used in Text elements
            const size_t floating_length = (rs_enable_float ? 2 : 0);

            theme_vars["GameMode"] = (rs_hide_gm ? theme_hide_value : GetPlaylistName(current.playlist));
            theme_vars["Rank"] = (rs_hide_rank ? theme_hide_value : current.rank);
            theme_vars["Div"] = (rs_hide_div ? theme_hide_value : current.division);
            theme_vars["MMR"] = (rs_hide_mmr ? theme_hide_value : Utils::FloatFixer(tstats.myMMR, floating_length)); // Utils::PointFixer(current.myMMR, 6, floating_length)
            theme_vars["MMRChange"] = (rs_hide_mmrc ? theme_hide_value : Utils::FloatFixer(tstats.MMRChange, floating_length)); // Utils::PointFixer(current.MMRChange, 6, floating_length)
            theme_vars["MMRCumulChange"] = (rs_hide_mmrcc ? theme_hide_value : Utils::FloatFixer(tstats.MMRCumulChange, floating_length)); // Utils::PointFixer(current.MMRCumulChange, 6, floating_length)
            theme_vars["Win"] = (rs_hide_win ? theme_hide_value : std::to_string(tstats.win));
            theme_vars["Loss"] = (rs_hide_loss ? theme_hide_value : std::to_string(tstats.loss));
            theme_vars["Streak"] = (rs_hide_streak ? theme_hide_value : std::to_string(tstats.streak));
            theme_vars["Demolition"] = (rs_hide_demo ? theme_hide_value : std::to_string(tstats.demo));
            theme_vars["Death"] = (rs_hide_death ? theme_hide_value : std::to_string(tstats.death));

            Utils::ReplaceAll(theme_vars["Rank"], "_", " ");

            // Replace MMR with MMRChange
            std::string mmr = theme_vars["MMR"];
            if (rs_replace_mmr)
                theme_vars["MMR"] = theme_vars["MMRChange"];
            if (rs_replace_mmrc)
                theme_vars["MMRChange"] = mmr;

            // Calculation of each element composing the theme
            rs_drawlist->Clear(); // Clear the array of vertices for the next step
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

        if (theme_render.elements.size())
        {
            ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

            if (!theme_refresh && rs_drawlist->VtxBuffer.Size)
            {
                // Fill the DrawList with previously generated vertices
                drawlist->CmdBuffer = rs_drawlist->CmdBuffer;
                drawlist->IdxBuffer = rs_drawlist->IdxBuffer;
                drawlist->VtxBuffer = rs_drawlist->VtxBuffer;

                drawlist->Flags = rs_drawlist->Flags;
                drawlist->_VtxCurrentIdx = drawlist->VtxBuffer.Size;
                drawlist->_VtxWritePtr = drawlist->VtxBuffer.end();
                drawlist->_IdxWritePtr = drawlist->IdxBuffer.end();
            }
            else
            {
                // Generates the vertices of each element
                int start = drawlist->VtxBuffer.Size;
                if (rs_rotate_enabled)
                    start = ImRotateStart(drawlist);

                for (auto& element : theme_render.elements)
                    RenderElement(drawlist, element);

                if (rs_rotate_enabled)
                    ImRotateEnd(rs_crotate, start, drawlist, ImRotationCenter(start, drawlist));

                // Stores generated vertices for future frames
                rs_drawlist->Clear();
                rs_drawlist = drawlist->CloneOutput();
            }

            // Displays a square and allows the movement of the overlay with the mouse
            if (settings_open)
            {
                float margin = 10.f;
                float rect_size = 10.f;
                LPPOINT mouse_pos = new tagPOINT;
                bool mouse_click = GetAsyncKeyState(VK_LBUTTON);
                ImVec2 screen_size = ImGui::GetIO().DisplaySize;
                ImVec2 overlay_pos = { (rs_x * screen_size.x), (rs_y * screen_size.y) };
                ImVec2 rect_pos = { overlay_pos.x, overlay_pos.y };

                GetCursorPos(mouse_pos);
                bool hover = (mouse_pos->x > (overlay_pos.x - rect_size - (margin * 2)) && mouse_pos->x < (overlay_pos.x + rect_size + (margin * 2)));
                hover = (hover && (mouse_pos->y > (overlay_pos.y - rect_size - (margin * 2)) && mouse_pos->y < (overlay_pos.y + rect_size + (margin * 2))));

                // If we hover over the area of the square or if we are moving it
                if (hover || overlay_move)
                {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

                    // Moves the overlay when you hold down the mouse click
                    if (mouse_click)
                    {
                        if (!overlay_move)
                        {
                            overlay_move = true;
                            overlay_origin = { float(mouse_pos->x), float(mouse_pos->y) };
                        }

                        overlay_cursor = { float(mouse_pos->x), float(mouse_pos->y) };
                        rect_pos = overlay_cursor;
                    }
                    else
                    {
                        // Change positions when mouse click is released
                        if (overlay_move)
                        {
                            rs_x = (overlay_cursor.x / screen_size.x);
                            rs_y = (overlay_cursor.y / screen_size.y);

                            overlay_move = false;
                            SetRefresh(1);
                        }
                        else
                            ImGui::SetTooltip("Click to move the overlay using the mouse");
                    }
                }

                drawlist->AddRectFilled({ (rect_pos.x - rect_size), (rect_pos.y - rect_size) }, { (rect_pos.x + rect_size), (rect_pos.y + rect_size) }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 0.5f }), 4.f, ImDrawCornerFlags_All);
                drawlist->AddRect({ (rect_pos.x - rect_size), (rect_pos.y - rect_size) }, { (rect_pos.x + rect_size), (rect_pos.y + rect_size) }, ImGui::ColorConvertFloat4ToU32({ 0.f, 0.f, 0.f, 0.5f }), 4.f, ImDrawCornerFlags_All, 2.f);
            }
            else
                overlay_move = false;
        }

        // Allows spawn transition
        if (rs_launch < 1.f)
        {
            rs_launch += 0.05f;
            SetRefresh(1);
        }
    }
    catch (const std::exception& err)
    {
        theme_refresh = 0;
        rs_drawlist->Clear();
        cvarManager->log("Error: " + std::string(err.what()));
    }

    ImGui::End();
}

void RocketStats::RenderSettings()
{
    ImVec2 settings_size = { 750, 0 };

    CVarWrapper cvar_x = cvarManager->getCvar("rs_x");
    CVarWrapper cvar_y = cvarManager->getCvar("rs_y");
    CVarWrapper cvar_scale = cvarManager->getCvar("rs_scale");
    CVarWrapper cvar_rotate = cvarManager->getCvar("rs_rotate");
    CVarWrapper cvar_opacity = cvarManager->getCvar("rs_opacity");

    ImGui::SetNextWindowPos(ImVec2{ 128, 256 }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(settings_size);

    ImGui::Begin((menu_title + "##Settings").c_str(), nullptr, (ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse));

    // Show menu only if menu image is loaded
    if (rs_logo != nullptr && rs_title != nullptr && rs_logo->IsLoadedForImGui() && rs_title->IsLoadedForImGui())
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
        std::string obs = "To view the in-game overlay on OBS, check \"Capture third-party overlays\" in the game capture.";
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
        ImGui::Checkbox("##in_file", &rs_in_file);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Updates RocketStats files with game information (usable in OBS)");

        ImGui::SetCursorPos({ 63, 54 });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(cvarManager->getCvar("rs_in_file").getDescription()).c_str());

        ImGui::SetWindowFontScale(1.3f);
        ImGui::SetCursorPos({ 355, 43 });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, cvarManager->getCvar("rs_mode").getDescription().c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ 295, 68 });
        ImGui::SetNextItemWidth(142);
        if (ImGui::BeginCombo("##modes_combo", modes.at(rs_mode).c_str(), ImGuiComboFlags_NoArrowButton))
        {
            int Trs_mode = rs_mode;
            for (int i = 0; i < modes.size(); ++i)
            {
                bool is_selected = (Trs_mode == i);
                if (ImGui::Selectable(modes.at(i).c_str(), is_selected))
                    rs_mode = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Restrict information to current game or keep longer");
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##modes_left", ImGuiDir_Left) && rs_mode > 0)
            --rs_mode;
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##modes_right", ImGuiDir_Right) && rs_mode < (modes.size() - 1))
            ++rs_mode;

        ImGui::SetWindowFontScale(1.3f);
        ImGui::SetCursorPos({ 585, 43 });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, cvarManager->getCvar("rs_theme").getDescription().c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ 525, 68 });
        ImGui::SetNextItemWidth(142);
        if (ImGui::BeginCombo("##themes_combo", theme_render.name.c_str(), ImGuiComboFlags_NoArrowButton))
        {
            int Trs_theme = rs_theme;
            for (int i = 0; i < themes.size(); ++i)
            {
                bool is_selected = (Trs_theme == i);
                if (ImGui::Selectable(themes.at(i).name.c_str(), is_selected))
                    rs_theme = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Themes available in RocketStats folders (fully customizable)");
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##themes_left", ImGuiDir_Left) && rs_theme > 0)
            --rs_theme;
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##themes_right", ImGuiDir_Right) && themes.size() && rs_theme < (themes.size() - 1))
            ++rs_theme;

        ImGui::SetCursorPos({ 103, 120 });
        if (ImGui::Button(cvar_x.getDescription().c_str(), { 65, 0 }))
            rs_x_edit = !rs_x_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the horizontal position of the overlay");
        ImGui::SetCursorPos({ 158, 120 });
        ImGui::SetNextItemWidth(rs_x_edit ? 170.f : 150.f);
        if (!rs_x_edit)
        {
            ImGui::SliderFloat("##x_position", &rs_x, 0.f, 1.f, "%.3f");
            ImGui::SetCursorPos({ 312, 120 });
            if (ImGui::Button("R##Rx_position"))
            {
                rs_x = 0.f;
                if (theme_config["x"].is_number())
                    rs_x = float(theme_config["x"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##x_position", &rs_x, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 421, 120 });
        if (ImGui::Button(cvar_y.getDescription().c_str(), { 65, 0 }))
            rs_y_edit = !rs_y_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the vertical position of the overlay");
        ImGui::SetCursorPos({ 476, 120 });
        ImGui::SetNextItemWidth(rs_y_edit ? 170.f : 150.f);
        if (!rs_y_edit)
        {
            ImGui::SliderFloat("##y_position", &rs_y, 0.f, 1.f, "%.3f");
            ImGui::SetCursorPos({ 630, 120 });
            if (ImGui::Button("R##Ry_position"))
            {
                rs_y = 0.f;
                if (theme_config["y"].is_number())
                    rs_y = float(theme_config["y"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##y_position", &rs_y, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 24, 165 });
        if (ImGui::Button(cvar_scale.getDescription().c_str(), { 65, 0 }))
            rs_scale_edit = !rs_scale_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the size of the overlay");
        ImGui::SetCursorPos({ 79, 165 });
        ImGui::SetNextItemWidth(rs_scale_edit ? 170.f : 150.f);
        if (!rs_scale_edit)
        {
            ImGui::SliderFloat("##scale", &rs_scale, cvar_scale.GetMinimum(), cvar_scale.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 233, 165 });
            if (ImGui::Button("R##Rscale"))
            {
                rs_scale = 1.f;
                if (theme_config["scale"].is_number())
                    rs_scale = float(theme_config["scale"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##scale", &rs_scale, 0.01f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 263, 165 });
        if (ImGui::Button(cvar_rotate.getDescription().c_str(), { 65, 0 }))
            rs_rotate_edit = !rs_rotate_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the rotation of the overlay");
        ImGui::SetCursorPos({ 318, 165 });
        ImGui::SetNextItemWidth(rs_rotate_edit ? 170.f : 150.f);
        if (!rs_rotate_edit)
        {
            ImGui::SliderFloat("##rotate", &rs_rotate, cvar_rotate.GetMinimum(), cvar_rotate.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 472, 165 });
            if (ImGui::Button("R##Rrotate"))
            {
                rs_rotate = 0.f;
                if (theme_config["rotate"].is_number())
                    rs_rotate = float(theme_config["rotate"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##rotate", &rs_rotate, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 502, 165 });
        if (ImGui::Button(cvar_opacity.getDescription().c_str(), { 65, 0 }))
            rs_opacity_edit = !rs_opacity_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the opacity of the overlay");
        ImGui::SetCursorPos({ 557, 165 });
        ImGui::SetNextItemWidth(rs_opacity_edit ? 170.f : 150.f);
        if (!rs_opacity_edit)
        {
            ImGui::SliderFloat("##opacity", &rs_opacity, cvar_opacity.GetMinimum(), cvar_opacity.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 711, 165 });
            if (ImGui::Button("R##Ropacity"))
            {
                rs_opacity = 1.f;
                if (theme_config["opacity"].is_number())
                    rs_opacity = float(theme_config["opacity"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##opacity", &rs_opacity, 0.001f, 0.1f, "%.3f");

        text_size = ImGui::CalcTextSize(obs.c_str());
        ImGui::SetCursorPos({ ((settings_size.x - text_size.x) / 2), 200});
        ImGui::TextColored(ImVec4{ 0.94f, 0.77f, 0.f, 1.f }, obs.c_str());

        ImGui::SetCursorPosY(228);
        ImGui::Separator();

        ImGui::SetCursorPos({ 0, 238 });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2) + image_pos.x, (image_size.Y / 2) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 23, 263 });
        ImGui::Checkbox("##overlay", &rs_disp_overlay);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Displays the overlay on the game screen");

        ImGui::SetCursorPos({ 63, 265 });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(cvarManager->getCvar("rs_disp_overlay").getDescription()).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (settings_size.x - 120), 241 });
        if (ImGui::Button("Open folder", { 110, 0 }))
            system(("powershell -WindowStyle Hidden \"start \"\"" + GetPath() + "\"\"\"").c_str());
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Access theme folders or files for OBS");
        ImGui::SetCursorPos({ (settings_size.x - 120), 266 });
        if (ImGui::Button("Reload Theme", { 88, 0 }))
        {
            LoadImgs();
            ChangeTheme(rs_theme);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Refresh current theme information (JSON and images)");
        ImGui::SetCursorPos({ (settings_size.x - 27), 266 });
        if (ImGui::Button("A", { 17, 0 }))
        {
            LoadImgs();
            LoadThemes();
            SetTheme(theme_render.name);
            ChangeTheme(rs_theme);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Reloads all the themes (adds or removes depending on the folders)");
        ImGui::SetCursorPos({ (settings_size.x - 120), 291 });
        if (ImGui::Button("Reset Stats", { 110, 0 }))
            ResetStats();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Resets all plugin information for all modes (MMR, Win, Loss, etc.)");

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 280, 258 });
        text_size = ImGui::CalcTextSize(theme_render.name.c_str());
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 1.f }, theme_render.name.c_str());
        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (285 + text_size.x), 265 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.5f }, (theme_render.version + (theme_render.date.size() ? (" - " + theme_render.date) : "")).c_str());
        ImGui::SetCursorPos({ 290, 282 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.8f }, ("Theme by " + theme_render.author).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ column_start, 328 });
        ImGui::BeginChild("##column1", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Checkbox(cvarManager->getCvar("rs_enable_inmenu").getDescription().c_str(), &rs_enable_inmenu);
        ImGui::Checkbox(cvarManager->getCvar("rs_enable_ingame").getDescription().c_str(), &rs_enable_ingame);
        ImGui::Checkbox(cvarManager->getCvar("rs_enable_float").getDescription().c_str(), &rs_enable_float);
        ImGui::Checkbox(cvarManager->getCvar("rs_replace_mmr").getDescription().c_str(), &rs_replace_mmr);
        ImGui::Checkbox(cvarManager->getCvar("rs_replace_mmrc").getDescription().c_str(), &rs_replace_mmrc);
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::SetCursorPosX(column_start + column_space + column_width);
        ImGui::BeginChild("##column2", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        if (!rs_in_file)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_gm").getDescription().c_str(), &rs_file_gm);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_rank").getDescription().c_str(), &rs_file_rank);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_div").getDescription().c_str(), &rs_file_div);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_mmr").getDescription().c_str(), &rs_file_mmr);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_mmrc").getDescription().c_str(), &rs_file_mmrc);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_mmrcc").getDescription().c_str(), &rs_file_mmrcc);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_win").getDescription().c_str(), &rs_file_win);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_loss").getDescription().c_str(), &rs_file_loss);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_streak").getDescription().c_str(), &rs_file_streak);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_demo").getDescription().c_str(), &rs_file_demo);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_death").getDescription().c_str(), &rs_file_death);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_boost").getDescription().c_str(), &rs_file_boost);
        if (!rs_in_file)
            ImGui::PopStyleVar();
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::SetCursorPosX(column_start + (column_space * 2) + (column_width * 2));
        ImGui::BeginChild("##column3", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_gm").getDescription().c_str(), &rs_hide_gm);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_rank").getDescription().c_str(), &rs_hide_rank);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_div").getDescription().c_str(), &rs_hide_div);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_mmr").getDescription().c_str(), &rs_hide_mmr);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_mmrc").getDescription().c_str(), &rs_hide_mmrc);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_mmrcc").getDescription().c_str(), &rs_hide_mmrcc);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_win").getDescription().c_str(), &rs_hide_win);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_loss").getDescription().c_str(), &rs_hide_loss);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_streak").getDescription().c_str(), &rs_hide_streak);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_demo").getDescription().c_str(), &rs_hide_demo);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_death").getDescription().c_str(), &rs_hide_death);
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
        text_size = ImGui::CalcTextSize(menu_version.c_str());
        ImGui::SameLine();
        ImGui::SetCursorPosX(settings_size.x - text_size.x - 7);
        ImGui::Text(menu_version.c_str());

        drawlist->PopClipRect();
    }
    else
    {
        ImGui::SetWindowFontScale(1.5f);
        ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Error - Check that this folder is present in BakkesMod: data/RocketStats");
        ImGui::SameLine();
        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPosX(settings_size.x - 80 - 7);
        if (ImGui::Button("Reload All", { 80, 0 }))
        {
            SetDefaultFolder();

            LoadImgs();
            LoadThemes();
            ChangeTheme(rs_theme);
            rs_logo = LoadImg("RocketStats_images/logo.png");
            rs_title = LoadImg("RocketStats_images/title.png");
        }
    }

    ImGui::End();

    // Delimits certain variables
    if (rs_x < cvar_x.GetMinimum())
        rs_x = cvar_x.GetMinimum();
    else if (rs_x > cvar_x.GetMaximum())
        rs_x = cvar_x.GetMaximum();

    if (rs_y < cvar_y.GetMinimum())
        rs_y = cvar_y.GetMinimum();
    else if (rs_y > cvar_y.GetMaximum())
        rs_y = cvar_y.GetMaximum();

    if (rs_scale < cvar_scale.GetMinimum())
        rs_scale = cvar_scale.GetMinimum();
    else if (rs_scale > cvar_scale.GetMaximum())
        rs_scale = cvar_scale.GetMaximum();

    if (rs_rotate < cvar_rotate.GetMinimum())
        rs_rotate = cvar_rotate.GetMinimum();
    else if (rs_rotate > cvar_rotate.GetMaximum())
        rs_rotate = cvar_rotate.GetMaximum();

    if (rs_opacity < cvar_opacity.GetMinimum())
        rs_opacity = cvar_opacity.GetMinimum();
    else if (rs_opacity > cvar_opacity.GetMaximum())
        rs_opacity = cvar_opacity.GetMaximum();

    // Check for changes before modifying cvars
    SetCVar("rs_mode", rs_mode);
    SetCVar("rs_theme", rs_theme);

    SetCVar("rs_x", rs_x, true);
    SetCVar("rs_y", rs_y, true);

    SetCVar("rs_scale", rs_scale, true);
    SetCVar("rs_rotate", rs_rotate, true);
    SetCVar("rs_opacity", rs_opacity, true);

    SetCVar("rs_disp_overlay", rs_disp_overlay);
    if (SetCVar("rs_enable_inmenu", rs_enable_inmenu))
    {
        if (!rs_enable_inmenu && !rs_enable_ingame)
            rs_enable_ingame = true;
    }
    if (SetCVar("rs_enable_ingame", rs_enable_ingame))
    {
        if (!rs_enable_ingame && !rs_enable_inmenu)
            rs_enable_inmenu = true;
    }
    SetCVar("rs_enable_float", rs_enable_float);

    SetCVar("rs_file_gm", rs_file_gm);
    SetCVar("rs_file_rank", rs_file_rank);
    SetCVar("rs_file_div", rs_file_div);
    SetCVar("rs_file_mmr", rs_file_mmr);
    SetCVar("rs_file_mmrc", rs_file_mmrc);
    SetCVar("rs_file_mmrcc", rs_file_mmrcc);
    SetCVar("rs_file_win", rs_file_win);
    SetCVar("rs_file_loss", rs_file_loss);
    SetCVar("rs_file_streak", rs_file_streak);
    SetCVar("rs_file_demo", rs_file_demo);
    SetCVar("rs_file_death", rs_file_death);
    SetCVar("rs_file_boost", rs_file_boost);

    SetCVar("rs_hide_gm", rs_hide_gm);
    SetCVar("rs_hide_rank", rs_hide_rank);
    SetCVar("rs_hide_div", rs_hide_div);
    SetCVar("rs_hide_mmr", rs_hide_mmr);
    SetCVar("rs_hide_mmrc", rs_hide_mmrc);
    SetCVar("rs_hide_mmrcc", rs_hide_mmrcc);
    SetCVar("rs_hide_win", rs_hide_win);
    SetCVar("rs_hide_loss", rs_hide_loss);
    SetCVar("rs_hide_streak", rs_hide_streak);
    SetCVar("rs_hide_demo", rs_hide_demo);
    SetCVar("rs_hide_death", rs_hide_death);
    SetCVar("rs_replace_mmr", rs_replace_mmr);
    SetCVar("rs_replace_mmrc", rs_replace_mmrc);
}

// Name of the menu that is used to toggle the window.
std::string RocketStats::GetMenuName()
{
    return menu_name;
}

// Title to give the menu
std::string RocketStats::GetMenuTitle()
{
    return menu_title;
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
    return settings_open;
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
