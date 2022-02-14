#pragma once
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

#include <map>
#include <fstream>
#include <functional>
#include <utils/parser.h>

#include "Utils.h"

#include "imgui/pch.h"

#include "json.hpp"

using json = nlohmann::json;

namespace fs = std::filesystem;

enum ToggleFlags_ {
	ToggleFlags_Toggle,
	ToggleFlags_Show,
	ToggleFlags_Hide
};
typedef int ToggleFlags;

struct Color {
	bool enable = false;
	ImColor color = ImGui::GetColorU32({ 255, 255, 255, 1 });
};

struct Element {
	std::string name = "Unknown";
	std::string type;
	std::string value;
	std::vector<ImVec2> positions;
	ImVec2 size;
	Color color;
	Color fill;
	Color stroke;
	float scale = 1;
};

struct Options {
	int x;
	int y;
	int width;
	int height;
	float scale;
	float opacity;
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
	std::string author = "Unknown";
	std::string version = "v1.0.0";
	std::string date = "";
	bool font = false;
	std::vector<Element> elements;
};

struct Vector2D {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};


class RocketStats : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
private:
	ImFont* font_custom;
	ImFont* font_default;
	ImFontAtlas* atlas_custom;

	std::shared_ptr<bool> enabled;
	std::string rs_path = "RocketStats";
	std::shared_ptr<ImageWrapper> rs_title;

	tm local_time;
	time_t current_time;

	char theme_refresh = 2;
	unsigned char theme_style = 0;

	json theme_config;
	Theme theme_render;
	std::vector<Theme> themes;
	std::map<std::string, std::string> theme_vars;
	std::map<std::string, std::shared_ptr<ImageWrapper>> theme_images;

	// PluginWindow
	bool isPluginOpen_ = false;
	bool isSettingsOpen_ = false;
	std::string menuName_ = "rocketstats";
	std::string menuTitle_ = "RocketStats";
	std::string menuVersion_ = "v4.0";

	void RenderIcon();
	void RenderOverlay();
	void RenderSettings();

	virtual void Render() override;
	virtual std::string GetMenuName() override;
	virtual std::string GetMenuTitle() override;
	virtual void SetImGuiContext(uintptr_t ctx) override;
	virtual bool ShouldBlockInput() override;
	virtual bool IsActiveOverlay() override;
	virtual void OnOpen() override;
	virtual void OnClose() override;

public:
	int RS_mode = 0;
	int RS_theme = 0;

	bool RS_in_file = true;
	bool RS_disp_obs = false;
	bool RS_disp_overlay = true;
	bool RS_enable_ingame = true;
	bool RS_enable_boost = true;
	bool RS_enable_float = false;
	bool RS_onchange_scale = true;
	bool RS_onchange_position = true;

	float RS_x = 0.7f;
	float RS_y = 0.575f;
	float RS_scale = 1.f;

	bool RS_x_edit = false;
	bool RS_y_edit = false;
	bool RS_scale_edit = false;

	// Utils
	Stats GetStats();
	std::string GetRank(int tierID);
	std::string GetPlaylistName(int playlistID);
	void LogImageLoadStatus(bool status, std::string imageName);
	std::shared_ptr<ImageWrapper> LoadImg(const std::string& _filename);
	std::shared_ptr<ImageWrapper> LoadImg(fs::path& _path);
	void LoadImgs();

	// PluginLoadRoutines
	virtual void onLoad();
	virtual void onUnload();

	// GameMgmt
	void ShowPlugin(std::string eventName);
	void TogglePlugin(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);
	void ToggleSettings(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);
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
	bool ChangeTheme(int idx);
	void RefreshTheme(std::string old, CVarWrapper now);
	//void Render(CanvasWrapper canvas);
	struct Element CalculateElement(json& element, Options& options, bool& check);
	void RenderElement(Element& element);

	// File I / O
	std::string GetPath(std::string _path = "", bool root = false);
	bool ExistsPath(std::string _filename, bool root = false);
	bool RemoveFile(std::string _filename, bool root = false);
	std::string ReadFile(std::string _filename, bool root = false);
	void WriteInFile(std::string _fileName, std::string _value, bool root = false);
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
