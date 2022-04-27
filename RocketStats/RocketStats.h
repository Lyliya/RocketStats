#pragma once
#pragma warning(disable: 4099)
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

#include <pch.h>
#include <json.hpp>
#include <fpstimer.hpp>
#include <resource.hpp>
#include <imgui/imgui_rotate.h>
#include "bakkesmod/wrappers/GuiManagerWrapper.h"

#include <map>
#include <vector>
#include <fstream>
#include <windows.h>
#include <functional>
#include <utils/parser.h>

#include "Utils.h"
#include "Languages.h"
#include "Resources/Resource.h"

#define  M_PI	3.14159265358979323846

using json = nlohmann::json;

namespace fs = std::filesystem;

enum ToggleFlags {
	ToggleFlags_Toggle,
	ToggleFlags_Show,
	ToggleFlags_Hide
};

enum RefreshFlags {
	RefreshFlags_Off,
	RefreshFlags_Refresh,
	RefreshFlags_RefreshAndImages
};

enum RecoveryFlags {
	RecoveryFlags_Off,
	RecoveryFlags_Files,
	RecoveryFlags_Welcome,
	RecoveryFlags_Process,
	RecoveryFlags_Finish
};

struct Color {
	bool enable = false;
	ImColor color = ImGui::GetColorU32({ 255.f, 255.f, 255.f, 1.f });
};

struct Element {
	std::string name = "Unknown";
	std::string type;
	std::string font;
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
	int games = 0;
	float myMMR = 100.f;
	float MMRChange = 0.f;
	float MMRCumulChange = 0.f;
	int win = 0;
	int loss = 0;
	int streak = 0;
	int demo = 0;
	int demoCumul = 0;
	int death = 0;
	int deathCumul = 0;
	bool isInit = false;
};

struct ThemeFont {
	int size = 0;
	std::string name = "";
	bool isDefault = false;
};

struct Theme {
	std::string name = "Unknown";
	std::string author = "Unknown";
	std::string version = "v1.0.0";
	std::string date = "";
	std::vector<ThemeFont> fonts = {};
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
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;
};


