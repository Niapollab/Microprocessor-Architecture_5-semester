#ifndef BUTTONSTATEBUILDER_H
#define BUTTONSTATEBUILDER_H
#include "ButtonState.h"

class ButtonStateBuilder
{
private:
    char _state;
    int _click_count;

    inline bool get_value(ButtonStateFlags flag) const;
    inline void invert_flag(ButtonStateFlags flag);

public:
    ButtonStateBuilder();
    ButtonStateBuilder& set_click_count(int click_count);
    ButtonStateBuilder& set_is_idle(bool is_idle);
    ButtonStateBuilder& set_is_start_press(bool is_start_press);
    ButtonStateBuilder& set_is_on_pressed(bool is_on_press);
    ButtonStateBuilder& set_is_end_press(bool is_end_press);
    ButtonState build() const;
};

inline bool ButtonStateBuilder::get_value(ButtonStateFlags flag) const
{
    return (bool)(_state & (char)flag);
}

inline void ButtonStateBuilder::invert_flag(ButtonStateFlags flag)
{
    _state ^= (char)flag;
}

#endif // BUTTONSTATEBUILDER_H
