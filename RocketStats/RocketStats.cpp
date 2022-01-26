/* ==================================
 *   Developped by Lyliya & NuSa
 * ================================== */

#include "RocketStats.h"

BAKKESMOD_PLUGIN(RocketStats, "RocketStats", "4.0", PERMISSION_ALL)

#pragma region Utils
std::string RocketStats::GetRank(int tierID)
{
    cvarManager->log("tier: " + std::to_string(tierID));
    if (tierID <= rank_nb)
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

int RocketStats::OpacityColor(float opacity)
{
    return (int)std::max(0, std::min(255, (int)std::round(opacity * 255)));
}

char* RocketStats::GetColorAlpha(std::vector<float> color, float opacity)
{
    char result[] = {char(color[0]), char(color[1]), char(color[2]), char(255)};

    if (color.size() == 4)
        result[3] = OpacityColor(float(color[3]) * float(opacity));

    return result;
}

void RocketStats::LogImageLoadStatus(bool status, std::string imageName)
{
    if (status)
        cvarManager->log(imageName + ": image load");
    else
        cvarManager->log(imageName + ": failed to load");
}

std::shared_ptr<ImageWrapper> RocketStats::LoadImg(const std::string& _filename, bool canvasLoad)
{
    return std::make_shared<ImageWrapper>((gameWrapper->GetBakkesModPath().string() + "/" + rs_path + "/" + _filename), canvasLoad);
}

void RocketStats::LoadImgs()
{
    int load_check = 0;

    crown = LoadImg("RocketStats_images/crown.png");
    load_check += (int)crown->LoadForCanvas();
    LogImageLoadStatus(crown->LoadForCanvas(), "crown");

    win = LoadImg("RocketStats_images/win.png");
    load_check += (int)win->LoadForCanvas();
    LogImageLoadStatus(win->LoadForCanvas(), "win");

    loose = LoadImg("RocketStats_images/loose.png");
    load_check += (int)loose->LoadForCanvas();
    LogImageLoadStatus(loose->LoadForCanvas(), "loose");

    streak = LoadImg("RocketStats_images/streak.png");
    load_check += (int)streak->LoadForCanvas();
    LogImageLoadStatus(streak->LoadForCanvas(), "streak");

    for (int i = 0; i < rank_nb; i++)
    {
        rank[i].image = LoadImg("RocketStats_images/" + rank[i].name + ".png");
        load_check += (int)rank[i].image->LoadForCanvas();
        LogImageLoadStatus(rank[i].image->LoadForCanvas(), rank[i].name);
    }
    cvarManager->log(std::to_string(load_check) + "/27 images were loaded successfully");
}
#pragma endregion

#pragma region PluginLoadRoutines
void RocketStats::onLoad()
{
    // notifierToken = gameWrapper->GetMMRWrapper().RegisterMMRNotifier(std::bind(&RocketStats::UpdateMMR, this, std::placeholders::_1));

    if (!ExistsPath(rs_path, true))
        rs_path = "data/" + rs_path;
    cvarManager->log("RS_path: " + gameWrapper->GetBakkesModPath().string() + "/" + rs_path);

    LoadThemes();
    WriteSettings();

    LoadImgs();

    cvarManager->registerNotifier(
        "RocketStats_reload_theme",
        [this](std::vector<std::string> params)
        { ChangeTheme(theme_selected); },
        "Reload theme",
        PERMISSION_ALL);

    cvarManager->registerNotifier(
        "RocketStats_reload_images",
        [this](std::vector<std::string> params)
        { LoadImgs(); },
        "Reload images",
        PERMISSION_ALL);

    cvarManager->registerNotifier(
        "RocketStats_reset_stats",
        [this](std::vector<std::string> params)
        { ResetStats(); },
        "Reset Stats",
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
    cvarManager->registerCvar("RS_disp_ig", "1", "Display information panel", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_hide_overlay_ig", "0", "Hide overlay while in-game", true, true, 0, true, 1);
    cvarManager->registerCvar("RS_disp_mmr", "1", "Display the current MMR", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_disp_wins", "1", "Display the wins on the current game mode", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_disp_losses", "1", "Display the losses on the current game mode", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_disp_streak", "1", "Display the streak on the current game mode", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_disp_rank", "1", "Display the rank on the current game mode", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_disp_gamemode", "1", "Display the current game mode", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_enable_float", "0", "Enable floating point for MMR (OBS only)", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_x_position", "0.700", "Overlay X position", true, true, 0, true, 1.0f).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_y_position", "0.575", "Overlay Y position", true, true, 0, true, 1.0f).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_scale", "1", "Overlay scale", true, true, 0, true, 10).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RocketStats_stop_boost", "1", "Stop Boost animation", true, true, 0, true, 1).addOnValueChanged(std::bind(&RocketStats::RefreshTheme, this, std::placeholders::_1, std::placeholders::_2));
    cvarManager->registerCvar("RS_session", "0", "Display session information instead of game mode", true, true, 0, true, 1, true);
    cvarManager->registerCvar("RS_theme", "Default", "Theme", true).addOnValueChanged([this](std::string old, CVarWrapper now) {
        if (!ChangeTheme(now.getStringValue()))
            now.setValue(old);
    });
}

void RocketStats::onUnload() {}
#pragma endregion

void RocketStats::RefreshTheme(std::string old, CVarWrapper now)
{
    theme_refresh = true;
}

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
    WriteMMRChange();
    WriteWin();
    WriteStreak();
    WriteLosses();
    WriteMMR();

    // Get TeamNum
    myTeamNum = myTeam.GetTeamNum();

    // Set Game Started
    isGameStarted = true;
    isGameEnded = false;

    UpdateMMR(gameWrapper->GetUniqueID());
    WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));

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

            theme_refresh = true;
            WriteWin();
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

            theme_refresh = true;
            WriteLosses();
        }

        WriteStreak();

        // Reset myTeamNum security
        myTeamNum = -1;

        WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));

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

        WriteStreak();
        WriteLosses();
    }
    isGameEnded = true;
    isGameStarted = false;
    WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));

    theme_refresh = true;
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

    if (stats[currentPlaylist].isInit == false)
    {
        stats[currentPlaylist].myMMR = mmr;
        stats[currentPlaylist].isInit = true;
    }
    stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (mmr - stats[currentPlaylist].myMMR);
    stats[currentPlaylist].myMMR = mmr;

    MajRank(currentPlaylist, mmrw.IsRanked(currentPlaylist), stats[currentPlaylist].myMMR, playerRank);
    SessionStats();
    WriteMMR();
    WriteMMRChange();

    theme_refresh = true;
    cvarManager->log("===== !UpdateMMR =====");
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

    theme_refresh = true;
}

