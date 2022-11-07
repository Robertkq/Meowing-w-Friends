#include "client.h"

namespace kq
{
    client::client(uint64_t(*func)(uint64_t))
        : client_interface<msgids>(func), m_name(), m_thr()
    {
        std::cout << "We got here\n";
        m_thr = std::thread([this]() {
            Connect("192.168.1.4", 60000);
            while (true)
            {
                if (!Incoming().empty())
                {
                    auto msg = Incoming().pop_front().msg;
                    switch (msg.getID())
                    {
                    case(msgids::test):
                    {
                        std::cout << "Test\n";
                        break;
                    }
                    }
                }
                
            }
            });
    }

    client::~client()
    {
       Disconnect();
        if (m_thr.joinable())
            m_thr.join();
    }
}