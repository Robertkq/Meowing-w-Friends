#ifndef KQMWFCLIENT
#define KQMWFCLIENT

#include "../Common/common.h"

namespace kq
{
    class client : public client_interface<msgids>
    {
    public:
        client(uint64_t(*func)(uint64_t));
        ~client();
    private:
        std::string m_name;
        std::thread m_thr;
    };
}

#endif