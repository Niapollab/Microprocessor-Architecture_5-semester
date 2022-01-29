#include "BaseButton.h"
#include <Arduino.h>

BaseButton::BaseButton() : _start_time(0), _number_of_clicks(0)
{
}

BaseButton::~BaseButton() 
{
}

ButtonState BaseButton::update()
{
    ButtonStateBuilder builder;
    builder.set_is_idle(_state_machine.curr_state() == InternalButtonState::INIT);

    bool activeLevel = get_raw_state();
    unsigned long now = millis();
    unsigned long waitTime = (now - _start_time);

    switch (_state_machine.curr_state())
    {
        case InternalButtonState::INIT:
            if (activeLevel)
            {
                _state_machine.change_state(InternalButtonState::DOWN);
                _start_time = now;
                _number_of_clicks = 0;
            }
            break;
        case InternalButtonState::DOWN:
            if ((!activeLevel) && (waitTime < (unsigned)get_debounce_time()))
                _state_machine.change_state(_state_machine.prev_state());
            else if (!activeLevel)
            {
                _state_machine.change_state(InternalButtonState::UP);
                _start_time = now;
            }
            else if ((activeLevel) && (waitTime > (unsigned)get_press_time()))
            {
                builder.set_is_start_press(true);
                
                _state_machine.change_state(InternalButtonState::PRESS);
            }
        break;
    case InternalButtonState::UP:
        if ((activeLevel) && (waitTime < (unsigned)get_debounce_time()))
            _state_machine.change_state(_state_machine.prev_state());
        else if (waitTime >= (unsigned)get_debounce_time())
        {
            ++_number_of_clicks;
            _state_machine.change_state(InternalButtonState::COUNT);
        }
        break;
    case InternalButtonState::COUNT:
        if (activeLevel)
        {
            _state_machine.change_state(InternalButtonState::DOWN);
            _start_time = now;
        }
        else if ((waitTime > (unsigned)get_click_time()) || (_number_of_clicks == max_allowed_clicks()))
        {
            builder.set_click_count(_number_of_clicks);
            reset();
        }
        break;
    case InternalButtonState::PRESS:
        if (!activeLevel)
        {
            _state_machine.change_state(InternalButtonState::PRESSEND);
            _start_time = now;
        }
        else
            builder.set_is_on_pressed(true);
        break;
    case InternalButtonState::PRESSEND:
        if ((activeLevel) && (waitTime < (unsigned)get_debounce_time()))
        _state_machine.change_state(_state_machine.prev_state());
        else if (waitTime >= (unsigned)get_debounce_time())
        {
            builder.set_is_end_press(true);
            reset();
        }
        break;
    default:
        _state_machine.reset();
        break;
    }

    return builder.build();
}