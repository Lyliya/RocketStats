/* ==================================
 *   Developped by Lyliya & NuSa
 * ================================== */

 // Include
#include "RocketStats.h"
#include "bakkesmod/wrappers/GameEvent/GameEventWrapper.h"
#include "bakkesmod/wrappers/GameEvent/ServerWrapper.h"
#include "bakkesmod/wrappers/ArrayWrapper.h"
#include "bakkesmod/wrappers/includes.h"
#include "utils/parser.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <stdio.h>

// File include
#include <iostream>
#include <fstream>

BAKKESMOD_PLUGIN(RocketStats, "RocketStats", "2.2", 0)

#pragma region Helpers
int HexadecimalToDecimal(std::string hex) {
	int hexLength = hex.length();
	double dec = 0;

	for (int i = 0; i < hexLength; ++i)
	{
		char b = hex[i];

		if (b >= 48 && b <= 57)
			b -= 48;
		else if (b >= 65 && b <= 70)
			b -= 55;
		else if (b >= 97 && b <= 102) {
			b -= 87;
		}

		dec += b * pow(16, ((hexLength - i) - 1));
	}

	return (int)dec;
}

RGB HexadecimalToRGB(std::string hex) {
	if (hex[0] != '#' || hex.length() != 7) {
		RGB tmp;
		tmp.r = 180;
		tmp.g = 180;
		tmp.b = 180;
		return tmp;
	}
	else {
		if (hex[0] == '#')
			hex = hex.erase(0, 1);

		RGB color;

		color.r = (unsigned char)HexadecimalToDecimal(hex.substr(0, 2));
		color.g = (unsigned char)HexadecimalToDecimal(hex.substr(2, 2));
		color.b = (unsigned char)HexadecimalToDecimal(hex.substr(4, 2));

		return color;
	}
}
#pragma endregion

std::string RocketStats::GetRank(int tierID) {
	cvarManager->log("tier:" + std::to_string(tierID));
	if (tierID <= rank_nb) {
		return rank[tierID].name;
	}
	else {
		return "norank";
	}
}

void RocketStats::onLoad()
{
	crown = std::make_shared<ImageWrapper>("./bakkesmod/RocketStats/RocketStats_images/crown.png", true);
	win = std::make_shared<ImageWrapper>("./bakkesmod/RocketStats/RocketStats_images/win.png", true);
	loose = std::make_shared<ImageWrapper>("./bakkesmod/RocketStats/RocketStats_images/loose.png", true);

	for (int i = 0; i < rank_nb; i++) {
		rank[i].image = std::make_shared<ImageWrapper>("./bakkesmod/RocketStats/RocketStats_images/" + rank[i].name + ".png", true);
		if (rank[i].image->LoadForCanvas()) {
			cvarManager->log(rank[i].name + " : image load");
		}
	}

	cvarManager->registerNotifier("RocketStats_reset_stats", [this](std::vector<std::string> params) {
		ResetStats();
		}
	, "Reset Stats", PERMISSION_ALL);

	// Unload
	cvarManager->registerNotifier("RocketStats_unload", [this](std::vector<std::string> params) {
		togglePlugin(false);
		}
	, "Unload Plugin", PERMISSION_ALL);

	//Load
	cvarManager->registerNotifier("RocketStats_load", [this](std::vector<std::string> params) {
		togglePlugin(true);
		}
	, "Load Plugin", PERMISSION_ALL);

	// Register drawable
	gameWrapper->RegisterDrawable(std::bind(&RocketStats::Render, this, std::placeholders::_1));

	// Hook on Event
	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&RocketStats::Start, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&RocketStats::GameEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", bind(&RocketStats::OnBoost, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed", bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));

	WriteInFile("RocketStats_Win.txt", std::to_string(0));
	WriteInFile("RocketStats_Streak.txt", std::to_string(0));
	WriteInFile("RocketStats_Loose.txt", std::to_string(0));
	WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));
	WriteInFile("RocketStats_MMR.txt", std::to_string(0));
	WriteInFile("RocketStats_Rank.txt", "");
	WriteInFile("RocketStats_GameMode.txt", "");

	initRank();

	// Load Settings
	cvarManager->registerCvar("RS_Use_v1", "0", "Use the v1 overlay", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_ig", "1", "Display information panel", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_mmr", "1", "Display the current MMR", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_wins", "1", "Display the wins on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_losses", "1", "Display the losses on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_streak", "1", "Display the streak on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_rank", "1", "Display the rank on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_gamemode", "1", "Display the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_x_position", "0.700", "Overlay X position", true, true, 0, true, 1.0f);
	cvarManager->registerCvar("RS_y_position", "0.575", "Overlay Y position", true, true, 0, true, 1.0f);
	cvarManager->registerCvar("RS_scale", "1", "Overlay scale", true, true, 0, true, 10);
	cvarManager->registerCvar("RS_disp_active", "0", "", true, true, 0, true, 1);
	cvarManager->registerCvar("RocketStats_stop_boost", "1", "Stop Boost animation", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_session", "0", "Display session stats", true, true, 0, true, 1, true);

	WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
}

void RocketStats::onUnload()
{
	gameWrapper->UnhookEvent("Function GameEvent_TA.Countdown.BeginState");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded");
	gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.BeginState");
	gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.EndState");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed");
	gameWrapper->UnregisterDrawables();
}

