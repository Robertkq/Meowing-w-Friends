#ifndef KQMWFSERVER
#define KQMWFSERVER

#include "../Common/common.h"

namespace kq
{
    class server : public server_interface<msgids>
    {
    public:
        server(uint16_t port, uint64_t(*func)(uint64_t));

        bool OnClientConnect(connection<msgids>* client) override;
        void OnClientDisconnect(connection<msgids>* client) override;
        void OnClientValidated(connection<msgids>* client) override;
        void OnClientUnvalidated(connection<msgids>* client) override;
        void OnMessage(connection<msgids>* client, message<msgids>& msg) override;
    private:

    };
}

#endif