/* ==================================
 *   Developped by Lyliya & NuSa
 * ================================== */

#include "RocketStats.h"
#include <fstream>
#include <utils/parser.h>

BAKKESMOD_PLUGIN(RocketStats, "RocketStats", "3.4", PERMISSION_ALL)

#pragma region utils
std::string RocketStats::GetRank(int tierID)
{
	cvarManager->log("tier: " + std::to_string(tierID));
	if (tierID <= rank_nb) return rank[tierID].name;
	else return "Unranked";
}

std::string RocketStats::GetPlaylistName(int playlistID)
{
	if (playlistName.find(playlistID) != playlistName.end()) return playlistName.at(playlistID);
	else return "Unknown Game Mode";
}

void RocketStats::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	while (replace(str, from, to)) {}
}

void RocketStats::LoadImgs()
{
	int load_check = 0;

	background = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\RocketStats_images\\background.png", true);
	load_check += (int)background->LoadForCanvas();
	LogImageLoadStatus(background->LoadForCanvas(), "background");

	crown = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\RocketStats_images\\crown.png", true);
	load_check += (int)crown->LoadForCanvas();
	LogImageLoadStatus(crown->LoadForCanvas(), "crown");

	win = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\RocketStats_images\\win.png", true);
	load_check += (int)win->LoadForCanvas();
	LogImageLoadStatus(win->LoadForCanvas(), "win");

	loose = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\RocketStats_images\\loose.png", true);
	load_check += (int)loose->LoadForCanvas();
	LogImageLoadStatus(loose->LoadForCanvas(), "loose");

	streak = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\RocketStats_images\\streak.png", true);
	load_check += (int)streak->LoadForCanvas();
	LogImageLoadStatus(streak->LoadForCanvas(), "streak");

	for (int i = 0; i < rank_nb; i++)
	{
		rank[i].image = std::make_shared<ImageWrapper>(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\RocketStats_images\\" + rank[i].name + ".png", true);
		load_check += (int)rank[i].image->LoadForCanvas();
		LogImageLoadStatus(rank[i].image->LoadForCanvas(), rank[i].name);
	}
	cvarManager->log(std::to_string(load_check) + "/26 images were loaded successfully");
}

void RocketStats::LogImageLoadStatus(bool status, std::string imageName) {
	if (status) cvarManager->log(imageName + ": image load");
	else cvarManager->log(imageName + ": failed to load");
}
#pragma endregion

#pragma region PluginLoadRoutines
void RocketStats::onLoad()
{
	//notifierToken = gameWrapper->GetMMRWrapper().RegisterMMRNotifier(std::bind(&RocketStats::UpdateMMR, this, std::placeholders::_1));

	LoadImgs();

	cvarManager->registerNotifier(
		"RocketStats_reset_stats",
		[this](std::vector<std::string> params) { ResetStats(); },
		"Reset Stats",
		PERMISSION_ALL
	);

	cvarManager->registerNotifier(
		"RocketStats_reload_images",
		[this](std::vector<std::string> params) { LoadImgs(); },
		"Reload images",
		PERMISSION_ALL
	);

	// Register drawable
	gameWrapper->RegisterDrawable(std::bind(&RocketStats::Render, this, std::placeholders::_1));

	// Hook on Event
	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&RocketStats::GameStart, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&RocketStats::GameEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", bind(&RocketStats::OnBoostStart, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Destroyed", bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));

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
#pragma endregion

#pragma region GameMgmt
void RocketStats::GameStart(std::string eventName)
{
	if (!gameWrapper->IsInOnlineGame() || isGameStarted) return;

	cvarManager->log("===== GameStart =====");
	CarWrapper me = gameWrapper->GetLocalCar();
	if (me.IsNull()) return;

	PriWrapper mePRI = me.GetPRI();
	if (mePRI.IsNull()) return;

	TeamInfoWrapper myTeam = mePRI.GetTeam();
	if (myTeam.IsNull()) return;

	MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
	currentPlaylist = mmrw.GetCurrentPlaylist();
	SkillRank playerRank = mmrw.GetPlayerRank(gameWrapper->GetUniqueID(), currentPlaylist);
	cvarManager->log(std::to_string(currentPlaylist) + " -> " + GetPlaylistName(currentPlaylist));

	writeGameMode();
	writeMMRChange();
	writeWin();
	writeStreak();
	writeLosses();
	writeMMR();

	// Get TeamNum
	myTeamNum = myTeam.GetTeamNum();

	// Set Game Started
	isGameStarted = true;
	isGameEnded = false;

	UpdateMMR(gameWrapper->GetUniqueID());
	WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));
}

