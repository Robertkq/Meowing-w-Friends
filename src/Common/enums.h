#ifndef KQMWFENUMS
#define KQMWFENUMS

#include <cstdint>

namespace kq
{
    enum GUIstate : uint8_t
    {
        Menu,
        Play,
        Options,
        Exit
    };

    enum msgids : uint8_t
    {
        // Server sends unique id for valid clients
        AssignID,
        // New player joins the game, announces all others
        RequestPositions,
        // The answer on a new player's request positions
        RequestAnswer,
        // Update on player's position
        UpdatePosition,
        //Delete a player that left
        DeleteMe
    };

}

#endif