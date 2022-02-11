#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    void RocketStats::DisplayRank(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, float scale, bool showText)
    {
        if (currentTier >= rank_nb)
        {
            currentTier = 0;
        }
        std::shared_ptr<ImageWrapper> image = rank[currentTier].image;

        canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
        canvas.SetPosition(imagePos);
        if (image->IsLoadedForCanvas())
            canvas.DrawTexture(image.get(), 0.5f * scale);

        if (showText)
        {
            std::string tmpRank = currentRank;
            replaceAll(tmpRank, "_", " ");
            canvas.SetPosition(textPos_tmp);
            if (currentDivision == "")
                canvas.DrawString(tmpRank, 2.0f * scale, 2.0f * scale);
            else
                canvas.DrawString(tmpRank + " " + currentDivision, 2.0f * scale, 2.0f * scale);
        }
    }
    void RocketStats::DisplayMMR(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale, bool showImage)
    {
        std::string mmr = to_string_with_precision(current.myMMR, 2);
        std::string change = to_string_with_precision(current.MMRChange, 2);

        if (showImage)
        {
            canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
            canvas.SetPosition(imagePos);
            if (crown->IsLoadedForCanvas())
                canvas.DrawTexture(crown.get(), 0.5f * scale);
        }

        canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
        canvas.SetPosition(textPos_tmp);
        if (current.MMRChange > 0)
            change = "+" + change;
        canvas.DrawString(mmr + " (" + change + ")", 2.0f * scale, 2.0f * scale);
    }
    void RocketStats::DisplayWins(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
    {
        canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
        canvas.SetPosition(imagePos);
        if (win->IsLoadedForCanvas())
            canvas.DrawTexture(win.get(), 0.5f * scale);

        canvas.SetColor(LinearColor{ 0, 255, 0, 255 });
        canvas.SetPosition(textPos_tmp);
        canvas.DrawString(std::to_string(current.win), 2.0f * scale, 2.0f * scale);
    }
    void RocketStats::DisplayLoose(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale)
    {
        canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
        canvas.SetPosition(imagePos);
        if (loose->IsLoadedForCanvas())
            canvas.DrawTexture(loose.get(), 0.5f * scale);

        canvas.SetColor(LinearColor{ 255, 0, 0, 255 });
        canvas.SetPosition(textPos_tmp);
        canvas.DrawString(std::to_string(current.losses), 2.0f * scale, 2.0f * scale);
    }
    void RocketStats::DisplayStreak(CanvasWrapper canvas, Vector2 imagePos, Vector2 textPos_tmp, Stats current, float scale, bool showImage)
    {
        if (showImage)
        {
            canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
            canvas.SetPosition(imagePos);
            if (streak->IsLoadedForCanvas())
                canvas.DrawTexture(streak.get(), 0.5f * scale);
        }

        canvas.SetColor(LinearColor{ 255, 255, 255, 255 });
        canvas.SetPosition(textPos_tmp);

        if (current.streak < 0)
            canvas.SetColor(LinearColor{ 255, 0, 0, 255 });
        else
            canvas.SetColor(LinearColor{ 0, 255, 0, 255 });

        std::string streak = std::to_string(current.streak);
        if (current.streak > 0)
            streak = "+" + streak;

        canvas.DrawString(streak, 2.0f * scale, 2.0f * scale);
    }
}