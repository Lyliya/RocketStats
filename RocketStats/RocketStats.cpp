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
    fs::path _path = (gameWrapper->GetBakkesModPath().string() + "/" + rs_path + "/" + _filename);
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
    cvarManager->log("RS_path: " + gameWrapper->GetBakkesModPath().string() + "/" + rs_path);

    LoadImgs();
    LoadThemes();

    ReadConfig();

    cvarManager->registerNotifier(
        "RS_toggle_menu",
        [this](std::vector<std::string> params)
        { isSettingsOpen_ = !isSettingsOpen_; },
        "Toggle menu",
        PERMISSION_ALL);

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
    cvarManager->registerCvar("RS_mode", std::to_string(RS_mode), "Mode", true, true, 0, true, 2, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_theme", std::to_string(RS_theme), "Theme", true, true, 0, false, 1, true).addOnValueChanged([this](std::string old, CVarWrapper now) {
        if (!ChangeTheme(now.getIntValue()))
            now.setValue(old);
    });

    cvarManager->registerCvar("RS_enable_float", (RS_enable_float ? "1" : "0"), "Enable floating point", true, true, 0, true, 1, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_enable_boost", (RS_enable_boost ? "1" : "0"), "Enable boost", true, true, 0, true, 1, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_disp_overlay", (RS_disp_overlay ? "1" : "0"), "Overlay display and settings", true, true, 0, true, 1, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_overlay_ig", (RS_hide_overlay_ig ? "1" : "0"), "Hide while in-game", true, true, 0, true, 1, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    cvarManager->registerCvar("RS_scale", std::to_string(RS_scale), "Scale", true, true, 0, true, 10.f, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_x_position", std::to_string(RS_x_position), "X position", true, true, 0, true, 1.f, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_y_position", std::to_string(RS_y_position), "Y position", true, true, 0, true, 1.f, true).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));

    if (gameWrapper->IsInGame())
        ShowPlugin("IsInGame");
}

void RocketStats::onUnload()
{
    if (isSettingsOpen_)
        cvarManager->executeCommand("togglemenu " + GetMenuName());
}
#pragma endregion

