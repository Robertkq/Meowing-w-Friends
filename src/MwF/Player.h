#ifndef KQPLAYER
#define KQPLAYER

#include "../Common/common.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace kq
{
    class Player
    {
    public:
        Player();
        const sf::Sprite& getSprite() const;

        void setTextureCode(uint8_t textureCode);
        uint8_t getTextureCode() const;
        
        const sf::Vector2f& getPosition() const;
        void setPosition(sf::Vector2f position);

        void move(float x, float y);
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        uint8_t m_textureCode;
    };
}

#endif