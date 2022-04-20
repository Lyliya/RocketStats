#include "../RocketStats.h"

void RocketStats::OnBoostStart(std::string eventName)
{
    // Check if boost enabled in options
    if (!rs_file_boost || gameWrapper->IsInReplay() || is_boosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        // Check that the boosting car is ours
        if (!bWrap.IsNull() && bWrap.GetbActive() == 1 && !is_boosting)
        {
            is_boosting = true;
            //SetRefresh(RefreshFlags_Refresh);
            VarBoost(true, false, false, true);
        }
    }
}

void RocketStats::OnBoostEnd(std::string eventName)
{
    // Check if boost enabled in options
    if (!rs_file_boost || gameWrapper->IsInReplay() || !is_boosting)
        return;

    CarWrapper cWrap = gameWrapper->GetLocalCar();

    if (!cWrap.IsNull())
    {
        BoostWrapper bWrap = cWrap.GetBoostComponent();

        // Check that the boosting car is ours
        if (!bWrap.IsNull() && bWrap.GetbActive() == 0 && is_boosting)
        {
            is_boosting = false;
            //SetRefresh(RefreshFlags_Refresh);
            VarBoost(true, false, false, false);
        }
    }
}

int RocketStats::GetBoostAmount()
{
    CarWrapper me = gameWrapper->GetLocalCar();
    if (me.IsNull())
        return -1;

    BoostWrapper boost = me.GetBoostComponent();
    if (boost.IsNull())
        return -1;

    return int(boost.GetCurrentBoostAmount() * 100.f);
}

// Act as toggle
// void RocketStats::StopBoost() {}