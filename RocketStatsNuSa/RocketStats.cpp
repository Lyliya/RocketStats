/* ==================================
 *   Developped by Lyliya & NuSa
 * ================================== */

 // Include
#include "RocketStats.h"
#include "bakkesmod/wrappers/GameEvent/GameEventWrapper.h"
#include "bakkesmod/wrappers/GameEvent/ServerWrapper.h"
#include "bakkesmod/wrappers/ArrayWrapper.h"
#include "bakkesmod\wrappers\includes.h"
#include "utils/parser.h"
#include <chrono>
#include <thread>

// File include
#include <iostream>
#include <fstream>

BAKKESMOD_PLUGIN(RocketStats, "RocketStats", "1.0", 0)

void RocketStats::onLoad()
{
	cvarManager->registerNotifier("RocketStats_reset_stats", [this](std::vector<string> params) {
		ResetStats();
	}
	, "Reset Stats", PERMISSION_ALL);

	// Register drawable
	gameWrapper->RegisterDrawable(std::bind(&RocketStats::Render, this, std::placeholders::_1));

	// Hook on Event
	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&RocketStats::Start, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&RocketStats::GameEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", bind(&RocketStats::OnBoost, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed", bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));
	//cvarManager->log("Load 1.1");

	WriteInFile("RocketStats_Win.txt", std::to_string(0));
	WriteInFile("RocketStats_Streak.txt", std::to_string(0));
	WriteInFile("RocketStats_Loose.txt", std::to_string(0));
	WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));

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

	WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
}

void RocketStats::onUnload()
{
	gameWrapper->UnhookEvent("Function GameEvent_TA.Countdown.BeginState");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded");
	gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.BeginState");
	gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.EndState");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed");
	//cvarManager->log("Unload 1.1");
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
		//cvarManager->log("Current GameMode: " + getPlaylistName(currentPlaylist));
		float save = mmrw.GetPlayerMMR(mySteamID, currentPlaylist);
		if (stats[currentPlaylist].isInit == false) {
			stats[currentPlaylist].myMMR = save;
			stats[currentPlaylist].isInit = true;
		}
		stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
		stats[currentPlaylist].myMMR = save;
		int tmp = ((stats[currentPlaylist].MMRChange < 0) ? -1 : 1) * std::round(fabs(stats[currentPlaylist].MMRChange));

		if (tmp > 0)
		{
			WriteInFile("RocketStats_MMRChange.txt", "+" + std::to_string(tmp));
		}
		else
		{
			WriteInFile("RocketStats_MMRChange.txt", std::to_string(tmp));
		}

		WriteInFile("RocketStats_Win.txt", std::to_string(stats[currentPlaylist].win));

		if (stats[currentPlaylist].streak > 0)
		{
			WriteInFile("RocketStats_Streak.txt", "+" + std::to_string(stats[currentPlaylist].streak));
		}
		else
		{
			WriteInFile("RocketStats_Streak.txt", std::to_string(stats[currentPlaylist].streak));
		}

		WriteInFile("RocketStats_Loose.txt", std::to_string(stats[currentPlaylist].losses));



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

			if (stats[currentPlaylist].streak < 0)
			{
				stats[currentPlaylist].streak = 1;
			}
			else
			{
				stats[currentPlaylist].streak += 1;
			}

			//cvarManager->log("You WIN");
			WriteInFile("RocketStats_Win.txt", std::to_string(stats[currentPlaylist].win));
		}
		else {
			// On Loose, Increase Win Number and decrease streak
			stats[currentPlaylist].losses += 1;
			if (stats[currentPlaylist].streak > 0)
			{
				stats[currentPlaylist].streak = 0;
			}
			else
			{
				stats[currentPlaylist].streak -= 1;
			}

			//cvarManager->log("You LOOSE");
			WriteInFile("RocketStats_Loose.txt", std::to_string(stats[currentPlaylist].losses));
		}

		if (stats[currentPlaylist].streak > 0)
		{
			WriteInFile("RocketStats_Streak.txt","+" + std::to_string(stats[currentPlaylist].streak));
		}
		else
		{
			WriteInFile("RocketStats_Streak.txt", std::to_string(stats[currentPlaylist].streak));
		}

		gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
			MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
			float save = mmrw.GetPlayerMMR(mySteamID, currentPlaylist);
			//cvarManager->log("Current Playlist: " + std::to_string(currentPlaylist));
			//cvarManager->log("New MMR: " + std::to_string(save));
			//cvarManager->log("Initial MMR: " + std::to_string(stats[currentPlaylist].myMMR));

			stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
			stats[currentPlaylist].myMMR = save;
			int tmp = ((stats[currentPlaylist].MMRChange < 0) ? -1 : 1) * std::round(fabs(stats[currentPlaylist].MMRChange));
			//cvarManager->log(std::string("MMR Change: ") + std::to_string(tmp));
			//cvarManager->log(std::string("MMR: ") + std::to_string(stats[currentPlaylist].myMMR));
			majRank(currentPlaylist, stats[currentPlaylist].myMMR);

			if (tmp > 0)
			{
				WriteInFile("RocketStats_MMRChange.txt","+" + std::to_string(tmp));
			}
			else
			{
				WriteInFile("RocketStats_MMRChange.txt", std::to_string(tmp));
			}
		}, 3);

		// Reset myTeamNum security
		myTeamNum = -1;

		WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
	}
}

