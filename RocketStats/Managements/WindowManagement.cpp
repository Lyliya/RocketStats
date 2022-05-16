#include "../RocketStats.h"

void RocketStats::Render()
{
    timer_30fps.tick();
    display_size = ImGui::GetIO().DisplaySize;

    is_online_game = gameWrapper->IsInOnlineGame();
    is_offline_game = gameWrapper->IsInGame();
    is_in_freeplay = gameWrapper->IsInFreeplay();
    is_in_game = (is_online_game || is_offline_game);

    // Capture of the escape key, to prevent the plugin from disappearing
    int idx = ImGui::GetKeyIndex(ImGuiKey_Escape);
    if (ImGui::IsKeyDown(idx))
        escape_state = true;
    else if (ImGui::IsKeyReleased(idx))
        escape_state = false;

    if (rs_recovery == RecoveryFlags_Files)
    {
        ImGui::SetNextWindowPos({ 10.f, (display_size.y - (95.f + 10.f)) }, ImGuiCond_Appearing);
        ImGui::SetNextWindowSize({ 0.f, 0.f });

        bool opened = true;
        ImGui::Begin((menu_title + "##Recovery").c_str(), &opened, (ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse));

        ImGui::Text(GetLang(LANG_MIGRATE_MESSAGE).c_str());

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
        if (rs_buttons_x)
            ImGui::SetCursorPosX(rs_buttons_x);

        float x = ImGui::GetCursorPosX();
        if (ImGui::Button(GetLang(LANG_MIGRATE_BUTTON_MIGRATE).c_str()))
        {
            opened = false;
            MigrateFolder();
        }
        ImGui::SameLine();
        if (ImGui::Button(GetLang(LANG_MIGRATE_BUTTON_REMOVE).c_str()))
        {
            opened = false;
            MigrateRemove();
        }
        ImGui::SameLine();
        if (ImGui::Button(GetLang(LANG_MIGRATE_BUTTON_NOTHING).c_str()))
            opened = false;
        ImGui::SameLine();
        rs_buttons_x = ((ImGui::GetWindowWidth() - (ImGui::GetCursorPosX() - x)) / 2);

        ImGui::End();

        if (!opened)
            onInit();

        return;
    }

    RenderOverlay();

    // Displays the button allowing the display and the hiding of the menu
    CVarWrapper rs_toggle_logo = cvarManager->getCvar("rs_toggle_logo");
    if (rs_toggle_logo && rs_toggle_logo.getBoolValue())
        RenderIcon();

    if (!overlay_move && settings_open)
    {
        CloseWelcome();
        RenderSettings();
    }

    // Displays the message to introduce the new version
    if (rs_recovery == RecoveryFlags_Welcome && rs_welcome != nullptr && rs_welcome->IsLoadedForImGui())
    {
        ImVec2 mouse_pos = ImGui::GetIO().MousePos;
        Vector2F image_size = rs_welcome->GetSizeF();
        bool mouse_click = GetAsyncKeyState(VK_LBUTTON);

        float max_width = (display_size.x / 2);
        if (max_width < image_size.X)
            image_size = { max_width, ((image_size.Y / image_size.X) * max_width) };
        ImVec2 image_min = { ((display_size.x - image_size.X) / 2), ((display_size.y - image_size.Y) / 2) };
        ImVec2 image_max = { (image_min.x + image_size.X), (image_min.y + image_size.Y) };

        bool hover = (mouse_pos.x > image_min.x && mouse_pos.x < image_max.x);
        hover = (hover && (mouse_pos.y > image_min.y && mouse_pos.y < image_max.y));

        // Close the new version message when clicking on the image
        if (hover && mouse_click)
            CloseWelcome();
        else
            ImGui::GetBackgroundDrawList()->AddImage(rs_welcome->GetImGuiTex(), image_min, image_max);
    }
    else if (rs_recovery == RecoveryFlags_Finish)
        rs_recovery = RecoveryFlags_Off;
}

