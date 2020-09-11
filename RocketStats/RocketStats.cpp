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

BAKKESMOD_PLUGIN(RocketStats, "RocketStats", "1.5", 0)

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

void RocketStats::onLoad()
{
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

	initRankList();
	initRank();

	// Load Settings
	cvarManager->registerCvar("RS_disp_ig", "1", "Display information panel", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_mmr", "1", "Display the current MMR", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_mmr_change", "1", "Display the MMR change on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_wins", "1", "Display the wins on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_losses", "1", "Display the losses on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_streak", "1", "Display the streak on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_rank", "1", "Display the rank on the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_disp_gamemode", "1", "Display the current game mode", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_x_position", "80", "Overlay X position", true, true, 0, true, 100);
	cvarManager->registerCvar("RS_y_position", "10", "Overlay Y position", true, true, 0, true, 100);
	cvarManager->registerCvar("RS_scale", "1", "Overlay scale", true, true, 1, true, 10);
	cvarManager->registerCvar("RS_disp_active", "0", "", true, true, 0, true, 1);
	cvarManager->registerCvar("RocketStats_stop_boost", "1", "Stop Boost animation", true, true, 0, true, 1);
	cvarManager->registerCvar("RS_session", "0", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_custom_color", "0", "Display custom colors", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_MMR", "#b4b4b4", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_MMRChange", "#b4b4b4", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_Wins", "#1fe018", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_Losses", "#e01818", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_Streak", "#b4b4b4", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_Rank", "#b4b4b4", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_GameMode", "#b4b4b4", "Display session stats", true, true, 0, true, 1, true);
	cvarManager->registerCvar("RS_Color_Background", "#000000", "Display session stats", true, true, 0, true, 1, true);

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

			initRankList();
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

		majRank(currentPlaylist, stats[currentPlaylist].myMMR);
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

		if (save <= 0) {
			return ComputeMMR(1);
		}

		stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
		stats[currentPlaylist].myMMR = save;
		majRank(currentPlaylist, stats[currentPlaylist].myMMR);

		SessionStats();
		writeMMR();
		writeMMRChange();
		}, intervalTime);
}

void RocketStats::SessionStats() {
	Stats tmp;
	auto it = playlistName.begin();

	for (; it != playlistName.end(); it++) {
		tmp.myMMR += stats[it->first].myMMR;
		tmp.MMRChange += stats[it->first].MMRChange;
		tmp.win += stats[it->first].win;
		tmp.losses += stats[it->first].losses;
	}

	session.myMMR = tmp.myMMR;
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
		kv.second.myMMR = 0;
		kv.second.MMRChange = 0;
		kv.second.win = 0;
		kv.second.losses = 0;
		kv.second.streak = 0;
		kv.second.isInit = 0;
	}
	session.myMMR = 0;
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

