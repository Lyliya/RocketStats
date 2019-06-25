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


	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&RocketStats::Start, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", bind(&RocketStats::GameEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.BeginState", bind(&RocketStats::OnBoost, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function CarComponent_Boost_TA.Active.EndState", bind(&RocketStats::OnBoostEnd, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed", bind(&RocketStats::GameDestroyed, this, std::placeholders::_1));
	cvarManager->log("Load 1.1");

	WriteInFile("RocketStats_Win.txt", std::to_string(0));
	WriteInFile("RocketStats_Streak.txt", std::to_string(0));
	WriteInFile("RocketStats_Loose.txt", std::to_string(0));
	WriteInFile("RocketStats_MMRChange.txt", std::to_string(0));

	initRankList();
	initRank();
}

void RocketStats::onUnload()
{
	gameWrapper->UnhookEvent("Function GameEvent_TA.Countdown.BeginState");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded");
	gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.BeginState");
	gameWrapper->UnhookEvent("Function CarComponent_Boost_TA.Active.EndState");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed");
	cvarManager->log("Unload 1.1");
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
		cvarManager->log("SteamID: " + std::to_string(mySteamID.ID));

		// Get and Update MMR
		MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
		currentPlaylist = mmrw.GetCurrentPlaylist();
		cvarManager->log(std::to_string(currentPlaylist));
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
			WriteInFile("RocketStats_MMRChange.txt", "+ " + std::to_string(tmp));
		}
		else
		{
			WriteInFile("RocketStats_MMRChange.txt", std::to_string(tmp));
		}

		WriteInFile("RocketStats_Win.txt", std::to_string(stats[currentPlaylist].win));

		if (stats[currentPlaylist].streak > 0)
		{
			WriteInFile("RocketStats_Streak.txt", "+ " + std::to_string(stats[currentPlaylist].streak));
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

		majRank(currentPlaylist, stats[currentPlaylist].myMMR);
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

			cvarManager->log("You WIN");
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

			cvarManager->log("You LOOSE");
			WriteInFile("RocketStats_Loose.txt", std::to_string(stats[currentPlaylist].losses));
		}

		if (stats[currentPlaylist].streak > 0)
		{
			WriteInFile("RocketStats_Streak.txt","+ " + std::to_string(stats[currentPlaylist].streak));
		}
		else
		{
			WriteInFile("RocketStats_Streak.txt", std::to_string(stats[currentPlaylist].streak));
		}

		gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
			MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
			float save = mmrw.GetPlayerMMR(mySteamID, currentPlaylist);
			cvarManager->log("Current Playlist: " + std::to_string(currentPlaylist));
			cvarManager->log("New MMR: " + std::to_string(save));
			cvarManager->log("Initial MMR: " + std::to_string(stats[currentPlaylist].myMMR));

			stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
			stats[currentPlaylist].myMMR = save;
			int tmp = ((stats[currentPlaylist].MMRChange < 0) ? -1 : 1) * std::round(fabs(stats[currentPlaylist].MMRChange));
			cvarManager->log(std::string("MMR Change: ") + std::to_string(tmp));
			cvarManager->log(std::string("MMR: ") + std::to_string(stats[currentPlaylist].myMMR));

			if (tmp > 0)
			{
				WriteInFile("RocketStats_MMRChange.txt","+ " + std::to_string(tmp));
			}
			else
			{
				WriteInFile("RocketStats_MMRChange.txt", std::to_string(tmp));
			}
		}, 3);

		// Reset myTeamNum security
		myTeamNum = -1;

		majRank(currentPlaylist, stats[currentPlaylist].myMMR);
	}
}

