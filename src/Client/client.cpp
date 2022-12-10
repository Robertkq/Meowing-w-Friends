#include "client.h"
#include "../MwF/Player.h"

namespace kq
{
    
    client::client(uint64_t(*func)(uint64_t), tsun_map<int, kq::Player>& ref, uint32_t& m_id)
        : client_interface<msgids>(func), m_name(), m_thr(), m_players(ref)
    {
        m_thr = std::thread([this, &m_id]() {
            Connect("192.168.1.6", 60000);
            while (true)
            {
                if (!Incoming().empty())
                {
                    auto msg = Incoming().pop_front().msg;
                    switch (msg.getID())
                    {
                    case(msgids::AssignID):
                    {
                        uint32_t id;
                        msg >> id;
                        m_id = id;
                        std::cout << "My id is: " << m_id << '\n';
                        break;
                    }
                    case(msgids::RequestPositions):
                    {
                        uint32_t id;
                        uint8_t textureCode;
                        msg >> id >> textureCode;
                        m_players[id] = kq::Player();
                        m_players[id].setTextureCode(textureCode);

                        textureCode = m_players[m_id].getTextureCode();
                        auto Pos = m_players[m_id].getPosition();
                        kq::message<msgids> response(msgids::RequestAnswer);
                        response << textureCode << Pos.x << Pos.y << m_id;
                        Send(response);
                        break;
                    }
                    case(msgids::RequestAnswer):
                    {
                        uint32_t id;
                        uint8_t textureCode;
                        float xPos, yPos;
                        msg >> id >> yPos >> xPos >> textureCode;
                        
                        m_players[id].setPosition(sf::Vector2f{ xPos, yPos });
                        m_players[id].setTextureCode(textureCode);
                        break;
                    }
                    case(msgids::UpdatePosition):
                    {
                        float xPos, yPos;
                        uint32_t uid;
                        msg >> uid >> yPos >> xPos;
                        m_players[uid].setPosition(sf::Vector2f{ xPos, yPos });
                        break;
                    }
                    case(msgids::DeleteMe):
                    {
                        uint32_t id;
                        msg >> id;
                        m_players.erase(id);
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