#ifndef BASEBUTTON_H
#define BASEBUTTON_H
#include "ButtonStateBuilder.h"

class BaseButton
{
private:
    enum class InternalButtonState
    {
        INIT = 0,
        DOWN = 1,
        UP = 2,
        COUNT = 3,
        PRESS = 6,
        PRESSEND = 7,
        UNKNOWN = 99
    };

    class ButtonStateMachine
    {
    private:
        InternalButtonState _prev_state;
        InternalButtonState _curr_state;
    
    public:
        inline ButtonStateMachine() : _prev_state(InternalButtonState::INIT), _curr_state(InternalButtonState::INIT)
        {
        }

        inline InternalButtonState prev_state() const
        {
            return _prev_state;
        }

        inline InternalButtonState curr_state() const
        {
            return _curr_state;
        }

        inline void change_state(InternalButtonState new_state)
        {
            _prev_state = _curr_state;
            _curr_state = new_state;
        }

        inline void reset()
        {
            _prev_state = InternalButtonState::INIT;
            _curr_state = InternalButtonState::INIT;
        }
    } _state_machine;

    unsigned long _start_time;
    int _number_of_clicks;

protected:
    inline virtual void reset();
    inline virtual int get_debounce_time() const;
    inline virtual int get_click_time() const;
    inline virtual int get_press_time() const;
    inline virtual int max_allowed_clicks() const;

    virtual bool get_raw_state() const = 0;

public:
    BaseButton();
    virtual ~BaseButton();

    virtual ButtonState update();
};

inline void BaseButton::reset()
{
    _state_machine.reset();
    _number_of_clicks = 0;
    _start_time = 0;
}

inline int BaseButton::get_debounce_time() const
{
    return 50;
}

inline int BaseButton::get_click_time() const
{
    return 400;
}

inline int BaseButton::get_press_time() const
{
    return 800;
}

inline int BaseButton::max_allowed_clicks() const
{
    return 100;
}

#endif // BASEBUTTON_H
