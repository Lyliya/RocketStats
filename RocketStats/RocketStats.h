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

	typedef struct Ranks {
		std::string nameMode;
		std::map<std::string, std::pair<float, float>> _rank;
	} Ranks;

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

	std::map<int, Stats> stats;
	Stats session;

	//Ranked function
	void initRank();
	void majRank(int _gameMode, float _currentMMR);
	void initRankList();
	
	void ResetStats();
	void StopBoost();
	void togglePlugin(bool state);
	
	//Var
	int myTeamNum = -1;
	SteamID mySteamID;
	
	int lastGameMode;
	int currentGameMode;
	float currentMMR;
	std::string currentRank;
	std::string lastRank;

	bool isLoad = true;

	std::map<int, Ranks> listRank;

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