void RocketStats::togglePlugin(bool state) {
	if (state == isLoad) {
		return;
	}
	else {
		if (state == false) {
			// Unload Plugin
			gameWrapper->UnhookEvent("Function GameEvent_TA.Countdown.BeginState");
			gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded");
			gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.BeginState");
			gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.EndState");
			gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed");
			gameWrapper->UnregisterDrawables();
			isLoad = state;
		}
		else if (state == true) {
			// Load Plugin
			gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&RocketStats::Start, this, std::placeholders::_1));
			gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&RocketStats::GameEnd, this, std::placeholders::_1));
			gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", bind(&RocketStats::OnBoost, this, std::placeholders::_1));
			gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
			gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed", bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));
			gameWrapper->RegisterDrawable(std::bind(&RocketStats::Render, this, std::placeholders::_1));

			WriteInFile("RocketStats_Win.txt", std::to_string(0));
			WriteInFile("RocketStats_Streak.txt", std::to_string(0));
			WriteInFile("RocketStats_Loose.txt", std::to_string(0));
			WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));
			WriteInFile("RocketStats_MMR.txt", std::to_string(0));
			WriteInFile("RocketStats_Rank.txt", "");
			WriteInFile("RocketStats_GameMode.txt", "");
			WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));

			initRank();

			isLoad = state;
		}
	}
}

void RocketStats::Start(std::string eventName)
{
	if (gameWrapper->IsInOnlineGame()) {
		CarWrapper me = gameWrapper->GetLocalCar();
		if (me.IsNull()) {
			return;
		}
		TeamInfoWrapper myTeam = me.GetPRI().GetTeam();
		if (myTeam.IsNull()) {
			return;
		}
		PriWrapper mePRI = me.GetPRI();

		// Get and Display SteamID
		mySteamID = mePRI.GetUniqueId();

		// Get and Update MMR
		MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
		currentPlaylist = mmrw.GetCurrentPlaylist();
		SkillRank playerRank = mmrw.GetPlayerRank(mySteamID, currentPlaylist);
		currentTier = playerRank.Tier;
		WriteInFile("RocketStats_GameMode.txt", getPlaylistName(currentPlaylist));

		//Session or Gamemode

		float save = mmrw.GetPlayerMMR(mySteamID, currentPlaylist);
		if (stats[currentPlaylist].isInit == false) {
			stats[currentPlaylist].myMMR = save;
			stats[currentPlaylist].isInit = true;
		}
		stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
		stats[currentPlaylist].myMMR = save;

		writeMMRChange();
		writeWin();
		writeStreak();
		writeLosses();
		writeMMR();

		// Get TeamNum
		myTeamNum = myTeam.GetTeamNum();

		// Set Game Started
		isGameEnded = false;
		isGameStarted = true;

		majRank(currentPlaylist, stats[currentPlaylist].myMMR, playerRank);
		WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));
	}
}

