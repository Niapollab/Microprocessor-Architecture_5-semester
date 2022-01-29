#include "HighActivatedButton.h"
#include <Arduino.h>

HighActivatedButton::HighActivatedButton(int pin, bool use_pullup) : HardwareButton(pin, use_pullup)
{
}

HighActivatedButton::HighActivatedButton() : HighActivatedButton(-1, false)
{
}

bool HighActivatedButton::get_raw_state() const
{
    return digitalRead(_pin) == HIGH;
}