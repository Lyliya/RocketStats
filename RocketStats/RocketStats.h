#pragma once
#pragma comment( lib, "pluginsdk.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

typedef struct Stats {
	float myMMR = 0;
	float MMRChange = 0;
	int win = 0;
	int losses = 0;
	int streak = 0;
	bool isInit = 0;
} Stats;

typedef struct RGB {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} RGB;

class RocketStats : public BakkesMod::Plugin::BakkesModPlugin
{
private : 
	std::shared_ptr<bool> enabled;

public:
	//Function
	virtual void onLoad();
	virtual void onUnload();
	void Start(std::string eventName);
	void GameEnd(std::string eventName);
	void OnBoost(std::string eventName);
	void OnBoostEnd(std::string eventName);
	void WriteInFile(std::string _fileName, std::string _value);
	void GameDestroyed(std::string eventName);
	void Render(CanvasWrapper canvas);
	void ComputeMMR(int intervalTime);
	void SessionStats();

	// Write info in file
	void writeMMR();
	void writeMMRChange();
	void writeStreak();
	void writeWin();
	void writeLosses();

	int currentPlaylist;
	bool isGameEnded;
	bool isGameStarted = false;
	bool isBoosting = false;

	std::string GetRank(int tierID);

	std::map<int, Stats> stats;
	Stats session;

	//Ranked function
	void initRank();
	void majRank(int _gameMode, float _currentMMR, SkillRank playerRank);
	
	void ResetStats();
	void StopBoost();
	void togglePlugin(bool state);
	
	void DisplayRank(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp);
	void DisplayMMR(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current);
	void DisplayWins(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current);
	void DisplayLoose(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current);
	void DisplayStreak(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current);


	//Var
	int myTeamNum = -1;
	SteamID mySteamID;
	
	int lastGameMode;
	int currentGameMode;
	float currentMMR;
	int currentTier;
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
		{10, "Ranked Duel"},
		{11, "Ranked Doubles"},
		{12, "Ranked Solo Standard"},
		{13, "Ranked Standard"},
		{14, "Mutator Mashup"},
		{16, "Rocket Labs"},
		{27, "Hoops"},
		{28, "Rumble"},
		{29, "Dropshot"},
		{30, "Snowday"},
	};
	std::string getPlaylistName(int playlistID);
};