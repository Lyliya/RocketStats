#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"


typedef struct {
	float myMMR, MMRChange = 0;
	int win, losses, streak = 0;
	bool isInit = 0;
} Stats;

class RocketStats : public BakkesMod::Plugin::BakkesModPlugin
{

	typedef struct {
		std::string nameMode;
		std::map<std::string, std::pair<float, float>> _rank;
	}Ranks;

private : 
	shared_ptr<bool> enabled;

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

	int currentPlaylist;
	bool isGameEnded;
	bool isGameStarted = false;
	bool isBoosting = false;

	std::map<int, Stats> stats;

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
	string currentRank;
	string lastRank;

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
		{15, "Snow Day"},
		{16, "Rocket Labs"},
		{17, "Hoops"},
		{18, "Rumble"},
		{23, "Dropshot"},
	};
	std::string getPlaylistName(int playlistID);
};