void RocketStats::initRankList()
{
	//1v1 Ranked code : 10
	Ranks v1Rank;
	v1Rank.nameMode = "1v1";
	v1Rank._rank = {
		{"Bronze_I", {0.0f, 153.0f}},
		{"Bronze_II", {153.0f, 202.0f}},
		{"Bronze_III", {213.0f, 264.0f}},
		{"Silver_I", {273.0f, 324.0f}},
		{"Silver_II", {332.0f, 384.0f}},
		{"Silver_III", {392.0f, 445.0f}},
		{"Gold_I", {453.0f, 505.0f}},
		{"Gold_II", {513.0f, 565.0f}},
		{"Gold_III", {572.0f, 625.0f}},
		{"Platinum_I", {628.0f, 685.0f}},
		{"Platinum_II", {687.0f, 745.0f}},
		{"Platinum_III", {752.0f, 805.0f}},
		{"Diamond_I", {808.0f, 865.0f}},
		{"Diamond_II", {867.0f, 925.0f}},
		{"Diamond_III", {926.0f, 985.0f}},
		{"Champion_I", {995.0f, 1060.0f}},
		{"Champion_II", {1075, 1143.0f}},
		{"Champion_III", {1147.0f, 1220.0f}},
		{"Grand_Champion", {1221.0f, 9999.0f}},
	};

	//2v2 Ranked code : 11
	Ranks v2Rank;
	v2Rank.nameMode = "2v2";
	v2Rank._rank = {
		{"Bronze_I", {0.0f, 180.0f}},
		{"Bronze_II", {189.0f, 244.0f}},
		{"Bronze_III", {250.0f, 304.0f}},
		{"Silver_I", {310.0f, 364.0f}},
		{"Silver_II", {369.0f, 425.0f}},
		{"Silver_III", {429.0f, 484.0f}},
		{"Gold_I", {488.0f, 545.0f}},
		{"Gold_II", {549.0f, 604.0f}},
		{"Gold_III", {612.0f, 680.0f}},
		{"Platinum_I", {692.0f, 760.0f}},
		{"Platinum_II", {772.0f, 840.0f}},
		{"Platinum_III", {852.0f, 920.0f}},
		{"Diamond_I", {933.0f, 1000.0f}},
		{"Diamond_II", {1012.0f, 1080.0f}},
		{"Diamond_III", {1093.0f, 1180.0f}},
		{"Champion_I", {1195.0f, 1280.0f}},
		{"Champion_II", {1294.0f, 1380.0f}},
		{"Champion_III", {1395.0f, 1499.0f}},
		{"Grand_Champion", {1500.0f, 9999.0f}},
	};

	//solo 3v3 Ranked code : 12
	Ranks sv3Rank;
	sv3Rank.nameMode = "solo 3v3";
	sv3Rank._rank = {
		{"Bronze_I", {0.0f, 154.0f}},
		{"Bronze_II", {151.0f, 208.0f}},
		{"Bronze_III", {209.0f, 270.0f}},
		{"Silver_I", {270.0f, 323.0f}},
		{"Silver_II", {329.0f, 384.0f}},
		{"Silver_III", {390.0f, 443.0f}},
		{"Gold_I", {451.0f, 503.0f}},
		{"Gold_II", {511.0f, 562.0f}},
		{"Gold_III", {572.0f, 622.0f}},
		{"Platinum_I", {635.0f, 683.0f}},
		{"Platinum_II", {692.0f, 742.0f}},
		{"Platinum_III", {749.0f, 804.0f}},
		{"Diamond_I", {815.0f, 880.0f}},
		{"Diamond_II", {895.0f, 960.0f}},
		{"Diamond_III", {975.0f, 1041.0f}},
		{"Champion_I", {1055.0f, 1120.0f}},
		{"Champion_II", {1134.0f, 1203.0f}},
		{"Champion_III", {1210.0f, 1283.0f}},
		{"Grand_Champion", {1287.0f, 9999.0f}},
	};

	//3v3 Standard Ranked code : 13
	Ranks v3Rank;
	v3Rank.nameMode = "3v3";
	v3Rank._rank = {
		{"Bronze_I", {0.0f, 180.0f}},
		{"Bronze_II", {189.0f, 244.0f}},
		{"Bronze_III", {247.0f, 301.0f}},
		{"Silver_I", {310.0f, 364.0f}},
		{"Silver_II", {369.0f, 425.0f}},
		{"Silver_III", {429.0f, 485.0f}},
		{"Gold_I", {490.0f, 545.0f}},
		{"Gold_II", {549.0f, 604.0f}},
		{"Gold_III", {612.0f, 680.0f}},
		{"Platinum_I", {693.0f, 760.0f}},
		{"Platinum_II", {771.0f, 840.0f}},
		{"Platinum_III", {852.0f, 920.0f}},
		{"Diamond_I", {933.0f, 1000.0f}},
		{"Diamond_II", {1011.0f, 1080.0f}},
		{"Diamond_III", {1094.0f, 1180.0f}},
		{"Champion_I", {1195.0f, 1280.0f}},
		{"Champion_II", {1294.0f, 1380.0f}},
		{"Champion_III", {1395.0f, 1500.0f}},
		{"Grand_Champion", {1500.0f, 9999.0f}},
	};

	// Hoops code : 27
	Ranks hopRank;
	hopRank.nameMode = "hoops";
	hopRank._rank = {
		{"Bronze_I", {0.0f, 140.0f}},
		{"Bronze_II", {141.0f, 203.0f}},
		{"Bronze_III", {201.0f, 271.0f}},
		{"Silver_I", {262.0f, 320.0f}},
		{"Silver_II", {322.0f, 389.0f}},
		{"Silver_III", {386.0f, 440.0f}},
		{"Gold_I", {449.0f, 500.0f}},
		{"Gold_II", {515.0f, 560.0f}},
		{"Gold_III", {572.0f, 622.0f}},
		{"Platinum_I", {632.0f, 683.0f}},
		{"Platinum_II", {693.0f, 741.0f}},
		{"Platinum_III", {752.0f, 804.0f}},
		{"Diamond_I", {807.0f, 864.0f}},
		{"Diamond_II", {868.0f, 922.0f}},
		{"Diamond_III", {935.0f, 1000.0f}},
		{"Champion_I", {1012.0f, 1082.0f}},
		{"Champion_II", {1087.0f, 1162.0f}},
		{"Champion_III", {1167.0f, 1240.0f}},
		{"Grand_Champion", {1242.0f, 9999.0f}},
	};

	// Rumble code : 28
	Ranks rumRank;
	rumRank.nameMode = "rumble";
	rumRank._rank = {
		{"Bronze_I", {0.0f, 154.0f}},
		{"Bronze_II", {146.0f, 211.0f}},
		{"Bronze_III", {205.0f, 262.0f}},
		{"Silver_I", {266.0f, 324.0f}},
		{"Silver_II", {329.0f, 388.0f}},
		{"Silver_III", {391.0f, 440.0f}},
		{"Gold_I", {450.0f, 501.0f}},
		{"Gold_II", {511.0f, 565.0f}},
		{"Gold_III", {569.0f, 622.0f}},
		{"Platinum_I", {630.0f, 685.0f}},
		{"Platinum_II", {691.0f, 743.0f}},
		{"Platinum_III", {748.0f, 802.0f}},
		{"Diamond_I", {810.0f, 863.0f}},
		{"Diamond_II", {870.0f, 923.0f}},
		{"Diamond_III", {933.0f, 1000.0f}},
		{"Champion_I", {1014.0f, 1081.0f}},
		{"Champion_II", {1090.0f, 1160.0f}},
		{"Champion_III", {1170.0f, 1240.0f}},
		{"Grand_Champion", {1241.0f, 9999.0f}},
	};

	// Dropshot code : 29
	Ranks dropRank;
	dropRank.nameMode = "dropshot";
	dropRank._rank = {
		{"Bronze_I", {0.0f, 151.0f}},
		{"Bronze_II", {146.0f, 206.0f}},
		{"Bronze_III", {205.0f, 271.0f}},
		{"Silver_I", {264.0f, 333.0f}},
		{"Silver_II", {329.0f, 380.0f}},
		{"Silver_III", {387.0f, 440.0f}},
		{"Gold_I", {450.0f, 501.0f}},
		{"Gold_II", {507.0f, 560.0f}},
		{"Gold_III", {573.0f, 620.0f}},
		{"Platinum_I", {635.0f, 681.0f}},
		{"Platinum_II", {690.0f, 742.0f}},
		{"Platinum_III", {755.0f, 802.0f}},
		{"Diamond_I", {813.0f, 863.0f}},
		{"Diamond_II", {870.0f, 924.0f}},
		{"Diamond_III", {935.0f, 1000.0f}},
		{"Champion_I", {1015.0f, 1081.0f}},
		{"Champion_II", {1087.0f, 1160.0f}},
		{"Champion_III", {1174.0f, 1253.0f}},
		{"Grand_Champion", {1243.0f, 9999.0f}},
	};

	// Snowday code : 30
	Ranks snowRank;
	snowRank.nameMode = "snowday";
	snowRank._rank = {
		{"Bronze_I", {0.0f, 153.0f}},
		{"Bronze_II", {154.0f, 213.0f}},
		{"Bronze_III", {208.0f, 268.0f}},
		{"Silver_I", {267.0f, 333.0f}},
		{"Silver_II", {323.0f, 392.0f}},
		{"Silver_III", {382.0f, 452.0f}},
		{"Gold_I", {449.0f, 503.0f}},
		{"Gold_II", {515.0f, 568.0f}},
		{"Gold_III", {575.0f, 620.0f}},
		{"Platinum_I", {635.0f, 682.0f}},
		{"Platinum_II", {695.0f, 740.0f}},
		{"Platinum_III", {750.0f, 800.0f}},
		{"Diamond_I", {813.0f, 861.0f}},
		{"Diamond_II", {867.0f, 923.0f}},
		{"Diamond_III", {935.0f, 1000.0f}},
		{"Champion_I", {1015.0f, 1080.0f}},
		{"Champion_II", {1089.0f, 1160.0f}},
		{"Champion_III", {1170.0f, 1239.0f}},
		{"Grand_Champion", {1241.0f, 9999.0f}},
	};

	listRank = {
		{10, v1Rank},
		{11, v2Rank},
		{12, sv3Rank},
		{13, v3Rank},
		{27, hopRank},
		{28, rumRank},
		{29, dropRank},
		{30, snowRank}
	};
}

