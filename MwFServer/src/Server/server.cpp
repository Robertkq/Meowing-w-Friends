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
        static uint32_t id = 1;
        kq::message<msgids> msg(msgids::AssignID);
        msg << id++;
        MessageClient(client, msg);
    }

    void server::OnClientUnvalidated(connection<msgids>* client) 
    {
        std::cout << "Unvalidated: " << client->getIP() << '\n';
    }

    void server::OnMessage(connection<msgids>* client, message<msgids>& msg)
    {
        switch (msg.getID())
        {
        case(msgids::UpdatePosition):
        {
            auto& response = msg; // alias
            // forward the updated position
            MessageAllClients(client, response);
            break;
        }
        case(msgids::RequestPositions):
        {
            auto& response = msg; // alias
            MessageAllClients(client, response);
            break;
        }
        case(msgids::RequestAnswer):
        {
            auto& reponse = msg; // alias
            // This is inneficient, O(n^2), should be O(n)
            MessageAllClients(client, msg);
        }
        }
    }
}