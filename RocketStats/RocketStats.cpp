/* ==================================
 *   Developped by Lyliya & NuSa
 * ================================== */

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
#pragma endregion

#pragma region PluginLoadRoutines
void RocketStats::onLoad()
{
    // notifierToken = gameWrapper->GetMMRWrapper().RegisterMMRNotifier(std::bind(&RocketStats::UpdateMMR, this, std::placeholders::_1));

    if (!ExistsPath(rs_path, true))
        rs_path = "data/" + rs_path;
    cvarManager->log("RS_path: " + GetPath());

    LoadImgs();
    LoadThemes();
    ReadConfig();
    ChangeTheme(RS_theme);
    rs_title = LoadImg("RocketStats_images/title.png");

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

    WriteInFile("RocketStats_GameMode.txt", "");
    WriteInFile("RocketStats_Rank.txt", "");
    WriteInFile("RocketStats_Div.txt", "");
    WriteInFile("RocketStats_MMR.txt", "0");
    WriteInFile("RocketStats_MMRChange.txt", "0");
    WriteInFile("RocketStats_MMRCumulChange.txt", "0");
    WriteInFile("RocketStats_Win.txt", "0");
    WriteInFile("RocketStats_Loss.txt", "0");
    WriteInFile("RocketStats_Streak.txt", "0");
    WriteInFile("RocketStats_BoostState.txt", "-1");

    RemoveFile("RocketStats_Loose.txt"); // Delete the old file
    RemoveFile("RocketStats_images/BoostState.txt"); // Delete the old file

    InitRank();

    // Register Cvars
    cvarManager->registerCvar("cl_rocketstats_settings", (isSettingsOpen_ ? "1" : "0"), "Display RocketStats settings", true, true, 0, true, 1, true).addOnValueChanged([this](std::string old, CVarWrapper now) {
        isSettingsOpen_ = now.getBoolValue();
    });

    cvarManager->registerCvar("RS_in_file", std::to_string(RS_in_file), "Informations", true, true, 0, true, 1, true).addOnValueChanged([this](std::string old, CVarWrapper now) {
        if (!now.getBoolValue())
            return;

        WriteGameMode();
        WriteMMR();
        WriteMMRChange();
        WriteMMRCumulChange();
        WriteWin();
        WriteLoss();
        WriteStreak();
        WriteInFile("RocketStats_BoostState.txt", std::to_string(gameWrapper->IsInGame() ? 0 : -1));
    });
    cvarManager->registerCvar("RS_mode", std::to_string(RS_mode), "Mode", true, true, 0, true, 2, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_theme", std::to_string(RS_theme), "Theme", true, true, 0, false, 1, false).addOnValueChanged([this](std::string old, CVarWrapper now) {
        if (!ChangeTheme(now.getIntValue()))
            now.setValue(old);
    });

    cvarManager->registerCvar("RS_x", std::to_string(RS_x), "X", true, true, 0, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_y", std::to_string(RS_y), "Y", true, true, 0, true, 1.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_scale", std::to_string(RS_scale), "Scale", true, true, 0, true, 10.f, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("RS_disp_overlay", (RS_disp_overlay ? "1" : "0"), "Overlay", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_disp_obs", (RS_disp_obs ? "1" : "0"), "Show on OBS", true, true, 0, true, 1, false);
    cvarManager->registerCvar("RS_enable_ingame", (RS_enable_ingame ? "1" : "0"), "Show while in-game", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_enable_boost", (RS_enable_boost ? "1" : "0"), "Enable boost", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_enable_float", (RS_enable_float ? "1" : "0"), "Enable floating point", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("RS_onchange_scale", (RS_onchange_scale ? "1" : "0"), "Reset scale on change", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_onchange_position", (RS_onchange_position ? "1" : "0"), "Reset position on change", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));


    if (gameWrapper->IsInGame())
        TogglePlugin("IsInGame", ToggleFlags_Show);
}

void RocketStats::onUnload()
{
    WriteConfig();

    gameWrapper->UnhookEvent("Function TAGame.GFxData_StartMenu_TA.EventTitleScreenClicked");
    gameWrapper->UnhookEvent("Function GameEvent_TA.Countdown.BeginState");
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded");
    gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.BeginState");
    gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.EndState");
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_TA.Destroyed");

    TogglePlugin("onUnload", ToggleFlags_Hide);
}
#pragma endregion

#pragma region GameMgmt
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
    }
}

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
    WriteMMR();
    WriteMMRChange();
    WriteMMRCumulChange();
    WriteWin();
    WriteLoss();
    WriteStreak();

    // Get TeamNum
    myTeamNum = myTeam.GetTeamNum();

    // Set Game Started
    isGameStarted = true;
    isGameEnded = false;

    UpdateMMR(gameWrapper->GetUniqueID());
    WriteConfig();
    if (RS_in_file)
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

            if (stats[currentPlaylist].streak < 0)
            {
                always.streak = 1;
                session.streak = 1;
                stats[currentPlaylist].streak = 1;
            }
            else
            {
                always.streak++;
                session.streak++;
                stats[currentPlaylist].streak++;
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

            if (stats[currentPlaylist].streak > 0)
            {
                always.streak = -1;
                session.streak = -1;
                stats[currentPlaylist].streak = -1;
            }
            else
            {
                always.streak--;
                session.streak--;
                stats[currentPlaylist].streak--;
            }

            theme_refresh = 1;
            WriteLoss();
        }

        WriteStreak();
        WriteConfig();

        // Reset myTeamNum security
        myTeamNum = -1;

        if (RS_in_file)
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

        if (stats[currentPlaylist].streak > 0)
        {
            always.streak = 0;
            session.streak = 0;
            stats[currentPlaylist].streak = -1;
        }
        else
        {
            always.streak--;
            session.streak--;
            stats[currentPlaylist].streak--;
        }

        WriteStreak();
        WriteLoss();
        WriteConfig();
    }

    isGameEnded = true;
    isGameStarted = false;
    if (RS_in_file)
        WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));

    theme_refresh = 1;
    cvarManager->log("===== !GameDestroyed =====");
}
#pragma endregion

