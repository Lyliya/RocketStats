#pragma once
#pragma comment( lib, "pluginsdk.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

#include "Structs.h"

#define replaceAll(str, from, to) while(replace(str, from, to));

namespace NS_RS {
	constexpr auto plugin_version = "3.5";

	class RocketStats : public BakkesMod::Plugin::BakkesModPlugin/*, public BakkesMod::Plugin::PluginWindow*/
	{
		int currentPlaylist = 0;
		bool isGameEnded = false;
		bool isGameStarted = false;
		bool isBoosting = false;

		std::map<int, Stats> stats;
		Stats session;

		//std::unique_ptr<MMRNotifierToken> notifierToken;

		int myTeamNum = -1;

		int lastGameMode = 0;
		int currentGameMode = 0;
		float currentMMR = 100.0f;
		int currentTier = 0;

		std::string currentDivision;
		std::string currentRank;
		std::string lastRank;

		std::shared_ptr<ImageWrapper> crown;
		std::shared_ptr<ImageWrapper> win;
		std::shared_ptr<ImageWrapper> loose;
		std::shared_ptr<ImageWrapper> streak;

		int rank_nb = 23;

		//Plugin Load Routines
		virtual void onLoad();
		virtual void onUnload();

		// Utils
		std::string GetRank(int tierID);
		std::string GetPlaylistName(int playlistID);
		void LoadImgs();
		void LogImageLoadStatus(bool status, std::string imageName);

		// Game Hooks
		void GameStart(std::string eventName);
		void GameEnd(std::string eventName);
		void GameDestroyed(std::string eventName);

		// Stats mgmt
		void UpdateMMR(UniqueIDWrapper id);
		void SessionStats();
		void ResetStats();

		// Boost Hooks
		void OnBoostStart(std::string eventName);
		void OnBoostEnd(std::string eventName);

		// Rank / Div
		void InitRank();
		void MajRank(int _gameMode, bool isRanked, float _currentMMR, SkillRank playerRank);

		// Overlay mgmt
		void DisplayRank(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, float scale, bool showText);
		void DisplayMMR(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale, bool showImage);
		void DisplayWins(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale);
		void DisplayLoose(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale);
		void DisplayStreak(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale, bool showImage);

		// File I/O
		void WriteInFile(std::string _fileName, std::string _value);
		void writeGameMode();
		void writeMMR();
		void writeMMRChange();
		void writeStreak();
		void writeWin();
		void writeLosses();

		// Render
		void Render(CanvasWrapper canvas);


		t_ranks rank[23] = {
			{"Unranked", nullptr},
			{"Bronze_I", nullptr},
			{"Bronze_II", nullptr},
			{"Bronze_III", nullptr},
			{"Silver_I", nullptr},
			{"Silver_II", nullptr},
			{"Silver_III", nullptr},
			{"Gold_I", nullptr},
			{"Gold_II", nullptr},
			{"Gold_III", nullptr},
			{"Platinum_I", nullptr},
			{"Platinum_II", nullptr},
			{"Platinum_III", nullptr},
			{"Diamond_I", nullptr},
			{"Diamond_II", nullptr},
			{"Diamond_III", nullptr},
			{"Champion_I", nullptr},
			{"Champion_II", nullptr},
			{"Champion_III", nullptr},
			{"Grand_Champion_I", nullptr},
			{"Grand_Champion_II", nullptr},
			{"Grand_Champion_III", nullptr},
			{"Supersonic_Legend", nullptr},
		};

		const std::map<int, std::string> playlistName = {
		{1, "Duel"},
		{2, "Doubles"},
		{3, "Standard"},
		{4, "Chaos"},

		{6, "Private Match"},
		{7, "Season"},
		{8, "Offline Splitscreen"},
		{9, "Training"},

		{10, "Ranked Duel"},
		{11, "Ranked Doubles"},
		{12, "Ranked Solo Standard"},
		{13, "Ranked Standard"},

		{15, "Casual SnowDay"},
		{16, "Experimental"},
		{17, "Casual Hoops"},
		{18, "Casual Rumble"},

		{19, "Workshop"},
		{20, "UGCTrainingEditor"},
		{21, "UGCTraining"},
		{22, "Custom Tournament"},
		{23, "Casual Dropshot"},
		{24, "Local"},
		{26, "FaceIt"},

		{27, "Ranked Hoops"},
		{28, "Ranked Rumble"},
		{29, "Ranked Dropshot"},
		{30, "Ranked SnowDay"},

		{31, "Ghost Hunt"},
		{32, "Beachball"},
		{33, "Spike Rush"},
		{34, "Season Tournament"},
		{35, "Rocket Labs"},
		{37, "Dropshot Rumble"},
		{38, "Heatseeker"},
		{41, "Boomer Ball"},
		{43, "Heatseeker Doubles"},
		{44, "Winter Breakaway"},
		{46, "Gridiron"},
		{47, "Super Cube"},
		{48, "Tactical Rumble"},
		{49, "Spring Loaded"}
		};
	};
}