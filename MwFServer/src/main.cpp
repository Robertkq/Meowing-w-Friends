#include "Server/server.h"

int main()
{
    kq::server Server(60000, scramble);
    Server.Start();
    while (true)
    {
        Server.Update();
    }
    return 0;
}