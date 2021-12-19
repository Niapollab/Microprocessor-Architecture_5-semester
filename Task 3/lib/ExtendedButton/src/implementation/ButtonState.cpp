#include "ButtonState.h"

ButtonState::ButtonState(int click_count, char state) : _click_count(click_count), _state(state)
{
}

ButtonState::ButtonState() : _click_count(0), _state(0)
{
}

int ButtonState::click_count() const
{
    return _click_count;
}

bool ButtonState::is_click() const
{
    return _click_count == 1;
}

bool ButtonState::is_double_click() const
{
    return _click_count == 2;
}

bool ButtonState::is_multi_click() const
{
    return _click_count > 2;
}

bool ButtonState::is_idle() const
{
    return get_value(ButtonStateFlags::IDLE_FLAG); 
}

bool ButtonState::is_press_starts() const
{
    return get_value(ButtonStateFlags::START_PRESS_FLAG);
}

bool ButtonState::is_on_pressed() const
{
    return is_press_starts() || get_value(ButtonStateFlags::ON_PRESSED_FLAG);
}

bool ButtonState::is_press_ends() const
{
    return get_value(ButtonStateFlags::END_PRESS_FLAG);
}