void RocketStats::GameEnd(std::string eventName)
{
	if (gameWrapper->IsInOnlineGame() && myTeamNum != -1) {
		ServerWrapper server = gameWrapper->GetOnlineGame();
		TeamWrapper winningTeam = server.GetGameWinner();


		if (winningTeam.IsNull()) {
			return;
		}
		int teamnum = winningTeam.GetTeamNum();

		// Game as ended
		isGameEnded = true;

		MMRWrapper mw = gameWrapper->GetMMRWrapper();

		if (myTeamNum == winningTeam.GetTeamNum()) {
			// On Win, Increase streak and Win Number
			stats[currentPlaylist].win += 1;
			session.win += 1;

			if (stats[currentPlaylist].streak < 0)
			{
				session.streak = 1;
				stats[currentPlaylist].streak = 1;
			}
			else
			{
				session.streak += 1;
				stats[currentPlaylist].streak += 1;
			}

			//cvarManager->log("You WIN");
			writeWin();
		}
		else {
			// On Loose, Increase Win Number and decrease streak
			stats[currentPlaylist].losses += 1;
			session.losses += 1;
			if (stats[currentPlaylist].streak > 0)
			{
				session.streak = -1;
				stats[currentPlaylist].streak = -1;
			}
			else
			{
				session.streak -= 1;
				stats[currentPlaylist].streak -= 1;
			}

			//cvarManager->log("You LOOSE");
			writeLosses();
		}

		ComputeMMR(3);
		writeStreak();

		// Reset myTeamNum security
		myTeamNum = -1;

		WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
	}
}

void RocketStats::GameDestroyed(std::string eventName) {
	//Check if Game Ended, if not, RAGE QUIT or disconnect
	if (isGameStarted == true && isGameEnded == false) {
		session.losses += 1;
		stats[currentPlaylist].losses += 1;
		if (stats[currentPlaylist].streak > 0)
		{
			session.streak = 0;
			stats[currentPlaylist].streak = -1;
		}
		else
		{
			session.streak -= 1;
			stats[currentPlaylist].streak -= 1;
		}

		//cvarManager->log("You LOOSE");
		writeStreak();
		writeLosses();

		ComputeMMR(10);
	}
	isGameEnded = true;
	isGameStarted = false;
	WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
}

void RocketStats::ComputeMMR(int intervalTime) {
	gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
		MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
		float save = mmrw.GetPlayerMMR(mySteamID, currentPlaylist);
		SkillRank playerRank = mmrw.GetPlayerRank(mySteamID, currentPlaylist);

		if (save <= 0) {
			return ComputeMMR(1);
		}

		currentTier = playerRank.Tier;
		stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
		stats[currentPlaylist].myMMR = save;
		majRank(currentPlaylist, stats[currentPlaylist].myMMR, playerRank);

		SessionStats();
		writeMMR();
		writeMMRChange();
		}, intervalTime);
}

void RocketStats::SessionStats() {
	Stats tmp;
	auto it = playlistName.begin();

	for (; it != playlistName.end(); it++) {
		tmp.MMRChange += stats[it->first].MMRChange;
		tmp.win += stats[it->first].win;
		tmp.losses += stats[it->first].losses;
	}

	session.myMMR = stats[currentPlaylist].myMMR;
	session.MMRChange = tmp.MMRChange;
	session.win = tmp.win;
	session.losses = tmp.losses;
}

void RocketStats::OnBoost(std::string eventName) {
	//cvarManager->log("BOOOOST");

	// Check if boost enabled in options
	bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
	if (IsBoostEnabled == false) {
		return;
	}

	if (gameWrapper->IsInReplay() || isBoosting)
		return;
	CarWrapper cWrap = gameWrapper->GetLocalCar();

	if (!cWrap.IsNull())
	{
		BoostWrapper bWrap = cWrap.GetBoostComponent();

		if (!bWrap.IsNull() && bWrap.GetbActive() == 1 && isBoosting == false) {
			//cvarManager->log("Tu boost");
			isBoosting = true;

			WriteInFile("RocketStats_images/BoostState.txt", std::to_string(1));
		}
		//cvarManager->log("BOOOOST ----> " + std::to_string(bWrap.GetbActive()));
	}

	return;
}

void RocketStats::OnBoostEnd(std::string eventName) {

	// Check if boost enabled in options
	bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
	if (!IsBoostEnabled)
		return;

	if (gameWrapper->IsInReplay() || !isBoosting)
		return;
	CarWrapper cWrap = gameWrapper->GetLocalCar();

	if (!cWrap.IsNull())
	{
		BoostWrapper bWrap = cWrap.GetBoostComponent();

		if (!bWrap.IsNull() && bWrap.GetbActive() == 0 && isBoosting == true) {
			//cvarManager->log("Tu ne boost plus");
			isBoosting = false;

			WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));
		}
		//cvarManager->log("BOOOOST ----> " + std::to_string(bWrap.GetbActive()));
	}
	return;
}

