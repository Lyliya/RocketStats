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
	int currentPlaylist;
	int isGameEnded;

	std::map<int, Stats> stats;

	//Ranked function
	void initRank();
	void majRank(int _gameMode, float _currentMMR);
	void initRankList();
	
	void ResetStats();
	
	//Var
	int myTeamNum = -1;
	SteamID mySteamID;
	
	int lastGameMode;
	int currentGameMode;
	float currentMMR;
	string currentRank;
	string lastRank;

	std::map<int, Ranks> listRank;
};