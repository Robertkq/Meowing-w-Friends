#ifndef KQCOLOR
#define KQCOLOR

#include "../Common/common.h"

namespace kq
{
    inline sf::Color setColor(uint8_t randNum)
    {
        randNum = randNum % 5;
        if (randNum == 0)
            return sf::Color::White;
        else if (randNum == 1)
            return sf::Color::Black;
        else if (randNum == 2)
            return sf::Color::Red;
        else if (randNum == 3)
            return sf::Color::Green;
        else
            return sf::Color::Blue;
    }

    inline uint8_t colorToCode(const sf::Color& color)
    {
        if (color == sf::Color::White)
            return 0;
        else if (color == sf::Color::Black)
            return 1;
        else if (color == sf::Color::Red)
            return 2;
        else if (color == sf::Color::Green)
            return 3;
        else return 4;
    }
}

#endif