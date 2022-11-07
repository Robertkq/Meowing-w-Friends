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
        test
    };

}

#endif