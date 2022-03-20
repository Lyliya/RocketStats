#include "../RocketStats.h"

void RocketStats::Render()
{
    is_online_game = gameWrapper->IsInOnlineGame();
    is_offline_game = gameWrapper->IsInGame();
    is_in_replay = gameWrapper->IsInReplay();
    is_in_game = (is_online_game || is_offline_game);
    is_in_pause = (is_in_game && gameWrapper->IsCursorVisible());

    RenderOverlay();
    RenderIcon();

    if (!overlay_move && settings_open)
        RenderSettings();

    // Capture of the escape key, to prevent the plugin from disappearing
    int idx = ImGui::GetKeyIndex(ImGuiKey_Escape);
    if (ImGui::IsKeyDown(idx))
        escape_state = true;
    else if (ImGui::IsKeyReleased(idx))
        escape_state = false;
}

void RocketStats::RenderIcon()
{
    // Displays the button allowing the display and the hiding of the menu
    if (!overlay_move && (!is_in_game || is_in_pause))
    {
        float margin = 20.f;
        float icon_size = (42.f * rs_screen_scale[0]);
        float icon_scale = (1.f - rs_screen_scale[0]);
        ImVec2 mouse_pos = ImGui::GetIO().MousePos;
        ImVec2 screen_size = ImGui::GetIO().DisplaySize;
        ImVec2 icon_pos = { 0.f, (screen_size.y * 0.459f * (icon_scale + (icon_scale * (0.18f - (1.f - rs_screen_scale[1]))) + 1.f)) };
        bool mouse_click = GetAsyncKeyState(VK_LBUTTON);
        ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

        bool hover = (mouse_pos.x > (icon_pos.x - icon_size - margin) && mouse_pos.x < (icon_pos.x + icon_size + margin));
        hover = (hover && (mouse_pos.y > (icon_pos.y - icon_size - margin) && mouse_pos.y < (icon_pos.y + icon_size + margin)));

        rs_logo_rotate += (rs_logo_mouv ? 0.15f : -0.15f);
        if (rs_logo_rotate < 0 || rs_logo_rotate >= 30.f)
            rs_logo_mouv = !rs_logo_mouv;

        if (rs_logo != nullptr && rs_logo->IsLoadedForImGui())
        {
            Vector2F image_size = rs_logo->GetSizeF();
            float rotate = ((90.f - rs_logo_rotate) * (float(M_PI) / 180.f));
            ImRotateStart(drawlist);
            drawlist->AddImage(rs_logo->GetImGuiTex(), { icon_pos.x - icon_size, icon_pos.y - icon_size }, { icon_pos.x + icon_size, icon_pos.y + icon_size }, { 0, 0 }, { 1, 1 }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, rs_launch }));
            ImRotateEnd(rotate);
        }
        else
        {
            drawlist->AddCircle({ icon_pos.x, icon_pos.y }, icon_size, ImColor{ 0.45f, 0.72f, 1.f, (hover ? 0.8f : 0.4f) }, 25, 4.f);
            drawlist->AddCircleFilled({ icon_pos.x, icon_pos.y }, icon_size, ImColor{ 0.04f, 0.52f, 0.89f, (hover ? 0.6f : 0.3f) }, 25);
        }


        // When hovering over the button area
        if (hover)
        {
            ImGui::SetTooltip("Show RocketStats menu");

            // When clicking in the button area
            if (mouse_click)
            {
                // Send the event only once to the click (not to each image)
                if (!mouse_state)
                {
                    mouse_state = true;
                    ToggleSettings("MouseEvent");
                }
            }
            else
                mouse_state = false;
        }
    }
}

