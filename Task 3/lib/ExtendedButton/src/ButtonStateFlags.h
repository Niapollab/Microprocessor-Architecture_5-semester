#ifndef BUTTONSTATEFLAGS_H
#define BUTTONSTATEFLAGS_H

enum class ButtonStateFlags : char
{
    IDLE_FLAG = 0b0001,
    START_PRESS_FLAG = 0b0010,
    ON_PRESSED_FLAG = 0b0100,
    END_PRESS_FLAG = 0b1000
};

#endif // BUTTONSTATEFLAGS_H