void RocketStats::GameEnd(std::string eventName)
{
	if (gameWrapper->IsInOnlineGame() && myTeamNum != -1)
	{
		cvarManager->log("===== GameEnd =====");
		ServerWrapper server = gameWrapper->GetOnlineGame();
		TeamWrapper winningTeam = server.GetGameWinner();
		if (winningTeam.IsNull()) return;

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

			writeWin();
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

			writeLosses();
		}

		writeStreak();

		// Reset myTeamNum security
		myTeamNum = -1;

		WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));

		gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
			UpdateMMR(gameWrapper->GetUniqueID());
		}, 3.0F);
	}
}

void RocketStats::GameDestroyed(std::string eventName)
{
	cvarManager->log("===== GameDestroyed =====");
	//Check if Game Ended, if not, RAGE QUIT or disconnect
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

		writeStreak();
		writeLosses();
	}
	isGameEnded = true;
	isGameStarted = false;
	WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
}
#pragma endregion

#pragma region StatsMgmt
void RocketStats::UpdateMMR(UniqueIDWrapper id)
{
	cvarManager->log("===== updateMMR =====");
	/*
	if (id.GetIdString() != gameWrapper->GetUniqueID().GetIdString()) {
		cvarManager->log("not the user");
		return;
	}
	cvarManager->log("user match");
	*/

	if (currentPlaylist == 0) {
		cvarManager->log("Invalid playlist id. Have you just opened the game ?");
		return;
	}

	MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
	float mmr = mmrw.GetPlayerMMR(id, currentPlaylist);
	SkillRank playerRank = mmrw.GetPlayerRank(id, currentPlaylist);

	if (stats[currentPlaylist].isInit == false) {
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
	WriteInFile("RocketStats_GameMode.txt", "");

	InitRank();
}
#pragma endregion

#pragma region BoostMgmt
void RocketStats::OnBoostStart(std::string eventName)
{
	// Check if boost enabled in options
	bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
	if (!IsBoostEnabled || gameWrapper->IsInReplay() || isBoosting) return;

	CarWrapper cWrap = gameWrapper->GetLocalCar();

	if (!cWrap.IsNull())
	{
		BoostWrapper bWrap = cWrap.GetBoostComponent();

		if (!bWrap.IsNull() && bWrap.GetbActive() == 1 && !isBoosting)
		{
			isBoosting = true;
			WriteInFile("RocketStats_images/BoostState.txt", std::to_string(1));
		}
	}

	return;
}

void RocketStats::OnBoostEnd(std::string eventName)
{
	// Check if boost enabled in options
	bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
	if (!IsBoostEnabled || gameWrapper->IsInReplay() || !isBoosting) return;

	CarWrapper cWrap = gameWrapper->GetLocalCar();

	if (!cWrap.IsNull())
	{
		BoostWrapper bWrap = cWrap.GetBoostComponent();

		if (!bWrap.IsNull() && bWrap.GetbActive() == 0 && isBoosting)
		{
			isBoosting = false;
			WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));
		}
	}
	return;
}

// Act as toggle
//void RocketStats::StopBoost() {}
#pragma endregion

