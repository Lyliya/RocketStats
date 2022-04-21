#include "../RocketStats.h"

void RocketStats::LoadThemes()
{
    cvarManager->log("===== LoadThemes =====");

    themes = {};
    std::string theme_base = GetPath("RocketStats_themes");
    if (fs::exists(theme_base))
    {
        // List the themes (taking the name of the folder)
        for (const auto& entry : fs::directory_iterator(theme_base))
        {
            std::string theme_path = entry.path().string();
            if (entry.is_directory() && fs::exists(theme_path + "/config.json"))
            {
                Theme theme;
                theme.name = theme_path.substr(theme_path.find_last_of("/\\") + 1);
                cvarManager->log("Theme: " + theme.name);

                // Puts the "Default" theme in the first position and "Redesign" in the second position
                if (theme.name == "Default" || theme.name == "Redesigned")
                {
                    size_t pos = ((theme.name == "Redesigned" && themes.at(0).name == "Default") ? 1 : 0);
                    themes.insert((themes.begin() + pos), theme);
                }
                else
                    themes.push_back(theme);
            }
        }
    }

    cvarManager->log("===== !LoadThemes =====");
}

bool RocketStats::ChangeTheme(int idx)
{
    cvarManager->log("===== ChangeTheme =====");

    // Stores current theme variables on error
    Theme old = {
        theme_render.name,
        theme_render.author,
        theme_render.version,
        theme_render.date,
        theme_render.fonts
    };

    try
    {
        // If the index of the theme does not fit in the list of themes, we do nothing
        if (themes.size() <= idx)
            return true;

        Theme& theme = themes.at(idx);

        // Read the JSON file including the settings of the chosen theme
        theme_config = ReadJSON("RocketStats_themes/" + theme.name + "/config.json");
        cvarManager->log(nlohmann::to_string(theme_config));

        if (theme_config.is_object())
        {
            theme_render.name = theme.name;

            if (theme_config.contains("author") && theme_config["author"].size())
                theme_render.author = theme_config["author"];

            if (theme_config.contains("version"))
            {
                std::string version = theme_config["version"];
                if (version.size() >= 2 && version[0] == 'v')
                    theme_render.version = version;
            }

            if (theme_config.contains("date"))
            {
                std::string date = theme_config["date"];
                if (date.size() == 10 && date[2] == '/' && date[5] == '/')
                    theme_render.date = date;
            }

            // Add default theme font to system
            bool default_font = false;
            if (theme_config.contains("font") && theme_config["font"].is_array() && theme_config["font"].size() == 2)
            {
                if (!theme_config.contains("fonts") || !theme_config["fonts"].is_array())
                    theme_config["fonts"] = json::array();

                default_font = true;
                theme_config["fonts"].insert(theme_config["fonts"].begin(), theme_config["font"]);
            }

            // Add theme fonts to system
            theme_render.fonts = {};
            if (theme_config.contains("fonts") && theme_config["fonts"].is_array())
            {
                for (int i = 0; i < theme_config["fonts"].size(); ++i)
                {
                    json font = theme_config["fonts"][i];
                    if (font.size() == 2 && font[0].is_string() && font[1].is_number_unsigned())
                    {
                        int font_size = font[1];
                        std::string font_file = font[0];

                        std::string font_prefix = "rs_";
                        std::string font_path = ("RocketStats_themes/" + theme_render.name + "/fonts/" + font_file);
                        std::string font_dest = ("../RocketStats/" + font_path);

                        if (font_file.size() && font_size > 0 && ExistsPath(font_path))
                        {
                            std::string font_name = Utils::tolower(font_prefix + (font_file.substr(0, font_file.find_last_of('.'))) + "_" + std::to_string(font_size));
                            theme_render.fonts.push_back({ font_size, font_name, (!i && default_font) });

                            GuiManagerWrapper gui = gameWrapper->GetGUIManager();
                            gui.LoadFont(font_name, font_dest, font_size);
                            cvarManager->log("Load font: " + font_name);
                        }
                    }
                }
            }

            if (themes_values[theme_render.name].is_object())
            {
                if (themes_values[theme_render.name]["x"].is_number())
                    rs_x = float(themes_values[theme_render.name]["x"]);
                if (themes_values[theme_render.name]["y"].is_number())
                    rs_y = float(themes_values[theme_render.name]["y"]);
                if (themes_values[theme_render.name]["scale"].is_number())
                    rs_scale = std::min(10.f, std::max(0.001f, float(themes_values[theme_render.name]["scale"])));
                if (themes_values[theme_render.name]["rotate"].is_number())
                    rs_rotate = std::min(180.f, std::max(-180.f, float(themes_values[theme_render.name]["rotate"])));
                if (themes_values[theme_render.name]["opacity"].is_number())
                    rs_opacity = std::min(1.f, std::max(0.f, float(themes_values[theme_render.name]["opacity"])));
            }

            cvarManager->log("Theme changed: " + theme.name + " (old: " + theme_render.name + ")");
            rs_theme = idx;
            SetRefresh(RefreshFlags_RefreshAndImages);
        }
        else
            cvarManager->log("Theme config: " + theme.name + " bad JSON");
    }
    catch (json::parse_error& e)
    {
        cvarManager->log("Theme config: " + std::to_string(idx) + " bad JSON -> " + std::string(e.what()));

        // Returns the variables as they were before the process
        theme_render.name = old.name;
        theme_render.author = old.author;
        theme_render.version = old.version;
        theme_render.date = old.date;
        theme_render.fonts = old.fonts;
    }

    cvarManager->log("===== !ChangeTheme =====");
    return (rs_theme == idx);
}

