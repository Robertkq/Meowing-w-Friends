#include "server.h"

namespace kq
{
    server::server(uint16_t port, uint64_t(*func)(uint64_t))
        : server_interface(port, func)
    {

    }

    bool server::OnClientConnect(connection<msgids>* client)
    {
        return true;
    }

    void server::OnClientDisconnect(connection<msgids>* client)
    {

    }

    void server::OnClientValidated(connection<msgids>* client) 
    {

    }

    void server::OnClientUnvalidated(connection<msgids>* client) 
    {

    }

    void server::OnMessage(connection<msgids>* client, message<msgids>& msg)
    {

    }
}