#pragma region StatsMgmt
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
        stats[currentPlaylist].MMRChange += MMRChange;

        always.MMRCumulChange += MMRChange;
        for (auto it = playlistName.begin(); it != playlistName.end(); it++)
            stats[it->first].MMRCumulChange += MMRChange;
    }
    else
        stats[currentPlaylist].isInit = true;
    stats[currentPlaylist].myMMR = mmr;

    MajRank(currentPlaylist, mmrw.IsRanked(currentPlaylist), stats[currentPlaylist].myMMR, playerRank);
    SessionStats();
    WriteMMR();
    WriteMMRChange();
    WriteMMRCumulChange();

    theme_refresh = 1;
    cvarManager->log("===== !UpdateMMR =====");
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
    }

    session.myMMR = stats[currentPlaylist].myMMR;
    session.MMRChange = tmp.MMRChange;
    session.MMRCumulChange = tmp.MMRCumulChange;
    session.win = tmp.win;
    session.loss = tmp.loss;
    session.isInit = true;

    always.myMMR = session.myMMR;

    theme_refresh = 1;
}

void RocketStats::ResetStats()
{
    always = Stats();
    session = Stats();
    for (auto &kv : stats)
        kv.second = Stats();

    WriteConfig();
    WriteInFile("RocketStats_GameMode.txt", "");
    WriteInFile("RocketStats_Rank.txt", "");
    WriteInFile("RocketStats_Div.txt", "");
    WriteInFile("RocketStats_MMR.txt", std::to_string(0));
    WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));
    WriteInFile("RocketStats_MMRCumulChange.txt", std::to_string(0));
    WriteInFile("RocketStats_Win.txt", std::to_string(0));
    WriteInFile("RocketStats_Loss.txt", std::to_string(0));
    WriteInFile("RocketStats_Streak.txt", std::to_string(0));

    InitRank();
    theme_refresh = 1;
}
#pragma endregion