#pragma region GameMgmt
void RocketStats::ShowPlugin(std::string eventName)
{
    if (!isSettingsOpen_)
        cvarManager->executeCommand("togglemenu " + GetMenuName());
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
    WriteInFile("RocketStats_BoostState.txt", std::to_string(0));
    WriteConfig();

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

        WriteInFile("RocketStats_BoostState.txt", std::to_string(-1));

        gameWrapper->SetTimeout([&](GameWrapper *gameWrapper)
                                { UpdateMMR(gameWrapper->GetUniqueID()); },
                                3.0F);

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

    std::string base = gameWrapper->GetBakkesModPath().string() + "/" + rs_path;
    std::string theme_base = base + "/RocketStats_themes";

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

                std::string fonts_path = theme_base + "/" + theme.name + "/fonts";
                if (fs::exists(fonts_path))
                {
                    for (const auto& fentry : fs::directory_iterator(fonts_path))
                    {
                        std::string font_path = fentry.path().u8string();
                        std::string font_filename = font_path.substr(font_path.find_last_of("/\\") + 1);

                        font_path = fonts_path + "/" + font_filename;
                        if (fentry.is_regular_file() && font_filename.substr(font_filename.find_last_of(".")) == ".fnt")
                        {
                            struct Font font;
                            font.name = font_filename.substr(0, font_filename.find_last_of("."));
                            cvarManager->log("Font: " + font.name);

                            std::string font_content = ReadFile(font_path.substr(base.length() + 1));
                            std::vector<std::string> lines = Utils::Split(font_content, '\n');

                            std::vector<std::string> pages_filename;
                            for (auto& line : lines)
                            {
                                line.erase(line.find('\r'));
                                if (line.find("page ") == 0)
                                {
                                    size_t page_start = line.find("file=\"");
                                    if (page_start != std::string::npos)
                                    {
                                        page_start += 6;
                                        size_t page_end = line.find('"', page_start);
                                        if (page_end != std::string::npos)
                                            pages_filename.push_back(line.substr(page_start, (page_end - page_start)));
                                    }
                                }
                                else if (line.find("char ") == 0)
                                    font.chars.push_back(Utils::SplitKeyInt(line, 5));
                                else if (line.find("kerning ") == 0)
                                    font.kernings.push_back(Utils::SplitKeyInt(line, 8));
                                else if (line.find("common ") == 0)
                                    font.common = Utils::SplitKeyInt(line, 7);
                            }

                            cvarManager->log(" > common base=" + std::to_string(font.common["base"]));
                            cvarManager->log(" > char_index=" + std::to_string(Utils::FindKeyInt(font.chars, "id", 49)));

                            std::vector<std::shared_ptr<ImageWrapper>> pages_images;
                            for (const auto& page_filename : pages_filename)
                            {
                                cvarManager->log(" > " + fonts_path + "/" + page_filename);
                                pages_images.push_back(std::make_shared<ImageWrapper>(fonts_path + "/" + page_filename, false, true));
                            }

                            theme.fonts.push_back(font);
                        }
                    }
                }

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

    try
    {
        std::string name = themes.at(idx).name;

        theme_config = json::parse(ReadFile("RocketStats_themes/" + name + "/config.json"));
        cvarManager->log(nlohmann::to_string(theme_config));

        if (theme_config.is_object())
        {
            cvarManager->log("Theme changed: " + name + " (old: " + themes.at(RS_theme).name + ")");
            RS_theme = idx;
            theme_refresh = 2;
        }
        else
            cvarManager->log("Theme config: " + name + " bad JSON");
    }
    catch (json::parse_error& e)
    {
        cvarManager->log("Theme config: " + std::to_string(idx) + " bad JSON -> " + std::string(e.what()));
    }

    cvarManager->log("===== !ChangeTheme =====");
    return (RS_theme == idx);
}

void RocketStats::RefreshTheme(std::string old, CVarWrapper now)
{
    theme_refresh = 1;
}

struct Element RocketStats::CalculateElement(json& element, std::map<std::string, std::any>& options, bool& check)
{
    check = false;
    struct Element calculated;

