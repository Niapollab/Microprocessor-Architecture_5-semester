#include "NumberBuilder.h"

NumberBuilder::NumberBuilder(int max_digit_count) : _max_digit_count(max_digit_count), _current_pos(0), _number(0)
{
}

bool NumberBuilder::can_add_digit() const
{
    return _current_pos < _max_digit_count;
}

bool NumberBuilder::can_backspace() const
{
    return _current_pos > 0;
}

void NumberBuilder::add_digit(Digit digit)
{
    int temp = (int)digit;
    if (can_add_digit() && (_current_pos >= 1 || temp != 0))
    {
        _number *= 10;
        _number += temp;

        ++_current_pos;
    }
}

void NumberBuilder::backspace()
{
    if (can_backspace())
    {
        _number /= 10;
        
        --_current_pos;
    }
}

void NumberBuilder::clear()
{
    _number = 0;
    _current_pos = 0;
}

int NumberBuilder::number() const
{
    return _number;
}