void RocketStats::initRank()
{
	lastGameMode = 0;
	currentGameMode = 0;
	currentMMR = 0;
	currentRank = "norank";
	lastRank = "norank";

	std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

	WriteInFile("RocketStats_images/rank.html", _value);
}

void RocketStats::majRank(int _gameMode, float _currentMMR)
{
	currentGameMode = _gameMode;
	currentMMR = _currentMMR;
	lastRank == currentRank;

	if (currentGameMode >= 10 && currentGameMode <= 13 || currentGameMode >= 27 && currentGameMode <= 30)
	{
		for (auto it = listRank[currentGameMode]._rank.begin(); it != listRank[currentGameMode]._rank.end(); it++)
		{
			if (currentMMR >= it->second.first && currentMMR <= it->second.second)
			{
				currentRank = it->first;
			}
		}

		if (currentRank != lastRank)
		{
			std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"" + currentRank + ".png" + "\" width = \"100\" height = \"100\" />";

			WriteInFile("RocketStats_images/rank.html", _value);
			WriteInFile("RocketStats_Rank.txt", currentRank);
		}
	}
	else
	{
		std::string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

		WriteInFile("RocketStats_images/rank.html", _value);
		WriteInFile("RocketStats_Rank.txt", currentRank);
	}
}

#pragma endregion