void RocketStats::ResetStats()
{
    for (auto &kv : stats)
        kv.second = Stats();
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
    theme_refresh = true;
}
#pragma endregion

#pragma region BoostMgmt
void RocketStats::OnBoostStart(std::string eventName)
{
    // Check if boost enabled in options
    bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
    if (!IsBoostEnabled || gameWrapper->IsInReplay() || isBoosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        if (!bWrap.IsNull() && bWrap.GetbActive() == 1 && !isBoosting)
        {
            isBoosting = true;
            theme_refresh = true;
            WriteInFile("RocketStats_images/BoostState.txt", std::to_string(1));
        }
    }

    return;
}

void RocketStats::OnBoostEnd(std::string eventName)
{
    // Check if boost enabled in options
    bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
    if (!IsBoostEnabled || gameWrapper->IsInReplay() || !isBoosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        if (!bWrap.IsNull() && bWrap.GetbActive() == 0 && isBoosting)
        {
            isBoosting = false;
            theme_refresh = true;
            WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));
        }
    }
    return;
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
        if (playerRank.MatchesPlayed < 10)
        {
            currentRank = "Placement: " + std::to_string(playerRank.MatchesPlayed) + "/10";
            currentDivision = "";
        }
        else
        {
            currentRank = GetRank(playerRank.Tier);
            currentDivision = "Div. " + std::to_string(playerRank.Division + 1);

            theme_refresh = true;
            WriteInFile("RocketStats_Div.txt", currentDivision);
        }

        if (currentRank != lastRank)
        {
            theme_refresh = true;
            WriteInFile("RocketStats_Rank.txt", currentRank);
        }
    }
    else
    {
        currentRank = GetPlaylistName(currentGameMode);
        currentDivision = "";

        theme_refresh = true;
        WriteInFile("RocketStats_Rank.txt", currentRank);
    }
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
                                pages_images.push_back(std::make_shared<ImageWrapper>(fonts_path + "/" + page_filename, true));
                            }

                            theme.fonts.push_back(font);
                        }
                    }
                }

                themes.push_back(theme);
            }
        }
    }

    cvarManager->log("===== !LoadThemes =====");
}

