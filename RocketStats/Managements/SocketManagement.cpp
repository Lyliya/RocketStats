#include "../RocketStats.h"

void RocketStats::SocketServer()
{
    m_server.init_asio();

    m_server.set_open_handler(std::bind(&RocketStats::SocketOpen, this, std::placeholders::_1));
    m_server.set_close_handler(std::bind(&RocketStats::SocketClose, this, std::placeholders::_1));
    m_server.set_message_handler(std::bind(&RocketStats::SocketReceive, this, std::placeholders::_1, std::placeholders::_2));

    m_server.listen(8085);
    m_server.start_accept();
    m_server.run();
}

void RocketStats::SocketOpen(connection_hdl hdl)
{
    m_connections.insert(hdl);
    SocketSend("State", "Connected");
}

void RocketStats::SocketClose(connection_hdl hdl)
{
    m_connections.erase(hdl);
}

void RocketStats::SocketReceive(connection_hdl hdl, server::message_ptr msg)
{
    std::string message = Utils::tolower(msg->get_payload());
    if (message == "request")
        m_server.send(hdl, SocketData("GameState", GetGameState(), "Request").dump(), websocketpp::frame::opcode::text);
}

json RocketStats::SocketData(std::string name, json data, std::string type)
{
    json obj = json::object();

    obj["name"] = name;
    obj["type"] = (type.size() ? type : "Default");
    obj["data"] = data;

    obj["states"] = json::object();
    obj["states"]["IsInGame"] = is_in_game;
    obj["states"]["IsInMenu"] = is_in_menu;
    obj["states"]["IsInFreeplay"] = is_in_freeplay;
    obj["states"]["IsInScoreboard"] = is_in_scoreboard;
    obj["states"]["IsOnlineGame"] = is_online_game;
    obj["states"]["IsOfflineGame"] = is_offline_game;

    return obj;
}

void RocketStats::SocketSend(std::string name, json data, std::string type)
{
    if (!name.size())
        return;

    SocketBroadcast(SocketData(name, data, type));
}

void RocketStats::SocketBroadcast(json data)
{
    for (connection_hdl it : m_connections)
        m_server.send(it, data.dump(), websocketpp::frame::opcode::text);
}