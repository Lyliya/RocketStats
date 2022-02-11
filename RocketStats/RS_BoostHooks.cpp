#include "pch.h"
#include "RocketStats.h"

namespace NS_RS {
    void RocketStats::OnBoostStart(std::string eventName)
    {
        cvarManager->log("boostStart");
        // Check if boost enabled in options
        bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
        if (!IsBoostEnabled || gameWrapper->IsInReplay() || isBoosting)
            return;

        CarWrapper cWrap = gameWrapper->GetLocalCar();

        if (!cWrap.IsNull())
        {
            BoostWrapper bWrap = cWrap.GetBoostComponent();

            if (!bWrap.IsNull() && bWrap.GetbActive() == 1 && !isBoosting)
            {
                isBoosting = true;
                WriteInFile("RocketStats_images/BoostState.txt", std::to_string(1));
            }
        }

        return;
    }

    void RocketStats::OnBoostEnd(std::string eventName)
    {
        cvarManager->log("boostEnd");
        // Check if boost enabled in options
        bool IsBoostEnabled = cvarManager->getCvar("RocketStats_stop_boost").getBoolValue();
        if (!IsBoostEnabled || gameWrapper->IsInReplay() || !isBoosting)
            return;

        CarWrapper cWrap = gameWrapper->GetLocalCar();

        if (!cWrap.IsNull())
        {
            BoostWrapper bWrap = cWrap.GetBoostComponent();

            if (!bWrap.IsNull() && bWrap.GetbActive() == 0 && isBoosting)
            {
                isBoosting = false;
                WriteInFile("RocketStats_images/BoostState.txt", std::to_string(0));
            }
        }
        return;
    }
}