#include "HardwareButton.h"
#include <Arduino.h>

HardwareButton::HardwareButton(int pin, bool use_pullup) : _pin(pin), _use_pullup(use_pullup)
{
}

HardwareButton::HardwareButton() : HardwareButton(-1, false)
{
}

int HardwareButton::pin() const
{
    return _pin;
}

int& HardwareButton::pin()
{
    return _pin;
}

bool HardwareButton::use_pullup() const
{
    return _use_pullup;
}

bool& HardwareButton::use_pullup()
{
    return _use_pullup;
}

ButtonState HardwareButton::update()
{
    if (_pin < 0)
    {
        ButtonStateBuilder builder;
        builder.set_is_idle(true);
        return builder.build();
    }

    pinMode(_pin, _use_pullup ? INPUT_PULLUP : INPUT);
    return BaseButton::update();
}