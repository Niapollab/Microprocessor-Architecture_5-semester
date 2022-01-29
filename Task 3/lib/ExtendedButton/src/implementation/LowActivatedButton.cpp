#include "LowActivatedButton.h"
#include <Arduino.h>

LowActivatedButton::LowActivatedButton(int pin, bool use_pullup) : HardwareButton(pin, use_pullup)
{
}

LowActivatedButton::LowActivatedButton() : LowActivatedButton(-1, false)
{
}

bool LowActivatedButton::get_raw_state() const
{
    return digitalRead(_pin) == LOW;
}