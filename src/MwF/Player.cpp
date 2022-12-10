#include "Player.h"

namespace kq
{
    Player::Player()
        : m_texture(), m_sprite(), m_textureCode()
    {}

    const sf::Sprite& Player::getSprite() const
    {
        return m_sprite;
    }

    void Player::setTextureCode(uint8_t textureCode)
    {
        static uint8_t numOfTextures = 1;
        textureCode = (textureCode % numOfTextures) + 1;
        std::string fileName = "textures/cat";
        fileName += std::to_string(textureCode) + ".png";
        if (m_texture.loadFromFile(fileName))
        {
            m_sprite.setTexture(m_texture);
        }
        else
        {
            std::cout << "Couldn't load texture: " << fileName << '\n';
        }
    }
    uint8_t Player::getTextureCode() const
    {
        return m_textureCode;
    }

    const sf::Vector2f& Player::getPosition() const
    {
        return m_sprite.getPosition();
    }

    void Player::setPosition(sf::Vector2f position)
    {
        m_sprite.setPosition(position);
    }

    void Player::move(float x, float y)
    {
        m_sprite.move(x, y);
    }
}