void RocketStats::RenderIcon()
{
    bool hide = (rs_recovery == RecoveryFlags_Off && !settings_open && (overlay_move || (is_in_game && !is_in_menu)));
    if (hide && rs_logo_flash < 0.f)
        return;

    float margin = 0.f;
    float icon_size = (42.f * rs_screen_scale[0]);
    float icon_scale = (1.f - rs_screen_scale[0]);
    ImVec2 icon_pos = { 0.f, (display_size.y * 0.459f * (icon_scale + (icon_scale * (0.18f - (1.f - rs_screen_scale[1]))) + 1.f)) };
    ImDrawList* drawlist = ImGui::GetBackgroundDrawList();

    // Flash on GameEnd
    if (rs_logo_flash >= 0.f)
    {
        rs_logo_flash += (0.1f * float(timer_30fps.frames()));
        if (rs_logo_flash > 2.f)
            rs_logo_flash = -1.f;
        else
            drawlist->AddCircleFilled({ icon_pos.x, icon_pos.y }, icon_size, ImColor{ 1.f, 1.f, 1.f, ((rs_logo_flash > 1.f) ? (2.f - rs_logo_flash) : rs_logo_flash) }, 25);
    }

    if (hide)
        return;

    ImVec2 mouse_pos = ImGui::GetIO().MousePos;
    bool mouse_click = GetAsyncKeyState(VK_LBUTTON);
    bool hover = (mouse_pos.x > (icon_pos.x - icon_size - margin) && mouse_pos.x < (icon_pos.x + icon_size + margin));
    hover = (hover && (mouse_pos.y > (icon_pos.y - icon_size - margin) && mouse_pos.y < (icon_pos.y + icon_size + margin)));

    // Handles logo movement
    rs_logo_rotate += ((rs_logo_mouv ? 0.3f : -0.3f) * float(timer_30fps.frames()));
    if (rs_logo_rotate < 0 || rs_logo_rotate >= 30.f)
    {
        rs_logo_mouv = !rs_logo_mouv;
        rs_logo_rotate = max(0.f, min(30.f, rs_logo_rotate));
    }

    // Displays the logo otherwise displays a circle instead
    if (rs_logo != nullptr && rs_logo->IsLoadedForImGui())
    {
        Vector2F image_size = rs_logo->GetSizeF();
        float rotate = ((90.f - rs_logo_rotate) * (float(M_PI) / 180.f));

        if (rs_llaunch < 1.f)
        {
            rs_llaunch += 0.05f;
            SetRefresh(RefreshFlags_Refresh);
        }

        ImRotateStart(drawlist);
        drawlist->AddImage(rs_logo->GetImGuiTex(), { icon_pos.x - icon_size, icon_pos.y - icon_size }, { icon_pos.x + icon_size, icon_pos.y + icon_size }, { 0, 0 }, { 1, 1 }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, rs_llaunch }));
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
        ImGui::SetTooltip(GetLang(LANG_TOGGLE_MENU_TOOLTIP).c_str());

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