bool RocketStats::ChangeTheme(std::string name)
{
    cvarManager->log("===== ChangeTheme =====");

    try
    {
        theme_config = json::parse(ReadFile("RocketStats_themes/" + name + "/config.json"));
        cvarManager->log(nlohmann::to_string(theme_config));

        if (theme_config.type() == json::value_t::object)
        {
            cvarManager->log("Theme changed: " + name + " (old: " + theme_selected + ")");
            theme_selected = name;
            theme_refresh = true;
        }
        else
            cvarManager->log("Theme config: " + name + " bad JSON");
    }
    catch (json::parse_error& e)
    {
        cvarManager->log("Theme config: " + name + " bad JSON -> " + e.what());
    }

    cvarManager->log("===== !ChangeTheme =====");
    return (theme_selected == name);
}

void RocketStats::DisplayRank(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, float scale, bool showText)
{
    if (currentTier >= rank_nb)
        currentTier = 0;
    std::shared_ptr<ImageWrapper> image = rank[currentTier].image;

    canvas.SetColor(LinearColor{255, 255, 255, 255});
    canvas.SetPosition(imagePos);
    if (image->IsLoadedForCanvas())
        canvas.DrawTexture(image.get(), 0.5f * scale);

    if (showText)
    {
        std::string tmpRank = currentRank;
        Utils::ReplaceAll(tmpRank, "_", " ");
        canvas.SetPosition(textPos_tmp);
        if (currentDivision == "")
            canvas.DrawString(tmpRank, 2.0f * scale, 2.0f * scale);
        else
            canvas.DrawString(tmpRank + " " + currentDivision, 2.0f * scale, 2.0f * scale);
    }
}
void RocketStats::DisplayMMR(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale, bool showImage)
{
    std::string mmr = to_string_with_precision(current.myMMR, 2);
    std::string change = to_string_with_precision(current.MMRChange, 2);

    if (showImage)
    {
        canvas.SetColor(LinearColor{255, 255, 255, 255});
        canvas.SetPosition(imagePos);
        if (crown->IsLoadedForCanvas())
            canvas.DrawTexture(crown.get(), 0.5f * scale);
    }

    canvas.SetColor(LinearColor{255, 255, 255, 255});
    canvas.SetPosition(textPos_tmp);
    if (current.MMRChange > 0)
        change = "+" + change;
    canvas.DrawString(mmr + " (" + change + ")", 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayWins(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
    canvas.SetColor(LinearColor{255, 255, 255, 255});
    canvas.SetPosition(imagePos);
    if (win->IsLoadedForCanvas())
        canvas.DrawTexture(win.get(), 0.5f * scale);

    canvas.SetColor(LinearColor{0, 255, 0, 255});
    canvas.SetPosition(textPos_tmp);
    canvas.DrawString(std::to_string(current.win), 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayLoose(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
    canvas.SetColor(LinearColor{255, 255, 255, 255});
    canvas.SetPosition(imagePos);
    if (loose->IsLoadedForCanvas())
        canvas.DrawTexture(loose.get(), 0.5f * scale);

    canvas.SetColor(LinearColor{255, 0, 0, 255});
    canvas.SetPosition(textPos_tmp);
    canvas.DrawString(std::to_string(current.losses), 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayStreak(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale, bool showImage)
{
    if (showImage)
    {
        canvas.SetColor(LinearColor{255, 255, 255, 255});
        canvas.SetPosition(imagePos);
        if (streak->IsLoadedForCanvas())
            canvas.DrawTexture(streak.get(), 0.5f * scale);
    }

    canvas.SetColor(LinearColor{255, 255, 255, 255});
    canvas.SetPosition(textPos_tmp);

    if (current.streak < 0)
        canvas.SetColor(LinearColor{255, 0, 0, 255});
    else
        canvas.SetColor(LinearColor{0, 255, 0, 255});

    std::string streak = std::to_string(current.streak);
    if (current.streak > 0)
        streak = "+" + streak;

    canvas.DrawString(streak, 2.0f * scale, 2.0f * scale);
}

void RocketStats::Render(CanvasWrapper canvas)
{
    bool RS_disp_ig = cvarManager->getCvar("RS_disp_ig").getBoolValue();
    bool RS_hide_overlay_ig = cvarManager->getCvar("RS_hide_overlay_ig").getBoolValue();

    if (!RS_disp_ig || isGameStarted && !isGameEnded && RS_hide_overlay_ig)
        return;

    bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
    Stats current = (RS_session == true) ? session : stats[currentPlaylist];

    try
    {
        if (theme_refresh || theme_render.name == "" || theme_render.name != theme_selected)
        {
            const Vector2 can_size = canvas.GetSize();

            std::vector<struct Element> elements;
            std::map<std::string, std::any> options = {
                { "pos_x", int(can_size.X * cvarManager->getCvar("RS_x_position").getFloatValue()) },
                { "pos_y", int(can_size.Y * cvarManager->getCvar("RS_y_position").getFloatValue()) },
                { "scale", float(cvarManager->getCvar("RS_scale").getFloatValue()) },
                { "session", cvarManager->getCvar("RS_session").getBoolValue() },
                { "floating_point", cvarManager->getCvar("RS_enable_float").getBoolValue() },

                { "width", int(theme_config["width"]) },
                { "height", int(theme_config["height"]) },
                { "opacity", float(theme_config["opacity"]) },

                { "stats", current }
            };

            theme_images.clear();
            for (auto& element : theme_config["elements"])
            {
                bool check = false;
                struct Element calculated = CalculateElement(canvas, element, options, check);
                if (check)
                    elements.push_back(calculated);
            }

            theme_refresh = false;
            theme_render.name = theme_selected;
            theme_render.elements = elements;

            cvarManager->log("Theme refresh: " + std::to_string(theme_refresh));
        }

        for (auto& element : theme_render.elements)
            RenderElement(canvas, element);
    }
    catch (const std::exception&) {}
}

struct Element RocketStats::CalculateElement(CanvasWrapper& canvas, json& element, std::map<std::string, std::any>& options, bool& check)
{
    check = false;
    struct Element calculated;

    if (!element.contains("visible") || element["visible"])
    {
        const auto can_size = canvas.GetSize();

        int pos_x = std::any_cast<int>(options["pos_x"]);
        int pos_y = std::any_cast<int>(options["pos_y"]);
        float scale = std::any_cast<float>(options["scale"]);
        bool session = std::any_cast<bool>(options["session"]);
        bool floating_point = std::any_cast<bool>(options["floating_point"]);

        int width = std::any_cast<int>(options["width"]);
        int height = std::any_cast<int>(options["height"]);
        float opacity = std::any_cast<float>(options["opacity"]);

        Stats current = std::any_cast<Stats>(options["stats"]);

        //try
        {
            std::vector<Vector2> positions;

            Vector2 element_pos = { (pos_x + (element.contains("x") ? int(float(element["x"]) * scale) : 0)), (pos_y + (element.contains("y") ? int(float(element["y"]) * scale) : 0)) };
            const Vector2 element_size = { ((element.contains("width") ? int(float(element["width"]) * scale) : 0)), ((element.contains("height") ? int(float(element["height"]) * scale) : 0)) };
            const float element_scale = (element.contains("scale") ? float(element["scale"]) : 1.0f);

            calculated.scale = (element_scale * scale);

            calculated.color.enable = true;
            if (element.contains("color"))
            {
                char* color = GetColorAlpha(element["color"], opacity);
                calculated.color = { true, color[0], color[1], color[2], color[3] };
            }

            if (element.contains("fill") && element["fill"].type() == json::value_t::array)
            {
                char* color = GetColorAlpha(element["fill"], opacity);
                calculated.fill = { true, color[0], color[1], color[2], color[3] };
            }

            if (element.contains("stroke") && element["stroke"].type() == json::value_t::array)
            {
                char* color = GetColorAlpha(element["stroke"], opacity);
                calculated.stroke = { true, color[0], color[1], color[2], color[3] };
            }

            if (element["type"] == "text")
            {
                calculated.scale *= 2.0f;
                calculated.wrap = (element.contains("wrap") ? bool(element["wrap"]) : false);
                calculated.shadow = (element.contains("shadow") ? bool(element["shadow"]) : false);

                if (element.contains("variable") && current.isInit)
                {
                    if (element["variable"] == "MMR")
                        calculated.value = to_string_with_precision(current.myMMR, (floating_point ? 2 : 0));
                    else if (element["variable"] == "MMRChange")
                        calculated.value = to_string_with_precision(current.MMRChange, (floating_point ? 2 : 0));
                    else if (element["variable"] == "Win")
                        calculated.value = std::to_string(current.win);
                    else if (element["variable"] == "Loose")
                        calculated.value = std::to_string(current.losses);
                    else if (element["variable"] == "Streak")
                        calculated.value = std::to_string(current.streak);
                }
                else
                    calculated.value = element["value"];

                if (element.contains("prefix"))
                    calculated.value = (std::string(element["prefix"]) + calculated.value);

                if (element.contains("suffix"))
                    calculated.value += std::string(element["suffix"]);

                const Vector2F string_size = canvas.GetStringSize(calculated.value, element["scale"], element["scale"]);
                element_pos.Y -= int(std::round(float(string_size.Y) * scale / 2)); // fix Y position

                if (element.contains("align") && element["align"].type() == json::value_t::string)
                {
                    if (element["align"] == "right")
                        element_pos.X -= int(float(string_size.X) * scale);
                    else if (element["align"] == "center")
                        element_pos.X -= int(std::round(float(string_size.X) * scale / 2));
                }

                if (element.contains("valign") && element["valign"].type() == json::value_t::string)
                {
                    if (element["valign"] == "bottom")
                        element_pos.Y -= int(float(string_size.Y) * scale);
                    else if (element["valign"] == "middle")
                        element_pos.Y -= int(std::round(float(string_size.Y) * scale / 2));
                }
            }
            else if (element["type"] == "line")
            {
                element_pos = { (pos_x + int(float(element["x1"]) * scale)), (pos_y + int(float(element["y1"]) * scale)) };
                const float element_width = (element.contains("width") ? (float)element["width"] : 1);

                calculated.width = element_width;
                calculated.scale = (element_width * scale);

                positions.push_back(Vector2{ (pos_x + int(float(element["x2"]) * scale)), (pos_y + int(float(element["y2"]) * scale)) });
            }
            else if (element["type"] == "triangle")
            {
                element_pos = { (pos_x + int(float(element["x1"]) * scale)), (pos_y + int(float(element["y1"]) * scale)) };

                positions.push_back(Vector2{ (pos_x + int(float(element["x2"]) * scale)), (pos_y + int(float(element["y2"]) * scale)) });
                positions.push_back(Vector2{ (pos_x + int(float(element["x3"]) * scale)), (pos_y + int(float(element["y3"]) * scale)) });
            }
            else if (element["type"] == "image")
            {
                calculated.scale *= 0.5f;
                calculated.value = element["file"];
                if (!theme_images[calculated.value])
                {
                    theme_images[calculated.value] = LoadImg("RocketStats_themes/" + theme_selected + "/images/" + calculated.value);
                    LogImageLoadStatus(theme_images[calculated.value]->LoadForCanvas(), (theme_selected + "->" + calculated.value));
                }
            }

            positions.emplace(positions.begin(), element_pos);

            calculated.type = element["type"];
            calculated.positions = positions;
            calculated.size = element_size;

            check = true;
        }
        //catch (const std::exception&) {}
    }

    return calculated;
}

void RocketStats::RenderElement(CanvasWrapper& canvas, Element& element)
{
    try
    {
        if (element.fill.enable)
        {
            canvas.SetColor(element.fill.r, element.fill.g, element.fill.b, element.fill.alpha);

            canvas.SetPosition(element.positions.at(0));
            if (element.type == "triangle")
                canvas.FillTriangle(element.positions.at(0), element.positions.at(1), element.positions.at(2), canvas.GetColor());
            else if (element.type == "rectangle")
                canvas.FillBox(element.size);
        }

        if (element.stroke.enable)
        {
            canvas.SetColor(element.stroke.r, element.stroke.g, element.stroke.b, element.stroke.alpha);

            canvas.SetPosition(element.positions.at(0));
            if (element.type == "triangle")
            {
                canvas.DrawLine(element.positions.at(0), element.positions.at(1), 1);
                canvas.DrawLine(element.positions.at(1), element.positions.at(2), 1);
                canvas.DrawLine(element.positions.at(2), element.positions.at(0), 1);
            }
            else if (element.type == "rectangle")
                canvas.DrawBox(element.size);
        }

        canvas.SetPosition(element.positions.at(0));
        canvas.SetColor(element.color.r, element.color.g, element.color.b, element.color.alpha);

        if (element.type == "image")
        {
            std::shared_ptr<ImageWrapper> image = theme_images[element.value];
            if (image->IsLoadedForCanvas())
                canvas.DrawTexture(image.get(), element.scale);
        }
        else if (element.type == "line")
            canvas.DrawLine(element.positions.at(0), element.positions.at(1), element.width);
        else if (element.type == "text")
            canvas.DrawString(element.value, element.scale, element.scale, element.shadow, element.wrap);
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

void RocketStats::WriteSettings()
{
    cvarManager->log("===== WriteSettings =====");

    std::string file = "plugins/settings/rocketstats.set";

    if (!ExistsPath(file, true))
    {
        const std::string settings = R"(RocketStats Plugin
9|Check/Uncheck what you want to display
1|Display session information instead of game mode|RS_session
7|
1|Enable Boost|RocketStats_stop_boost
1|Display information in game|RS_disp_ig
7|
10|RS_disp_ig
7|
1|Hide overlay while in-game|RS_hide_overlay_ig
7|
1|Enable floating point for MMR (OBS only)|RS_enable_float
6|Theme|RS_theme|Default@Default&Redesigned@Redesigned
1|Display Game Mode|RS_disp_gamemode
7|
1|Display Rank|RS_disp_rank
7|
1|Display MMR|RS_disp_mmr
7|
1|Display Wins|RS_disp_wins
7|
1|Display Losses|RS_disp_losses
7|
1|Display Streak|RS_disp_streak
9|
9|Place your overlay (Only if display information in game is check)
4|X position|RS_x_position|0|1.0
4|Y position|RS_y_position|0|1.0
4|Scale|RS_scale|0|10
11|
9|
0|Reload Theme|RocketStats_reload_theme
7|
0|Reload Pictures|RocketStats_reload_images
7|
0|Reset|RocketStats_reset_stats
8|
9|Version 4.0, Developped by @Lyliiya & @NuSa_yt for @Maylie_tv
9|Update in 4.0 by Arubinu#9947 (Arubinu42 complex themes in game)
9|Update in 3.5 by marioesho, Arubinu#9947 (Arubinu42 theme in game)
9|Update in 3.4 by Larsluph#7713, Arubinu#9947 (Rank display in OBS)
9|Update in 3.2 by Larsluph#7713
9|Update in 3.0 by Lyliya#4276, Larsluph#7713 (EpicGames integration)
9|Update in 2.2 by Lyliya#4276, Larsluph#7713 (scale and v1 toggle, MMR and session Fix)
9|Update in 2.1 by Lyliya#4276, Th3Ant#9411, Larsluph#7713 (resolution fix, placement match)
9|Update in 2.0 by Lyliya#4276, Larsluph#7713, Th3Ant#9411 & NuSa#0666 (New overlay, new ranks, bugfix)
9|Donate : https://www.paypal.me/rocketstats
)";
    
        const size_t start = (settings.find("|RS_theme|") + 10);
        const size_t end = std::min(settings.find("\r", start), settings.find("\n", start));

        std::string themes_names = "Default@Default&Redesigned@Redesigned";
        for (auto& theme : themes)
        {
            cvarManager->log(" > " + theme.name);
            themes_names += "&" + theme.name + "@" + theme.name;
        }

        cvarManager->log("=====> WriteSettings: Exists");
        WriteInFile(file, (settings.substr(0, start) + themes_names + settings.substr(end)), true);
        cvarManager->executeCommand("cl_settings_refreshplugins");
    }

    gameWrapper->SetTimeout([this, file](GameWrapper* gameWrapper) {
        RemoveFile(file, true);
    }, 3.000f);

    cvarManager->log("===== !WriteSettings =====");
}

void RocketStats::WriteGameMode()
{
    WriteInFile("RocketStats_GameMode.txt", GetPlaylistName(currentPlaylist));
}

void RocketStats::WriteMMR()
{
    std::string tmp;
    if (cvarManager->getCvar("RS_enable_float").getBoolValue())
        tmp = to_string_with_precision(stats[currentPlaylist].myMMR, 2);
    else
        tmp = std::to_string(int(stats[currentPlaylist].myMMR));
    WriteInFile("RocketStats_MMR.txt", tmp);
}
void RocketStats::WriteMMRChange()
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

void RocketStats::WriteStreak()
{
    bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
    Stats current = (RS_session == true) ? session : stats[currentPlaylist];

    if (current.streak > 0)
        WriteInFile("RocketStats_Streak.txt", "+" + std::to_string(current.streak));
    else
        WriteInFile("RocketStats_Streak.txt", std::to_string(current.streak));
}

void RocketStats::WriteWin()
{
    bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
    Stats current = (RS_session == true) ? session : stats[currentPlaylist];
    WriteInFile("RocketStats_Win.txt", std::to_string(current.win));
}

void RocketStats::WriteLosses()
{
    bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
    Stats current = (RS_session == true) ? session : stats[currentPlaylist];
    WriteInFile("RocketStats_Loose.txt", std::to_string(current.losses));
}
#pragma endregion