void RocketStats::GameDestroyed(std::string eventName) {
	//Check if Game Ended, if not, RAGE QUIT or disconnect
	if (isGameStarted == true && isGameEnded == false) {
		stats[currentPlaylist].losses += 1;
		if (stats[currentPlaylist].streak > 0)
		{
			stats[currentPlaylist].streak = 0;
		}
		else
		{
			stats[currentPlaylist].streak -= 1;
		}

		//cvarManager->log("You LOOSE");
		if (stats[currentPlaylist].streak > 0)
		{
			WriteInFile("RocketStats_Streak.txt", "+" + std::to_string(stats[currentPlaylist].streak));
		}
		else
		{
			WriteInFile("RocketStats_Streak.txt", std::to_string(stats[currentPlaylist].streak));
		}
		WriteInFile("RocketStats_Loose.txt", std::to_string(stats[currentPlaylist].losses));

		gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
			MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
			float save = mmrw.GetPlayerMMR(mySteamID, currentPlaylist);
			//cvarManager->log("Current Playlist: " + std::to_string(currentPlaylist));
			//cvarManager->log("New MMR: " + std::to_string(save));
			//cvarManager->log("Initial MMR: " + std::to_string(stats[currentPlaylist].myMMR));

			stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
			stats[currentPlaylist].myMMR = save;
			int tmp = ((stats[currentPlaylist].MMRChange < 0) ? -1 : 1) * std::round(fabs(stats[currentPlaylist].MMRChange));
			//cvarManager->log(std::string("MMR Change: ") + std::to_string(tmp));
			//cvarManager->log(std::string("MMR: ") + std::to_string(stats[currentPlaylist].myMMR));
			majRank(currentPlaylist, stats[currentPlaylist].myMMR);

			if (tmp > 0)
			{
				WriteInFile("RocketStats_MMRChange.txt", "+" + std::to_string(tmp));
			}
			else
			{
				WriteInFile("RocketStats_MMRChange.txt", std::to_string(tmp));
			}
		}, 10);		
	}
	isGameEnded = true;
	isGameStarted = false;
	WriteInFile("RocketStats_images/BoostState.txt", std::to_string(-1));
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
	cvarManager->log("hey");
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
	WriteInFile("RocketStats_Win.txt", std::to_string(0));
	WriteInFile("RocketStats_Streak.txt", std::to_string(0));
	WriteInFile("RocketStats_Loose.txt", std::to_string(0));
	WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));

	initRank();
}