void RocketStats::SetTheme(std::string name)
{
    // Search the index of a theme with its name (changes current theme if found)
    for (int i = 0; i < themes.size(); ++i)
    {
        if (themes.at(i).name == name)
        {
            cvarManager->log("SetTheme: [" + std::to_string(i) + "] " + name);

            rs_theme = i;
            break;
        }
    }
}

void RocketStats::SetRefresh(unsigned char value)
{
    if (theme_refresh < value)
        theme_refresh = value;
}

void RocketStats::RefreshFiles(std::string old, CVarWrapper now)
{
    UpdateFiles(true);
    RefreshTheme(old, now);
}

void RocketStats::RefreshTheme(std::string old, CVarWrapper now)
{
    bool refresh = true;
    bool value = now.getBoolValue();
    std::string name = now.getCVarName();
    if (name == "rs_disp_overlay")
        rs_disp_overlay = value;
    else if (name == "rs_enable_inmenu")
        rs_enable_inmenu = value;
    else if (name == "rs_enable_ingame")
        rs_enable_ingame = value;
    else if (name == "rs_enable_inscoreboard")
        rs_enable_inscoreboard = value;
    else
        refresh = false;

    if (refresh)
    {
        cvarManager->log("SetCVar: " + std::string(name) + " " + std::to_string(value));
        RefreshVars();
    }

    SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::RefreshVars()
{
    CVarWrapper cvar_x = cvarManager->getCvar("rs_x");
    CVarWrapper cvar_y = cvarManager->getCvar("rs_y");
    CVarWrapper cvar_scale = cvarManager->getCvar("rs_scale");
    CVarWrapper cvar_rotate = cvarManager->getCvar("rs_rotate");
    CVarWrapper cvar_opacity = cvarManager->getCvar("rs_opacity");

    // Delimits certain variables
    if (rs_x < cvar_x.GetMinimum())
        rs_x = cvar_x.GetMinimum();
    else if (rs_x > cvar_x.GetMaximum())
        rs_x = cvar_x.GetMaximum();

    if (rs_y < cvar_y.GetMinimum())
        rs_y = cvar_y.GetMinimum();
    else if (rs_y > cvar_y.GetMaximum())
        rs_y = cvar_y.GetMaximum();

    if (rs_scale < cvar_scale.GetMinimum())
        rs_scale = cvar_scale.GetMinimum();
    else if (rs_scale > cvar_scale.GetMaximum())
        rs_scale = cvar_scale.GetMaximum();

    if (rs_rotate < cvar_rotate.GetMinimum())
        rs_rotate = cvar_rotate.GetMinimum();
    else if (rs_rotate > cvar_rotate.GetMaximum())
        rs_rotate = cvar_rotate.GetMaximum();

    if (rs_opacity < cvar_opacity.GetMinimum())
        rs_opacity = cvar_opacity.GetMinimum();
    else if (rs_opacity > cvar_opacity.GetMaximum())
        rs_opacity = cvar_opacity.GetMaximum();

    // Check for changes before modifying cvars
    if (SetCVar("rs_mode", rs_mode))
        UpdateFiles();
    SetCVar("rs_theme", rs_theme);

    SetCVar("rs_x", rs_x, true);
    SetCVar("rs_y", rs_y, true);

    SetCVar("rs_scale", rs_scale, true);
    SetCVar("rs_rotate", rs_rotate, true);
    SetCVar("rs_opacity", rs_opacity, true);

    SetCVar("rs_disp_overlay", rs_disp_overlay);
    if (SetCVar("rs_enable_inmenu", rs_enable_inmenu) && !rs_enable_inmenu && !rs_enable_ingame && !rs_enable_inscoreboard)
        rs_enable_ingame = true;
    if (SetCVar("rs_enable_ingame", rs_enable_ingame) && !rs_enable_ingame && !rs_enable_inmenu && !rs_enable_inscoreboard)
        rs_enable_inmenu = true;
    if (SetCVar("rs_enable_inscoreboard", rs_enable_inscoreboard) && !rs_enable_ingame && !rs_enable_inmenu && !rs_enable_inscoreboard)
        rs_enable_inmenu = true;
    SetCVar("rs_enable_float", rs_enable_float);
    SetCVar("rs_preview_rank", rs_preview_rank);
    SetCVar("rs_roman_numbers", rs_roman_numbers);

    if (SetCVar("rs_replace_mmr", rs_replace_mmr) && rs_replace_mmr && rs_replace_mmr_cc)
        rs_replace_mmr_cc = false;
    if (SetCVar("rs_replace_mmr_cc", rs_replace_mmr_cc) && rs_replace_mmr_cc && rs_replace_mmr)
        rs_replace_mmr = false;
    if (SetCVar("rs_replace_mmrc", rs_replace_mmrc) && rs_replace_mmrc && rs_replace_mmrc_cc)
        rs_replace_mmrc_cc = false;
    if (SetCVar("rs_replace_mmrc_cc", rs_replace_mmrc_cc) && rs_replace_mmrc_cc && rs_replace_mmrc)
        rs_replace_mmrc = false;
    if (SetCVar("rs_replace_mmrcc", rs_replace_mmrcc) && rs_replace_mmrcc && rs_replace_mmrcc_c)
        rs_replace_mmrcc_c = false;
    if (SetCVar("rs_replace_mmrcc_c", rs_replace_mmrcc_c) && rs_replace_mmrcc_c && rs_replace_mmrcc)
        rs_replace_mmrcc = false;

    SetCVar("rs_in_file", rs_in_file);
    SetCVar("rs_file_games", rs_file_games);
    SetCVar("rs_file_gm", rs_file_gm);
    SetCVar("rs_file_rank", rs_file_rank);
    SetCVar("rs_file_div", rs_file_div);
    SetCVar("rs_file_mmr", rs_file_mmr);
    SetCVar("rs_file_mmrc", rs_file_mmrc);
    SetCVar("rs_file_mmrcc", rs_file_mmrcc);
    SetCVar("rs_file_win", rs_file_win);
    SetCVar("rs_file_loss", rs_file_loss);
    SetCVar("rs_file_streak", rs_file_streak);
    SetCVar("rs_file_winratio", rs_file_winratio);
    SetCVar("rs_file_winpercentage", rs_file_winpercentage);
    SetCVar("rs_file_demo", rs_file_demo);
    SetCVar("rs_file_demom", rs_file_demom);
    SetCVar("rs_file_democ", rs_file_democ);
    SetCVar("rs_file_death", rs_file_death);
    SetCVar("rs_file_deathm", rs_file_deathm);
    SetCVar("rs_file_deathc", rs_file_deathc);
    SetCVar("rs_file_boost", rs_file_boost);

    SetCVar("rs_hide_games", rs_hide_games);
    SetCVar("rs_hide_gm", rs_hide_gm);
    SetCVar("rs_hide_rank", rs_hide_rank);
    SetCVar("rs_hide_div", rs_hide_div);
    SetCVar("rs_hide_mmr", rs_hide_mmr);
    SetCVar("rs_hide_mmrc", rs_hide_mmrc);
    SetCVar("rs_hide_mmrcc", rs_hide_mmrcc);
    SetCVar("rs_hide_win", rs_hide_win);
    SetCVar("rs_hide_loss", rs_hide_loss);
    SetCVar("rs_hide_streak", rs_hide_streak);
    SetCVar("rs_hide_winratio", rs_hide_winratio);
    SetCVar("rs_hide_winpercentage", rs_hide_winpercentage);
    SetCVar("rs_hide_demo", rs_hide_demo);
    SetCVar("rs_hide_demom", rs_hide_demom);
    SetCVar("rs_hide_democ", rs_hide_democ);
    SetCVar("rs_hide_death", rs_hide_death);
    SetCVar("rs_hide_deathm", rs_hide_deathm);
    SetCVar("rs_hide_deathc", rs_hide_deathc);
}

Element RocketStats::CalculateElement(json& element, Options& options, bool& check)
{
    check = false;
    Element calculated;

    if (!element.contains("visible") || element["visible"])
    {
        try
        {
            Vector2D element_2d;
            std::vector<ImVec2> positions;

            if (element.contains("name") && element["name"].size())
                calculated.name = element["name"];

            if (element.contains("x"))
                element_2d.x = int(float(element["x"].is_string() ? Utils::EvaluateExpression(element["x"], options.width, display_size) : int(element["x"])) * options.scale);

            if (element.contains("y"))
                element_2d.y = int(float(element["y"].is_string() ? Utils::EvaluateExpression(element["y"], options.height, display_size) : int(element["y"])) * options.scale);

            if (element.contains("width"))
                element_2d.width = int(float(element["width"].is_string() ? Utils::EvaluateExpression(element["width"], options.width, display_size) : int(element["width"])) * options.scale);

            if (element.contains("height"))
                element_2d.height = int(float(element["height"].is_string() ? Utils::EvaluateExpression(element["height"], options.height, display_size) : int(element["height"])) * options.scale);

            ImVec2 element_pos = { float(options.x + element_2d.x), float(options.y + element_2d.y) };
            ImVec2 element_size = { float(element_2d.width), float(element_2d.height) };
            const float element_scale = (element.contains("scale") ? float(element["scale"]) : 1.f);
            const float element_rotate = (element.contains("rotate") ? float(element["rotate"]) : 0.f);
            const float element_opacity = (options.opacity * (element.contains("opacity") ? float(element["opacity"]) : 1.f));

            calculated.scale = (element_scale * options.scale);

            calculated.color.enable = true;
            if (element.contains("color") && element["color"].is_array())
                calculated.color = { true, Utils::GetImColor(element["color"], element_opacity) };

            if (element.contains("fill") && element["fill"].is_array())
                calculated.fill = { true, Utils::GetImColor(element["fill"], element_opacity) };

            if (element.contains("stroke") && element["stroke"].is_array())
                calculated.stroke = { true, Utils::GetImColor(element["stroke"], element_opacity) };

            if (element["type"] == "text" && element["value"].size())
            {
                calculated.scale *= 2.f;
                calculated.value = element["value"];

                Utils::ReplaceVars(calculated.value, theme_vars, [this, &element, &options, &calculated, &element_opacity](const std::string& key, std::string& value) {
                    std::string tkey = key;
                    if (tkey == "MMR" && rs_replace_mmr)
                        tkey = "MMRChange";
                    else if (tkey == "MMR" && rs_replace_mmr_cc)
                        tkey = "MMRCumulChange";
                    else if (tkey == "MMRChange" && rs_replace_mmrc)
                        tkey = "MMR";
                    else if (tkey == "MMRChange" && rs_replace_mmrc_cc)
                        tkey = "MMRCumulChange";
                    else if (tkey == "MMRCumulChange" && rs_replace_mmrcc)
                        tkey = "MMR";
                    else if (tkey == "MMRCumulChange" && rs_replace_mmrcc_c)
                        tkey = "MMRChange";

                    if (element.contains("sign") && element["sign"] == tkey && value != theme_hide_value)
                    {
                        bool positive = (value.at(0) != '-' && value.at(0) != '0');
                        if (positive)
                            value = ("+" + value);
                    }

                    if (element.contains("chameleon") && element["chameleon"] == tkey)
                    {
                        bool positive = (value.at(0) != '-');
                        calculated.color.color = Utils::GetImColor({ float(positive ? 30 : 224), float(positive ? 224 : 24), float(positive ? 24 : 24) }, element_opacity);
                    }
                });

                if (!calculated.value.size())
                    return calculated;

                if (element.contains("transform") && element["transform"].is_string())
                {
                    std::string transform = element["transform"];
                    if (transform == "lower")
                        calculated.value = Utils::tolower(calculated.value);
                    else if (transform == "upper")
                        calculated.value = Utils::toupper(calculated.value);
                    else if (transform == "capitalize")
                        calculated.value = Utils::capitalize(calculated.value);
                }

                int font_pos = -1;
                if (theme_render.fonts.size())
                {
                    if (theme_render.fonts.at(0).isDefault)
                        font_pos = 0;

                    bool specific = (element.contains("font") && element["font"].is_string() && element["font"].size());
                    if (specific)
                    {
                        for (int i = 0; i < theme_render.fonts.size(); ++i)
                        {
                            if (theme_render.fonts.at(i).name.substr(3, (theme_render.fonts.at(i).name.find_last_of('_') - 3)) == Utils::tolower(element["font"]))
                            {
                                font_pos = i;
                                break;
                            }
                        }
                    }
                }

                ImVec2 string_size;
                ImGui::SetWindowFontScale(1.f);
                if (font_pos >= 0)
                {
                    calculated.font = theme_render.fonts.at(font_pos).name;
                    calculated.scale *= theme_render.fonts.at(font_pos).size;

                    GuiManagerWrapper gui = gameWrapper->GetGUIManager();
                    string_size = gui.GetFont(theme_render.fonts.at(font_pos).name)->CalcTextSizeA(calculated.scale, FLT_MAX, 0.f, calculated.value.c_str());
                }
                else
                {
                    ImGui::SetWindowFontScale(calculated.scale);
                    string_size = ImGui::CalcTextSize(calculated.value.c_str());
                }

                if (element.contains("align") && element["align"].is_string())
                {
                    if (element["align"] == "right")
                        element_pos.x -= string_size.x;
                    else if (element["align"] == "center")
                        element_pos.x -= (string_size.x / 2.f);
                }

                if (element.contains("valign") && element["valign"].is_string())
                {
                    if (element["valign"] == "bottom")
                        element_pos.y -= string_size.y;
                    else if (element["valign"] == "middle")
                        element_pos.y -= (string_size.y / 2.f);
                }
            }
            else if (element["type"] == "line")
            {
                element_pos.x = float(options.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(element["x1"], options.width, display_size) : int(element["x1"])) * options.scale);
                element_pos.y = float(options.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(element["y1"], options.height, display_size) : int(element["y1"])) * options.scale);
                const float element_width = (element.contains("scale") ? float(element["scale"]) : 1);

                element_size.x = element_width;
                calculated.scale = (element_width * options.scale);

                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(element["x2"], options.width, display_size) : int(element["x2"])) * options.scale),
                    float(options.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(element["y2"], options.height, display_size) : int(element["y2"])) * options.scale)
                    });
            }
            else if (element["type"] == "rectangle")
            {
                element_size.x = (element.contains("rounding") ? float(element["rounding"]) : 0.f);

                positions.push_back(ImVec2{
                    element_pos.x + element_2d.width,
                    element_pos.y + element_2d.height
                    });
            }
            else if (element["type"] == "triangle")
            {
                element_pos.x = float(options.x) + (float(element["x1"].is_string() ? Utils::EvaluateExpression(element["x1"], options.width, display_size) : int(element["x1"])) * options.scale);
                element_pos.y = float(options.y) + (float(element["y1"].is_string() ? Utils::EvaluateExpression(element["y1"], options.height, display_size) : int(element["y1"])) * options.scale);

                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x2"].is_string() ? Utils::EvaluateExpression(element["x2"], options.width, display_size) : int(element["x2"])) * options.scale),
                    float(options.y) + (float(element["y2"].is_string() ? Utils::EvaluateExpression(element["y2"], options.height, display_size) : int(element["y2"])) * options.scale)
                    });
                positions.push_back(ImVec2{
                    float(options.x) + (float(element["x3"].is_string() ? Utils::EvaluateExpression(element["x3"], options.width, display_size) : int(element["x3"])) * options.scale),
                    float(options.y) + (float(element["y3"].is_string() ? Utils::EvaluateExpression(element["y3"], options.height, display_size) : int(element["y3"])) * options.scale)
                    });
            }
            else if (element["type"] == "circle")
            {
                const float radius = float(element["radius"].is_string() ? Utils::EvaluateExpression(element["radius"], options.width, display_size) : int(element["radius"]));

                element_size.x = (radius * options.scale);
                element_size.y = float(element.contains("segments") ? int(element["segments"]) : 0);
            }
            else if (element["type"] == "pie_chart")
            {
                const float radius = float(element["radius"].is_string() ? Utils::EvaluateExpression(element["radius"], options.width, display_size) : int(element["radius"]));
                const float item_arc_span = (float(M_PI) * 2);
                const float angle_min = ((element.contains("angle-min") ? float(element["angle-min"]) : 0.f) - 90.f);
                const float angle_max = ((element.contains("angle-max") ? float(element["angle-max"]) : 0.f) - 90.f);
                const float radian_min = ((angle_min / 360.f) * item_arc_span);
                const float radian_max = ((angle_max / 360.f) * item_arc_span);

                element_size.x = (radius * options.scale);
                element_size.y = float(element.contains("segments") ? int(element["segments"]) : 0);

                positions.push_back(ImVec2{ radian_min, radian_max });

                if (element.contains("stroke"))
                {
                    positions.push_back(ImVec2{
                        (element_pos.x + ((element_size.x * cos(radian_min)))),
                        (element_pos.y + ((element_size.x * sin(radian_min))))
                        });
                }
            }
            else if (element["type"] == "image")
            {
                calculated.scale *= 0.5f;
                calculated.value = element["file"];

                if (!element.contains("color"))
                    calculated.color = { true, Utils::GetImColor({ 255.f, 255.f, 255.f }, element_opacity) };

                if (calculated.value == "{{Rank}}")
                {
                    theme_images[calculated.value] = rank[0].image;

                    // Returns the casual games image, otherwise returns the current ranking image
                    if (current.playlist >= 1 && current.playlist <= 4)
                        theme_images[calculated.value] = casual;
                    else if (current.ranked || rs_preview_rank)
                        theme_images[calculated.value] = rank[(!rs_hide_rank && current.tier < rank_nb) ? current.tier : 0].image;
                }
                else if (!theme_images[calculated.value])
                {
                    // Get the requested image
                    element_size = { 0, 0 };
                    std::string image_path = "RocketStats_themes/" + themes.at(rs_theme).name + "/images/" + calculated.value;

                    cvarManager->log("Load image: " + image_path);
                    theme_images[calculated.value] = LoadImg(image_path);
                }

                // Calculate the image only if it is loaded (request for recalculation later if needed)
                if (theme_images[calculated.value]->GetImGuiTex() != nullptr)
                {
                    Vector2F image_size = theme_images[calculated.value]->GetSizeF();
                    element_size = {
                        (image_size.X * calculated.scale),
                        (image_size.Y * calculated.scale)
                    };

                    if (element.contains("align") && element["align"].is_string())
                    {
                        if (element["align"] == "right")
                            element_pos.x -= element_size.x;
                        else if (element["align"] == "center")
                            element_pos.x -= (element_size.x / 2.f);
                    }

                    if (element.contains("valign") && element["valign"].is_string())
                    {
                        if (element["valign"] == "bottom")
                            element_pos.y -= element_size.y;
                        else if (element["valign"] == "middle")
                            element_pos.y -= (element_size.y / 2.f);
                    }

                    element_size.x += element_pos.x;
                    element_size.y += element_pos.y;
                }
            }

            positions.emplace(positions.begin(), element_pos);

            calculated.type = element["type"];
            calculated.positions = positions;
            calculated.size = element_size;
            if (element_rotate)
            {
                calculated.rotate_enable = true;
                calculated.rotate = ((90.f - element_rotate) * (float(M_PI) / 180.f)); // Convert degrees to radians
            }

            check = true;
        }
        catch (const std::exception& e)
        {
            cvarManager->log("CalculateElement error: " + std::string(e.what()));
        }
    }

    return calculated;
}