void RocketStats::RenderOverlay()
{
    bool show_overlay = ((rs_enable_ingame && is_in_game) || (rs_enable_inmenu && !is_in_game));
    if (!rs_disp_overlay || !show_overlay)
        return;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin(menu_title.c_str(), (bool*)1, (ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoFocusOnAppearing));

    try
    {
        // Calculation each element of the theme (only during a modification)
        if (overlay_move || theme_refresh || theme_render.name == "" || (themes.size() > rs_theme && theme_render.name != themes.at(rs_theme).name))
        {
            Stats tstats = GetStats();
            ImVec2 screen_size = ImGui::GetIO().DisplaySize;

            // Refresh all images
            if (theme_refresh == 2)
            {
                theme_images.clear();
                cvarManager->log("refresh all images");
            }

            // Reset the menu variables if you change the theme
            if (theme_prev != theme_render.name)
            {
                if (!GetCVar("rs_x", rs_x))
                {
                    rs_x = 0.f;
                    if (theme_config["x"].is_number())
                        rs_x = float(theme_config["x"]);
                }

                if (!GetCVar("rs_y", rs_y))
                {
                    rs_y = 0.f;
                    if (theme_config["y"].is_number())
                        rs_y = float(theme_config["y"]);
                }

                if (!GetCVar("rs_scale", rs_scale))
                {
                    rs_scale = 1.f;
                    if (theme_config["scale"].is_number())
                        rs_scale = float(theme_config["scale"]);
                }

                if (!GetCVar("rs_rotate", rs_rotate))
                {
                    rs_rotate = 0.f;
                    if (theme_config["rotate"].is_number())
                        rs_rotate = float(theme_config["rotate"]);
                }

                if (!GetCVar("rs_opacity", rs_opacity))
                {
                    rs_opacity = 1.f;
                    if (theme_config["opacity"].is_number())
                        rs_opacity = float(theme_config["opacity"]);
                }
            }
            theme_prev = theme_render.name;

            // Checks if there is a rotation to apply and converts degrees to radians
            rs_rotate_enabled = (theme_config["rotate"].is_number() && (rs_rotate + float(theme_config["rotate"])));
            if (rs_rotate)
            {
                rs_rotate_enabled = true;
                rs_crotate = ((90.f - rs_rotate) * (float(M_PI) / 180.f));
            }
            else if (rs_rotate_enabled)
                rs_crotate = ((90.f - rs_rotate + float(theme_config["rotate"])) * (float(M_PI) / 180.f));

            // Different global options used when calculating elements
            std::vector<Element> elements;
            Options options = {
                int(rs_x * screen_size.x),
                int(rs_y * screen_size.y),
                (theme_config.contains("width") ? int(theme_config["width"]) : 0),
                (theme_config.contains("height") ? int(theme_config["height"]) : 0),
                (rs_scale * (theme_config.contains("scale") ? float(theme_config["scale"]) : 1.f)),
                (rs_launch * rs_opacity * (theme_config.contains("opacity") ? float(theme_config["opacity"]) : 1.f))
            };

            // Change the position of the overlay when moving with the mouse
            if (overlay_move)
            {
                options.x = int(overlay_cursor.x);
                options.y = int(overlay_cursor.y);
            }

            // Creation of the different variables used in Text elements
            const size_t floating_length = (rs_enable_float ? 2 : 0);

            theme_vars["GameMode"] = (rs_hide_gm ? theme_hide_value : GetPlaylistName(current.playlist));
            theme_vars["Rank"] = (rs_hide_rank ? theme_hide_value : current.rank);
            theme_vars["Div"] = (rs_hide_div ? theme_hide_value : current.division);
            theme_vars["MMR"] = (rs_hide_mmr ? theme_hide_value : Utils::FloatFixer(tstats.myMMR, floating_length)); // Utils::PointFixer(current.myMMR, 6, floating_length)
            theme_vars["MMRChange"] = (rs_hide_mmrc ? theme_hide_value : Utils::FloatFixer(tstats.MMRChange, floating_length)); // Utils::PointFixer(current.MMRChange, 6, floating_length)
            theme_vars["MMRCumulChange"] = (rs_hide_mmrcc ? theme_hide_value : Utils::FloatFixer(tstats.MMRCumulChange, floating_length)); // Utils::PointFixer(current.MMRCumulChange, 6, floating_length)
            theme_vars["Win"] = (rs_hide_win ? theme_hide_value : std::to_string(tstats.win));
            theme_vars["Loss"] = (rs_hide_loss ? theme_hide_value : std::to_string(tstats.loss));
            theme_vars["Streak"] = (rs_hide_streak ? theme_hide_value : std::to_string(tstats.streak));
            theme_vars["Demolition"] = (rs_hide_demo ? theme_hide_value : std::to_string(tstats.demo));
            theme_vars["Death"] = (rs_hide_death ? theme_hide_value : std::to_string(tstats.death));

            Utils::ReplaceAll(theme_vars["Rank"], "_", " ");

            // Replace MMR with MMRChange
            std::string mmr = theme_vars["MMR"];
            if (rs_replace_mmr)
                theme_vars["MMR"] = theme_vars["MMRChange"];
            if (rs_replace_mmrc)
                theme_vars["MMRChange"] = mmr;

            // Calculation of each element composing the theme
            rs_drawlist->Clear(); // Clear the array of vertices for the next step
            for (auto& element : theme_config["elements"])
            {
                bool check = false;
                Element calculated = CalculateElement(element, options, check);
                if (check)
                    elements.push_back(calculated);
            }

            theme_refresh = 0;
            theme_render.elements = elements;
        }

        if (theme_render.elements.size())
        {
            ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

            if (!theme_refresh && rs_drawlist->VtxBuffer.Size)
            {
                // Fill the DrawList with previously generated vertices
                drawlist->CmdBuffer = rs_drawlist->CmdBuffer;
                drawlist->IdxBuffer = rs_drawlist->IdxBuffer;
                drawlist->VtxBuffer = rs_drawlist->VtxBuffer;

                drawlist->Flags = rs_drawlist->Flags;
                drawlist->_VtxCurrentIdx = drawlist->VtxBuffer.Size;
                drawlist->_VtxWritePtr = drawlist->VtxBuffer.end();
                drawlist->_IdxWritePtr = drawlist->IdxBuffer.end();
            }
            else
            {
                // Generates the vertices of each element
                int start = drawlist->VtxBuffer.Size;
                if (rs_rotate_enabled)
                    start = ImRotateStart(drawlist);

                for (auto& element : theme_render.elements)
                    RenderElement(drawlist, element);

                if (rs_rotate_enabled)
                    ImRotateEnd(rs_crotate, start, drawlist, ImRotationCenter(start, drawlist));

                // Stores generated vertices for future frames
                rs_drawlist->Clear();
                rs_drawlist = drawlist->CloneOutput();
            }

            // Displays a square and allows the movement of the overlay with the mouse
            if (settings_open)
            {
                float margin = 10.f;
                float rect_size = 10.f;
                bool mouse_click = GetAsyncKeyState(VK_LBUTTON);
                ImVec2 mouse_pos = ImGui::GetIO().MousePos;
                ImVec2 screen_size = ImGui::GetIO().DisplaySize;
                ImVec2 overlay_pos = { (rs_x * screen_size.x), (rs_y * screen_size.y) };
                ImVec2 rect_pos = { overlay_pos.x, overlay_pos.y };

                bool hover = (mouse_pos.x > (overlay_pos.x - rect_size - (margin * 2)) && mouse_pos.x < (overlay_pos.x + rect_size + (margin * 2)));
                hover = (hover && (mouse_pos.y > (overlay_pos.y - rect_size - (margin * 2)) && mouse_pos.y < (overlay_pos.y + rect_size + (margin * 2))));

                // If we hover over the area of the square or if we are moving it
                if (hover || overlay_move)
                {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

                    // Moves the overlay when you hold down the mouse click
                    if (mouse_click)
                    {
                        if (!overlay_move)
                        {
                            overlay_move = true;
                            overlay_origin = { float(mouse_pos.x), float(mouse_pos.y) };
                        }

                        overlay_cursor = { float(mouse_pos.x), float(mouse_pos.y) };
                        rect_pos = overlay_cursor;
                    }
                    else
                    {
                        // Change positions when mouse click is released
                        if (overlay_move)
                        {
                            rs_x = (overlay_cursor.x / screen_size.x);
                            rs_y = (overlay_cursor.y / screen_size.y);

                            overlay_move = false;
                            SetRefresh(1);
                        }
                        else
                            ImGui::SetTooltip("Click to move the overlay using the mouse");
                    }
                }

                drawlist->AddRectFilled({ (rect_pos.x - rect_size), (rect_pos.y - rect_size) }, { (rect_pos.x + rect_size), (rect_pos.y + rect_size) }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 0.5f }), 4.f, ImDrawCornerFlags_All);
                drawlist->AddRect({ (rect_pos.x - rect_size), (rect_pos.y - rect_size) }, { (rect_pos.x + rect_size), (rect_pos.y + rect_size) }, ImGui::ColorConvertFloat4ToU32({ 0.f, 0.f, 0.f, 0.5f }), 4.f, ImDrawCornerFlags_All, 2.f);
            }
            else
                overlay_move = false;
        }

        // Allows spawn transition
        if (rs_launch < 1.f)
        {
            rs_launch += 0.05f;
            SetRefresh(1);
        }
    }
    catch (const std::exception& err)
    {
        theme_refresh = 0;
        rs_drawlist->Clear();
        cvarManager->log("Error: " + std::string(err.what()));
    }

    ImGui::End();
}

