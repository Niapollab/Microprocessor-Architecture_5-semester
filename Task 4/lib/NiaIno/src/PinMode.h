#ifndef PINMODE_H
#define PINMODE_H
#include <stdint.h>

enum class PinMode : uint8_t
{
    INPUT = 0,
    OUTPUT = 1,
    INPUT_PULLUP = 2
};

#endif // PINMODE_H