// Act as toggle
void RocketStats::StopBoost()
{
	//cvarManager->log("hey");
}

void RocketStats::ResetStats()
{
	for (auto& kv : stats) {
		kv.second.myMMR = 100.0f;
		kv.second.MMRChange = 0;
		kv.second.win = 0;
		kv.second.losses = 0;
		kv.second.streak = 0;
		kv.second.isInit = 0;
	}
	session.myMMR = 100.0f;
	session.MMRChange = 0;
	session.win = 0;
	session.losses = 0;
	session.streak = 0;
	session.isInit = 0;
	WriteInFile("RocketStats_Win.txt", std::to_string(0));
	WriteInFile("RocketStats_Streak.txt", std::to_string(0));
	WriteInFile("RocketStats_Loose.txt", std::to_string(0));
	WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));
	WriteInFile("RocketStats_MMR.txt", std::to_string(0));
	WriteInFile("RocketStats_Rank.txt", "");
	WriteInFile("RocketStats_GameMode.txt", "");

	initRank();
}

void RocketStats::WriteInFile(std::string _fileName, std::string _value)
{
	std::ofstream myFile;

	myFile.open("./bakkesmod/RocketStats/" + _fileName, std::ios::out | std::ios::trunc);

	if (myFile.is_open())
	{
		myFile << _value;

		myFile.close();
	}
}

std::string RocketStats::getPlaylistName(int playlistID)
{
	if (playlistName.find(playlistID) != playlistName.end()) {
		return playlistName.at(playlistID);
	}
	return "Unknown Game Mode";
}

#pragma region Rank/Div
void RocketStats::initRank()
{
	lastGameMode = 0;
	currentGameMode = 0;
	currentMMR = 0;
	currentDivision = " nodiv";
	currentRank = "norank";
	lastRank = "norank";

	std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

	WriteInFile("RocketStats_images/rank.html", _value);
}

void RocketStats::majRank(int _gameMode, float _currentMMR, SkillRank playerRank)
{
	currentGameMode = _gameMode;
	currentMMR = _currentMMR;
	lastRank == currentRank;

	if (currentGameMode >= 10 && currentGameMode <= 13 || currentGameMode >= 27 && currentGameMode <= 30)
	{
		if (playerRank.MatchesPlayed < 10 && playerRank.Tier == 0) {
			currentDivision = " Division " + std::to_string(playerRank.Division + 1);
			currentRank = "Placement: ";
			currentDivision = std::to_string(playerRank.MatchesPlayed) + "/10";
		}
		else {
			currentRank = GetRank(playerRank.Tier);
			currentDivision = " Div. " + std::to_string(playerRank.Division + 1);
		}
		//currentRank = GetRank(playerRank.Tier);
		//currentDivision = " Div. " + std::to_string(playerRank.Division + 1);

		if (currentRank != lastRank)
		{
			std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"" + currentRank + ".png" + "\" width = \"100\" height = \"100\" />";

			WriteInFile("RocketStats_images/rank.html", _value);
			WriteInFile("RocketStats_Rank.txt", currentRank);
		}
	}
	else
	{
		currentRank = "norank";
		currentDivision = " nodiv";

		std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

		WriteInFile("RocketStats_images/rank.html", _value);
		WriteInFile("RocketStats_Rank.txt", currentRank);
	}
}

#pragma endregion

void RocketStats::DisplayRank(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, float scale)
{
	std::string tmpRank = currentRank;
	if (currentTier >= rank_nb) {
		currentTier = 0;
	}
	auto image = rank[currentTier].image;
	std::replace(tmpRank.begin(), tmpRank.end(), '_', ' ');
	canvas.SetColor(255, 255, 255, 255);
	canvas.SetPosition(imagePos);
	if (image->IsLoadedForCanvas()) canvas.DrawTexture(image.get(), 0.5f * scale);
	canvas.SetPosition(textPos_tmp);
	canvas.DrawString(tmpRank + currentDivision, 2.0f * scale, 2.0f * scale);
}

