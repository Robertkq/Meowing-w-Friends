#include "MwF.h"
#include "color.h"

namespace kq
{
    MwF::MwF(unsigned int width, unsigned int height, const std::string& title)
        : m_window(sf::VideoMode(width, height), title), m_deltaClock(),
        m_state(GUIstate::Menu), m_players(), m_client(scramble, m_players, m_id),
        m_id(), m_speed(3), m_load(true)
        
    {
        srand(unsigned int(time(NULL)));
        
        m_window.setFramerateLimit(60);
        ImGui::SFML::Init(m_window);
    }

    void MwF::run()
    {
        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(m_window, event);

                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }
            }
            ImGui::SFML::Update(m_window, m_deltaClock.restart());

            

            if (m_state == GUIstate::Exit)
            {
                m_window.close();
                return;
            }
            else if (m_state == GUIstate::Menu)
            {
                Menu();
            }
            else if (m_state == GUIstate::Play)
            {
                Play();
            }

            
            
        }
    }

    void MwF::Menu()
    {
        m_load = true;
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBackground;
        ImGui::SetNextWindowSize(ImVec2{ 1600, 900 });
        if (!ImGui::Begin("Meowing with Friends", nullptr,  window_flags))
        {
            // Small optimisation if early fail
            ImGui::End();
        }

        ImVec2 pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos({ pos.x + 780, pos.y + 15 });
        if (m_client.IsConnected())
        {
            ImGui::TextColored(ImVec4(0.f, 255.f, 0.f, 1.f),"Connected!");
        }
        else
        {
            ImGui::TextColored(ImVec4(255.f, 0.f, 0.f, 1.f),"Disconnected");
        }
        
        
        if (ImGui::Button("Play", ImVec2{ 1600, 290 }))
        {
            if (m_client.IsConnected())
            {
                m_state = GUIstate::Play;
            }
        }
        if (ImGui::Button("Options", ImVec2{ 1600, 290 }))
        {
            m_state = GUIstate::Options;
        }
        if (ImGui::Button("Exit", ImVec2{ 1600, 290 }))
        {
            m_state = GUIstate::Exit;
        }

        ImGui::End();

        m_window.clear(sf::Color(105, 105, 105));
        ImGui::SFML::Render(m_window);
        m_window.display();
    }

    void MwF::Play()
    {
        if (m_load == true)
        {
            kq::message<msgids> msg(msgids::RequestPositions);

            // Send to server
            float radius = (rand() % 51) + 100.f;
            uint8_t textureCode = (uint8_t)rand();

            msg << radius << textureCode << m_id;
            m_client.Send(msg);

            m_players[m_id] = kq::Player();
            m_players[m_id].setTextureCode(textureCode);

            //m_players[m_id] = sf::CircleShape(radius);
            //sf::Color color = setColor(colorCode);
            //m_players[m_id].setFillColor(color);
            //m_players[m_id].setOutlineColor(color);
            
            m_load = false;
        }
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBackground;
        if (!ImGui::Begin("Meowing with Friends", nullptr, window_flags))
        {
            // Small optimisation if early fail
            ImGui::End();
        }

        ImGui::End();
        // IO
        bool focus = m_window.hasFocus();
        auto currentPosition = m_players[m_id].getPosition();

        if (focus && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_players[m_id].move(0, -1 * m_speed);
        }
        if (focus && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_players[m_id].move(0, 1 * m_speed);
        }
        if (focus && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_players[m_id].move(-1 * m_speed, 0);
        }
        if (focus && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_players[m_id].move(1 * m_speed, 0);
        }
        if (focus && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            kq::message<msgids> msg(msgids::DeleteMe);
            msg << m_id;
            m_client.Send(msg);
            m_players.clear();
            m_state = GUIstate::Menu;
        }
        auto nextPosition = m_players[m_id].getPosition();
        if (currentPosition != nextPosition)
        {
            kq::message<msgids> msg(msgids::UpdatePosition);
            msg << static_cast<float>(nextPosition.x) << static_cast<float>(nextPosition.y) << m_id;
            m_client.Send(msg);
        }

        m_window.clear(sf::Color(105, 105, 105));
        // Rendering

        for (auto& pair : m_players)
        {
            auto& player = pair.second;
            m_window.draw(player.getSprite());
        }

        ImGui::SFML::Render(m_window);
        m_window.display();
    }

    MwF::~MwF()
    {
        ImGui::SFML::Shutdown();
    }

}