#pragma region BoostMgmt
void RocketStats::OnBoostStart(std::string eventName)
{
    // Check if boost enabled in options
    if (!RS_enable_boost || gameWrapper->IsInReplay() || isBoosting)
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
    if (!RS_enable_boost || gameWrapper->IsInReplay() || !isBoosting)
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

            WriteInFile("RocketStats_Div.txt", currentDivision);
        }

        if (currentRank != lastRank)
            WriteInFile("RocketStats_Rank.txt", currentRank);
    }
    else
    {
        currentRank = GetPlaylistName(currentGameMode);
        currentDivision = "";

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
        for (const auto& entry : fs::directory_iterator(theme_base))
        {
            std::string theme_path = entry.path().u8string();
            if (entry.is_directory() && fs::exists(theme_path + "/config.json"))
            {
                struct Theme theme;
                theme.name = theme_path.substr(theme_path.find_last_of("/\\") + 1);
                cvarManager->log("Theme: " + theme.name);

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
        if (themes.size() <= idx)
            return true;

        Theme& theme = themes.at(idx);

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

            theme_render.font_name = "";
            if (theme_config.contains("font") && theme_config["font"].is_array() && theme_config["font"].size() == 2)
            {
                if (theme_config["font"][0].is_string() && theme_config["font"][1].is_number_unsigned())
                {
                    int font_size = theme_config["font"][1];
                    std::string font_file = theme_config["font"][0];

                    std::string font_prefix = "rs_";
                    std::string font_path = ("RocketStats_themes/" + theme_render.name + "/fonts/" + font_file);
                    std::string font_dest = ("data/fonts/" + font_prefix + font_file);

                    if (font_file.size() && font_size > 0 && ExistsPath(font_path))
                    {
                        if (!ExistsPath(font_dest, true))
                            fs::copy(GetPath(font_path), GetPath(font_dest, true));

                        theme_render.font_size = font_size;
                        theme_render.font_name = font_prefix + (font_file.substr(0, font_file.find_last_of('.'))) + "_" + std::to_string(font_size);

                        GuiManagerWrapper gui = gameWrapper->GetGUIManager();
                        gui.LoadFont(theme_render.font_name, (font_prefix + font_file), font_size);
                        cvarManager->log("Load font: " + theme_render.font_name);
                    }
                }
            }

            cvarManager->log("Theme changed: " + theme.name + " (old: " + ((themes.size() > RS_theme) ? themes.at(RS_theme).name : "Unknown") + ")");
            RS_theme = idx;
            theme_refresh = 2;
        }
        else
            cvarManager->log("Theme config: " + theme.name + " bad JSON");
    }
    catch (json::parse_error& e)
    {
        cvarManager->log("Theme config: " + std::to_string(idx) + " bad JSON -> " + std::string(e.what()));

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
                element_2d.x = int(float(element["x"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x"], options.width)) : int(element["x"])) * options.scale);

            if (element.contains("y"))
                element_2d.y = int(float(element["y"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y"], options.height)) : int(element["y"])) * options.scale);

            if (element.contains("width"))
                element_2d.width = int(float(element["width"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["width"], options.width)) : int(element["width"])) * options.scale);

            if (element.contains("height"))
                element_2d.height = int(float(element["height"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["height"], options.height)) : int(element["height"])) * options.scale);

            ImVec2 element_pos = { float(options.x + element_2d.x), float(options.y + element_2d.y) };
            ImVec2 element_size = { float(element_2d.width), float(element_2d.height) };
            const float element_scale = (element.contains("scale") ? float(element["scale"]) : 1.0f);

            calculated.scale = (element_scale * options.scale);

            calculated.color.enable = true;
            if (element.contains("color") && element["color"].is_array())
                calculated.color = { true, Utils::GetImColor(element["color"], options.opacity) };

            if (element.contains("fill") && element["fill"].is_array())
                calculated.fill = { true, Utils::GetImColor(element["fill"], options.opacity) };

            if (element.contains("stroke") && element["stroke"].is_array())
                calculated.stroke = { true, Utils::GetImColor(element["stroke"], options.opacity) };

            if (element["type"] == "text" && element["value"].size())
            {
                calculated.scale *= 2.0f;
                calculated.value = element["value"];

                Utils::ReplaceVars(calculated.value, theme_vars, [this, &element, &options, &calculated](const std::string &key, std::string &value) {
                    if (element.contains("sign") && element["sign"] == key)
                    {
                        bool positive = (value.at(0) != '-');
                        if (positive)
                            value = ("+" + value);
                    }

                    if (element.contains("chameleon") && element["chameleon"] == key)
                    {
                        bool positive = (value.at(0) != '-');
                        calculated.color.color = Utils::GetImColor({ float(positive ? 30 : 224), float(positive ? 224 : 24), float(positive ? 24 : 24) }, options.opacity);
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
                element_pos.x = float(options.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x1"], options.width)) : int(element["x1"])) * options.scale);
                element_pos.y = float(options.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y1"], options.height)) : int(element["y1"])) * options.scale);
                const float element_width = (element.contains("scale") ? (float)element["scale"] : 1);

                element_size.x = element_width;
                calculated.scale = (element_width * options.scale);

                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x2"], options.width)) : int(element["x2"])) * options.scale),
                    float(options.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y2"], options.height)) : int(element["y2"])) * options.scale)
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
                element_pos.x = float(options.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x1"], options.width)) : int(element["x1"])) * options.scale);
                element_pos.y = float(options.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y1"], options.height)) : int(element["y1"])) * options.scale);

                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x2"], options.width)) : int(element["x2"])) * options.scale),
                    float(options.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y2"], options.height)) : int(element["y2"])) * options.scale)
                });
                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x3"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x3"], options.width)) : int(element["x3"])) * options.scale),
                    float(options.y) + (float(element["y3"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y3"], options.height)) : int(element["y3"])) * options.scale)
                });
            }
            else if (element["type"] == "circle")
            {
                element_size.x = (float(element["radius"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["radius"], options.width)) : int(element["radius"])) * options.scale);
                element_size.y = float(element.contains("segments") ? int(element["segments"]) : 0);
            }
            else if (element["type"] == "image")
            {
                calculated.scale *= 0.5f;
                calculated.value = element["file"];

                if (calculated.value == "{{Rank}}")
                {
                    theme_images[calculated.value] = rank[(currentTier < rank_nb) ? currentTier : 0].image;
                }
                else if (!theme_images[calculated.value])
                {
                    element_size = { 0, 0 };
                    std::string image_path = "RocketStats_themes/" + themes.at(RS_theme).name + "/images/" + calculated.value;

                    cvarManager->log("load image: " + image_path);
                    theme_images[calculated.value] = LoadImg(image_path);
                }

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

            check = true;
        }
        catch (const std::exception& e)
        {
            cvarManager->log("CalculateElement error: " + std::string(e.what()));
        }
    }

    return calculated;
}

void RocketStats::RenderElement(Element& element)
{
    try
    {
        ImDrawList* drawlist;
        if (RS_disp_obs)
            drawlist = ImGui::GetBackgroundDrawList();
        else
            drawlist = ImGui::GetOverlayDrawList();

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
                    drawlist->AddImage(image->GetImGuiTex(), element.positions.at(0), element.size);
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

                if (font && font->IsLoaded())
                    drawlist->AddText(font, element.scale, element.positions.at(0), element.color.color, element.value.c_str());
            }
            else
            {
                ImGui::SetWindowFontScale(element.scale);
                drawlist->AddText(element.positions.at(0), element.color.color, element.value.c_str());
            }
        }
        else if (element.type == "line")
            drawlist->AddLine(element.positions.at(0), element.positions.at(1), element.color.color, element.size.x);
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

void RocketStats::ReadConfig()
{
    cvarManager->log("===== ReadConfig =====");

    std::string file = "data/rocketstats.json";
    if (ExistsPath(file, true))
    {
        try
        {
            json config = json::parse(ReadFile(file, true));
            cvarManager->log(nlohmann::to_string(config));

            if (config.is_object())
            {
                if (config["settings"].is_object())
                {
                    if (config["settings"]["mode"].is_number_unsigned())
                        RS_mode = config["settings"]["mode"];

                    if (config["settings"]["theme"].is_string())
                    {
                        std::string name = config["settings"]["theme"];
                        for (int i = 0; i < themes.size(); ++i)
                        {
                            if (themes.at(i).name == name)
                                RS_theme = i;
                        }
                    }

                    if (config["settings"]["scale"].is_number_unsigned() || config["settings"]["scale"].is_number_integer() || config["settings"]["scale"].is_number_float())
                        RS_scale = config["settings"]["scale"];

                    if (config["settings"]["position"].is_array() && config["settings"]["position"].size() == 2)
                    {
                        if (config["settings"]["position"][0].is_number_unsigned() || config["settings"]["position"][0].is_number_integer() || config["settings"]["position"][0].is_number_float())
                            RS_x = config["settings"]["position"][0];

                        if (config["settings"]["position"][1].is_number_unsigned() || config["settings"]["position"][1].is_number_integer() || config["settings"]["position"][1].is_number_float())
                            RS_y = config["settings"]["position"][1];
                    }

                    if (config["settings"]["overlay"].is_boolean())
                        RS_disp_overlay = config["settings"]["overlay"];

                    if (config["settings"]["obs"].is_boolean())
                        RS_disp_obs = config["settings"]["obs"];

                    if (config["settings"]["ingame"].is_number_unsigned())
                        RS_enable_ingame = config["settings"]["ingame"];

                    if (config["settings"]["boost"].is_boolean())
                        RS_enable_boost = config["settings"]["boost"];

                    if (config["settings"]["float"].is_boolean())
                        RS_enable_float = config["settings"]["float"];

                    if (config["settings"]["onchange_scale"].is_boolean())
                        RS_onchange_scale = config["settings"]["onchange_scale"];

                    if (config["settings"]["onchange_position"].is_number_unsigned())
                        RS_onchange_position = config["settings"]["onchange_position"];

                    cvarManager->log("Config: stats loaded");
                    always.isInit = true;
                }

                if (config["always"].is_object())
                {
                    if (config["always"]["MMRCumulChange"].is_number_unsigned() || config["always"]["MMRCumulChange"].is_number_integer())
                        always.MMRCumulChange = config["always"]["MMRCumulChange"];

                    if (config["always"]["Win"].is_number_unsigned())
                        always.win = config["always"]["Win"];

                    if (config["always"]["Loss"].is_number_unsigned())
                        always.loss = config["always"]["Loss"];

                    if (config["always"]["Streak"].is_number_unsigned() || config["always"]["Streak"].is_number_integer())
                        always.streak = config["always"]["Streak"];

                    cvarManager->log("Config: stats loaded");
                    always.isInit = true;
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
}

void RocketStats::WriteConfig()
{
    cvarManager->log("===== WriteConfig =====");

    json tmp = {};

    tmp["settings"] = {};
    tmp["settings"]["mode"] = RS_mode;
    tmp["settings"]["theme"] = theme_render.name;
    tmp["settings"]["scale"] = RS_scale;
    tmp["settings"]["position"] = { RS_x, RS_y };
    tmp["settings"]["overlay"] = RS_disp_overlay;
    tmp["settings"]["obs"] = RS_disp_obs;
    tmp["settings"]["ingame"] = RS_enable_ingame;
    tmp["settings"]["boost"] = RS_enable_boost;
    tmp["settings"]["float"] = RS_enable_float;
    tmp["settings"]["onchange_scale"] = RS_onchange_scale;
    tmp["settings"]["onchange_position"] = RS_onchange_position;

    tmp["always"] = {};
    tmp["always"]["MMRCumulChange"] = always.MMRCumulChange;
    tmp["always"]["Win"] = always.win;
    tmp["always"]["Loss"] = always.loss;
    tmp["always"]["Streak"] = always.streak;

    WriteInFile("data/rocketstats.json", nlohmann::to_string(tmp), true);

    cvarManager->log("===== !WriteConfig =====");
}

void RocketStats::WriteGameMode()
{
    if (RS_in_file)
        WriteInFile("RocketStats_GameMode.txt", GetPlaylistName(currentPlaylist));
}

void RocketStats::WriteMMR()
{
    if (!RS_in_file)
        return;

    std::string tmp = Utils::FloatFixer(stats[currentPlaylist].myMMR, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMR.txt", tmp);
}

void RocketStats::WriteMMRChange()
{
    if (!RS_in_file)
        return;

    Stats current = GetStats();
    std::string tmp = Utils::FloatFixer(current.MMRChange, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRChange.txt", (((current.MMRChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteMMRCumulChange()
{
    if (!RS_in_file)
        return;

    Stats current = GetStats();
    std::string tmp = Utils::FloatFixer(current.MMRCumulChange, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRCumulChange.txt", (((current.MMRCumulChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteWin()
{
    if (RS_in_file)
        WriteInFile("RocketStats_Win.txt", std::to_string(GetStats().win));
}

void RocketStats::WriteLoss()
{
    if (RS_in_file)
        WriteInFile("RocketStats_Loss.txt", std::to_string(GetStats().loss));
}

void RocketStats::WriteStreak()
{
    if (!RS_in_file)
        return;

    Stats current = GetStats();
    std::string tmp = std::to_string(current.streak);

    WriteInFile("RocketStats_Streak.txt", (((current.streak > 0) ? "+" : "") + tmp));
}
#pragma endregion

#pragma region PluginWindow
void RocketStats::Render()
{
    RenderIcon();
    RenderOverlay();

    if (isSettingsOpen_)
        RenderSettings();
}

void RocketStats::RenderIcon()
{
    float margin = 20.f;
    float icon_size = 35.f;
    bool ingame = (gameWrapper->IsInGame() || gameWrapper->IsInOnlineGame());
    ImVec2 mouse_pos = ImGui::GetIO().MousePos;
    ImVec2 screen_size = ImGui::GetIO().DisplaySize;
    ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

    ImVec2 icon_pos = { -10.f, (screen_size.y * 0.459f) };

    bool hover = (mouse_pos.x > (icon_pos.x - icon_size - margin) && mouse_pos.x < (icon_pos.x + icon_size + margin));
    hover = (hover && (mouse_pos.y > (icon_pos.y - icon_size - margin) && mouse_pos.y < (icon_pos.y + icon_size + margin)));
    if (!ingame || hover)
    {
        drawlist->AddCircle({ icon_pos.x, icon_pos.y }, icon_size, ImColor{ 0.45f, 0.72f, 1.f, (hover ? 0.8f : 0.4f) }, 25, 4.f);
        drawlist->AddCircleFilled({ icon_pos.x, icon_pos.y }, icon_size, ImColor{ 0.04f, 0.52f, 0.89f, (hover ? 0.6f : 0.3f) }, 25);

        if (hover)
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::IsMouseClicked(0))
                ToggleSettings("MouseEvent");
        }
    }
}

void RocketStats::RenderOverlay()
{
    if (!RS_disp_overlay || (isGameStarted && !isGameEnded && !RS_enable_ingame))
        return;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin((menuTitle_ + " - Overlay").c_str(), (bool*)1, (ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs));

    try
    {
        if (theme_refresh || theme_render.name == "" || (themes.size() > RS_theme && theme_render.name != themes.at(RS_theme).name))
        {
            Stats current = GetStats();
            ImVec2 screen_size = ImGui::GetIO().DisplaySize;

            if (theme_refresh == 2)
            {
                if (RS_onchange_scale)
                    RS_scale = 1.0f;

                if (RS_onchange_position && theme_config.contains("x") && theme_config.contains("y"))
                {
                    RS_x = theme_config["x"];
                    RS_y = theme_config["y"];
                }
            }

            std::vector<struct Element> elements;
            Options options = {
                int(RS_x * screen_size.x),
                int(RS_y * screen_size.y),
                (theme_config.contains("width") ? int(theme_config["width"]) : 0),
                (theme_config.contains("height") ? int(theme_config["height"]) : 0),
                (RS_scale * (theme_config.contains("scale") ? float(theme_config["scale"]) : 1.f)),
                (theme_config.contains("opacity") ? float(theme_config["opacity"]) : 0.f)
            };

            const size_t floating_length = (RS_enable_float ? 2 : 0);
            if (current.isInit)
            {
                theme_vars["GameMode"] = GetPlaylistName(currentPlaylist);
                theme_vars["Rank"] = currentRank;
                theme_vars["Div"] = currentDivision;
                theme_vars["MMR"] = Utils::FloatFixer(current.myMMR, floating_length); // Utils::PointFixer(current.myMMR, 6, floating_length)
                theme_vars["MMRChange"] = Utils::FloatFixer(current.MMRChange, floating_length); // Utils::PointFixer(current.MMRChange, 6, floating_length)
                theme_vars["MMRCumulChange"] = Utils::FloatFixer(current.MMRCumulChange, floating_length); // Utils::PointFixer(current.MMRCumulChange, 6, floating_length)
                theme_vars["Win"] = std::to_string(current.win);
                theme_vars["Loss"] = std::to_string(current.loss);
                theme_vars["Streak"] = std::to_string(current.streak);

                Utils::ReplaceAll(theme_vars["Rank"], "_", " ");
            }
            else
            {
                theme_vars["GameMode"] = "Unknown Game Mode";
                theme_vars["Rank"] = "norank";
                theme_vars["Div"] = "nodiv";
                theme_vars["MMR"] = Utils::FloatFixer(100.0f, floating_length);
                theme_vars["MMRChange"] = Utils::FloatFixer(0.0f, floating_length);
                theme_vars["MMRCumulChange"] = Utils::FloatFixer(0.0f, floating_length);
                theme_vars["Win"] = "0";
                theme_vars["Loss"] = "0";
                theme_vars["Streak"] = "0";
            }

            if (theme_refresh == 2)
            {
                theme_images.clear();
                cvarManager->log("refresh all images");
            }

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

        for (auto& element : theme_render.elements)
            RenderElement(element);
    }
    catch (const std::exception&) {}

    ImGui::End();
}

void RocketStats::RenderSettings()
{
    ImVec2 settings_size = { 750, 0 };

    ImGui::SetNextWindowPos(ImVec2{ 128, 256 }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(settings_size);

    ImGui::Begin(menuTitle_.c_str(), &isSettingsOpen_, ImGuiWindowFlags_None);

    if (rs_title != nullptr && rs_title->IsLoadedForImGui())
    {
        ImVec2 text_size;
        ImVec2 image_pos;
        ImVec2 win_pos = ImGui::GetWindowPos();
        ImVec2 win_size = ImGui::GetWindowSize();
        Vector2F image_size = rs_title->GetSizeF();
        ImDrawList* drawlist = ImGui::GetWindowDrawList();
        std::string developers = "Developped by @Lyliiya & @NuSa_yt for @Maylie_tv";

        ImVec2 p0 = win_pos;
        ImVec2 p1 = { (win_pos.x + win_size.x), (win_pos.y + win_size.y) };

        p0.x += 1;
        p1.x -= 1;
        drawlist->PushClipRect(p0, p1);

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
        ImGui::SetNextItemWidth(180);
        ImGui::Combo("##mode", &RS_mode, "Session\0GameMode\0Always\0");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Restrict information to current game or keep longer");

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

        ImGui::SetCursorPos({ 45, 120 });
        if (ImGui::Button(cvarManager->getCvar("RS_scale").getDescription().c_str(), { 45, 0 }))
            RS_scale_edit = !RS_scale_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the size of the overlay");
        ImGui::SetCursorPos({ 85, 120 });
        ImGui::SetNextItemWidth(150);
        if (RS_scale_edit)
            ImGui::InputFloat("##scale", &RS_scale, 0.1f, 1.f, "%.3f");
        else
            ImGui::SliderFloat("##scale", &RS_scale, 0.f, 10.f, "%.3f");

        ImGui::SetCursorPos({ 280, 120 });
        if (ImGui::Button(cvarManager->getCvar("RS_x").getDescription().c_str(), { 45, 0 }))
            RS_x_edit = !RS_x_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the horizontal position of the overlay");
        ImGui::SetCursorPos({ 320, 120 });
        ImGui::SetNextItemWidth(150);
        if (RS_x_edit)
            ImGui::InputFloat("##x_position", &RS_x, 0.001f, 0.1f, "%.3f");
        else
            ImGui::SliderFloat("##x_position", &RS_x, 0.f, 1.f, "%.3f");

        ImGui::SetCursorPos({ 515, 120 });
        if (ImGui::Button(cvarManager->getCvar("RS_y").getDescription().c_str(), { 45, 0 }))
            RS_y_edit = !RS_y_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the vertical position of the overlay");
        ImGui::SetCursorPos({ 555, 120 });
        ImGui::SetNextItemWidth(150);
        if (RS_y_edit)
            ImGui::InputFloat("##y_position", &RS_y, 0.001f, 0.1f, "%.3f");
        else
            ImGui::SliderFloat("##y_position", &RS_y, 0.f, 1.f, "%.3f");

        ImGui::SetCursorPosY(155);
        ImGui::Separator();

        ImGui::SetCursorPos({ 0, 165 });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2) + image_pos.x, (image_size.Y / 2) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 23, 190 });
        ImGui::Checkbox("##overlay", &RS_disp_overlay);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Displays the overlay on the game screen");

        ImGui::SetCursorPos({ 63, 192 });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(cvarManager->getCvar("RS_disp_overlay").getDescription()).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (settings_size.x - 120), 168 });
        if (ImGui::Button("Open folder", { 110, 0 }))
            system(("powershell -WindowStyle Hidden \"start \"\"" + GetPath() + "\"\"\"").c_str());
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Access theme folders or files for OBS");
        ImGui::SetCursorPos({ (settings_size.x - 120), 193 });
        if (ImGui::Button("Reload Theme", { 88, 0 }))
            ChangeTheme(RS_theme);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Refresh current theme information (JSON and images)");
        ImGui::SetCursorPos({ (settings_size.x - 27), 193 });
        if (ImGui::Button("A", { 17, 0 }))
        {
            std::string name = theme_render.name;
            LoadThemes();

            for (int i = 0; i < themes.size(); ++i)
            {
                if (themes.at(i).name == name)
                    RS_theme = i;
            }

            ChangeTheme(RS_theme);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Reloads all the themes (adds or removes depending on the folders)");
        ImGui::SetCursorPos({ (settings_size.x - 120), 218 });
        if (ImGui::Button("Reset Stats", { 110, 0 }))
            ResetStats();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Resets all plugin information for all modes (MMR, Win, Loss, etc.)");

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 280, 185 });
        text_size = ImGui::CalcTextSize(theme_render.name.c_str());
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 1.f }, theme_render.name.c_str());
        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (285 + text_size.x), 192 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.5f }, (theme_render.version + (theme_render.date.size() ? (" - " + theme_render.date) : "")).c_str());
        ImGui::SetCursorPos({ 290, 209 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.8f }, ("Theme by " + theme_render.author).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ 15, 255 });
        ImGui::BeginGroup();
        ImGui::Checkbox(cvarManager->getCvar("RS_disp_obs").getDescription().c_str(), &RS_disp_obs);
        ImGui::Checkbox(cvarManager->getCvar("RS_enable_ingame").getDescription().c_str(), &RS_enable_ingame);
        ImGui::EndGroup();

        ImGui::SetCursorPos({ 15, 255 });
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Checkbox(cvarManager->getCvar("RS_enable_boost").getDescription().c_str(), &RS_enable_boost);
        ImGui::Checkbox(cvarManager->getCvar("RS_enable_float").getDescription().c_str(), &RS_enable_float);
        ImGui::EndGroup();

        ImGui::SetCursorPos({ 15, 255 });
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Checkbox(cvarManager->getCvar("RS_onchange_scale").getDescription().c_str(), &RS_onchange_scale);
        ImGui::Checkbox(cvarManager->getCvar("RS_onchange_position").getDescription().c_str(), &RS_onchange_position);
        ImGui::EndGroup();

        /*
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
            LoadThemes();
            ChangeTheme(RS_theme);
            rs_title = LoadImg("RocketStats_images/title.png");
        }
    }

    ImGui::End();

    if (RS_scale < 0)
        RS_scale = 0;

    if (RS_mode != cvarManager->getCvar("RS_mode").getIntValue())
        cvarManager->getCvar("RS_mode").setValue(RS_mode);
    if (RS_theme != cvarManager->getCvar("RS_theme").getIntValue())
        cvarManager->getCvar("RS_theme").setValue(RS_theme);

    if (RS_scale != cvarManager->getCvar("RS_scale").getFloatValue())
        cvarManager->getCvar("RS_scale").setValue(RS_scale);
    if (RS_x != cvarManager->getCvar("RS_x").getFloatValue())
        cvarManager->getCvar("RS_x").setValue(RS_x);
    if (RS_y != cvarManager->getCvar("RS_y").getFloatValue())
        cvarManager->getCvar("RS_y").setValue(RS_y);

    if (RS_disp_overlay != cvarManager->getCvar("RS_disp_overlay").getBoolValue())
        cvarManager->getCvar("RS_disp_overlay").setValue(RS_disp_overlay);
    if (RS_disp_obs != cvarManager->getCvar("RS_disp_obs").getBoolValue())
        cvarManager->getCvar("RS_disp_obs").setValue(RS_disp_obs);
    if (RS_enable_ingame != cvarManager->getCvar("RS_enable_ingame").getBoolValue())
        cvarManager->getCvar("RS_enable_ingame").setValue(RS_enable_ingame);
    if (RS_enable_boost != cvarManager->getCvar("RS_enable_boost").getBoolValue())
        cvarManager->getCvar("RS_enable_boost").setValue(RS_enable_boost);
    if (RS_enable_float != cvarManager->getCvar("RS_enable_float").getBoolValue())
        cvarManager->getCvar("RS_enable_float").setValue(RS_enable_float);
    if (RS_onchange_scale != cvarManager->getCvar("RS_onchange_scale").getBoolValue())
        cvarManager->getCvar("RS_onchange_scale").setValue(RS_onchange_scale);
    if (RS_onchange_position != cvarManager->getCvar("RS_onchange_position").getBoolValue())
        cvarManager->getCvar("RS_onchange_position").setValue(RS_onchange_position);
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
    return true;
}

void RocketStats::OnOpen()
{
    //ToggleSettings("OnOpen", ToggleFlags_Show);
}

void RocketStats::OnClose()
{
    ToggleSettings("OnClose", ToggleFlags_Hide);
}
#pragma endregion
