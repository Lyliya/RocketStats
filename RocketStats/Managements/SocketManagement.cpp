#include "../RocketStats.h"

void RocketStats::InitWebSocket()
{
    try {
        if (m_server.is_listening()) {
            cvarManager->log("WebSocket already running!");
            return;
        }

        cvarManager->log("Starting WebSocket");

#ifdef _DEBUG
        m_server.set_access_channels(websocketpp::log::alevel::all);

        static std::ofstream ws_log("RS_ws.log");
        static std::ofstream ws_err_log("RS_ws_err.log");

        m_server.get_alog().set_ostream(&ws_log);
        m_server.get_alog().write(websocketpp::log::alevel::app, "RocketStats::InitWebSocket");

        m_server.get_elog().set_ostream(&ws_err_log);
        m_server.get_elog().write(websocketpp::log::alevel::app, "RocketStats::InitWebSocket err_log");
#endif // _DEBUG

        m_server.init_asio();

        m_server.set_open_handler(std::bind(&RocketStats::SocketOpen, this, std::placeholders::_1));
        m_server.set_close_handler(std::bind(&RocketStats::SocketClose, this, std::placeholders::_1));
        m_server.set_message_handler(std::bind(&RocketStats::SocketReceive, this, std::placeholders::_1, std::placeholders::_2));

        m_server.reset();

        m_server.listen(settings.ws_server.port);
        m_server.start_accept();
        m_server.run();
    }
    catch (websocketpp::exception const& e) {
        cvarManager->log(e.code().message());
        cvarManager->log(std::to_string(e.code().value()));
        cvarManager->log(e.what());
    }
    catch (...) {
        cvarManager->log("Other exception");
    }
}

void RocketStats::ShutdownWebSocket() {
    if (m_server.is_listening()) {
        m_server.stop_listening();

        SocketSend("State", "Disconnected");
        for (connection_hdl con : m_connections) {
            server::connection_ptr con_ptr = m_server.get_con_from_hdl(con);
            if (con_ptr->get_state() == websocketpp::session::state::open) {
                con_ptr->close(websocketpp::close::status::normal, "Shutting down RocketStats");
                con_ptr->terminate(make_error_code(websocketpp::error::value::general));
            }
        }
        m_server.stop();

    }

    if (server_thread.joinable()) {
        server_thread.join();
    }
}

void RocketStats::SocketOpen(connection_hdl hdl)
{
    m_connections.insert(hdl);
    rooms_aggregated.push_back(hdl);

    SocketSend("State", "Connected");
    gameWrapper->Execute([&](GameWrapper* gameWrapper) {
        SendGameState("Initialization");
    });
}

void RocketStats::SocketClose(connection_hdl hdl)
{
    m_connections.erase(hdl);
    SocketUnsubscribe(hdl, {}, true);
}

void RocketStats::SocketReceive(connection_hdl hdl, server::message_ptr msg)
{
    WebSocketCommand op = SocketCommandParse(msg->get_payload());

    if (op.command == "request")
        m_server.send(hdl, SocketData("GameState", GetGameState(), "Request").dump(), websocketpp::frame::opcode::text);
    else if (op.command == "subscribe" && op.domains.size() && op.domains[0] == "rooms")
        m_server.send(hdl, SocketData("Subscribed", SocketSubscribe(hdl, op.payload["rooms"])).dump(), websocketpp::frame::opcode::text);
}

WebSocketCommand RocketStats::SocketCommandParse(std::string message)
{
    size_t pos = message.find(" ");
    std::vector<std::string> tmp = Utils::Split(message.substr(0, pos), ':');
    std::string cmd = tmp.front();
    tmp.erase(tmp.begin());

    json payload;
    try
    {
        payload = json::parse(message.substr(pos + 1));
    }
    catch (json::parse_error& e)
    {
        cvarManager->log("Config: bad JSON -> " + std::string(e.what()));
    }

    return WebSocketCommand{
        cmd,
        tmp,
        payload
    };
}

json RocketStats::SocketSubscribe(connection_hdl hdl, json rooms)
{
    auto it = std::find(rooms_aggregated.begin(), rooms_aggregated.end(), hdl);
    if (it != rooms_aggregated.end())
        rooms_aggregated.erase(it);

    json subscribed = json::array();
    if (rooms.is_array())
    {
        for (const auto& room : rooms)
        {
            auto it = std::find(settings.ws_server.rooms_whitelist.begin(), settings.ws_server.rooms_whitelist.end(), std::string(room));
            if (it != settings.ws_server.rooms_whitelist.end())
            {
                if (ws_rooms.find(room) == ws_rooms.end())
                    ws_rooms[room] = {};

                if (std::find(ws_rooms[room].begin(), ws_rooms[room].end(), hdl) == ws_rooms[room].end())
                    ws_rooms[room].push_back(hdl);

                subscribed.push_back(room);
            }
        }
    }

    return subscribed;
}

json RocketStats::SocketUnsubscribe(connection_hdl hdl, json rooms, bool all)
{
    auto it = std::find(rooms_aggregated.begin(), rooms_aggregated.end(), hdl);
    if (it != rooms_aggregated.end())
        rooms_aggregated.erase(it);

    json unsubscribed = json::array();
    for (const auto& [key, room] : ws_rooms)
    {
        if (all || (rooms.is_array() && std::find(rooms.begin(), rooms.end(), key) != rooms.end()))
        {
            auto it = std::find(room.begin(), room.end(), hdl);
            if (it != room.end())
            {
                ws_rooms[key].erase(it);

                unsubscribed.push_back(key);
            }
        }
    }

    if (rooms.is_array())
    {
        for (const auto& room : rooms)
        {
            if (ws_rooms.find(room) != ws_rooms.end())
            {
                auto it = std::find(ws_rooms[room].begin(), ws_rooms[room].end(), hdl);
                if (it != ws_rooms[room].end())
                {
                    ws_rooms[room].erase(it);

                    unsubscribed.push_back(room);
                }
            }
        }
    }

    return unsubscribed;
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