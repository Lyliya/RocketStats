#include "../RocketStats.h"

bool RocketStats::isPrimaryPlayer(PriWrapper PRI)
{
    bool check = !gameWrapper->IsInOnlineGame();
    ServerWrapper server = gameWrapper->GetOnlineGame();
    PlayerControllerWrapper player = server.GetLocalPrimaryPlayer();
    PriWrapper playerPRI = player.GetPRI();

    check = (check || PRI.IsNull()); // null PRI
    check = (check || server.IsNull()); // null server

    check = (check || player.IsNull()); // null controller
    check = (check || playerPRI.IsNull()); // null player PRI

    check = (check || PRI.GetUniqueIdWrapper().GetUID() != playerPRI.GetUniqueIdWrapper().GetUID());

    return !check;
}

void RocketStats::onStatEvent(ServerWrapper caller, void* params)
{
    StatEventParams* pstats = (StatEventParams*)params;
    if (!gameWrapper->IsInOnlineGame())
        return;

    StatEventWrapper event = StatEventWrapper(pstats->StatEvent);

    std::string name = event.GetEventName(); // error
    //cvarManager->log("onStatEvent e:" + name + "=" + std::to_string(event.GetPoints()));
}

void RocketStats::onStatTickerMessage(ServerWrapper caller, void* params)
{
    StatTickerParams* pstats = (StatTickerParams*)params;
    if (!gameWrapper->IsInOnlineGame())
        return;

    PriWrapper receiver = PriWrapper(pstats->Receiver);
    PriWrapper victim = PriWrapper(pstats->Victim);
    StatEventWrapper event = StatEventWrapper(pstats->StatEvent);

    std::string name = event.GetEventName();
    //cvarManager->log("onStatTickerMessage receiver:" + std::string(isPrimaryPlayer(receiver) ? "1" : "0") + " victim:" + std::string(isPrimaryPlayer(victim) ? "1" : "0") + " e:" + name + "=" + std::to_string(event.GetPoints()));
    if (name == "Demolish" && receiver && victim)
    {
        bool demo = isPrimaryPlayer(receiver);
        if (demo && current.playlist)
        {
            ++session.demo;
            ++session.demoCumul;
            ++stats[current.playlist].demo;
            ++stats[current.playlist].demoCumul;
            ++always_gm[current.playlist].demo;
            ++always_gm[current.playlist].demoCumul;
            SetRefresh(RefreshFlags_Refresh);

            if (rs_file_demo)
                WriteInFile("RocketStats_Demolition.txt", std::to_string(0));
        }

        bool death = isPrimaryPlayer(victim);
        if (death && current.playlist)
        {
            ++session.death;
            ++session.deathCumul;
            ++stats[current.playlist].death;
            ++stats[current.playlist].deathCumul;
            ++always_gm[current.playlist].death;
            ++always_gm[current.playlist].deathCumul;
            SetRefresh(RefreshFlags_Refresh);

            if (rs_file_death)
                WriteInFile("RocketStats_Death.txt", std::to_string(0));
        }
    }
}

void RocketStats::InitRank()
{
    int tier = current.tier;
    bool ranked = current.ranked;
    int playlist = current.playlist;

    last_rank = "";
    last_division = "";
    current = t_current();

    current.tier = tier;
    current.ranked = ranked;
    current.playlist = playlist;
}

void RocketStats::MajRank(bool isRanked, float _currentMMR, SkillRank playerRank)
{
    current.tier = playerRank.Tier;
    current.ranked = isRanked;

    if (isRanked)
    {
        current.preview_rank = GetRank(playerRank.Tier);
        current.preview_division = "Div. " + std::to_string(playerRank.Division + 1);

        if (current.playlist != 34 && playerRank.MatchesPlayed < 10)
        {
            current.rank = "Placement: " + std::to_string(playerRank.MatchesPlayed) + "/10";
            current.division = "";
        }
        else
        {
            current.rank = current.preview_rank;
            current.division = current.preview_division;
        }
    }
    else
    {
        current.rank = GetPlaylistName(current.playlist);
        current.division = "";

        current.preview_rank = current.rank;
        current.preview_division = current.division;
    }

    WriteRank();
    WriteDiv();

    SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::UpdateMMR(UniqueIDWrapper id)
{
    cvarManager->log("===== UpdateMMR =====");
    /*
    if (id.GetIdString() != gameWrapper->GetUniqueID().GetIdString()) {
        cvarManager->log("Not the user");
        return;
    }
    cvarManager->log("User match");
    */

    if (current.playlist == 0)
    {
        cvarManager->log("Invalid playlist id. Have you just opened the game ?");
        return;
    }

    MMRWrapper mmrw = gameWrapper->GetMMRWrapper();
    float mmr = mmrw.GetPlayerMMR(id, current.playlist);
    SkillRank playerRank = mmrw.GetPlayerRank(id, current.playlist);

    if (stats[current.playlist].isInit)
    {
        float MMRChange = (mmr - stats[current.playlist].myMMR);

        always.MMRChange = MMRChange;
        session.MMRChange = MMRChange;
        stats[current.playlist].MMRChange = MMRChange;
        always_gm[current.playlist].MMRChange = MMRChange;

        always.MMRCumulChange += MMRChange;
        session.MMRCumulChange += MMRChange;
        stats[current.playlist].MMRCumulChange += MMRChange;
        always_gm[current.playlist].MMRCumulChange += MMRChange;
    }
    else
        stats[current.playlist].isInit = true;

    always.myMMR = mmr;
    session.myMMR = mmr;
    stats[current.playlist].myMMR = mmr;
    always_gm[current.playlist].myMMR = mmr;

    MajRank(mmrw.IsRanked(current.playlist), stats[current.playlist].myMMR, playerRank);
    SessionStats();
    WriteMMR();
    WriteMMRChange();

    SetRefresh(RefreshFlags_Refresh);
    cvarManager->log("===== !UpdateMMR =====");
}

void RocketStats::InitStats()
{
    session = Stats();
    for (auto& kv : stats)
        kv.second = Stats();

    always = Stats();
    always.isInit = true;
    for (auto& kv : always_gm)
    {
        kv.second = Stats();
        kv.second.isInit = true;
    }
}

void RocketStats::SessionStats()
{
    Stats tmp;

    for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
    {
        tmp.MMRCumulChange += stats[it->first].MMRChange;
        tmp.win += stats[it->first].win;
        tmp.loss += stats[it->first].loss;
        tmp.demo += stats[it->first].demo;
        tmp.demoCumul += stats[it->first].demo;
        tmp.death += stats[it->first].death;
        tmp.deathCumul += stats[it->first].death;
    }

    session.myMMR = stats[current.playlist].myMMR;
    session.MMRChange = stats[current.playlist].MMRChange;
    session.win = tmp.win;
    session.loss = tmp.loss;
    session.demo = tmp.demo;
    session.demoCumul = tmp.demoCumul;
    session.death = tmp.death;
    session.deathCumul = tmp.deathCumul;
    session.isInit = true;

    always.myMMR = session.myMMR;
    always.MMRChange = session.MMRChange;
    always.isInit = true;

    SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::ResetStats()
{
    InitStats();

    WriteConfig();
    ResetFiles();

    InitRank();
    SetRefresh(RefreshFlags_Refresh);
}

void RocketStats::ResetBasicStats()
{
    current.demo = 0;
    current.death = 0;
}
