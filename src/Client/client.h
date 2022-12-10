#ifndef KQMWFCLIENT
#define KQMWFCLIENT

#include "../Common/common.h"
#include "../MwF/tsun_map.h"
#include "../MwF/Player.h"

namespace kq
{
    class client : public client_interface<msgids>
    {
    public:
        client(uint64_t(*func)(uint64_t), tsun_map<int, kq::Player>& ref, uint32_t& m_id);
        ~client();
    private:
        std::string m_name;
        std::thread m_thr;
        tsun_map<int, kq::Player>& m_players;
    };
}

#endif