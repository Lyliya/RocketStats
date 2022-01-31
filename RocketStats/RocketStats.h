#pragma once
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

#include <any>
#include <map>
#include <fstream>
#include <functional>
#include <utils/parser.h>

#include "Utils.h"

#include "json.hpp"

using json = nlohmann::json;

namespace fs = std::filesystem;

struct Color {
	bool enable = false;
	unsigned char r = 255;
	unsigned char g = 255;
	unsigned char b = 255;
	unsigned char alpha = 255;
};

struct Element {
	std::string name = "Unknown";
	std::string type;
	std::string value;
	std::vector<Vector2> positions;
	Vector2 size;
	float scale = 1;
	float width = 1;
	Color color;
	Color fill;
	Color stroke;
	bool wrap = false;
	bool shadow = false;
};

struct Font {
	std::string name = "Unknown";
	std::map<std::string, int> common;
	std::vector<std::shared_ptr<ImageWrapper>> pages;
	std::vector<std::map<std::string, int>> chars;
	std::vector<std::map<std::string, int>> kernings;
};

struct Stats {
	float myMMR = 100.0f;
	float MMRChange = 0.0f;
	float MMRCumulChange = 0.0f;
	int win = 0;
	int loss = 0;
	int streak = 0;
	bool isInit = 0;
};

struct Theme {
	std::string name = "Unknown";
	std::vector<Font> fonts;
	std::vector<Element> elements;
};

struct Vector2D {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};


class RocketStats : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	std::shared_ptr<bool> enabled;
	std::string rs_path = "RocketStats";

	char theme_refresh = 2;
	unsigned char theme_style = 0;
	std::string theme_selected = "Default";

	json theme_config;
	Theme theme_render;
	std::vector<Theme> themes;
	std::map<std::string, std::string> theme_vars;
	std::map<std::string, std::shared_ptr<ImageWrapper>> theme_images;

public:
	// Utils
	Stats GetStats();
	std::string GetRank(int tierID);
	std::string GetPlaylistName(int playlistID);
	void LogImageLoadStatus(bool status, std::string imageName);
	std::shared_ptr<ImageWrapper> LoadImg(const std::string& _filename, bool canvasLoad = true);
	void LoadImgs();

	// PluginLoadRoutines
	virtual void onLoad();
	virtual void onUnload();

	// GameMgmt
	void GameStart(std::string eventName);
	void GameEnd(std::string eventName);
	void GameDestroyed(std::string eventName);

	// StatsMgmt
	void UpdateMMR(UniqueIDWrapper id);
	void SessionStats();
	void ResetStats();

	// BoostMgmt
	void OnBoostStart(std::string eventName);
	void OnBoostEnd(std::string eventName);
	//void StopBoost();

	// Rank / Div
	void InitRank();
	void MajRank(int _gameMode, bool isRanked, float _currentMMR, SkillRank playerRank);

	// OverlayMgmt
	void LoadThemes();
	bool ChangeTheme(std::string name);
	void RefreshTheme(std::string old, CVarWrapper now);
	void Render(CanvasWrapper canvas);
	struct Element CalculateElement(CanvasWrapper& canvas, json& element, std::map<std::string, std::any>& options, bool& check);
	void RenderElement(CanvasWrapper& canvas, Element& element);

	// File I / O
	bool ExistsPath(std::string _filename, bool root = false);
	bool RemoveFile(std::string _filename, bool root = false);
	std::string ReadFile(std::string _filename, bool root = false);
	void WriteInFile(std::string _fileName, std::string _value, bool root = false);
	void WriteSettings();
	void ReadConfig();
	void WriteConfig();
	void WriteGameMode();
	void WriteMMR();
	void WriteMMRChange();
	void WriteMMRCumulChange();
	void WriteWin();
	void WriteLoss();
	void WriteStreak();

	int currentPlaylist = 0;
	bool isGameEnded = false;
	bool isGameStarted = false;
	bool isBoosting = false;

	Stats always;
	Stats session;
	std::map<int, Stats> stats;

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
	std::shared_ptr<ImageWrapper> loss;
	std::shared_ptr<ImageWrapper> streak;

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
