#include "MwF.h"

namespace kq
{
    MwF::MwF(unsigned int width, unsigned int height, const std::string& title)
        : m_window(sf::VideoMode(width, height), title), m_deltaClock(),
        m_state(GUIstate::Menu)
    {
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

            ImGui::ShowDemoWindow();

            m_window.clear();
            ImGui::SFML::Render(m_window);
            m_window.display();
        }
    }

    void MwF::Menu()
    {

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

        
        if (ImGui::Button("Play", ImVec2{ 1600, 300 }))
        {
            m_state = GUIstate::Play;
        }
        if (ImGui::Button("Options", ImVec2{ 1600, 300 }))
        {
            m_state = GUIstate::Options;
        }
        if (ImGui::Button("Exit", ImVec2{ 1600, 300 }))
        {
            m_state = GUIstate::Exit;
        }

        ImGui::End();
    }

    void MwF::Play()
    {
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
    }

    MwF::~MwF()
    {
        ImGui::SFML::Shutdown();
    }

}