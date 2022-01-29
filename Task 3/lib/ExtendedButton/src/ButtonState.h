#ifndef BUTTONSTATE_H
#define BUTTONSTATE_H
#include "ButtonStateFlags.h"

class ButtonState
{
private:
    int _click_count;
    char _state;

    inline bool get_value(ButtonStateFlags flag) const;

public:
    ButtonState(int click_count, char state);
    ButtonState();

    int click_count() const;
    bool is_click() const;
    bool is_double_click() const;
    bool is_multi_click() const;
    bool is_idle() const;
    bool is_press_starts() const;
    bool is_on_pressed() const;
    bool is_press_ends() const;
};

inline bool ButtonState::get_value(ButtonStateFlags flag) const
{
    return (bool)(_state & (char)flag);
}

#endif // BUTTONSTATE_H