#pragma region Rank/Div
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
		if (playerRank.MatchesPlayed < 10)
		{
			currentRank = "Placement: " + std::to_string(playerRank.MatchesPlayed) + "/10";
			currentDivision = "";
		}
		else
		{
			currentRank = GetRank(playerRank.Tier);
			currentDivision = "Div. " + std::to_string(playerRank.Division + 1);
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
#pragma endregion

#pragma region OverlayMgmt
void RocketStats::DisplayRank(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, float scale, bool showRankText)
{
	std::string tmpRank = currentRank;
	if (currentTier >= rank_nb)
	{
		currentTier = 0;
	}
	std::shared_ptr<ImageWrapper> image = rank[currentTier].image;
	replaceAll(tmpRank, "_", " ");

	canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
	canvas.SetPosition(imagePos);
	if (image->IsLoadedForCanvas()) canvas.DrawTexture(image.get(), 0.5f * scale);

	if (showRankText)
	{
		canvas.SetPosition(textPos_tmp);
		if (currentDivision == "") canvas.DrawString(tmpRank, 2.0f * scale, 2.0f * scale);
		else canvas.DrawString(tmpRank + " " + currentDivision, 2.0f * scale, 2.0f * scale);
	}
}

void RocketStats::DisplayMMR(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale, bool showMMRImage)
{
	std::string mmr = to_string_with_precision(current.myMMR, 2);
	std::string change = to_string_with_precision(current.MMRChange, 2);

	if (showMMRImage)
	{
		canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
		canvas.SetPosition(imagePos);
		if (crown->IsLoadedForCanvas()) canvas.DrawTexture(crown.get(), 0.5f * scale);
	}

	canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
	canvas.SetPosition(textPos_tmp);
	if (current.MMRChange > 0) change = "+" + change;
	canvas.DrawString(mmr + " (" + change + ")", 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayWins(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
	canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
	canvas.SetPosition(imagePos);
	if (win->IsLoadedForCanvas()) canvas.DrawTexture(win.get(), 0.5f * scale);

	canvas.SetColor(LinearColor{ 0, 255, 0, 255 });
	canvas.SetPosition(textPos_tmp);
	canvas.DrawString(std::to_string(current.win), 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayLoose(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
	canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
	canvas.SetPosition(imagePos);
	if (loose->IsLoadedForCanvas()) canvas.DrawTexture(loose.get(), 0.5f * scale);

	canvas.SetColor(LinearColor{ 255, 0, 0, 255 });
	canvas.SetPosition(textPos_tmp);
	canvas.DrawString(std::to_string(current.losses), 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayStreak(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
	canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
	canvas.SetPosition(imagePos);
	if (streak->IsLoadedForCanvas()) canvas.DrawTexture(streak.get(), 0.5f * scale);

	canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
	canvas.SetPosition(textPos_tmp);

	if (current.streak < 0) canvas.SetColor(LinearColor{ 255, 0, 0, 255 });
	else canvas.SetColor(LinearColor{ 0, 255, 0, 255 });

	std::string streak = std::to_string(current.streak);
	if (current.streak > 0) streak = "+" + streak;

	canvas.DrawString(streak, 2.0f * scale, 2.0f * scale);
}

void RocketStats::Render(CanvasWrapper canvas)
{
	bool RS_disp_ig = cvarManager->getCvar("RS_disp_ig").getBoolValue();
	bool RS_hide_overlay_ig = cvarManager->getCvar("RS_hide_overlay_ig").getBoolValue();

	if (!RS_disp_ig || isGameStarted && !isGameEnded && RS_hide_overlay_ig) return;

	bool RS_Use_v1 = cvarManager->getCvar("RS_Use_v1").getBoolValue();
	bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
	float RS_x_position = cvarManager->getCvar("RS_x_position").getFloatValue();
	float RS_y_position = cvarManager->getCvar("RS_y_position").getFloatValue();
	float RS_scale = cvarManager->getCvar("RS_scale").getFloatValue();
	Stats current = (RS_session == true) ? session : stats[currentPlaylist];

	if (!RS_Use_v1)
	{
		auto canSize = canvas.GetSize();
		Vector2 imagePos = { int(RS_x_position * canSize.X), int(RS_y_position * canSize.Y) };

		// Add Background
		canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
		canvas.SetPosition(imagePos);
		if (background->IsLoadedForCanvas()) canvas.DrawTexture(background.get(), RS_scale * 1.3);
		imagePos.X += int(45 * RS_scale);

		Vector2 textPos_tmp = imagePos;

		textPos_tmp.X += int(70 * RS_scale);
		textPos_tmp.Y += int(10 * RS_scale);

		// Display Rank
		if (cvarManager->getCvar("RS_disp_rank").getBoolValue())
		{
			DisplayRank(canvas, imagePos, textPos_tmp, RS_scale, false);
		}

		// Display MMR
		if (cvarManager->getCvar("RS_disp_mmr").getBoolValue())
		{
			DisplayMMR(canvas, imagePos, textPos_tmp, current, RS_scale, false);
			imagePos.X += int(305 * RS_scale);
			textPos_tmp.X += int(305 * RS_scale);
		}

		// Display Win
		if (cvarManager->getCvar("RS_disp_wins").getBoolValue())
		{
			DisplayWins(canvas, imagePos, textPos_tmp, current, RS_scale);
			imagePos.X += int(110 * RS_scale);
			textPos_tmp.X += int(110 * RS_scale);
		}

		// Display Loose
		if (cvarManager->getCvar("RS_disp_losses").getBoolValue())
		{
			DisplayLoose(canvas, imagePos, textPos_tmp, current, RS_scale);
			imagePos.X += int(110 * RS_scale);
			textPos_tmp.X += int(110 * RS_scale);
		}

		// Display Streak
		if (cvarManager->getCvar("RS_disp_streak").getBoolValue())
		{
			DisplayStreak(canvas, imagePos, textPos_tmp, current, RS_scale);
		}
	}
	else
	{
		std::vector<std::string> RS_values = {
			"RS_disp_gamemode",
			"RS_disp_rank",
			"RS_disp_mmr",
			"RS_disp_wins",
			"RS_disp_losses",
			"RS_disp_streak",
		};

		unsigned int size = 0;
		for (auto& it : RS_values)
		{
			bool tmp = cvarManager->getCvar(it).getBoolValue();
			if (tmp) size += 1;
			if (it == "RS_disp_mmr") size += 1;
		}

		// Draw box here
		Vector2 drawLoc = {
			int(canvas.GetSize().X * RS_x_position),
			int(canvas.GetSize().Y * RS_y_position)
		};
		Vector2 sizeBox = {
			int(175 * RS_scale),
			int((23 * size) * RS_scale)
		};
		canvas.SetPosition(drawLoc);

		//Set background color
		canvas.SetColor(LinearColor{ 0, 0, 0, 150 });
		canvas.FillBox(sizeBox);

		// Draw text
		Vector2 textPos = { int(drawLoc.X + 10), int(drawLoc.Y + 10) };
		for (auto& it : RS_values)
		{
			bool tmp = cvarManager->getCvar(it).getBoolValue();

			if (tmp)
			{
				//Set the position
				canvas.SetPosition(textPos);

				//Set Color and Text for the value
				if (it == "RS_disp_gamemode")
				{
					canvas.SetColor(LinearColor{ 180, 180, 180, 255 });
					canvas.DrawString(GetPlaylistName(currentPlaylist), RS_scale, RS_scale);
				}
				else if (it == "RS_disp_rank")
				{
					std::string tmpRank = currentRank;
					if (currentTier >= rank_nb) currentTier = 0;
					replaceAll(tmpRank, "_", " ");
					canvas.SetColor(LinearColor{ 180, 180, 180, 255 });
					if (currentDivision == "") canvas.DrawString(tmpRank, RS_scale, RS_scale);
					else canvas.DrawString(tmpRank + " " + currentDivision, RS_scale, RS_scale);
				}
				else if (it == "RS_disp_mmr")
				{
					canvas.SetColor(LinearColor{ 180, 180, 180, 255 });
					std::string mmr = to_string_with_precision(current.myMMR, 2);
					canvas.DrawString("MMR : " + mmr, RS_scale, RS_scale);

					textPos.Y += int(20 * RS_scale);
					canvas.SetPosition(textPos);

					std::string mmrchange = to_string_with_precision(current.MMRChange, 2);
					if (current.MMRChange >= 0)
					{
						canvas.SetColor(LinearColor{ 30, 224, 24, 255 });
						canvas.DrawString("MMRChange : +" + mmrchange, RS_scale, RS_scale);
					}
					else
					{
						canvas.SetColor(LinearColor{ 224, 24, 24, 255 });
						canvas.DrawString("MMRChange : " + mmrchange, RS_scale, RS_scale);
					}
				}
				else if (it == "RS_disp_wins")
				{
					canvas.SetColor(LinearColor{ 30, 224, 24, 255 });
					canvas.DrawString("Win : " + std::to_string(current.win), RS_scale, RS_scale);
				}
				else if (it == "RS_disp_losses")
				{
					canvas.SetColor(LinearColor{ 224, 24, 24, 255 });
					canvas.DrawString("Losses : " + std::to_string(current.losses), RS_scale, RS_scale);
				}
				else if (it == "RS_disp_streak")
				{
					if (current.streak >= 0)
					{
						canvas.SetColor(LinearColor{ 30, 224, 24, 255 });
						canvas.DrawString("Streak : +" + std::to_string(current.streak), RS_scale, RS_scale);
					}
					else
					{
						canvas.SetColor(LinearColor{ 224, 24, 24, 255 });
						canvas.DrawString("Streak : " + std::to_string(current.streak), RS_scale, RS_scale);
					}
				}
				// Increase Y position
				textPos.Y += int(20 * RS_scale);
			}
		}
	}
}
#pragma endregion

#pragma region File I/O
void RocketStats::WriteInFile(std::string _filename, std::string _value)
{
	std::ofstream stream(gameWrapper->GetBakkesModPath().string() + "\\RocketStats\\" + _filename, std::ios::out | std::ios::trunc);

	if (stream.is_open()) {
		stream << _value;
		stream.close();
	}
	else {
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

	if (current.MMRChange > 0) WriteInFile("RocketStats_MMRChange.txt", "+" + tmp);
	else WriteInFile("RocketStats_MMRChange.txt", tmp);
}

void RocketStats::writeStreak()
{
	bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
	Stats current = (RS_session == true) ? session : stats[currentPlaylist];

	if (current.streak > 0) WriteInFile("RocketStats_Streak.txt", "+" + std::to_string(current.streak));
	else WriteInFile("RocketStats_Streak.txt", std::to_string(current.streak));
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
#pragma endregion
