#pragma once
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

#include "json.hpp"
#include "imgui/pch.h"
#include "imgui/imgui_rotate.h"
#include "bakkesmod/wrappers/GuiManagerWrapper.h"

#include <map>
#include <fstream>
#include <functional>
#include <utils/parser.h>

#include "Utils.h"

#define  M_PI	3.14159265358979323846

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
	ImColor color = ImGui::GetColorU32({ 255.f, 255.f, 255.f, 1.f });
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
	float scale = 1.f;
	bool rotate_enable = false;
	float rotate = 0.f;
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
	int demo = 0;
	int death = 0;
	bool isInit = false;
};

struct Theme {
	std::string name = "Unknown";
	std::string author = "Unknown";
	std::string version = "v1.0.0";
	std::string date = "";
	int font_size = 0;
	std::string font_name = "";
	std::vector<Element> elements;
};

struct StatTickerParams {
	uintptr_t Receiver; // person who got a stat
	uintptr_t Victim; // person who is victim of a stat (only exists for demos afaik)
	uintptr_t StatEvent;
};

struct StatEventParams {
	uintptr_t PRI; // always primary player
	uintptr_t StatEvent; // wrapper for the stat event
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
	std::shared_ptr<bool> enabled;
	std::string rs_path = "RocketStats";
	std::string rs_fonts = "../../";
	std::shared_ptr<ImageWrapper> rs_title;

	bool mouse_state = false;
	bool escape_state = false;
	std::string hide_value = "##";

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

	bool RS_disp_obs = false;
	bool RS_disp_overlay = true;
	bool RS_enable_inmenu = true;
	bool RS_enable_ingame = true;
	bool RS_enable_float = false;
	bool RS_onchange_scale = true;
	bool RS_onchange_rotate = true;
	bool RS_onchange_position = true;

	bool RS_in_file = true;
	bool RS_file_gm = true;
	bool RS_file_rank = true;
	bool RS_file_div = true;
	bool RS_file_mmr = true;
	bool RS_file_mmrc = true;
	bool RS_file_mmrcc = true;
	bool RS_file_win = true;
	bool RS_file_loss = true;
	bool RS_file_streak = true;
	bool RS_file_demo = false;
	bool RS_file_death = false;
	bool RS_file_boost = true;

	bool RS_replace_mmr = false;
	bool RS_hide_gm = false;
	bool RS_hide_rank = false;
	bool RS_hide_div = false;
	bool RS_hide_mmr = false;
	bool RS_hide_mmrc = false;
	bool RS_hide_mmrcc = false;
	bool RS_hide_win = false;
	bool RS_hide_loss = false;
	bool RS_hide_streak = false;
	bool RS_hide_demo = false;
	bool RS_hide_death = false;

	float RS_x = 0.7f;
	float RS_y = 0.575f;
	float RS_scale = 1.f;
	bool RS_rotate_enabled = false;
	float RS_rotate = 0.f;
	float RS_crotate = 0.f;
	float RS_opacity = 1.f;

	bool RS_x_edit = false;
	bool RS_y_edit = false;
	bool RS_scale_edit = false;
	bool RS_rotate_edit = false;
	bool RS_opacity_edit = false;

	// Utils
	Stats GetStats();
	std::string GetRank(int tierID);
	std::string GetPlaylistName(int playlistID);
	void LogImageLoadStatus(bool status, std::string imageName);
	std::shared_ptr<ImageWrapper> LoadImg(const std::string& _filename);
	std::shared_ptr<ImageWrapper> LoadImg(fs::path& _path);
	void LoadImgs();
	void RecoveryOldVars();

	// PluginLoadRoutines
	virtual void onLoad();
	virtual void onUnload();
	void ShowPlugin(std::string eventName);
	void TogglePlugin(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);
	void ToggleSettings(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);

	// GameMgmt
	void GameStart(std::string eventName);
	void GameEnd(std::string eventName);
	void GameDestroyed(std::string eventName);

	// StatsMgmt
	bool isPrimaryPlayer(PriWrapper pri);
	void onStatEvent(ServerWrapper caller, void* args);
	void onStatTickerMessage(ServerWrapper caller, void* args);
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
	void SetTheme(std::string name);
	void RefreshTheme(std::string old, CVarWrapper now);
	//void Render(CanvasWrapper canvas);
	struct Element CalculateElement(json& element, Options& options, bool& check);
	void RenderElement(ImDrawList* drawlist, Element& element);

	// File I / O
	std::string GetPath(std::string _path = "", bool root = false);
	bool ExistsPath(std::string _filename, bool root = false);
	bool RemoveFile(std::string _filename, bool root = false);
	std::string ReadFile(std::string _filename, bool root = false);
	void WriteInFile(std::string _fileName, std::string _value, bool root = false);
	void ResetFiles();
	bool ReadConfig();
	void WriteConfig();
	void WriteGameMode();
	void WriteRank();
	void WriteDiv();
	void WriteMMR();
	void WriteMMRChange();
	void WriteMMRCumulChange();
	void WriteWin();
	void WriteLoss();
	void WriteStreak();
	void WriteBoost();
	void WriteDemo();
	void WriteDeath();

	int currentPlaylist = 0;
	bool isInGame = false;
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