void RocketStats::RenderOverlay()
{
    bool show_overlay = ((rs_enable_inmenu && is_in_menu) || (rs_enable_ingame && is_in_game && (!is_in_scoreboard || is_in_freeplay)) || (rs_enable_inscoreboard && is_in_scoreboard && !is_in_freeplay));
    if (!rs_disp_overlay || !show_overlay || (rs_recovery != RecoveryFlags_Off && rs_recovery != RecoveryFlags_Finish))
        return;

    ImGui::SetNextWindowPos({ 0.f, 0.f }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize({ 0.f, 0.f });

    ImGui::Begin(menu_title.c_str(), (bool*)1, (ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoFocusOnAppearing));

    try
    {
        // Calculation each element of the theme (only during a modification)
        if (overlay_move || theme_refresh || theme_render.name == "" || (themes.size() > rs_theme && theme_render.name != themes.at(rs_theme).name))
        {
            Stats tstats = GetStats();

            theme_size = { 0, 0 };
            if (theme_config["width"].is_string())
                theme_size.x = float(Utils::EvaluateExpression(theme_config["width"], int(display_size.x), display_size));
            else if (theme_config["width"].is_number())
                theme_size.x = float(theme_config["width"]);
            if (theme_config["height"].is_string())
                theme_size.y = float(Utils::EvaluateExpression(theme_config["height"], int(display_size.y), display_size));
            else if (theme_config["height"].is_number())
                theme_size.y = float(theme_config["height"]);

            // Refresh all images
            if (theme_refresh == 2)
            {
                theme_images.clear();
                cvarManager->log("Refresh all images");
            }

            // Reset the menu variables if you change the theme
            if (theme_prev != theme_render.name)
            {
                if (rs_recovery != RecoveryFlags_Finish && !GetCVar("rs_scale", rs_scale))
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

                if (rs_recovery != RecoveryFlags_Finish && !GetCVar("rs_x", rs_x))
                {
                    rs_x = 0.f;
                    if (theme_config["x"].is_string())
                        rs_x = (float(Utils::EvaluateExpression(theme_config["x"], int(theme_size.x * rs_scale), display_size)) / display_size.x);
                    else if (theme_config["x"].is_number())
                        rs_x = float(theme_config["x"]);
                }

                if (rs_recovery != RecoveryFlags_Finish && !GetCVar("rs_y", rs_y))
                {
                    rs_y = 0.f;
                    if (theme_config["y"].is_string())
                        rs_y = (float(Utils::EvaluateExpression(theme_config["y"], int(theme_size.y * rs_scale), display_size)) / display_size.y);
                    else if (theme_config["y"].is_number())
                        rs_y = float(theme_config["y"]);
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
                int(rs_x * display_size.x),
                int(rs_y * display_size.y),
                int(theme_size.x),
                int(theme_size.y),
                rs_scale,
                (rs_launch * rs_opacity)
            };

            // Change the position of the overlay when moving with the mouse
            if (overlay_move)
            {
                options.x = int(overlay_cursor.x);
                options.y = int(overlay_cursor.y);
            }

            VarsReplace(theme_vars);

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

            if (!theme_refresh && rs_drawlist->VtxBuffer.Size && windows_count == ImGui::GetIO().MetricsRenderWindows)
            {
                // Fill the DrawList with previously generated vertices
                drawlist->CmdBuffer = rs_drawlist->CmdBuffer;
                drawlist->IdxBuffer = rs_drawlist->IdxBuffer;
                drawlist->VtxBuffer = rs_drawlist->VtxBuffer;

                drawlist->Flags = rs_drawlist->Flags;
                drawlist->_VtxCurrentIdx = (unsigned int)drawlist->VtxBuffer.Size;
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
                    ImRotateEnd(rs_crotate, start, drawlist, ImRotationCenter(start, ImGui::GetBackgroundDrawList()));

                // Stores generated vertices for future frames
                rs_drawlist->Clear();
                rs_drawlist = drawlist->CloneOutput();

                // Avoid conflicts between different plugins using ImGui
                windows_count = ImGui::GetIO().MetricsRenderWindows;
            }

            // Displays a square and allows the movement of the overlay with the mouse
            if (settings_open)
            {
                float margin = 10.f;
                float rect_size = 10.f;
                bool mouse_click = GetAsyncKeyState(VK_LBUTTON);
                ImVec2 mouse_pos = ImGui::GetIO().MousePos;
                ImVec2 overlay_pos = { (rs_x * display_size.x), (rs_y * display_size.y) };
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
                            rs_x = (overlay_cursor.x / display_size.x);
                            rs_y = (overlay_cursor.y / display_size.y);

                            overlay_move = false;
                            SetRefresh(RefreshFlags_Refresh);
                        }
                        else
                            ImGui::SetTooltip(GetLang(LANG_OVERLAY_MOVE).c_str());
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
            SetRefresh(RefreshFlags_Refresh);
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
    std::string tooltip;
    ImVec2 settings_size = { 750.f, 0.f };

    CVarWrapper cvar_scale = cvarManager->getCvar("rs_scale");
    CVarWrapper cvar_rotate = cvarManager->getCvar("rs_rotate");
    CVarWrapper cvar_opacity = cvarManager->getCvar("rs_opacity");

    GuiManagerWrapper gui = gameWrapper->GetGUIManager();
    ImFont* font = gui.GetFont("Ubuntu-Regular28");
    bool menu_font = font->IsLoaded();

    if (menu_font)
        ImGui::PushFont(font);

    ImGui::SetNextWindowPos({ 128.f, 256.f }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(settings_size);

    ImGui::Begin((menu_title + "##Settings").c_str(), nullptr, (ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse));

    ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));

    // Show menu only if menu image is loaded
    if (rs_logo != nullptr && rs_title != nullptr && rs_logo->IsLoadedForImGui() && rs_title->IsLoadedForImGui())
    {
        bool select_all;
        float column_nb = 3;
        float column_space = 10.f;
        float column_start = 25.f;
        float column_width = ((settings_size.x - (column_start * 2.f) - (column_space * (column_nb - 1.f))) / column_nb);

        ImVec2 tpos;
        ImVec2 text_size;
        ImVec2 image_pos;
        ImVec2 win_pos = ImGui::GetWindowPos();
        ImVec2 win_size = ImGui::GetWindowSize();
        Vector2F image_size = rs_title->GetSizeF();
        ImDrawList* drawlist = ImGui::GetWindowDrawList();

        ImVec2 p0 = win_pos;
        ImVec2 p1 = { (win_pos.x + win_size.x), (win_pos.y + win_size.y) };

        p0.x += 1;
        p1.x -= 1;
        drawlist->PushClipRect(p0, p1); // Allows you to delimit the area of the window (without internal borders)

        std::time(&current_time);
        const auto time_error = localtime_s(&local_time, &current_time);

        // Documentation
        float circle_size = 21.5f;
        const float radian_min = (((210.f - 90.f) / 360.f) * ARC_SPAN);
        const float radian_max = (((270.f - 90.f) / 360.f) * ARC_SPAN);
        ImU32 circle_color = ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Border));
        ImVec2 circle_end = { (win_pos.x + win_size.x - 6.f), (win_pos.y + 1.f) };
        ImVec2 circle_start = { (circle_end.x + ((circle_size * cos(radian_min)))), (circle_end.y + ((circle_size * sin(radian_min)))) };

        ImGui::SetWindowFontScale(1.3f / (font ? 2.f : 1.f));
        drawlist->PathLineTo(circle_start);
        drawlist->PathArcTo(circle_end, circle_size, radian_min, radian_max, 20);
        drawlist->PathStroke(circle_color, false, 1.f);
        drawlist->AddLine({ (circle_start.x - 1.f), (circle_start.y - 1.f) }, { (circle_start.x + 15.f), (circle_start.y - 1.f) }, circle_color, 1.f);
        drawlist->AddText({ (win_pos.x + win_size.x - 14.f), win_pos.y }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 1.f }), "?");

        if (ImGui::GetMousePos().x >= (circle_start.x - 6.f) && ImGui::GetMousePos().x <= (win_pos.x + win_size.x - 1.f) && ImGui::GetMousePos().y >= win_pos.y && ImGui::GetMousePos().y <= circle_start.y)
        {
            tooltip = GetLang(LANG_DOCUMENTATION);
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                system("powershell -WindowStyle Hidden \"start https://github.com/Lyliya/RocketStats/wiki\"");
        }

        // First Part
        ImGui::SetCursorPos({ 0.f, 27.f });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2.f) + image_pos.x, (image_size.Y / 2.f) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ 23.f, 52.f });
        ImGui::Checkbox("##overlay", &rs_disp_overlay);
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_OVERLAY_TOOLTIP);

        ImGui::SetCursorPos({ 63.f, 54.f });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(GetLang(LANG_OVERLAY)).c_str());

        ImGui::SetWindowFontScale(1.3f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ 355.f, 43.f });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, GetLang(LANG_MODE).c_str());

        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ 295.f, 68.f });
        ImGui::SetNextItemWidth(142.f);
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
            tooltip = GetLang(LANG_IN_FILE_TOOLTIP);
        ImGui::SameLine(0.f, 0.f);
        if (ImGui::ArrowButton("##modes_left", ImGuiDir_Left) && rs_mode > 0)
            --rs_mode;
        ImGui::SameLine(0.f, 0.f);
        if (ImGui::ArrowButton("##modes_right", ImGuiDir_Right) && rs_mode < (modes.size() - 1))
            ++rs_mode;

        ImGui::SetWindowFontScale(1.3f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ 585.f, 43.f });
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, GetLang(LANG_THEME).c_str());

        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ 525.f, 68.f });
        ImGui::SetNextItemWidth(142.f);
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
            tooltip = GetLang(LANG_THEME_TOOLTIP);
        ImGui::SameLine(0.f, 0.f);
        if (ImGui::ArrowButton("##themes_left", ImGuiDir_Left) && rs_theme > 0)
            --rs_theme;
        ImGui::SameLine(0.f, 0.f);
        if (ImGui::ArrowButton("##themes_right", ImGuiDir_Right) && themes.size() && rs_theme < (themes.size() - 1))
            ++rs_theme;

        ImGui::SetCursorPos({ 103.f, 120.f });
        if (ImGui::Button(GetLang(LANG_X).c_str(), { 65.f, 0.f }))
            rs_x_edit = !rs_x_edit;
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_X_TOOLTIP);
        ImGui::SetCursorPos({ 158.f, 120.f });
        ImGui::SetNextItemWidth(rs_x_edit ? 170.f : 150.f);
        if (!rs_x_edit)
        {
            ImGui::SliderFloat("##x_position", &rs_x, 0.f, 1.f, "%.3f");
            ImGui::SetCursorPos({ 312.f, 120.f });
            if (ImGui::Button("R##Rx_position"))
            {
                rs_x = 0.f;
                if (theme_config["x"].is_string())
                    rs_x = (float(Utils::EvaluateExpression(theme_config["x"], int(theme_size.x * rs_scale), display_size)) / display_size.x);
                else if (theme_config["x"].is_number())
                    rs_x = float(theme_config["x"]);
            }
            if (ImGui::IsItemHovered())
                tooltip = GetLang(LANG_RESET_TOOLTIP);
        }
        else
            ImGui::InputFloat("##x_position", &rs_x, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 421.f, 120.f });
        if (ImGui::Button(GetLang(LANG_Y).c_str(), { 65.f, 0.f }))
            rs_y_edit = !rs_y_edit;
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_Y_TOOLTIP);
        ImGui::SetCursorPos({ 476.f, 120.f });
        ImGui::SetNextItemWidth(rs_y_edit ? 170.f : 150.f);
        if (!rs_y_edit)
        {
            ImGui::SliderFloat("##y_position", &rs_y, 0.f, 1.f, "%.3f");
            ImGui::SetCursorPos({ 630.f, 120.f });
            if (ImGui::Button("R##Ry_position"))
            {
                rs_y = 0.f;
                if (theme_config["y"].is_string())
                    rs_y = (float(Utils::EvaluateExpression(theme_config["y"], int(theme_size.y * rs_scale), display_size)) / display_size.y);
                else if (theme_config["y"].is_number())
                    rs_y = float(theme_config["y"]);
            }
            if (ImGui::IsItemHovered())
                tooltip = GetLang(LANG_RESET_TOOLTIP);
        }
        else
            ImGui::InputFloat("##y_position", &rs_y, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 24.f, 165.f });
        if (ImGui::Button(GetLang(LANG_SCALE).c_str(), { 65, 0 }))
            rs_scale_edit = !rs_scale_edit;
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_SCALE_TOOLTIP);
        ImGui::SetCursorPos({ 79.f, 165.f });
        ImGui::SetNextItemWidth(rs_scale_edit ? 170.f : 150.f);
        if (!rs_scale_edit)
        {
            ImGui::SliderFloat("##scale", &rs_scale, cvar_scale.GetMinimum(), cvar_scale.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 233.f, 165.f });
            if (ImGui::Button("R##Rscale"))
            {
                rs_scale = 1.f;
                if (theme_config["scale"].is_number())
                    rs_scale = float(theme_config["scale"]);
            }
            if (ImGui::IsItemHovered())
                tooltip = GetLang(LANG_RESET_TOOLTIP);
        }
        else
            ImGui::InputFloat("##scale", &rs_scale, 0.01f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 263.f, 165.f });
        if (ImGui::Button(GetLang(LANG_ROTATE).c_str(), { 65, 0 }))
            rs_rotate_edit = !rs_rotate_edit;
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_ROTATE_TOOLTIP);
        ImGui::SetCursorPos({ 318.f, 165.f });
        ImGui::SetNextItemWidth(rs_rotate_edit ? 170.f : 150.f);
        if (!rs_rotate_edit)
        {
            ImGui::SliderFloat("##rotate", &rs_rotate, cvar_rotate.GetMinimum(), cvar_rotate.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 472.f, 165.f });
            if (ImGui::Button("R##Rrotate"))
            {
                rs_rotate = 0.f;
                if (theme_config["rotate"].is_number())
                    rs_rotate = float(theme_config["rotate"]);
            }
            if (ImGui::IsItemHovered())
                tooltip = GetLang(LANG_RESET_TOOLTIP);
        }
        else
            ImGui::InputFloat("##rotate", &rs_rotate, 0.001f, 0.1f, "%.3f");

        ImGui::SetCursorPos({ 502.f, 165.f });
        if (ImGui::Button(GetLang(LANG_OPACITY).c_str(), { 65.f, 0.f }))
            rs_opacity_edit = !rs_opacity_edit;
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_OPACITY_TOOLTIP);
        ImGui::SetCursorPos({ 557.f, 165.f });
        ImGui::SetNextItemWidth(rs_opacity_edit ? 170.f : 150.f);
        if (!rs_opacity_edit)
        {
            ImGui::SliderFloat("##opacity", &rs_opacity, cvar_opacity.GetMinimum(), cvar_opacity.GetMaximum(), "%.3f");
            ImGui::SetCursorPos({ 711.f, 165.f });
            if (ImGui::Button("R##Ropacity"))
            {
                rs_opacity = 1.f;
                if (theme_config["opacity"].is_number())
                    rs_opacity = float(theme_config["opacity"]);
            }
            if (ImGui::IsItemHovered())
                tooltip = GetLang(LANG_RESET_TOOLTIP);
        }
        else
            ImGui::InputFloat("##opacity", &rs_opacity, 0.001f, 0.1f, "%.3f");

        text_size = ImGui::CalcTextSize(GetLang(LANG_OVERLAY_OBS).c_str());
        ImGui::SetCursorPos({ ((settings_size.x - text_size.x) / 2.f), 200.f });
        ImGui::TextColored(ImVec4{ 0.94f, 0.77f, 0.f, 1.f }, GetLang(LANG_OVERLAY_OBS).c_str());

        ImGui::SetCursorPosY(228.f);
        ImGui::Separator();

        // Second Part
        ImGui::SetCursorPos({ 0.f, 238.f });
        image_pos = { p0.x + ImGui::GetCursorPosX(), p0.y + ImGui::GetCursorPosY() };
        drawlist->AddImage(rs_title->GetImGuiTex(), image_pos, { (image_size.X / 2) + image_pos.x, (image_size.Y / 2) + image_pos.y });

        ImGui::SetWindowFontScale(1.7f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ 23.f, 263.f });
        ImGui::Checkbox("##in_file", &rs_in_file);
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_IN_FILE_TOOLTIP);

        ImGui::SetCursorPos({ 63.f, 265.f });
        ImGui::TextColored(ImVec4{ 0.2f, 0.2f, 0.2f, 1.f }, Utils::toupper(GetLang(LANG_IN_FILE)).c_str());

        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ (settings_size.x - 135.f), 241.f });
        if (ImGui::Button(GetLang(LANG_OPEN_FOLDER).c_str(), { 125.f, 0.f }))
            system(("powershell -WindowStyle Hidden \"start \"\"" + GetPath() + "\"\"\"").c_str());
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_OPEN_FOLDER_TOOLTIP);
        ImGui::SetCursorPos({ (settings_size.x - 135.f), 266.f });
        if (ImGui::Button(GetLang(LANG_RELOAD_THEME).c_str(), { 103.f, 0.f }))
        {
            LoadImgs();
            ChangeTheme(rs_theme);
        }
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_RELOAD_THEME_TOOLTIP);
        ImGui::SetCursorPos({ (settings_size.x - 27.f), 266.f });
        if (ImGui::Button(GetLang(LANG_RELOAD_THEME_A).c_str(), { 17.f, 0.f }))
        {
            LoadImgs();
            LoadThemes();
            SetTheme(theme_render.name);
            ChangeTheme(rs_theme);
        }
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_RELOAD_THEME_A_TOOLTIP);
        ImGui::SetCursorPos({ (settings_size.x - 135.f), 291.f });
        if (ImGui::Button(GetLang(LANG_RESET_STATS).c_str(), { 125.f, 0.f }))
            ResetStats();
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_RESET_STATS_TOOLTIP);

        ImGui::SetWindowFontScale(1.7f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ 280.f, 258.f });
        text_size = ImGui::CalcTextSize(theme_render.name.c_str());
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 1.f }, theme_render.name.c_str());
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::SetCursorPos({ (285.f + text_size.x), 265.f });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.5f }, (theme_render.version + (theme_render.date.size() ? (" - " + theme_render.date) : "")).c_str());
        ImGui::SetCursorPos({ 290.f, 282.f });
        ImGui::TextColored(ImVec4{ 1.f, 1.f, 1.f, 0.8f }, ((GetLang(LANG_THEME_BY) + " ").c_str() + theme_render.author).c_str());

        ImGui::SetCursorPos({ (column_start - 8.f), 350.f });
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::BeginChild("##column1", { (column_width + 16.f), 205.f }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Checkbox(GetLang(LANG_SHOW_IN_MENU).c_str(), &rs_enable_inmenu);
        ImGui::Checkbox(GetLang(LANG_SHOW_IN_GAME).c_str(), &rs_enable_ingame);
        ImGui::Checkbox(GetLang(LANG_SHOW_IN_SCOREBOARD).c_str(), &rs_enable_inscoreboard);
        ImGui::Checkbox(GetLang(LANG_FLOATING_POINT).c_str(), &rs_enable_float);
        ImGui::Checkbox(GetLang(LANG_PREVIEW_RANK).c_str(), &rs_preview_rank);
        ImGui::Checkbox(GetLang(LANG_ROMAN_NUMBERS).c_str(), &rs_roman_numbers);
        ImGui::Checkbox(GetLang(LANG_MMR_TO_MMRCHANGE).c_str(), &rs_replace_mmr);
        ImGui::Checkbox(GetLang(LANG_MMR_TO_MMRCUMULCHANGE).c_str(), &rs_replace_mmr_cc);
        ImGui::Checkbox(GetLang(LANG_MMRCHANGE_TO_MMR).c_str(), &rs_replace_mmrc);
        ImGui::Checkbox(GetLang(LANG_MMRCHANGE_TO_MMRCUMULCHANGE).c_str(), &rs_replace_mmrc_cc);
        ImGui::Checkbox(GetLang(LANG_MMRCUMULCHANGE_TO_MMR).c_str(), &rs_replace_mmrcc);
        ImGui::Checkbox(GetLang(LANG_MMRCUMULCHANGE_TO_MMRCHANGE).c_str(), &rs_replace_mmrcc_c);
        ImGui::EndChild();

        rs_select_all_file = (rs_file_games && rs_file_gm && rs_file_rank && rs_file_div &&
            rs_file_mmr && rs_file_mmrc && rs_file_mmrcc &&
            rs_file_win && rs_file_loss && rs_file_streak && rs_file_winratio && rs_file_winpercentage && rs_file_score &&
            rs_file_boost &&
            rs_file_shots && rs_file_saves && rs_file_goals && rs_file_dropshot && rs_file_knockout && rs_file_miscs && rs_file_accolades);
        select_all = rs_select_all_file;
        tpos = { (column_start + column_space + (column_width + 16.f) - 0.5f), 323.f };
        ImGui::SetCursorPos(tpos);
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.3f, 0.3f, 0.3f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.3f, 0.3f, 0.3f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.3f, 0.3f, 0.3f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_CheckMark, { 0.f, 0.f, 0.f, 0.8f });
        ImGui::GetWindowDrawList()->AddLine({ (tpos.x + win_pos.x + 5.f), (tpos.y + win_pos.y + 17.f) }, { (tpos.x + win_pos.x + 200.f), (tpos.y + win_pos.y + 17.f) }, ImGui::ColorConvertFloat4ToU32({ 0.3f, 0.3f, 0.3f, 1.f }), 2.f);
        ImGui::Checkbox("##select_all_file", &select_all);
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_SELECT_ALL_TOOLTIP);
        ImGui::PopStyleColor(4);
        ImGui::SetWindowFontScale(1.2f / (font ? 2.f : 1.f));
        ImGui::SameLine();
        ImGui::SetCursorPosY(316.f);
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, GetLang(LANG_FILE_TITLE).c_str());
        ImGui::SetCursorPos({ (column_start + column_space + (column_width + 16.f)), 350.f });
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::BeginChild("##column2", { (column_width - 8.f), 205.f }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        if (!rs_in_file)
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::Checkbox(GetLang(LANG_GAMES).c_str(), &rs_file_games);
        ImGui::Checkbox(GetLang(LANG_GAMEMODE).c_str(), &rs_file_gm);
        ImGui::Checkbox(GetLang(LANG_RANK).c_str(), &rs_file_rank);
        ImGui::Checkbox(GetLang(LANG_DIVISION).c_str(), &rs_file_div);
        ImGui::Checkbox(GetLang(LANG_MMR).c_str(), &rs_file_mmr);
        ImGui::Checkbox(GetLang(LANG_MMRCHANGE).c_str(), &rs_file_mmrc);
        ImGui::Checkbox(GetLang(LANG_MMRCUMULCHANGE).c_str(), &rs_file_mmrcc);
        ImGui::Checkbox(GetLang(LANG_WINS).c_str(), &rs_file_win);
        ImGui::Checkbox(GetLang(LANG_LOSSES).c_str(), &rs_file_loss);
        ImGui::Checkbox(GetLang(LANG_STREAKS).c_str(), &rs_file_streak);
        ImGui::Checkbox(GetLang(LANG_WINRATIO).c_str(), &rs_file_winratio);
        ImGui::Checkbox(GetLang(LANG_WINPERCENTAGE).c_str(), &rs_file_winpercentage);
        ImGui::Checkbox(GetLang(LANG_SCORE).c_str(), &rs_file_score);
        ImGui::Checkbox(GetLang(LANG_SHOTS).c_str(), &rs_file_shots);
        ImGui::Checkbox(GetLang(LANG_SAVES).c_str(), &rs_file_saves);
        ImGui::Checkbox(GetLang(LANG_GOALS).c_str(), &rs_file_goals);
        ImGui::Checkbox(GetLang(LANG_DROPSHOT).c_str(), &rs_file_dropshot);
        ImGui::Checkbox(GetLang(LANG_KNOCKOUT).c_str(), &rs_file_knockout);
        ImGui::Checkbox(GetLang(LANG_MISCS).c_str(), &rs_file_miscs);
        ImGui::Checkbox(GetLang(LANG_ACCOLADES).c_str(), &rs_file_accolades);
        ImGui::Checkbox(GetLang(LANG_BOOST).c_str(), &rs_file_boost);
        if (!rs_in_file)
            ImGui::PopStyleVar();
        ImGui::EndChild();

        if (select_all != rs_select_all_file)
        {
            rs_select_all_file = !rs_select_all_file;

            rs_file_games = rs_select_all_file;
            rs_file_gm = rs_select_all_file;
            rs_file_rank = rs_select_all_file;
            rs_file_div = rs_select_all_file;
            rs_file_mmr = rs_select_all_file;
            rs_file_mmrc = rs_select_all_file;
            rs_file_mmrcc = rs_select_all_file;
            rs_file_win = rs_select_all_file;
            rs_file_loss = rs_select_all_file;
            rs_file_streak = rs_select_all_file;
            rs_file_winratio = rs_select_all_file;
            rs_file_winpercentage = rs_select_all_file;
            rs_file_score = rs_select_all_file;
            rs_file_shots = rs_select_all_file;
            rs_file_saves = rs_select_all_file;
            rs_file_goals = rs_select_all_file;
            rs_file_dropshot = rs_select_all_file;
            rs_file_knockout = rs_select_all_file;
            rs_file_miscs = rs_select_all_file;
            rs_file_accolades = rs_select_all_file;
            rs_file_boost = rs_select_all_file;
        }

        rs_select_all_hide = (rs_hide_games && rs_hide_gm && rs_hide_rank && rs_hide_div &&
            rs_hide_mmr && rs_hide_mmrc && rs_hide_mmrcc &&
            rs_hide_win && rs_hide_loss && rs_hide_streak && rs_hide_winratio && rs_hide_winpercentage && rs_hide_score &&
            rs_hide_shots && rs_hide_saves && rs_hide_goals && rs_hide_dropshot && rs_hide_knockout && rs_hide_miscs && rs_hide_accolades);
        select_all = rs_select_all_hide;
        tpos = { (column_start + (column_space * 2.f) + ((column_width * 2.f) + 16.f)), 323.f };
        ImGui::SetCursorPos(tpos);
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.3f, 0.3f, 0.3f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.3f, 0.3f, 0.3f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.3f, 0.3f, 0.3f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_CheckMark, { 0.f, 0.f, 0.f, 0.8f });
        ImGui::GetWindowDrawList()->AddLine({ (tpos.x + win_pos.x + 5.f), (tpos.y + win_pos.y + 17.f) }, { (tpos.x + win_pos.x + 200.f), (tpos.y + win_pos.y + 17.f) }, ImGui::ColorConvertFloat4ToU32({ 0.3f, 0.3f, 0.3f, 1.f }), 2.f);
        ImGui::Checkbox("##select_all_hide", &select_all);
        if (ImGui::IsItemHovered())
            tooltip = GetLang(LANG_SELECT_ALL_TOOLTIP);
        ImGui::PopStyleColor(4);
        ImGui::SetWindowFontScale(1.2f / (font ? 2.f : 1.f));
        ImGui::SameLine();
        ImGui::SetCursorPosY(316.f);
        ImGui::TextColored(ImVec4{ 0.8f, 0.8f, 0.8f, 1.f }, GetLang(LANG_HIDE_TITLE).c_str());
        ImGui::SetCursorPos({ (column_start + (column_space * 2.f) + ((column_width * 2.f) + 16.f)), 350.f });
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::BeginChild("##column3", { (column_width - 8.f), 205.f }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Checkbox(GetLang(LANG_GAMES).c_str(), &rs_hide_games);
        ImGui::Checkbox(GetLang(LANG_GAMEMODE).c_str(), &rs_hide_gm);
        ImGui::Checkbox(GetLang(LANG_RANK).c_str(), &rs_hide_rank);
        ImGui::Checkbox(GetLang(LANG_DIVISION).c_str(), &rs_hide_div);
        ImGui::Checkbox(GetLang(LANG_MMR).c_str(), &rs_hide_mmr);
        ImGui::Checkbox(GetLang(LANG_MMRCHANGE).c_str(), &rs_hide_mmrc);
        ImGui::Checkbox(GetLang(LANG_MMRCUMULCHANGE).c_str(), &rs_hide_mmrcc);
        ImGui::Checkbox(GetLang(LANG_WINS).c_str(), &rs_hide_win);
        ImGui::Checkbox(GetLang(LANG_LOSSES).c_str(), &rs_hide_loss);
        ImGui::Checkbox(GetLang(LANG_STREAKS).c_str(), &rs_hide_streak);
        ImGui::Checkbox(GetLang(LANG_WINRATIO).c_str(), &rs_hide_winratio);
        ImGui::Checkbox(GetLang(LANG_WINPERCENTAGE).c_str(), &rs_hide_winpercentage);
        ImGui::Checkbox(GetLang(LANG_SCORE).c_str(), &rs_hide_score);
        ImGui::Checkbox(GetLang(LANG_SHOTS).c_str(), &rs_hide_shots);
        ImGui::Checkbox(GetLang(LANG_SAVES).c_str(), &rs_hide_saves);
        ImGui::Checkbox(GetLang(LANG_GOALS).c_str(), &rs_hide_goals);
        ImGui::Checkbox(GetLang(LANG_DROPSHOT).c_str(), &rs_hide_dropshot);
        ImGui::Checkbox(GetLang(LANG_KNOCKOUT).c_str(), &rs_hide_knockout);
        ImGui::Checkbox(GetLang(LANG_MISCS).c_str(), &rs_hide_miscs);
        ImGui::Checkbox(GetLang(LANG_ACCOLADES).c_str(), &rs_hide_accolades);
        ImGui::EndChild();

        if (select_all != rs_select_all_hide)
        {
            rs_select_all_hide = !rs_select_all_hide;

            rs_hide_games = rs_select_all_hide;
            rs_hide_gm = rs_select_all_hide;
            rs_hide_rank = rs_select_all_hide;
            rs_hide_div = rs_select_all_hide;
            rs_hide_mmr = rs_select_all_hide;
            rs_hide_mmrc = rs_select_all_hide;
            rs_hide_mmrcc = rs_select_all_hide;
            rs_hide_win = rs_select_all_hide;
            rs_hide_loss = rs_select_all_hide;
            rs_hide_streak = rs_select_all_hide;
            rs_hide_winratio = rs_select_all_hide;
            rs_hide_winpercentage = rs_select_all_hide;
            rs_hide_score = rs_select_all_hide;
            rs_hide_shots = rs_select_all_hide;
            rs_hide_saves = rs_select_all_hide;
            rs_hide_goals = rs_select_all_hide;
            rs_hide_dropshot = rs_select_all_hide;
            rs_hide_knockout = rs_select_all_hide;
            rs_hide_miscs = rs_select_all_hide;
            rs_hide_accolades = rs_select_all_hide;
        }

        /* Variable to use to animate images
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
        float fps = ImGui::GetIO().Framerate;
        ImGui::Text(("Framerate: " + std::to_string(fps)).c_str());
        */

        // Footer
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
        ImGui::Separator();

        ImGui::TextColored(((time_error || local_time.tm_sec % 2) ? ImVec4{ 0.04f, 0.52f, 0.89f, 1.f } : ImVec4{ 1.f, 1.f, 1.f, 0.5f }), GetLang(LANG_DONATE).c_str());
        if (ImGui::IsItemHovered())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                system("powershell -WindowStyle Hidden \"start https://www.paypal.com/paypalme/rocketstats\"");
        }
        ImGui::SameLine();
        ImGui::Text("|");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4{ 0.04f, 0.52f, 0.89f, 1.f }, "Discord");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                system("powershell -WindowStyle Hidden \"start https://discord.gg/weBCBE4\"");
        }
        ImGui::SameLine();
        text_size = ImGui::CalcTextSize(GetLang(LANG_DEVELOPERS).c_str());
        ImGui::SetCursorPosX((settings_size.x - text_size.x) / 2.f);
        ImGui::Text(GetLang(LANG_DEVELOPERS).c_str());
        text_size = ImGui::CalcTextSize(menu_version.c_str());
        ImGui::SameLine();
        ImGui::SetCursorPosX(settings_size.x - text_size.x - 7.f);
        ImGui::Text(menu_version.c_str());

        drawlist->PopClipRect();
    }
    else
    {
        ImGui::SetWindowFontScale(1.5f / (font ? 2.f : 1.f));
        ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), (GetLang(LANG_ERROR) + ": data/RocketStats").c_str());
        ImGui::SameLine();
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));
        ImGui::SetCursorPosX(settings_size.x - 80.f - 7.f);
        if (ImGui::Button(GetLang(LANG_ERROR_RELOAD).c_str(), { 80.f, 0.f }))
        {
            LoadImgs();
            LoadThemes();
            ChangeTheme(rs_theme);
            rs_logo = LoadImg("RocketStats_images/logo.png");
            rs_title = LoadImg("RocketStats_images/title.png");
        }
    }

    ImGui::End();

    if (!tooltip.empty())
    {
        ImGui::Begin((menu_title + "##Tooltip").c_str(), nullptr, (ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoFocusOnAppearing));
        ImGui::SetWindowFontScale(1.f / (font ? 2.f : 1.f));

        ImVec4 color;
        float padding = 8.f;
        ImVec2 mouse_pos = ImGui::GetIO().MousePos;
        ImDrawList* drawlist = ImGui::GetForegroundDrawList();
        ImVec2 text_size = ImGui::CalcTextSize(tooltip.c_str());
        ImVec2 tooltip_min = { (mouse_pos.x + 25.f), (mouse_pos.y + 2.f) };
        ImVec2 tooltip_max = { (tooltip_min.x + text_size.x + (2.f * padding)), (tooltip_min.y + text_size.y + (2.f * padding)) };

        color = ImGui::GetStyleColorVec4(ImGuiCol_FrameBg);
        drawlist->AddRectFilled(tooltip_min, tooltip_max, ImGui::ColorConvertFloat4ToU32({ color.x, color.x, color.x, 0.7f }));
        color = ImGui::GetStyleColorVec4(ImGuiCol_Border);
        drawlist->AddRect(tooltip_min, tooltip_max, ImGui::ColorConvertFloat4ToU32({ color.x, color.x, color.x, 0.4f }));
        color = ImGui::GetStyleColorVec4(ImGuiCol_Text);
        drawlist->AddText({ (tooltip_min.x + padding), (tooltip_min.y + padding) }, ImGui::ColorConvertFloat4ToU32({ color.x, color.x, color.x, 0.7f }), tooltip.c_str());

        ImGui::End();
    }

    if (menu_font)
        ImGui::PopFont();

    RefreshVars();
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
    return (settings_open || rs_recovery == RecoveryFlags_Files);
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
        }, 0.02f);
    }

    ToggleSettings("OnClose", ToggleFlags_Hide);
}