class RocketStats : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
private:
	int rs_recovery = RecoveryFlags_Off;
	float rs_launch = 0.f;
	float rs_llaunch = 0.f;
	bool rs_logo_mouv = false;
	float rs_buttons_x = 0.f;
	float rs_logo_rotate = 0.f;
	float rs_screen_scale[2] = { 1.f, 1.f };
	std::vector<std::string> rs_lang;
	std::shared_ptr<ImageWrapper> rs_logo;
	std::shared_ptr<ImageWrapper> rs_title;
	std::shared_ptr<ImageWrapper> rs_welcome;
	ImDrawList* rs_drawlist = IM_NEW(ImDrawList(NULL));

	// Time
	tm local_time;
	time_t current_time;
	FPSTimer timer_30fps = FPSTimer(30, true);

	// Themes
	ImVec2 theme_size = { 0.f, 0.f };
	ImVec2 display_size = { 0.f, 0.f };
	unsigned char theme_style = 0;
	unsigned char theme_refresh = 2;

	json theme_config = json::object();
	json themes_values = json::object();
	Theme theme_render;
	std::string theme_prev = "";
	std::string theme_hide_value = "##";
	std::vector<Theme> themes;
	std::vector<std::string> modes;
	std::map<std::string, std::string> theme_vars;
	std::map<std::string, std::shared_ptr<ImageWrapper>> theme_images;

	// Overlay
	bool overlay_move = false;
	ImVec2 overlay_cursor;
	ImVec2 overlay_origin;

	//std::unique_ptr<MMRNotifierToken> notifierToken;

	// Game states
	int menu_stack = 0;
	bool is_in_game = false;
	bool is_in_menu = false;
	bool is_in_freeplay = false;
	bool is_in_scoreboard = false;
	bool is_online_game = false;
	bool is_offline_game = false;
	bool is_boosting = false;
	bool is_game_ended = false;
	bool is_game_started = false;

	// All stats
	Stats always;
	Stats session;
	std::map<int, Stats> stats;
	std::map<int, Stats> always_gm;

	// Current stats
	int my_team_num = -1;

	typedef struct s_current {
		int demo = 0;
		int tier = 0;
		int death = 0;
		int playlist = 0;
		bool ranked = false;
		std::string rank = "norank";
		std::string division = "nodiv";
		std::string preview_rank = "norank";
		std::string preview_division = "nodiv";
		int rank_number = 0;
		int division_number = 0;
		int preview_rank_number = 0;
		int preview_division_number = 0;
	} t_current;

	t_current current;
	std::string last_rank = "norank";
	std::string last_division = "nodiv";

	// Rank & Division
	int rank_nb = 23;
	std::shared_ptr<ImageWrapper> casual;
	std::vector<std::string> roman_numbers = { "", "I", "II", "III", "IV", "V" };

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

	const std::map<int, std::string> playlist_name = {
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

	// PluginWindow
	int windows_count = -1;
	bool mouse_state = false;
	bool escape_state = false;
	bool plugin_open = false;
	bool settings_open = false;
	std::string menu_name = "rocketstats";
	std::string menu_title = "RocketStats";
	std::string menu_version = "";

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
	int rs_mode = 0;
	int rs_theme = 0;

	bool rs_disp_obs = false;
	bool rs_disp_overlay = true;
	bool rs_enable_inmenu = true;
	bool rs_enable_ingame = true;
	bool rs_enable_inscoreboard = true;
	bool rs_enable_float = false;
	bool rs_preview_rank = false;
	bool rs_roman_numbers = true;

	bool rs_replace_mmr = false;
	bool rs_replace_mmr_cc = false;
	bool rs_replace_mmrc = false;
	bool rs_replace_mmrc_cc = false;
	bool rs_replace_mmrcc = false;
	bool rs_replace_mmrcc_c = false;

	bool rs_in_file = true;
	bool rs_select_all_file = true;
	bool rs_file_games = true;
	bool rs_file_gm = true;
	bool rs_file_rank = true;
	bool rs_file_div = true;
	bool rs_file_mmr = true;
	bool rs_file_mmrc = true;
	bool rs_file_mmrcc = true;
	bool rs_file_win = true;
	bool rs_file_loss = true;
	bool rs_file_streak = true;
	bool rs_file_winratio = true;
	bool rs_file_winpercentage = true;
	bool rs_file_demo = true;
	bool rs_file_demom = true;
	bool rs_file_democ = true;
	bool rs_file_death = true;
	bool rs_file_deathm = true;
	bool rs_file_deathc = true;
	bool rs_file_boost = true;

	bool rs_select_all_hide = true;
	bool rs_hide_games = false;
	bool rs_hide_gm = false;
	bool rs_hide_rank = false;
	bool rs_hide_div = false;
	bool rs_hide_mmr = false;
	bool rs_hide_mmrc = false;
	bool rs_hide_mmrcc = false;
	bool rs_hide_win = false;
	bool rs_hide_loss = false;
	bool rs_hide_streak = false;
	bool rs_hide_winratio = false;
	bool rs_hide_winpercentage = false;
	bool rs_hide_demo = false;
	bool rs_hide_demom = false;
	bool rs_hide_democ = false;
	bool rs_hide_death = false;
	bool rs_hide_deathm = false;
	bool rs_hide_deathc = false;

	float rs_x = 0.7f;
	float rs_y = 0.575f;
	float rs_scale = 1.f;
	bool rs_rotate_enabled = false;
	float rs_rotate = 0.f;
	float rs_crotate = 0.f;
	float rs_opacity = 1.f;

	bool rs_x_edit = false;
	bool rs_y_edit = false;
	bool rs_scale_edit = false;
	bool rs_rotate_edit = false;
	bool rs_opacity_edit = false;

	// Utils
	Stats GetStats();
	std::string GetRank(int tierID);
	std::string GetRankName(int tierID, int& number);
	std::string GetPlaylistName(int playlistID);
	std::string GetRoman(int number);
	std::string AddRoman(std::string str, int number);
	void LogImageLoadStatus(bool status, std::string imageName);
	std::shared_ptr<ImageWrapper> LoadImg(const std::string& _filename);
	std::shared_ptr<ImageWrapper> LoadImg(fs::path& _path);
	void LoadImgs();
	bool GetCVar(const char* name, int& value);
	bool GetCVar(const char* name, bool& value);
	bool GetCVar(const char* name, float& value);
	bool SetCVar(const char* name, int& value, bool save = false);
	bool SetCVar(const char* name, bool& value, bool save = false);
	bool SetCVar(const char* name, float& value, bool save = false);
	void CloseWelcome();
	bool RecoveryOldVars();

	// PluginLoadRoutines
	virtual void onLoad();
	virtual void onUnload();
	void onInit();
	void SetCustomProtocol();
	void ShowPlugin(std::string eventName);
	void UpdateUIScale(std::string eventName);
	void TogglePlugin(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);
	void ToggleSettings(std::string eventName, ToggleFlags mode = ToggleFlags_Toggle);

	// GameManagement
	void GameStart(std::string eventName);
	void GameEnd(std::string eventName);
	void GameDestroyed(std::string eventName);
	int GetGameTime();
	TeamWrapper GetTeam(bool opposing);
	ImColor GetTeamColor(TeamWrapper team);

	// StatsManagement
	bool isPrimaryPlayer(PriWrapper pri);
	void onStatEvent(ServerWrapper caller, void* args);
	void onStatTickerMessage(ServerWrapper caller, void* args);
	void InitRank();
	void MajRank(bool isRanked, float _currentMMR, SkillRank playerRank);
	void UpdateMMR(UniqueIDWrapper id);
	void InitStats();
	void SessionStats();
	void ResetStats();
	void ResetBasicStats();

	// BoostManagement
	void OnBoostStart(std::string eventName);
	void OnBoostEnd(std::string eventName);
	int GetBoostAmount();
	//void StopBoost();

	// OverlayManagement
	void LoadThemes();
	bool ChangeTheme(int idx);
	void SetTheme(std::string name);
	void SetRefresh(unsigned char value);
	void RefreshFiles(std::string old, CVarWrapper now);
	void RefreshTheme(std::string old, CVarWrapper now);
	void RefreshVars();
	Element CalculateElement(json& element, Options& options, bool& check);
	void RenderElement(ImDrawList* drawlist, Element& element);

	// LangManagement
	void ChangeLang(int id = IDB_LANG_INT);
	std::string GetLang(LangStringId id);

	// FileManagement
	std::string GetPath(std::string _path = "", bool root = false);
	bool ExistsPath(std::string _filename, bool root = false);
	bool RemoveFile(std::string _filename, bool root = false);
	std::string ReadFile(std::string _filename, bool root = false);
	json ReadJSON(std::string _filename, bool root = false);
	void WriteInFile(std::string _fileName, std::string _value, bool root = false);
	bool WriteResInFile(std::string _filename, int id, const char* type, bool root = false);
	void MigrateFolder();
	void MigrateRemove();
	void UpdateFiles(bool force = false);
	void ResetFiles();
	bool ReadConfig();
	void WriteConfig();

	// VarManagement
	std::string VarGames(bool write = false, bool force = false, bool default_value = false);
	std::string VarGameMode(bool write = false, bool force = false, bool default_value = false);
	std::string VarRank(bool write = false, bool force = false, bool default_value = false, int* number = nullptr);
	std::string SubVarRankName(std::string value, int number, bool default_value = false);
	std::string SubVarRankNumber(std::string value, int number, bool default_value = false);
	std::string VarDiv(bool write = false, bool force = false, bool default_value = false, int* number = nullptr);
	std::string SubVarDivName(std::string value, int number, bool default_value = false);
	std::string SubVarDivNumber(std::string value, int number, bool default_value = false);
	std::string VarMMR(bool write = false, bool force = false, bool default_value = false);
	std::string VarMMRChange(bool write = false, bool force = false, bool default_value = false);
	std::string VarMMRCumulChange(bool write = false, bool force = false, bool default_value = false);
	std::string VarWin(bool write = false, bool force = false, bool default_value = false);
	std::string VarLoss(bool write = false, bool force = false, bool default_value = false);
	std::string VarStreak(bool write = false, bool force = false, bool default_value = false);
	std::string VarWinRatio(bool write = false, bool force = false, bool default_value = false);
	std::string VarWinPercentage(bool write = false, bool force = false, bool default_value = false);
	std::string VarDemolitions(bool write = false, bool force = false, bool default_value = false);
	std::string VarDemolitionsMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDemolitionsCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarDeath(bool write = false, bool force = false, bool default_value = false);
	std::string VarDeathMatch(bool write = false, bool force = false, bool default_value = false);
	std::string VarDeathCumul(bool write = false, bool force = false, bool default_value = false);
	std::string VarBoost(bool write = false, bool force = false, bool default_value = false, bool enabled = false);
};