    if (!element.contains("visible") || element["visible"])
    {
        Vector2D base_2d = {
            std::any_cast<int>(options["pos_x"]),
            std::any_cast<int>(options["pos_y"]),
            std::any_cast<int>(options["width"]),
            std::any_cast<int>(options["height"])
        };

        float scale = std::any_cast<float>(options["scale"]);
        float opacity = std::any_cast<float>(options["opacity"]);
        Stats current = std::any_cast<Stats>(options["stats"]);

        try
        {
            Vector2D element_2d;
            std::vector<ImVec2> positions;

            if (element.contains("name"))
                calculated.name = element["name"];

            if (element.contains("x"))
                element_2d.x = int(float(element["x"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x"], base_2d.width)) : int(element["x"])) * scale);

            if (element.contains("y"))
                element_2d.y = int(float(element["y"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y"], base_2d.height)) : int(element["y"])) * scale);

            if (element.contains("width"))
                element_2d.width = int(float(element["width"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["width"], base_2d.width)) : int(element["width"])) * scale);

            if (element.contains("height"))
                element_2d.height = int(float(element["height"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["height"], base_2d.height)) : int(element["height"])) * scale);

            ImVec2 element_pos = { float(base_2d.x + element_2d.x), float(base_2d.y + element_2d.y) };
            ImVec2 element_size = { float(element_2d.width), float(element_2d.height) };
            const float element_scale = (element.contains("scale") ? float(element["scale"]) : 1.0f);

            calculated.scale = (element_scale * scale);

            calculated.color.enable = true;
            if (element.contains("color") && element["color"].is_array())
                calculated.color = { true, Utils::GetImColor(element["color"], opacity) };

            if (element.contains("fill") && element["fill"].is_array())
                calculated.fill = { true, Utils::GetImColor(element["fill"], opacity) };

            if (element.contains("stroke") && element["stroke"].is_array())
                calculated.stroke = { true, Utils::GetImColor(element["stroke"], opacity) };

            if (element["type"] == "text")
            {
                calculated.scale *= 2.0f;
                calculated.value = element["value"];
                calculated.wrap = (element.contains("wrap") ? bool(element["wrap"]) : false);
                calculated.shadow = (element.contains("shadow") ? bool(element["shadow"]) : false);

                Utils::ReplaceVars(calculated.value, theme_vars, [this, &element, &calculated, &opacity](const std::string &key, std::string &value) {
                    if (element.contains("sign") && element["sign"] == key)
                    {
                        bool positive = (value.at(0) != '-');
                        if (positive)
                            value = ("+" + value);
                    }

                    if (element.contains("chameleon") && element["chameleon"] == key)
                    {
                        bool positive = (value.at(0) != '-');
                        cvarManager->log("chameleon: " + calculated.name + " > " + (positive ? "positive" : "negative"));
                        calculated.color.color = Utils::GetImColor({ float(positive ? 30 : 224), float(positive ? 224 : 24), float(positive ? 24 : 24) }, opacity);
                    }
                });

                ImGui::SetWindowFontScale(calculated.scale);
                const ImVec2 string_size = ImGui::CalcTextSize(calculated.value.c_str());

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
                element_pos.x = float(base_2d.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x1"], base_2d.width)) : int(element["x1"])) * scale);
                element_pos.y = float(base_2d.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y1"], base_2d.height)) : int(element["y1"])) * scale);
                const float element_width = (element.contains("width") ? (float)element["width"] : 1);

                calculated.width = element_width;
                calculated.scale = (element_width * scale);

                positions.push_back(ImVec2{
                    float(base_2d.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x2"], base_2d.width)) : int(element["x2"])) * scale),
                    float(base_2d.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y2"], base_2d.height)) : int(element["y2"])) * scale)
                });
            }
            else if (element["type"] == "rectangle")
            {
                positions.push_back(ImVec2{
                    element_pos.x + element_2d.width,
                    element_pos.y + element_2d.height
                    });
            }
            else if (element["type"] == "triangle")
            {
                element_pos.x = float(base_2d.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x1"], base_2d.width)) : int(element["x1"])) * scale);
                element_pos.y = float(base_2d.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y1"], base_2d.height)) : int(element["y1"])) * scale);

                positions.push_back(ImVec2{
                    float(base_2d.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x2"], base_2d.width)) : int(element["x2"])) * scale),
                    float(base_2d.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y2"], base_2d.height)) : int(element["y2"])) * scale)
                    });
                positions.push_back(ImVec2{
                    float(base_2d.x) + (float(element["x3"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["x3"], base_2d.width)) : int(element["x3"])) * scale),
                    float(base_2d.y) + (float(element["y3"].is_string() ? Utils::EvaluateExpression(Utils::ExpressionSanitize(element["y3"], base_2d.height)) : int(element["y3"])) * scale)
                    });
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
                //else
                //    LogImageLoadStatus(theme_images[calculated.value]->IsLoadedForImGui(), (RS_theme + "->" + calculated.value));

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
        if (element.fill.enable)
        {
            if (element.type == "triangle")
                ImGui::GetOverlayDrawList()->AddTriangleFilled(element.positions.at(0), element.positions.at(1), element.positions.at(2), element.fill.color);
            else if (element.type == "rectangle")
                ImGui::GetOverlayDrawList()->AddRectFilled(element.positions.at(0), element.positions.at(1), element.fill.color, 0);
        }

        if (element.stroke.enable)
        {
            if (element.type == "triangle")
                ImGui::GetOverlayDrawList()->AddTriangle(element.positions.at(0), element.positions.at(1), element.positions.at(2), element.stroke.color, 1);
            else if (element.type == "rectangle")
                ImGui::GetOverlayDrawList()->AddRect(element.positions.at(0), element.positions.at(1), element.stroke.color, 0);
        }

        if (element.type == "image")
        {
            std::shared_ptr<ImageWrapper> image = theme_images[element.value];
            if (image->IsLoadedForImGui())
            {
                if (element.size.x && element.size.y)
                    ImGui::GetOverlayDrawList()->AddImage(image->GetImGuiTex(), element.positions.at(0), element.size);
                else
                    theme_refresh = 1;
            }
        }
        else if (element.type == "text")
        {
            ImGui::SetWindowFontScale(element.scale);
            ImGui::GetOverlayDrawList()->AddText(element.positions.at(0), element.color.color, element.value.c_str()); // element.shadow element.wrap
        }
        else if (element.type == "line")
            ImGui::GetOverlayDrawList()->AddLine(element.positions.at(0), element.positions.at(1), element.color.color, element.width);
    }
    catch (const std::exception&) {}
}
#pragma endregion

#pragma region File I / O
bool RocketStats::ExistsPath(std::string _filename, bool root)
{
    std::string _path = gameWrapper->GetBakkesModPath().string() + "/";

    if (root)
        _path += _filename;
    else
        _path += "RocketStats\\" + _filename;

    return fs::exists(_path);
}

bool RocketStats::RemoveFile(std::string _filename, bool root)
{
    if (!ExistsPath(_filename, root))
        return true;

    std::string _path = gameWrapper->GetBakkesModPath().string() + "/";

    if (root)
        _path += _filename;
    else
        _path += "RocketStats\\" + _filename;

    try
    {
        return fs::remove(_path);
    }
    catch (const std::exception&) {}

    return false;
}

std::string RocketStats::ReadFile(std::string _filename, bool root)
{
    std::string _value = "";
    std::string _path = gameWrapper->GetBakkesModPath().string() + "/";

    if (root)
        _path += _filename;
    else
        _path += rs_path + "/" + _filename;

    if (fs::is_regular_file(_path))
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
    std::string _path = gameWrapper->GetBakkesModPath().string() + "/";

    if (root)
        _path += _filename;
    else
        _path += rs_path + "/" + _filename;

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
    WriteInFile("RocketStats_GameMode.txt", GetPlaylistName(currentPlaylist));
}

void RocketStats::WriteMMR()
{
    std::string tmp = Utils::FloatFixer(stats[currentPlaylist].myMMR, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMR.txt", tmp);
}

void RocketStats::WriteMMRChange()
{
    Stats current = GetStats();
    std::string tmp = Utils::FloatFixer(current.MMRChange, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRChange.txt", (((current.MMRChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteMMRCumulChange()
{
    Stats current = GetStats();
    std::string tmp = Utils::FloatFixer(current.MMRCumulChange, (RS_enable_float ? 2 : 0));

    WriteInFile("RocketStats_MMRCumulChange.txt", (((current.MMRCumulChange > 0) ? "+" : "") + tmp));
}

void RocketStats::WriteWin()
{
    WriteInFile("RocketStats_Win.txt", std::to_string(GetStats().win));
}

void RocketStats::WriteLoss()
{
    WriteInFile("RocketStats_Loss.txt", std::to_string(GetStats().loss));
}

void RocketStats::WriteStreak()
{
    Stats current = GetStats();
    std::string tmp = std::to_string(current.streak);

    WriteInFile("RocketStats_Streak.txt", (((current.streak > 0) ? "+" : "") + tmp));
}
#pragma endregion

#pragma region PluginWindow
void RocketStats::Render()
{
    if (isSettingsOpen_)
        RenderSettings();

    RenderOverlay();
}

void RocketStats::RenderSettings()
{
    ImGui::SetNextWindowPos(ImVec2(128, 256), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin(menuTitle_.c_str(), &isSettingsOpen_, ImGuiWindowFlags_None);

    /*
    ImVec2 mouse = ImGui::GetIO().MousePos;
    ImGui::Text(("Mouse: " + std::to_string(mouse.x) + "x" + std::to_string(mouse.y)).c_str());
    float fps = ImGui::GetIO().Framerate;
    ImGui::Text(("Framerate: " + std::to_string(fps)).c_str());
    ImGui::Text("");
    */

    ImGui::Text("Informations mode");
    ImGui::SameLine();
    ImGui::Text("                                                                                                          ");
    ImGui::SameLine();
    if (ImGui::Button("Open folder"))
        system(("powershell -WindowStyle Hidden \"start \"\"" + gameWrapper->GetBakkesModPath().string() + "/" + rs_path + "\"\"\"").c_str());
    ImGui::SameLine();
    if (ImGui::Button("Reset Stats"))
        ResetStats();
    ImGui::SetNextItemWidth(250);
    ImGui::Combo((" " + cvarManager->getCvar("RS_mode").getDescription()).c_str(), &RS_mode, "Session\0GameMode\0Always\0");
    ImGui::SameLine();
    ImGui::Text("                         ");
    ImGui::SameLine();
    ImGui::Text((" " + cvarManager->getCvar("RS_enable_float").getDescription()).c_str());
    ImGui::SameLine();
    ImGui::Checkbox("##enable_float", &RS_enable_float);
    ImGui::SameLine();
    ImGui::Text((" " + cvarManager->getCvar("RS_enable_boost").getDescription()).c_str());
    ImGui::SameLine();
    ImGui::Checkbox("##enable_boost", &RS_enable_boost);

    ImGui::Text("");

    ImGui::Checkbox((" " + cvarManager->getCvar("RS_disp_overlay").getDescription()).c_str(), &RS_disp_overlay);
    //if (!RS_disp_overlay)
    //    ImGui::BeginDisabled();
    ImGui::SameLine();
    ImGui::Text("                                                            ");
    ImGui::SameLine();
    ImGui::Text((" " + cvarManager->getCvar("RS_hide_overlay_ig").getDescription()).c_str());
    ImGui::SameLine();
    ImGui::Checkbox("##hide_overlay_ig", &RS_hide_overlay_ig);
    ImGui::IsItemHovered();
    ImGui::SameLine();
    if (ImGui::Button("Reload Theme")) // change to "Reload Themes"
        ChangeTheme(RS_theme);
    ImGui::SetNextItemWidth(212);
    if (ImGui::BeginCombo("##themes_combo", themes.at(RS_theme).name.c_str(), ImGuiComboFlags_NoArrowButton))
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
    ImGui::SameLine(0, 0);
    if (ImGui::ArrowButton("##themes_left", ImGuiDir_Left) && RS_theme > 0)
        --RS_theme;
    ImGui::SameLine(0, 0);
    if (ImGui::ArrowButton("##themes_right", ImGuiDir_Right) && themes.size() && RS_theme < (themes.size() - 1))
        ++RS_theme;
    ImGui::SameLine();
    ImGui::Text((cvarManager->getCvar("RS_theme").getDescription() + "          ").c_str());
    ImGui::SameLine();
    ImGui::SetNextItemWidth(250);
    ImGui::SliderFloat((" " + cvarManager->getCvar("RS_scale").getDescription()).c_str(), &RS_scale, 0.f, 10.f, "%.3f");
    ImGui::SetNextItemWidth(250);
    ImGui::SliderFloat((" " + cvarManager->getCvar("RS_x_position").getDescription() + "     ").c_str(), &RS_x_position, 0.f, 1.f, "%.3f");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(250);
    ImGui::SliderFloat((" " + cvarManager->getCvar("RS_y_position").getDescription()).c_str(), &RS_y_position, 0.f, 1.f, "%.3f");
    //if (!RS_disp_overlay)
    //    ImGui::EndDisabled();

    ImGui::End();

    if (RS_mode != cvarManager->getCvar("RS_mode").getIntValue())
        cvarManager->getCvar("RS_mode").setValue(RS_mode);
    if (RS_theme != cvarManager->getCvar("RS_theme").getIntValue())
        cvarManager->getCvar("RS_theme").setValue(RS_theme);

    if (RS_enable_float != cvarManager->getCvar("RS_enable_float").getBoolValue())
        cvarManager->getCvar("RS_enable_float").setValue(RS_enable_float);
    if (RS_enable_boost != cvarManager->getCvar("RS_enable_boost").getBoolValue())
        cvarManager->getCvar("RS_enable_boost").setValue(RS_enable_boost);
    if (RS_disp_overlay != cvarManager->getCvar("RS_disp_overlay").getBoolValue())
        cvarManager->getCvar("RS_disp_overlay").setValue(RS_disp_overlay);
    if (RS_hide_overlay_ig != cvarManager->getCvar("RS_hide_overlay_ig").getBoolValue())
        cvarManager->getCvar("RS_hide_overlay_ig").setValue(RS_hide_overlay_ig);

    if (RS_scale != cvarManager->getCvar("RS_scale").getFloatValue())
        cvarManager->getCvar("RS_scale").setValue(RS_scale);
    if (RS_x_position != cvarManager->getCvar("RS_x_position").getFloatValue())
        cvarManager->getCvar("RS_x_position").setValue(RS_x_position);
    if (RS_y_position != cvarManager->getCvar("RS_y_position").getFloatValue())
        cvarManager->getCvar("RS_y_position").setValue(RS_y_position);
}

void RocketStats::RenderOverlay()
{
    if (!RS_disp_overlay || (isGameStarted && !isGameEnded && RS_hide_overlay_ig))
        return;

    ImGui::SetNextWindowPos(ImVec2(128, 256), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin((menuTitle_ + " - Overlay").c_str(), (bool*)1, (ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs));

    //try
    {
        if (theme_refresh || theme_render.name == "" || theme_render.name != themes.at(RS_theme).name)
        {
            Stats current = GetStats();
            ImVec2 screen_size = ImGui::GetIO().DisplaySize;

            std::vector<struct Element> elements;
            std::map<std::string, std::any> options = {
                { "pos_x", int(RS_x_position * screen_size.x) },
                { "pos_y", int(RS_y_position * screen_size.y) },
                { "scale", RS_scale },

                { "width", (theme_config.contains("width") ? int(theme_config["width"]) : 0) },
                { "height", (theme_config.contains("height") ? int(theme_config["height"]) : 0) },
                { "opacity", (theme_config.contains("opacity") ? float(theme_config["opacity"]) : 0.f) },

                { "stats", current }
            };

            cvarManager->log("pos_x: " + std::to_string(std::any_cast<int>(options["pos_x"])));
            cvarManager->log("pos_y: " + std::to_string(std::any_cast<int>(options["pos_y"])));
            cvarManager->log("width: " + std::to_string(std::any_cast<int>(options["width"])));
            cvarManager->log("height: " + std::to_string(std::any_cast<int>(options["height"])));
            cvarManager->log("scale: " + std::to_string(std::any_cast<float>(options["scale"])));
            cvarManager->log("opacity: " + std::to_string(std::any_cast<float>(options["opacity"])));

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
            theme_render.name = themes.at(RS_theme).name;
            theme_render.elements = elements;
        }

        for (auto& element : theme_render.elements)
            RenderElement(element);
    }
    //catch (const std::exception&) {}

    ImGui::End();
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
    //isSettingsOpen_ = true;
}

void RocketStats::OnClose()
{
    isSettingsOpen_ = false;
}
#pragma endregion