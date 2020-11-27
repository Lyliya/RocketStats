#pragma once
#pragma comment( lib, "pluginsdk.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

struct Stats {
	float myMMR = 100.0f;
	float MMRChange = 0.0f;
	int win = 0;
	int losses = 0;
	int streak = 0;
	bool isInit = 0;
};

class RocketStats : public BakkesMod::Plugin::BakkesModPlugin
{
private: 
	std::shared_ptr<bool> enabled;

public:
	virtual void onLoad();
	virtual void onUnload();
	void togglePlugin(bool state);

	std::string GetRank(int tierID);
	std::string GetPlaylistName(int playlistID);

	void GameStart(std::string eventName);
	void GameEnd(std::string eventName);
	void GameDestroyed(std::string eventName);

	void UpdateMMR(float intervalTime);
	void SessionStats();
	void ResetStats();

	void OnBoostStart(std::string eventName);
	void OnBoostEnd(std::string eventName);
	void StopBoost();


	void InitRank();
	void MajRank(int _gameMode, float _currentMMR, SkillRank playerRank);

	void DisplayRank(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, float scale);
	void DisplayMMR(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale);
	void DisplayWins(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale);
	void DisplayLoose(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale);
	void DisplayStreak(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale);
	void Render(CanvasWrapper canvas);

	void WriteInFile(std::string _fileName, std::string _value);
	void writeMMR();
	void writeMMRChange();
	void writeStreak();
	void writeWin();
	void writeLosses();

	int currentPlaylist = 0;
	bool isGameEnded = false;
	bool isGameStarted = false;
	bool isBoosting = false;


	std::map<int, Stats> stats;
	Stats session;

	int myTeamNum = -1;
	SteamID mySteamID = {0};
	
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

	bool isLoad = true;

	int rank_nb = 23;

	typedef struct s_ranks {
		std::string name;
		std::shared_ptr<ImageWrapper> image;
	} t_ranks;

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
		{7, "Offline Season"},
		{8, "Offline Splitscreen"},
		{9, "Training"},

		{10, "Ranked Duel"},
		{11, "Ranked Doubles"},
		{12, "Ranked Solo Standard"},
		{13, "Ranked Standard"},

		{14, "Mutator Mashup"},
		{15, "SnowdayPromotion"}, // not sure
		{16, "Rocket Labs"},
		{17, "Casual Basketball"},
		{18, "Casual Rumble"},
		{23, "Casual Dropshot"}, // not sure

		{19, "Workshop Map"},
		{22, "Tournament Match"},
		{24, "Local Match"},

		{27, "Hoops"},
		{28, "Rumble"},
		{29, "Dropshot"},
		{30, "Snowday"},

		{31, "Haunted Ball"},
		{32, "Beachball"},
		{33, "Rugby"},
		{37, "RumShot"}, // not sure
		{38, "Heatseeker"}, // not sure
		{41, "Boomer Ball"}
	};
};
