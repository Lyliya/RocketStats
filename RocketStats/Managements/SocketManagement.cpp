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

        m_server.listen(8085);
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
    SocketSend("State", "Connected");
    gameWrapper->Execute([&](GameWrapper* gameWrapper) {
        SendGameState("Initialization");
    });
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