void RocketStats::WriteInFile(std::string _fileName, std::string _value)
{
	ofstream myFile;

	myFile.open("./bakkesmod/RocketStats/" + _fileName, ios::out | ios::trunc);

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
		{"Bronze_II", {142.0f, 204.0f}},
		{"Bronze_III", {207.0f, 264.0f}},
		{"Silver_I", {272.0f, 326.0f}},
		{"Silver_II", {327.0f, 384.0f}},
		{"Silver_III", {389.0f, 444.0f}},
		{"Gold_I", {453.0f, 504.0f}},
		{"Gold_II", {507.0f, 566.0f}},
		{"Gold_III", {572.0f, 624.0f}},
		{"Platinum_I", {632.0f, 685.0f}},
		{"Platinum_II", {686.0f, 745.0f}},
		{"Platinum_III", {752.0f, 805.0f}},
		{"Diamond_I", {812.0f, 865.0f}},
		{"Diamond_II", {866.0f, 925.0f}},
		{"Diamond_III", {929.0f, 983.0f}},
		{"Champion_I", {995.0f, 1062.0f}},
		{"Champion_II", {1074.0f, 1144.0f}},
		{"Champion_III", {1155.0f, 1223.0f}},
		{"Grand_Champion", {1223.0f, 9999.0f}},
	};

	//2v2 Ranked code : 11
	Ranks v2Rank;
	v2Rank.nameMode = "2v2";
	v2Rank._rank = {
		{"Bronze_I", {0.0f, 182.0f}},
		{"Bronze_II", {189.0f, 246.0f}},
		{"Bronze_III", {250.0f, 303.0f}},
		{"Silver_I", {312.0f, 365.0f}},
		{"Silver_II", {370.0f, 425.0f}},
		{"Silver_III", {428.0f, 483.0f}},
		{"Gold_I", {498.0f, 545.0f}},
		{"Gold_II", {547.0f, 602.0f}},
		{"Gold_III", {614.0f, 680.0f}},
		{"Platinum_I", {695.0f, 760.0f}},
		{"Platinum_II", {774.0f, 841.0f}},
		{"Platinum_III", {854.0f, 920.0f}},
		{"Diamond_I", {934.0f, 1001.0f}},
		{"Diamond_II", {1014.0f, 1080.0f}},
		{"Diamond_III", {1095.0f, 1180.0f}},
		{"Champion_I", {1195.0f, 1280.0f}},
		{"Champion_II", {1285.0f, 1380.0f}},
		{"Champion_III", {1395.0f, 1500.0f}},
		{"Grand_Champion", {1501.0f, 9999.0f}},
	};

	//solo 3v3 Ranked code : 12
	Ranks sv3Rank;
	sv3Rank.nameMode = "solo 3v3";
	sv3Rank._rank = {
		{"Bronze_I", {0.0f, 153.0f}},
		{"Bronze_II", {150.0f, 209.0f}},
		{"Bronze_III", {210.0f, 274.0f}},
		{"Silver_I", {266.0f, 329.0f}},
		{"Silver_II", {328.0f, 387.0f}},
		{"Silver_III", {389.0f, 443.0f}},
		{"Gold_I", {449.0f, 506.0f}},
		{"Gold_II", {510.0f, 563.0f}},
		{"Gold_III", {571.0f, 623.0f}},
		{"Platinum_I", {630.0f, 683.0f}},
		{"Platinum_II", {692.0f, 745.0f}},
		{"Platinum_III", {753.0f, 804.0f}},
		{"Diamond_I", {815.0f, 881.0f}},
		{"Diamond_II", {895.0f, 961.0f}},
		{"Diamond_III", {975.0f, 1042.0f}},
		{"Champion_I", {1055.0f, 1123.0f}},
		{"Champion_II", {1124.0f, 1201.0f}},
		{"Champion_III", {1211.0f, 1292.0f}},
		{"Grand_Champion", {1287.0f, 9999.0f}},
	};

	//3v3 Standard Ranked code : 13
	Ranks v3Rank;
	v3Rank.nameMode = "solo 3v3";
	v3Rank._rank = {
		{"Bronze_I", {0.0f, 184.0f}},
		{"Bronze_II", {185.0f, 251.0f}},
		{"Bronze_III", {248.0f, 309.0f}},
		{"Silver_I", {308.0f, 366.0f}},
		{"Silver_II", {369.0f, 423.0f}},
		{"Silver_III", {430.0f, 485.0f}},
		{"Gold_I", {489.0f, 545.0f}},
		{"Gold_II", {548.0f, 604.0f}},
		{"Gold_III", {612.0f, 682.0f}},
		{"Platinum_I", {695.0f, 761.0f}},
		{"Platinum_II", {773.0f, 841.0f}},
		{"Platinum_III", {854.0f, 920.0f}},
		{"Diamond_I", {934.0f, 1001.0f}},
		{"Diamond_II", {1012.0f, 1080.0f}},
		{"Diamond_III", {1095.0f, 1180.0f}},
		{"Champion_I", {1195.0f, 1280.0f}},
		{"Champion_II", {1295.0f, 1380.0f}},
		{"Champion_III", {1395.0f, 1499.0f}},
		{"Grand_Champion", {1501.0f, 9999.0f}},
	};

	listRank = {
		{10, v1Rank},
		{11, v2Rank},
		{12, sv3Rank},
		{13, v3Rank}
	};
}

