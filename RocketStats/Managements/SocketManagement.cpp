#include "../RocketStats.h"

void RocketStats::SocketServer()
{
    m_server.init_asio();

    m_server.set_open_handler(std::bind(&RocketStats::SocketOpen, this, std::placeholders::_1));
    m_server.set_close_handler(std::bind(&RocketStats::SocketClose, this, std::placeholders::_1));
    m_server.set_message_handler(std::bind(&RocketStats::SocketMessage, this, std::placeholders::_1, std::placeholders::_2));

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

void RocketStats::SocketMessage(connection_hdl hdl, server::message_ptr msg)
{
    for (connection_hdl it : m_connections)
        m_server.send(it, msg);
}

void RocketStats::SocketSend(std::string name, json data, std::string type)
{
    if (!name.size())
        return;

    json obj = json::object();

    obj["name"] = name;
    obj["type"] = (type.size() ? type : "Default");
    obj["data"] = data;

    obj["states"] = json::object();
    obj["states"]["is_in_game"] = is_in_game;
    obj["states"]["is_in_menu"] = is_in_menu;
    obj["states"]["is_in_freeplay"] = is_in_freeplay;
    obj["states"]["is_in_scoreboard"] = is_in_scoreboard;
    obj["states"]["is_online_game"] = is_online_game;
    obj["states"]["is_offline_game"] = is_offline_game;

    SocketBroadcast(obj);
}

void RocketStats::SocketBroadcast(json data)
{
    for (connection_hdl it : m_connections)
        m_server.send(it, data.dump(), websocketpp::frame::opcode::text);
}