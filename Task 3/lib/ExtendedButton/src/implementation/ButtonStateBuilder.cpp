#include "ButtonStateBuilder.h"

ButtonStateBuilder::ButtonStateBuilder() : _state(0), _click_count(0)
{
}

ButtonStateBuilder& ButtonStateBuilder::set_click_count(int click_count)
{
    _click_count = click_count;
    return *this;
}

ButtonStateBuilder& ButtonStateBuilder::set_is_idle(bool is_idle)
{
    if (get_value(ButtonStateFlags::IDLE_FLAG) != is_idle)
        invert_flag(ButtonStateFlags::IDLE_FLAG);
    
    return *this;
}

ButtonStateBuilder& ButtonStateBuilder::set_is_start_press(bool is_start_press)
{
    if (get_value(ButtonStateFlags::START_PRESS_FLAG) != is_start_press)
        invert_flag(ButtonStateFlags::START_PRESS_FLAG);

    return *this;
}

ButtonStateBuilder& ButtonStateBuilder::set_is_on_pressed(bool is_on_press)
{
    if (get_value(ButtonStateFlags::ON_PRESSED_FLAG) != is_on_press)
        invert_flag(ButtonStateFlags::ON_PRESSED_FLAG);
    
    return *this;
}

ButtonStateBuilder& ButtonStateBuilder::set_is_end_press(bool is_end_press)
{
    if (get_value(ButtonStateFlags::END_PRESS_FLAG) != is_end_press)
        invert_flag(ButtonStateFlags::END_PRESS_FLAG);
        
    return *this;
}

ButtonState ButtonStateBuilder::build() const
{
    return ButtonState(_click_count, _state);
}