void RocketStats::RenderElement(ImDrawList* drawlist, Element& element)
{
    try
    {
        if (element.rotate_enable)
            ImRotateStart(drawlist); // Saves the position of the vertex array for future rotation

        if (element.fill.enable)
        {
            if (element.type == "triangle")
                drawlist->AddTriangleFilled(element.positions.at(0), element.positions.at(1), element.positions.at(2), element.fill.color);
            else if (element.type == "rectangle")
                drawlist->AddRectFilled(element.positions.at(0), element.positions.at(1), element.fill.color, element.size.x, ImDrawCornerFlags_All);
            else if (element.type == "circle")
                drawlist->AddCircleFilled(element.positions.at(0), element.size.x, element.fill.color, int(element.size.y ? element.size.y : 12));
            else if (element.type == "pie_chart")
            {
                drawlist->PathLineTo(element.positions.at(0));
                drawlist->PathArcTo(element.positions.at(0), element.size.x, element.positions.at(1).x, element.positions.at(1).y, int(element.size.y));
                drawlist->PathFillConvex(element.fill.color);
            }
        }

        if (element.stroke.enable)
        {
            if (element.type == "triangle")
                drawlist->AddTriangle(element.positions.at(0), element.positions.at(1), element.positions.at(2), element.stroke.color, element.scale);
            else if (element.type == "rectangle")
                drawlist->AddRect(element.positions.at(0), element.positions.at(1), element.stroke.color, element.size.x, ImDrawCornerFlags_All, element.scale);
            else if (element.type == "circle")
                drawlist->AddCircle(element.positions.at(0), element.size.x, element.stroke.color, int(element.size.y ? element.size.y : 12), element.scale);
            else if (element.type == "pie_chart")
            {
                drawlist->PathLineTo(element.positions.at(2));
                drawlist->PathArcTo(element.positions.at(0), element.size.x, element.positions.at(1).x, element.positions.at(1).y, int(element.size.y));
                drawlist->PathStroke(element.stroke.color, false, element.scale);
            }
        }

        if (element.type == "image")
        {
            std::shared_ptr<ImageWrapper> image = theme_images[element.value];
            if (image != nullptr && image->GetImGuiTex() != nullptr && element.size.x && element.size.y)
                drawlist->AddImage(image->GetImGuiTex(), element.positions.at(0), element.size, ImVec2{ 0, 0 }, ImVec2{ 1, 1 }, element.color.color);
            else
                SetRefresh(RefreshFlags_Refresh);
        }
        else if (element.type == "text")
        {
            ImGui::SetWindowFontScale(1);
            if (theme_render.fonts.size() && (element.font.size() || theme_render.fonts.at(0).isDefault))
            {
                GuiManagerWrapper gui = gameWrapper->GetGUIManager();
                ImFont* font = gui.GetFont(element.font.size() ? element.font : theme_render.fonts.at(0).name);

                // Display text if font is loaded
                if (font && font->IsLoaded())
                    drawlist->AddText(font, element.scale, element.positions.at(0), element.color.color, element.value.c_str());
            }
            else
            {
                // Displays text without font
                ImGui::SetWindowFontScale(element.scale);
                drawlist->AddText(element.positions.at(0), element.color.color, element.value.c_str());
            }
        }
        else if (element.type == "line")
            drawlist->AddLine(element.positions.at(0), element.positions.at(1), element.color.color, element.size.x);

        if (element.rotate_enable)
            ImRotateEnd(element.rotate); // Applies the rotation to the vertices of the current element
    }
    catch (const std::exception&) {}
}
