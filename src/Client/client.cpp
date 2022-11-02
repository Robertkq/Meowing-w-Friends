#include "client.h"

namespace kq
{
    client::client(uint64_t(*func)(uint64_t))
        : client_interface<msgids>(func)
    {

    }
}