void RocketStats::initRank()
{
	lastGameMode = 0;
	currentGameMode = 0;
	currentMMR = 0;
	currentRank = "norank";
	lastRank = "norank";

	string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

	WriteInFile("RocketStats_images/current_image.html", _value);
}

void RocketStats::majRank(int _gameMode, float _currentMMR)
{
	currentGameMode = _gameMode;
	currentMMR = _currentMMR;
	lastRank == currentRank;

	if (currentGameMode >= 10 && currentGameMode <= 13)
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
			string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"" + currentRank + ".png" + "\" width = \"100\" height = \"100\" />";

			WriteInFile("RocketStats_images/current_image.html", _value);
		}
	}
	else
	{
		string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"100\" height = \"100\" />";

		WriteInFile("RocketStats_images/current_image.html", _value);
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
	Vector2 drawLoc = { xPos *RS_x_position, yPos * RS_y_position};
	Vector2 sizeBox = { 170 * RS_scale, (23*size) * RS_scale };
	canvas.SetPosition(drawLoc);
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
				std::string tmpRank = currentRank;
				std::replace(tmpRank.begin(), tmpRank.end(), '_', ' ');
				canvas.SetColor(180, 180, 180, 255);
				canvas.DrawString(tmpRank, RS_scale, RS_scale);
			}
			else if (it == "RS_disp_mmr")
			{
				canvas.SetColor(180, 180, 180, 255);
				std::stringstream ss;
				ss << std::fixed << std::setprecision(2) << stats[currentPlaylist].myMMR;
				std::string mmr = ss.str();
				canvas.DrawString("MMR : " + mmr, RS_scale, RS_scale);
			}
			else if (it == "RS_disp_mmr_change")
			{
				std::stringstream ss;
				ss << std::fixed << std::setprecision(2) << stats[currentPlaylist].MMRChange;
				std::string mmr = ss.str();
				if (stats[currentPlaylist].MMRChange >= 0)
				{
					canvas.SetColor(30, 224, 24, 255);
					canvas.DrawString("MMRChange : +" + mmr, RS_scale, RS_scale);
				}
				else
				{
					canvas.SetColor(224, 24, 24, 255);
					canvas.DrawString("MMRChange : " + mmr, RS_scale, RS_scale);
				}
			}
			else if (it == "RS_disp_wins")
			{
				canvas.SetColor(30, 224, 24, 255);
				canvas.DrawString("Win : " + std::to_string(stats[currentPlaylist].win), RS_scale, RS_scale);
			}
			else if (it == "RS_disp_losses")
			{
				canvas.SetColor(224, 24, 24, 255);
				canvas.DrawString("Losses : " + std::to_string(stats[currentPlaylist].losses), RS_scale, RS_scale);
			}
			else if (it == "RS_disp_streak")
			{
				if (stats[currentPlaylist].streak >= 0)
				{
					canvas.SetColor(30, 224, 24, 255);
					canvas.DrawString("Streak : +" + std::to_string(stats[currentPlaylist].streak), RS_scale, RS_scale);
				}
				else
				{
					canvas.SetColor(224, 24, 24, 255);
					canvas.DrawString("Streak : " + std::to_string(stats[currentPlaylist].streak), RS_scale, RS_scale);
				}
			}
			// Increase Y position;
			textPos.Y += (20 * RS_scale);
		}
	}
}