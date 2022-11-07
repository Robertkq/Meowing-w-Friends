#include "server.h"

namespace kq
{
    server::server(uint16_t port, uint64_t(*func)(uint64_t))
        : server_interface(port, func)
    {
       
    }

    bool server::OnClientConnect(connection<msgids>* client)
    {
        std::cout << "New connection: " << client->getIP() << '\n';
        return true;
    }

    void server::OnClientDisconnect(connection<msgids>* client)
    {
        std::cout << "Disconnection: " << client->getIP() << '\n';
    }

    void server::OnClientValidated(connection<msgids>* client) 
    {
        std::cout << "Validated: " << client->getIP() << '\n';
    }

    void server::OnClientUnvalidated(connection<msgids>* client) 
    {
        std::cout << "Unvalidated: " << client->getIP() << '\n';
    }

    void server::OnMessage(connection<msgids>* client, message<msgids>& msg)
    {

    }
}