void RocketStats::RenderSettings()
{
    ImVec2 settings_size = { 750, 0 };

    CVarWrapper cvar_x = cvarManager->getCvar("rs_x");
    CVarWrapper cvar_y = cvarManager->getCvar("rs_y");
    CVarWrapper cvar_scale = cvarManager->getCvar("rs_scale");
    CVarWrapper cvar_rotate = cvarManager->getCvar("rs_rotate");
    CVarWrapper cvar_opacity = cvarManager->getCvar("rs_opacity");

    ImGui::SetNextWindowPos(ImVec2{ 128, 256 }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(settings_size);

    ImGui::Begin((menu_title + "##Settings").c_str(), nullptr, (ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse));

    // Show menu only if menu image is loaded
    if (rs_logo != nullptr && rs_title != nullptr && rs_logo->IsLoadedForImGui() && rs_title->IsLoadedForImGui())
    {
        float column_nb = 3;
        float column_space = 10.f;
        float column_start = 25.f;
        float column_width = ((settings_size.x - (column_start * 2) - (column_space * (column_nb - 1))) / column_nb);

        ImVec2 text_size;
        ImVec2 image_pos;
        ImVec2 win_pos = ImGui::GetWindowPos();
        ImVec2 win_size = ImGui::GetWindowSize();
        Vector2F image_size = rs_title->GetSizeF();
        ImDrawList* drawlist = ImGui::GetWindowDrawList();
        std::string obs = "To view the in-game overlay on OBS, check \"Capture third-party overlays\" in the game capture.";
        std::string developers = "Developped by @Lyliya, @NuSa_yt, @Arubinu42 & @Larsluph";

        ImVec2 p0 = win_pos;
        ImVec2 p1 = { (win_pos.x + win_size.x), (win_pos.y + win_size.y) };

        p0.x += 1;
        p1.x -= 1;
        drawlist->PushClipRect(p0, p1); // Allows you to delimit the area of the window (without internal borders)

        std::time(&current_time);
        const auto time_error = localtime_s(&local_time, &current_time);

        ImGui::SetCursorPos({ 0, 27 });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2) + image_pos.x, (image_size.Y / 2) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 23, 52 });
        ImGui::Checkbox("##in_file", &rs_in_file);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Updates RocketStats files with game information (usable in OBS)");

        ImGui::SetCursorPos({ 63, 54 });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(cvarManager->getCvar("rs_in_file").getDescription()).c_str());

        ImGui::SetWindowFontScale(1.3f);
        ImGui::SetCursorPos({ 355, 43 });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, cvarManager->getCvar("rs_mode").getDescription().c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ 295, 68 });
        ImGui::SetNextItemWidth(142);
        if (ImGui::BeginCombo("##modes_combo", modes.at(rs_mode).c_str(), ImGuiComboFlags_NoArrowButton))
        {
            int Trs_mode = rs_mode;
            for (int i = 0; i < modes.size(); ++i)
            {
                bool is_selected = (Trs_mode == i);
                if (ImGui::Selectable(modes.at(i).c_str(), is_selected))
                    rs_mode = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Restrict information to current game or keep longer");
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##modes_left", ImGuiDir_Left) && rs_mode > 0)
            --rs_mode;
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##modes_right", ImGuiDir_Right) && rs_mode < (modes.size() - 1))
            ++rs_mode;

        ImGui::SetWindowFontScale(1.3f);
        ImGui::SetCursorPos({ 585, 43 });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, cvarManager->getCvar("rs_theme").getDescription().c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ 525, 68 });
        ImGui::SetNextItemWidth(142);
        if (ImGui::BeginCombo("##themes_combo", theme_render.name.c_str(), ImGuiComboFlags_NoArrowButton))
        {
            int Trs_theme = rs_theme;
            for (int i = 0; i < themes.size(); ++i)
            {
                bool is_selected = (Trs_theme == i);
                if (ImGui::Selectable(themes.at(i).name.c_str(), is_selected))
                    rs_theme = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Themes available in RocketStats folders (fully customizable)");
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##themes_left", ImGuiDir_Left) && rs_theme > 0)
            --rs_theme;
        ImGui::SameLine(0, 0);
        if (ImGui::ArrowButton("##themes_right", ImGuiDir_Right) && themes.size() && rs_theme < (themes.size() - 1))
            ++rs_theme;

        ImGui::SetCursorPos({ 103, 120 });
        if (ImGui::Button(cvar_x.getDescription().c_str(), { 65, 0 }))
            rs_x_edit = !rs_x_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the horizontal position of the overlay");
        ImGui::SetCursorPos({ 158, 120 });
        ImGui::SetNextItemWidth(rs_x_edit ? 170.f : 150.f);
        if (!rs_x_edit)
        {
            ImGui::SliderFloat("##x_position", &rs_x, 0.f, 1.f, "%.3f");
            ImGui::SetCursorPos({ 312, 120 });
            if (ImGui::Button("R##Rx_position"))
            {
                rs_x = 0.f;
                if (theme_config["x"].is_number())
                    rs_x = float(theme_config["x"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##x_position", &rs_x, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 421, 120 });
        if (ImGui::Button(cvar_y.getDescription().c_str(), { 65, 0 }))
            rs_y_edit = !rs_y_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Changes the vertical position of the overlay");
        ImGui::SetCursorPos({ 476, 120 });
        ImGui::SetNextItemWidth(rs_y_edit ? 170.f : 150.f);
        if (!rs_y_edit)
        {
            ImGui::SliderFloat("##y_position", &rs_y, 0.f, 1.f, "%.3f");
            ImGui::SetCursorPos({ 630, 120 });
            if (ImGui::Button("R##Ry_position"))
            {
                rs_y = 0.f;
                if (theme_config["y"].is_number())
                    rs_y = float(theme_config["y"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##y_position", &rs_y, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 24, 165 });
        if (ImGui::Button(cvar_scale.getDescription().c_str(), { 65, 0 }))
            rs_scale_edit = !rs_scale_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the size of the overlay");
        ImGui::SetCursorPos({ 79, 165 });
        ImGui::SetNextItemWidth(rs_scale_edit ? 170.f : 150.f);
        if (!rs_scale_edit)
        {
            ImGui::SliderFloat("##scale", &rs_scale, cvar_scale.GetMinimum(), cvar_scale.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 233, 165 });
            if (ImGui::Button("R##Rscale"))
            {
                rs_scale = 1.f;
                if (theme_config["scale"].is_number())
                    rs_scale = float(theme_config["scale"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##scale", &rs_scale, 0.01f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 263, 165 });
        if (ImGui::Button(cvar_rotate.getDescription().c_str(), { 65, 0 }))
            rs_rotate_edit = !rs_rotate_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the rotation of the overlay");
        ImGui::SetCursorPos({ 318, 165 });
        ImGui::SetNextItemWidth(rs_rotate_edit ? 170.f : 150.f);
        if (!rs_rotate_edit)
        {
            ImGui::SliderFloat("##rotate", &rs_rotate, cvar_rotate.GetMinimum(), cvar_rotate.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 472, 165 });
            if (ImGui::Button("R##Rrotate"))
            {
                rs_rotate = 0.f;
                if (theme_config["rotate"].is_number())
                    rs_rotate = float(theme_config["rotate"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##rotate", &rs_rotate, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 502, 165 });
        if (ImGui::Button(cvar_opacity.getDescription().c_str(), { 65, 0 }))
            rs_opacity_edit = !rs_opacity_edit;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Choose the opacity of the overlay");
        ImGui::SetCursorPos({ 557, 165 });
        ImGui::SetNextItemWidth(rs_opacity_edit ? 170.f : 150.f);
        if (!rs_opacity_edit)
        {
            ImGui::SliderFloat("##opacity", &rs_opacity, cvar_opacity.GetMinimum(), cvar_opacity.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 711, 165 });
            if (ImGui::Button("R##Ropacity"))
            {
                rs_opacity = 1.f;
                if (theme_config["opacity"].is_number())
                    rs_opacity = float(theme_config["opacity"]);
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Reset to original value");
        }
        else
            ImGui::InputFloat("##opacity", &rs_opacity, 0.001f, 0.1f, "%.3f");

        text_size = ImGui::CalcTextSize(obs.c_str());
        ImGui::SetCursorPos({ ((settings_size.x - text_size.x) / 2), 200 });
        ImGui::TextColored(ImVec4{ 0.94f, 0.77f, 0.f, 1.f }, obs.c_str());

        ImGui::SetCursorPosY(228);
        ImGui::Separator();

        ImGui::SetCursorPos({ 0, 238 });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2) + image_pos.x, (image_size.Y / 2) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 23, 263 });
        ImGui::Checkbox("##overlay", &rs_disp_overlay);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Displays the overlay on the game screen");

        ImGui::SetCursorPos({ 63, 265 });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(cvarManager->getCvar("rs_disp_overlay").getDescription()).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (settings_size.x - 120), 241 });
        if (ImGui::Button("Open folder", { 110, 0 }))
            system(("powershell -WindowStyle Hidden \"start \"\"" + GetPath() + "\"\"\"").c_str());
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Access theme folders or files for OBS");
        ImGui::SetCursorPos({ (settings_size.x - 120), 266 });
        if (ImGui::Button("Reload Theme", { 88, 0 }))
        {
            LoadImgs();
            ChangeTheme(rs_theme);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Refresh current theme information (JSON and images)");
        ImGui::SetCursorPos({ (settings_size.x - 27), 266 });
        if (ImGui::Button("A", { 17, 0 }))
        {
            LoadImgs();
            LoadThemes();
            SetTheme(theme_render.name);
            ChangeTheme(rs_theme);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Reloads all the themes (adds or removes depending on the folders)");
        ImGui::SetCursorPos({ (settings_size.x - 120), 291 });
        if (ImGui::Button("Reset Stats", { 110, 0 }))
            ResetStats();
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Resets all plugin information for all modes (MMR, Win, Loss, etc.)");

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPos({ 280, 258 });
        text_size = ImGui::CalcTextSize(theme_render.name.c_str());
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 1.f }, theme_render.name.c_str());
        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ (285 + text_size.x), 265 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.5f }, (theme_render.version + (theme_render.date.size() ? (" - " + theme_render.date) : "")).c_str());
        ImGui::SetCursorPos({ 290, 282 });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.8f }, ("Theme by " + theme_render.author).c_str());

        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPos({ column_start, 328 });
        ImGui::BeginChild("##column1", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Checkbox(cvarManager->getCvar("rs_enable_inmenu").getDescription().c_str(), &rs_enable_inmenu);
        ImGui::Checkbox(cvarManager->getCvar("rs_enable_ingame").getDescription().c_str(), &rs_enable_ingame);
        ImGui::Checkbox(cvarManager->getCvar("rs_enable_float").getDescription().c_str(), &rs_enable_float);
        ImGui::Checkbox(cvarManager->getCvar("rs_replace_mmr").getDescription().c_str(), &rs_replace_mmr);
        ImGui::Checkbox(cvarManager->getCvar("rs_replace_mmrc").getDescription().c_str(), &rs_replace_mmrc);
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::SetCursorPosX(column_start + column_space + column_width);
        ImGui::BeginChild("##column2", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        if (!rs_in_file)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_gm").getDescription().c_str(), &rs_file_gm);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_rank").getDescription().c_str(), &rs_file_rank);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_div").getDescription().c_str(), &rs_file_div);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_mmr").getDescription().c_str(), &rs_file_mmr);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_mmrc").getDescription().c_str(), &rs_file_mmrc);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_mmrcc").getDescription().c_str(), &rs_file_mmrcc);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_win").getDescription().c_str(), &rs_file_win);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_loss").getDescription().c_str(), &rs_file_loss);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_streak").getDescription().c_str(), &rs_file_streak);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_demo").getDescription().c_str(), &rs_file_demo);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_death").getDescription().c_str(), &rs_file_death);
        ImGui::Checkbox(cvarManager->getCvar("rs_file_boost").getDescription().c_str(), &rs_file_boost);
        if (!rs_in_file)
            ImGui::PopStyleVar();
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::SetCursorPosX(column_start + (column_space * 2) + (column_width * 2));
        ImGui::BeginChild("##column3", { column_width, 205 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_gm").getDescription().c_str(), &rs_hide_gm);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_rank").getDescription().c_str(), &rs_hide_rank);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_div").getDescription().c_str(), &rs_hide_div);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_mmr").getDescription().c_str(), &rs_hide_mmr);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_mmrc").getDescription().c_str(), &rs_hide_mmrc);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_mmrcc").getDescription().c_str(), &rs_hide_mmrcc);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_win").getDescription().c_str(), &rs_hide_win);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_loss").getDescription().c_str(), &rs_hide_loss);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_streak").getDescription().c_str(), &rs_hide_streak);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_demo").getDescription().c_str(), &rs_hide_demo);
        ImGui::Checkbox(cvarManager->getCvar("rs_hide_death").getDescription().c_str(), &rs_hide_death);
        ImGui::EndChild();

        /* Variable to use to animate images
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        float fps = ImGui::GetIO().Framerate;
        ImGui::Text(("Framerate: " + std::to_string(fps)).c_str());
        */

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::Separator();

        ImGui::TextColored(((time_error || local_time.tm_sec % 2) ? ImVec4{ 0.04f, 0.52f, 0.89f, 1.f } : ImVec4{ 1.f, 1.f, 1.f, 0.5f }), "Donate");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::IsMouseClicked(0))
                system("powershell -WindowStyle Hidden \"start https://www.paypal.com/paypalme/rocketstats\"");
        }
        ImGui::SameLine();
        text_size = ImGui::CalcTextSize(developers.c_str());
        ImGui::SetCursorPosX((settings_size.x - text_size.x) / 2);
        ImGui::Text(developers.c_str());
        text_size = ImGui::CalcTextSize(menu_version.c_str());
        ImGui::SameLine();
        ImGui::SetCursorPosX(settings_size.x - text_size.x - 7);
        ImGui::Text(menu_version.c_str());

        drawlist->PopClipRect();
    }
    else
    {
        ImGui::SetWindowFontScale(1.5f);
        ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Error - Check that this folder is present in BakkesMod: data/RocketStats");
        ImGui::SameLine();
        ImGui::SetWindowFontScale(1.f);
        ImGui::SetCursorPosX(settings_size.x - 80 - 7);
        if (ImGui::Button("Reload All", { 80, 0 }))
        {
            SetDefaultFolder();

            LoadImgs();
            LoadThemes();
            ChangeTheme(rs_theme);
            rs_logo = LoadImg("RocketStats_images/logo.png");
            rs_title = LoadImg("RocketStats_images/title.png");
        }
    }

    ImGui::End();

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
    SetCVar("rs_mode", rs_mode);
    SetCVar("rs_theme", rs_theme);

    SetCVar("rs_x", rs_x, true);
    SetCVar("rs_y", rs_y, true);

    SetCVar("rs_scale", rs_scale, true);
    SetCVar("rs_rotate", rs_rotate, true);
    SetCVar("rs_opacity", rs_opacity, true);

    SetCVar("rs_disp_overlay", rs_disp_overlay);
    if (SetCVar("rs_enable_inmenu", rs_enable_inmenu))
    {
        if (!rs_enable_inmenu && !rs_enable_ingame)
            rs_enable_ingame = true;
    }
    if (SetCVar("rs_enable_ingame", rs_enable_ingame))
    {
        if (!rs_enable_ingame && !rs_enable_inmenu)
            rs_enable_inmenu = true;
    }
    SetCVar("rs_enable_float", rs_enable_float);

    SetCVar("rs_file_gm", rs_file_gm);
    SetCVar("rs_file_rank", rs_file_rank);
    SetCVar("rs_file_div", rs_file_div);
    SetCVar("rs_file_mmr", rs_file_mmr);
    SetCVar("rs_file_mmrc", rs_file_mmrc);
    SetCVar("rs_file_mmrcc", rs_file_mmrcc);
    SetCVar("rs_file_win", rs_file_win);
    SetCVar("rs_file_loss", rs_file_loss);
    SetCVar("rs_file_streak", rs_file_streak);
    SetCVar("rs_file_demo", rs_file_demo);
    SetCVar("rs_file_death", rs_file_death);
    SetCVar("rs_file_boost", rs_file_boost);

    SetCVar("rs_hide_gm", rs_hide_gm);
    SetCVar("rs_hide_rank", rs_hide_rank);
    SetCVar("rs_hide_div", rs_hide_div);
    SetCVar("rs_hide_mmr", rs_hide_mmr);
    SetCVar("rs_hide_mmrc", rs_hide_mmrc);
    SetCVar("rs_hide_mmrcc", rs_hide_mmrcc);
    SetCVar("rs_hide_win", rs_hide_win);
    SetCVar("rs_hide_loss", rs_hide_loss);
    SetCVar("rs_hide_streak", rs_hide_streak);
    SetCVar("rs_hide_demo", rs_hide_demo);
    SetCVar("rs_hide_death", rs_hide_death);
    SetCVar("rs_replace_mmr", rs_replace_mmr);
    SetCVar("rs_replace_mmrc", rs_replace_mmrc);
}

// Name of the menu that is used to toggle the window.
std::string RocketStats::GetMenuName()
{
    return menu_name;
}

// Title to give the menu
std::string RocketStats::GetMenuTitle()
{
    return menu_title;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void RocketStats::SetImGuiContext(uintptr_t ctx)
{
    ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool RocketStats::ShouldBlockInput()
{
    return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool RocketStats::IsActiveOverlay()
{
    return settings_open;
}

void RocketStats::OnOpen()
{
    //ToggleSettings("OnOpen", ToggleFlags_Show);
}

void RocketStats::OnClose()
{
    // Displays the plugin immediately after pressing the escape key
    if (escape_state)
    {
        escape_state = false;
        gameWrapper->SetTimeout([&](GameWrapper* gameWrapper) {
            cvarManager->executeCommand("togglemenu " + GetMenuName());
            }, 0.02F);
    }

    ToggleSettings("OnClose", ToggleFlags_Hide);
}