void RocketStats::DisplayMMR(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << current.myMMR;
	std::string mmr = ss.str();
	std::stringstream ss_change;
	ss_change << std::fixed << std::setprecision(2) << current.MMRChange;
	std::string change = ss_change.str();
	canvas.SetColor(255, 255, 255, 255);
	canvas.SetPosition(imagePos);
	if (crown->IsLoadedForCanvas()) canvas.DrawTexture(crown.get(), 0.5f * scale);
	canvas.SetPosition(textPos_tmp);
	canvas.SetColor(255, 255, 255, 255);
	if (current.MMRChange > 0) {
		change = "+" + change;
	}
	canvas.DrawString(mmr + " (" + change + ")", 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayWins(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
	canvas.SetColor(255, 255, 255, 255);
	canvas.SetPosition(imagePos);
	if (win->IsLoadedForCanvas()) canvas.DrawTexture(win.get(), 0.5f * scale);
	canvas.SetPosition(textPos_tmp);
	canvas.SetColor(0, 255, 0, 255);
	canvas.DrawString(std::to_string(current.win), 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayLoose(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
	canvas.SetColor(255, 255, 255, 255);
	canvas.SetPosition(imagePos);
	if (loose->IsLoadedForCanvas()) canvas.DrawTexture(loose.get(), 0.5f * scale);
	canvas.SetPosition(textPos_tmp);
	canvas.SetColor(255, 0, 0, 255);
	canvas.DrawString(std::to_string(current.losses), 2.0f * scale, 2.0f * scale);
}
void RocketStats::DisplayStreak(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
{
	canvas.SetColor(255, 255, 255, 255);
	canvas.SetPosition(textPos_tmp);
	if (current.streak < 0) {
		canvas.SetColor(255, 0, 0, 255);
	}
	else {
		canvas.SetColor(0, 255, 0, 255);
	}
	std::string streak = std::to_string(current.streak);
	if (current.streak > 0) {
		streak = "+" + streak;
	}
	canvas.DrawString(streak, 2.0f * scale, 2.0f * scale);
}

void RocketStats::Render(CanvasWrapper canvas)
{
	bool RS_Use_v1 = cvarManager->getCvar("RS_Use_v1").getBoolValue();
	bool RS_disp_ig = cvarManager->getCvar("RS_disp_ig").getBoolValue();
	float RS_x_position = cvarManager->getCvar("RS_x_position").getFloatValue();
	float RS_y_position = cvarManager->getCvar("RS_y_position").getFloatValue();
	float RS_scale = cvarManager->getCvar("RS_scale").getFloatValue();
	cvarManager->getCvar("RS_disp_active").setValue(RS_disp_ig);

	if (!RS_disp_ig) {
		return;
	}

	bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
	Stats current = (RS_session == true) ? session : stats[currentPlaylist];

	if (!RS_Use_v1) {
		auto canSize = canvas.GetSize();
		Vector2 imagePos = { RS_x_position * canSize.X, RS_y_position * canSize.Y };
		Vector2 textPos_tmp = imagePos;

		textPos_tmp.X += 50 * RS_scale;
		textPos_tmp.Y += 10 * RS_scale;

		// Display Rank
		if (cvarManager->getCvar("RS_disp_rank").getBoolValue()) {
			DisplayRank(canvas, imagePos, textPos_tmp, RS_scale);
			imagePos.Y += 50 * RS_scale;
			textPos_tmp.Y += 50 * RS_scale;
		}

		// Display MMR
		if (cvarManager->getCvar("RS_disp_mmr").getBoolValue()) {
			DisplayMMR(canvas, imagePos, textPos_tmp, current, RS_scale);
			imagePos.Y += 50 * RS_scale;
			textPos_tmp.Y += 50 * RS_scale;
		}

		// Display Win
		if (cvarManager->getCvar("RS_disp_wins").getBoolValue()) {
			DisplayWins(canvas, imagePos, textPos_tmp, current, RS_scale);
			imagePos.Y += 50 * RS_scale;
			textPos_tmp.Y += 50 * RS_scale;
		}

		// Display Loose
		if (cvarManager->getCvar("RS_disp_losses").getBoolValue()) {
			DisplayLoose(canvas, imagePos, textPos_tmp, current, RS_scale);
		}

		if (cvarManager->getCvar("RS_disp_streak").getBoolValue()) {
			textPos_tmp.X += 75 * RS_scale;
			textPos_tmp.Y -= 25 * RS_scale;
			DisplayStreak(canvas, imagePos, textPos_tmp, current, RS_scale);
		}
	}
	else {
		std::vector<std::string> RS_values = {
			"RS_disp_gamemode",
			"RS_disp_rank",
			"RS_disp_mmr",
			"RS_disp_wins",
			"RS_disp_losses",
			"RS_disp_streak",
		};

		unsigned int size = 0;
		for (auto& it : RS_values) {
			bool tmp = cvarManager->getCvar(it).getBoolValue();
			if (tmp)
				size += 1;
			if (it == "RS_disp_mmr") {
				size += 1;
			}
		}

		// Draw box here
		Vector2 drawLoc = { canvas.GetSize().X * RS_x_position, canvas.GetSize().Y * RS_y_position };
		Vector2 sizeBox = { 175 * RS_scale, (23 * size) * RS_scale };
		canvas.SetPosition(drawLoc);

		//Set background Color
		canvas.SetColor(0, 0, 0, 150);
		canvas.FillBox(sizeBox);

		// Draw text
		Vector2 textPos = { (drawLoc.X + 10), (drawLoc.Y + 10) };
		for (auto& it : RS_values) {
			bool tmp = cvarManager->getCvar(it).getBoolValue();

			if (tmp) {
				//Set the position
				canvas.SetPosition(textPos);

				//Set Color and Text for the value
				if (it == "RS_disp_gamemode") {
					canvas.SetColor(180, 180, 180, 255);
					canvas.DrawString(getPlaylistName(currentPlaylist), RS_scale, RS_scale);
				}
				else if (it == "RS_disp_rank")
				{
					std::string tmpRank = currentRank + currentDivision;
					std::replace(tmpRank.begin(), tmpRank.end(), '_', ' ');
					canvas.SetColor(180, 180, 180, 255);
					canvas.DrawString(tmpRank, RS_scale, RS_scale);
				}
				else if (it == "RS_disp_mmr")
				{
					canvas.SetColor(180, 180, 180, 255);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << current.myMMR;
					std::string mmr = ss.str();
					canvas.DrawString("MMR : " + mmr, RS_scale, RS_scale);

					textPos.Y += (20 * RS_scale);
					canvas.SetPosition(textPos);

					std::stringstream ss_change;
					ss_change << std::fixed << std::setprecision(2) << current.MMRChange;
					std::string mmrchange = ss_change.str();
					if (current.MMRChange >= 0)
					{
						canvas.SetColor(30, 224, 24, 255);
						canvas.DrawString("MMRChange : +" + mmrchange, RS_scale, RS_scale);
					}
					else
					{
						canvas.SetColor(224, 24, 24, 255);
						canvas.DrawString("MMRChange : " + mmrchange, RS_scale, RS_scale);
					}
				}
				else if (it == "RS_disp_wins")
				{
					canvas.SetColor(30, 224, 24, 255);
					canvas.DrawString("Win : " + std::to_string(current.win), RS_scale, RS_scale);
				}
				else if (it == "RS_disp_losses")
				{
					canvas.SetColor(224, 24, 24, 255);
					canvas.DrawString("Losses : " + std::to_string(current.losses), RS_scale, RS_scale);
				}
				else if (it == "RS_disp_streak")
				{
					if (current.streak >= 0)
					{
						canvas.SetColor(30, 224, 24, 255);
						canvas.DrawString("Streak : +" + std::to_string(current.streak), RS_scale, RS_scale);
					}
					else
					{
						canvas.SetColor(224, 24, 24, 255);
						canvas.DrawString("Streak : " + std::to_string(current.streak), RS_scale, RS_scale);
					}
				}
				// Increase Y position;
				textPos.Y += (20 * RS_scale);
			}
		}
	}
}

void RocketStats::writeMMR()
{
	bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();

	WriteInFile("RocketStats_MMR.txt", std::to_string((int)stats[currentPlaylist].myMMR));
}
void RocketStats::writeMMRChange()
{
	bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
	Stats current = (RS_session == true) ? session : stats[currentPlaylist];
	int tmp = ((current.MMRChange < 0) ? -1 : 1) * std::round(fabs(current.MMRChange));

	if (tmp >= 0) {
		WriteInFile("RocketStats_MMRChange.txt", "+" + std::to_string(tmp));
	}
	else {
		WriteInFile("RocketStats_MMRChange.txt", std::to_string(tmp));
	}
}

void RocketStats::writeStreak()
{
	bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
	Stats current = (RS_session == true) ? session : stats[currentPlaylist];

	if (current.streak > 0)
	{
		WriteInFile("RocketStats_Streak.txt", "+" + std::to_string(current.streak));
	}
	else
	{
		WriteInFile("RocketStats_Streak.txt", std::to_string(current.streak));
	}
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