void RocketStats::GameDestroyed(std::string eventName) {
	//Check if Game Ended, if not, RAGE QUIT or disconnect
	if (isGameEnded == false) {
		stats[currentPlaylist].losses += 1;
		if (stats[currentPlaylist].streak > 0)
		{
			stats[currentPlaylist].streak = 0;
		}
		else
		{
			stats[currentPlaylist].streak -= 1;
		}

		cvarManager->log("You LOOSE");
		if (stats[currentPlaylist].streak > 0)
		{
			WriteInFile("RocketStats_Streak.txt", "+ " + std::to_string(stats[currentPlaylist].streak));
		}
		else
		{
			WriteInFile("RocketStats_Streak.txt", std::to_string(stats[currentPlaylist].streak));
		}
		WriteInFile("RocketStats_Loose.txt", std::to_string(stats[currentPlaylist].losses));

		gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
			MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
			float save = mmrw.GetPlayerMMR(mySteamID, currentPlaylist);
			cvarManager->log("Current Playlist: " + std::to_string(currentPlaylist));
			cvarManager->log("New MMR: " + std::to_string(save));
			cvarManager->log("Initial MMR: " + std::to_string(stats[currentPlaylist].myMMR));

			stats[currentPlaylist].MMRChange = stats[currentPlaylist].MMRChange + (save - stats[currentPlaylist].myMMR);
			stats[currentPlaylist].myMMR = save;
			int tmp = ((stats[currentPlaylist].MMRChange < 0) ? -1 : 1) * std::round(fabs(stats[currentPlaylist].MMRChange));
			cvarManager->log(std::string("MMR Change: ") + std::to_string(tmp));
			cvarManager->log(std::string("MMR: ") + std::to_string(stats[currentPlaylist].myMMR));

			if (tmp > 0)
			{
				WriteInFile("RocketStats_MMRChange.txt", "+ " + std::to_string(tmp));
			}
			else
			{
				WriteInFile("RocketStats_MMRChange.txt", std::to_string(tmp));
			}
		}, 10);

		isGameEnded = true;
	}
}

void RocketStats::OnBoost(std::string eventName) {
	//cvarManager->log("BOOOOST");

	CarWrapper cWrap = gameWrapper->GetLocalCar();

	if (!cWrap.IsNull())
	{
		BoostWrapper bWrap = cWrap.GetBoostComponent();

		cvarManager->log("BOOOOST ----> " + std::to_string(bWrap.GetbActive()));
	}
	return;
}

void RocketStats::OnBoostEnd(std::string eventName) {
	//cvarManager->log("Stop BOOST");

	CarWrapper cWrap = gameWrapper->GetLocalCar();

	if (!cWrap.IsNull())
	{
		BoostWrapper bWrap = cWrap.GetBoostComponent();

		cvarManager->log("Stop BOOOOST ----> " + std::to_string(bWrap.GetbActive()));
	}
	return;
}

void RocketStats::ResetStats()
{
	for (auto& kv : stats) {
		kv.second.MMRChange = 0;
		kv.second.win = 0;
		kv.second.losses = 0;
		kv.second.streak = 0;
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

	myFile.open("./bakkesmod/" + _fileName, ios::out | ios::trunc);

	if (myFile.is_open())
	{
		myFile << _value;

		myFile.close();
	}
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
		{"Grand_Champion", {1223.0f, 1300.0f}},
	};

	//1v1 Ranked code : 11
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
		{"Grand_Champion", {1501.0f, 1631.0f}},
	};

	listRank = {
		{10, v1Rank},
		{11, v2Rank}
	};
}

void RocketStats::initRank()
{
	lastGameMode = 0;
	currentGameMode = 0;
	currentMMR = 0;
	currentRank = "norank";
	lastRank = "norank";

	cvarManager->log(std::string("Ouverture file "));

	string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"40\" height = \"40\" />";

	WriteInFile("RocketStats_images/current_image.html", _value);

	cvarManager->log(std::string("Close file "));
}

void RocketStats::majRank(int _gameMode, float _currentMMR)
{
	currentGameMode = _gameMode;
	currentMMR = _currentMMR;
	lastRank == currentRank;

	if (currentGameMode >= 10 && currentGameMode <= 13)	
	{
		cvarManager->log(std::string("Current Game Mode -----> ") + std::to_string(currentGameMode));

		for (auto it = listRank[currentGameMode]._rank.begin(); it != listRank[currentGameMode]._rank.end(); it++)
		{
			if (currentMMR >= it->second.first && currentMMR <= it->second.second)
			{
				currentRank = it->first;

				cvarManager->log(std::string("Rank ") + currentRank);
			}
		}

		if (currentRank != lastRank)
		{
			cvarManager->log(std::string("Ouverture file "));

			string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"" + currentRank + ".png" + "\" width = \"40\" height = \"40\" />";

			WriteInFile("RocketStats_images/current_image.html", _value);

			cvarManager->log(std::string("Close file "));
		}
	}
	else
	{
		string _value = "<meta http-equiv = \"refresh\" content = \"5\" /><img src = \"current.png\" width = \"40\" height = \"40\" />";

		WriteInFile("RocketStats_images/current_image.html", _value);
	}
}

#pragma endregion