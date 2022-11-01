#include "scramble.h"

uint64_t scramble(uint64_t num)
{
    return ((num ^ 0x5A9B6C2F0F011) & 0xF0F0F0F0F0F0F0) >> 3;
}