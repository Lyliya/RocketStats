#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    void RocketStats::Render(CanvasWrapper canvas)
    {
        bool RS_disp_ig = cvarManager->getCvar("RS_disp_ig").getBoolValue();
        bool RS_hide_overlay_ig = cvarManager->getCvar("RS_hide_overlay_ig").getBoolValue();

        if (!RS_disp_ig || isGameStarted && !isGameEnded && RS_hide_overlay_ig)
            return;

        bool RS_Use_v1 = cvarManager->getCvar("RS_Use_v1").getBoolValue();
        bool RS_Use_v2 = cvarManager->getCvar("RS_Use_v2").getBoolValue();
        bool RS_session = cvarManager->getCvar("RS_session").getBoolValue();
        float RS_x_position = cvarManager->getCvar("RS_x_position").getFloatValue();
        float RS_y_position = cvarManager->getCvar("RS_y_position").getFloatValue();
        float RS_scale = cvarManager->getCvar("RS_scale").getFloatValue();
        Stats current = (RS_session == true) ? session : stats[currentPlaylist];

        if (RS_Use_v1)
        {
            std::vector<std::string> RS_values = {
                "RS_disp_gamemode",
                "RS_disp_rank",
                "RS_disp_mmr",
                "RS_disp_wins",
                "RS_disp_losses",
                "RS_disp_streak",
            };

            unsigned int size = 0;
            for (auto& it : RS_values)
            {
                bool tmp = cvarManager->getCvar(it).getBoolValue();
                if (tmp)
                    size += 1;
                if (it == "RS_disp_mmr")
                    size += 1;
            }

            // Draw box here
            Vector2 drawLoc = {
                int(canvas.GetSize().X * RS_x_position),
                int(canvas.GetSize().Y * RS_y_position) };
            Vector2 sizeBox = {
                int(175 * RS_scale),
                int((23 * size) * RS_scale) };
            canvas.SetPosition(drawLoc);

            // Set background color
            canvas.SetColor(LinearColor{ 0, 0, 0, 150 });
            canvas.FillBox(sizeBox);

            // Draw text
            Vector2 textPos = { int(drawLoc.X + 10), int(drawLoc.Y + 10) };
            for (auto& it : RS_values)
            {
                bool tmp = cvarManager->getCvar(it).getBoolValue();

                if (tmp)
                {
                    // Set the position
                    canvas.SetPosition(textPos);

                    // Set Color and Text for the value
                    if (it == "RS_disp_gamemode")
                    {
                        canvas.SetColor(LinearColor{ 180, 180, 180, 255 });
                        canvas.DrawString(GetPlaylistName(currentPlaylist), RS_scale, RS_scale);
                    }
                    else if (it == "RS_disp_rank")
                    {
                        std::string tmpRank = currentRank;
                        if (currentTier >= rank_nb)
                            currentTier = 0;
                        replaceAll(tmpRank, "_", " ");
                        canvas.SetColor(LinearColor{ 180, 180, 180, 255 });
                        if (currentDivision == "")
                            canvas.DrawString(tmpRank, RS_scale, RS_scale);
                        else
                            canvas.DrawString(tmpRank + " " + currentDivision, RS_scale, RS_scale);
                    }
                    else if (it == "RS_disp_mmr")
                    {
                        canvas.SetColor(LinearColor{ 180, 180, 180, 255 });
                        std::string mmr = to_string_with_precision(current.myMMR, 2);
                        canvas.DrawString("MMR : " + mmr, RS_scale, RS_scale);

                        textPos.Y += int(20 * RS_scale);
                        canvas.SetPosition(textPos);

                        std::string mmrchange = to_string_with_precision(current.MMRChange, 2);
                        if (current.MMRChange >= 0)
                        {
                            canvas.SetColor(LinearColor{ 30, 224, 24, 255 });
                            canvas.DrawString("MMRChange : +" + mmrchange, RS_scale, RS_scale);
                        }
                        else
                        {
                            canvas.SetColor(LinearColor{ 224, 24, 24, 255 });
                            canvas.DrawString("MMRChange : " + mmrchange, RS_scale, RS_scale);
                        }
                    }
                    else if (it == "RS_disp_wins")
                    {
                        canvas.SetColor(LinearColor{ 30, 224, 24, 255 });
                        canvas.DrawString("Win : " + std::to_string(current.win), RS_scale, RS_scale);
                    }
                    else if (it == "RS_disp_losses")
                    {
                        canvas.SetColor(LinearColor{ 224, 24, 24, 255 });
                        canvas.DrawString("Losses : " + std::to_string(current.losses), RS_scale, RS_scale);
                    }
                    else if (it == "RS_disp_streak")
                    {
                        if (current.streak >= 0)
                        {
                            canvas.SetColor(LinearColor{ 30, 224, 24, 255 });
                            canvas.DrawString("Streak : +" + std::to_string(current.streak), RS_scale, RS_scale);
                        }
                        else
                        {
                            canvas.SetColor(LinearColor{ 224, 24, 24, 255 });
                            canvas.DrawString("Streak : " + std::to_string(current.streak), RS_scale, RS_scale);
                        }
                    }
                    // Increase Y position
                    textPos.Y += int(20 * RS_scale);
                }
            }
        }
        else if (RS_Use_v2)
        {
            auto canSize = canvas.GetSize();
            Vector2 imagePos = { int(RS_x_position * canSize.X), int(RS_y_position * canSize.Y) };
            Vector2 textPos_tmp = imagePos;

            textPos_tmp.X += int(50 * RS_scale);
            textPos_tmp.Y += int(10 * RS_scale);

            // Display Rank
            if (cvarManager->getCvar("RS_disp_rank").getBoolValue())
            {
                DisplayRank(canvas, imagePos, textPos_tmp, RS_scale, true);
                imagePos.Y += int(50 * RS_scale);
                textPos_tmp.Y += int(50 * RS_scale);
            }

            // Display MMR
            if (cvarManager->getCvar("RS_disp_mmr").getBoolValue())
            {
                DisplayMMR(canvas, imagePos, textPos_tmp, current, RS_scale, true);
                imagePos.Y += int(50 * RS_scale);
                textPos_tmp.Y += int(50 * RS_scale);
            }

            // Display Win
            if (cvarManager->getCvar("RS_disp_wins").getBoolValue())
            {
                DisplayWins(canvas, imagePos, textPos_tmp, current, RS_scale);
                imagePos.Y += int(50 * RS_scale);
                textPos_tmp.Y += int(50 * RS_scale);
            }

            // Display Loose
            if (cvarManager->getCvar("RS_disp_losses").getBoolValue())
            {
                DisplayLoose(canvas, imagePos, textPos_tmp, current, RS_scale);
            }

            // Display Streak
            if (cvarManager->getCvar("RS_disp_streak").getBoolValue())
            {
                textPos_tmp.X += int(75 * RS_scale);
                textPos_tmp.Y -= int(25 * RS_scale);
                DisplayStreak(canvas, imagePos, textPos_tmp, current, RS_scale, false);
            }
        }
        else
        {
            const bool displayRank = cvarManager->getCvar("RS_disp_rank").getBoolValue();
            const bool displayMMR = cvarManager->getCvar("RS_disp_mmr").getBoolValue();
            const bool displayWins = cvarManager->getCvar("RS_disp_wins").getBoolValue();
            const bool displayLosses = cvarManager->getCvar("RS_disp_losses").getBoolValue();
            const bool displayStreak = cvarManager->getCvar("RS_disp_streak").getBoolValue();
            int size = 0;

            if (displayRank)
                size += 70;
            if (displayMMR)
                size += 250;
            if (displayWins)
                size += 110;
            if (displayLosses)
                size += 110;
            if (displayStreak)
                size += 110;
            if (displayWins || displayLosses || displayStreak)
                size += 50;

            auto canSize = canvas.GetSize();

            // Draw box here
            Vector2 backgroundPos = { int(RS_x_position * canSize.X), int(RS_y_position * canSize.Y) };
            Vector2 sizeBox = {
                int(size * RS_scale),
                int(50 * RS_scale) };
            canvas.SetPosition(backgroundPos);
            canvas.SetColor(LinearColor{ 0, 0, 0, 255 });
            canvas.FillBox(sizeBox);

            Vector2 imagePos = backgroundPos;
            imagePos.X += int(30 * RS_scale);

            Vector2 textPos_tmp = imagePos;
            textPos_tmp.Y += int(10 * RS_scale);

            // Display Rank
            if (displayRank)
            {
                DisplayRank(canvas, imagePos, textPos_tmp, RS_scale, false);
                imagePos.X += int(70 * RS_scale);
                textPos_tmp.X += int(70 * RS_scale);
            }

            // Display MMR
            if (displayMMR)
            {
                DisplayMMR(canvas, imagePos, textPos_tmp, current, RS_scale, false);
                imagePos.X += int(250 * RS_scale);
                textPos_tmp.X += int(250 * RS_scale);
            }

            // Adjust text postition for the rest with images
            textPos_tmp.X += int(70 * RS_scale);

            // Display Win
            if (displayWins)
            {
                DisplayWins(canvas, imagePos, textPos_tmp, current, RS_scale);
                imagePos.X += int(110 * RS_scale);
                textPos_tmp.X += int(110 * RS_scale);
            }

            // Display Loose
            if (displayLosses)
            {
                DisplayLoose(canvas, imagePos, textPos_tmp, current, RS_scale);
                imagePos.X += int(110 * RS_scale);
                textPos_tmp.X += int(110 * RS_scale);
            }

            // Display Streak
            if (displayStreak)
            {
                DisplayStreak(canvas, imagePos, textPos_tmp, current, RS_scale, true);
            }
        }
    }
}