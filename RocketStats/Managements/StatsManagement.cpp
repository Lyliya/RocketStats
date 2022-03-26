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
            ++stats[current.playlist].demo;
            ++always_gm[current.playlist].demo;
            SetRefresh(1);

            if (rs_file_demo)
                WriteInFile("RocketStats_Demolition.txt", std::to_string(0));
        }

        bool death = isPrimaryPlayer(victim);
        if (death && current.playlist)
        {
            ++session.death;
            ++stats[current.playlist].death;
            ++always_gm[current.playlist].death;
            SetRefresh(1);

            if (rs_file_death)
                WriteInFile("RocketStats_Death.txt", std::to_string(0));
        }
    }
}

void RocketStats::InitRank()
{
    int tier = current.tier;
    int playlist = current.playlist;

    current = t_current();

    last_rank = "norank";
    current.tier = tier;
    current.playlist = playlist;
}

void RocketStats::MajRank(bool isRanked, float _currentMMR, SkillRank playerRank)
{
    current.tier = playerRank.Tier;

    if (isRanked)
    {
        if (current.playlist != 34 && playerRank.MatchesPlayed < 10)
        {
            current.rank = "Placement: " + std::to_string(playerRank.MatchesPlayed) + "/10";
            current.division = "";
        }
        else
        {
            current.rank = GetRank(playerRank.Tier);
            current.division = "Div. " + std::to_string(playerRank.Division + 1);

            if (rs_file_div)
                WriteInFile("RocketStats_Div.txt", current.division);
        }

        if (rs_file_rank && current.rank != last_rank)
            WriteInFile("RocketStats_Rank.txt", current.rank);
    }
    else
    {
        current.rank = GetPlaylistName(current.playlist);
        current.division = "";

        if (rs_file_rank)
            WriteInFile("RocketStats_Rank.txt", current.rank);
    }

    SetRefresh(1);
}

void RocketStats::UpdateMMR(UniqueIDWrapper id)
{
    cvarManager->log("===== UpdateMMR =====");
    /*
    if (id.GetIdString() != gameWrapper->GetUniqueID().GetIdString()) {
        cvarManager->log("not the user");
        return;
    }
    cvarManager->log("user match");
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

        always.MMRChange += MMRChange;
        stats[current.playlist].MMRChange = MMRChange;
        always_gm[current.playlist].MMRChange = MMRChange;

        always.MMRCumulChange += MMRChange;
        for (auto it = playlist_name.begin(); it != playlist_name.end(); ++it)
        {
            stats[it->first].MMRCumulChange += MMRChange;
            always_gm[it->first].MMRCumulChange += MMRChange;
        }
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
    WriteMMRCumulChange();

    SetRefresh(1);
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
        tmp.MMRChange += stats[it->first].MMRChange;
        tmp.MMRCumulChange += stats[it->first].MMRChange;
        tmp.win += stats[it->first].win;
        tmp.loss += stats[it->first].loss;
        tmp.demo += stats[it->first].demo;
        tmp.death += stats[it->first].death;
    }

    session.myMMR = stats[current.playlist].myMMR;
    session.MMRChange = tmp.MMRChange;
    session.MMRCumulChange = tmp.MMRCumulChange;
    session.win = tmp.win;
    session.loss = tmp.loss;
    session.demo = tmp.demo;
    session.death = tmp.death;
    session.isInit = true;

    always.myMMR = session.myMMR;
    always.MMRChange = session.MMRChange;
    always.isInit = true;

    SetRefresh(1);
}

void RocketStats::ResetStats()
{
    InitStats();

    WriteConfig();
    ResetFiles();

    InitRank();
    SetRefresh(1);
}
