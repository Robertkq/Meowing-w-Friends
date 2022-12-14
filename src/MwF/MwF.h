#ifndef KQMWF
#define KQMWF

#include "../Common/common.h"
#include "../Client/client.h"
#include "tsun_map.h"
#include "Player.h"

namespace kq
{
    // Main class for the game
    class MwF
    {
    public:
        MwF(unsigned int width = 1600, unsigned int height = 900, const std::string& title = "Meowing with Friends");
        ~MwF();
        void run();
    private:
        void Menu();
        void Play();

        sf::RenderWindow m_window;
        sf::Clock m_deltaClock;

        GUIstate m_state;

        kq::tsun_map<int, kq::Player> m_players;
        client m_client;
        uint32_t m_id;
        int32_t m_speed;

        bool m_load;

        
    };
}

#endif