void RocketStats::Render(CanvasWrapper canvas)
{
	bool RS_disp_ig = cvarManager->getCvar("RS_disp_ig").getBoolValue();
	int RS_x_position = cvarManager->getCvar("RS_x_position").getIntValue();
	int RS_y_position = cvarManager->getCvar("RS_y_position").getIntValue();
	float RS_scale = cvarManager->getCvar("RS_scale").getFloatValue();
	cvarManager->getCvar("RS_disp_active").setValue(RS_disp_ig);

	if (!RS_disp_ig) {
		return;
	}

	bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
	Stats current = (RS_session == true) ? session : stats[currentPlaylist];

	// CustomColor
	bool custom_color = cvarManager->getCvar("RS_custom_color").getBoolValue();
	std::string RS_Color_MMR = cvarManager->getCvar("RS_Color_MMR").getStringValue();
	std::string RS_Color_MMRChange = cvarManager->getCvar("RS_Color_MMRChange").getStringValue();
	std::string RS_Color_Wins = cvarManager->getCvar("RS_Color_Wins").getStringValue();
	std::string RS_Color_Losses = cvarManager->getCvar("RS_Color_Losses").getStringValue();
	std::string RS_Color_Streak = cvarManager->getCvar("RS_Color_Streak").getStringValue();
	std::string RS_Color_Rank = cvarManager->getCvar("RS_Color_Rank").getStringValue();
	std::string RS_Color_Gamemode = cvarManager->getCvar("RS_Color_GameMode").getStringValue();
	std::string RS_Color_Background = cvarManager->getCvar("RS_Color_Background").getStringValue();

	std::vector<std::string> RS_values = {
		"RS_disp_gamemode",
		"RS_disp_rank",
		"RS_disp_mmr",
		"RS_disp_mmr_change",
		"RS_disp_wins",
		"RS_disp_losses",
		"RS_disp_streak",
	};

	unsigned int size = 0;
	for (auto& it : RS_values) {
		bool tmp = cvarManager->getCvar(it).getBoolValue();
		if (tmp)
			size += 1;
	}

	int xPos = canvas.GetSize().X / 100;
	int yPos = canvas.GetSize().Y / 100;

	// Draw box here
	Vector2 drawLoc = { xPos * RS_x_position, yPos * RS_y_position };
	Vector2 sizeBox = { 170 * RS_scale, (23 * size) * RS_scale };
	canvas.SetPosition(drawLoc);

	//Set background Color
	if (custom_color) {
		RGB background_color = HexadecimalToRGB(RS_Color_Background);
		canvas.SetColor(background_color.r, background_color.g, background_color.b, 150);
	}
	else {
		canvas.SetColor(0, 0, 0, 150);
	}
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
				RGB gamemode_color = HexadecimalToRGB(RS_Color_Gamemode);
				canvas.SetColor(gamemode_color.r, gamemode_color.g, gamemode_color.b, 255);
				//canvas.SetColor(180, 180, 180, 255);
				canvas.DrawString(getPlaylistName(currentPlaylist), RS_scale, RS_scale);
			}
			else if (it == "RS_disp_rank")
			{
				std::string tmpRank = currentRank;
				std::replace(tmpRank.begin(), tmpRank.end(), '_', ' ');
				RGB rank_color = HexadecimalToRGB(RS_Color_Rank);
				canvas.SetColor(rank_color.r, rank_color.g, rank_color.b, 255);
				//canvas.SetColor(180, 180, 180, 255);
				canvas.DrawString(tmpRank, RS_scale, RS_scale);
			}
			else if (it == "RS_disp_mmr")
			{
				RGB mmr_color = HexadecimalToRGB(RS_Color_MMR);
				canvas.SetColor(mmr_color.r, mmr_color.g, mmr_color.b, 255);
				//canvas.SetColor(180, 180, 180, 255);
				std::stringstream ss;
				ss << std::fixed << std::setprecision(2) << current.myMMR;
				std::string mmr = ss.str();
				canvas.DrawString("MMR : " + mmr, RS_scale, RS_scale);
			}
			else if (it == "RS_disp_mmr_change")
			{
				std::stringstream ss;
				ss << std::fixed << std::setprecision(2) << current.MMRChange;
				std::string mmr = ss.str();
				if (current.MMRChange >= 0)
				{
					if (custom_color == true) {
						RGB MMRChange_color = HexadecimalToRGB(RS_Color_MMRChange);
						canvas.SetColor(MMRChange_color.r, MMRChange_color.g, MMRChange_color.b, 255);
					}
					else {
						canvas.SetColor(30, 224, 24, 255);
					}
					canvas.DrawString("MMRChange : +" + mmr, RS_scale, RS_scale);
				}
				else
				{
					if (custom_color == true) {
						RGB MMRChange_color = HexadecimalToRGB(RS_Color_MMRChange);
						canvas.SetColor(MMRChange_color.r, MMRChange_color.g, MMRChange_color.b, 255);
					}
					else {
						canvas.SetColor(224, 24, 24, 255);
					}
					canvas.DrawString("MMRChange : " + mmr, RS_scale, RS_scale);
				}
			}
			else if (it == "RS_disp_wins")
			{
				if (custom_color) {
					RGB wins_color = HexadecimalToRGB(RS_Color_Wins);
					canvas.SetColor(wins_color.r, wins_color.g, wins_color.b, 255);
				}
				else {
					canvas.SetColor(30, 224, 24, 255);
				}
				canvas.DrawString("Win : " + std::to_string(current.win), RS_scale, RS_scale);
			}
			else if (it == "RS_disp_losses")
			{
				if (custom_color) {
					RGB losses_color = HexadecimalToRGB(RS_Color_Losses);
					canvas.SetColor(losses_color.r, losses_color.g, losses_color.b, 255);
				}
				else {
					canvas.SetColor(224, 24, 24, 255);
				}
				canvas.DrawString("Losses : " + std::to_string(current.losses), RS_scale, RS_scale);
			}
			else if (it == "RS_disp_streak")
			{
				if (current.streak >= 0)
				{
					if (custom_color == true) {
						RGB streak_color = HexadecimalToRGB(RS_Color_Streak);
						canvas.SetColor(streak_color.r, streak_color.g, streak_color.b, 255);
					}
					else {
						canvas.SetColor(30, 224, 24, 255);
					}
					canvas.DrawString("Streak : +" + std::to_string(current.streak), RS_scale, RS_scale);
				}
				else
				{
					if (custom_color == true) {
						RGB streak_color = HexadecimalToRGB(RS_Color_Streak);
						canvas.SetColor(streak_color.r, streak_color.g, streak_color.b, 255);
					}
					else {
						canvas.SetColor(224, 24, 24, 255);
					}
					canvas.DrawString("Streak : " + std::to_string(current.streak), RS_scale, RS_scale);
				}
			}
			// Increase Y position;
			textPos.Y += (20 * RS_scale);
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
