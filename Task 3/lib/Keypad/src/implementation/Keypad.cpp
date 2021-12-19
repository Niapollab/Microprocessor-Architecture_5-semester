#include "Keypad.h"
#include <Arduino.h>

Keypad::Keypad(const int* rows_pins, int rows_pins_size, const int* columns_pins, int columns_pins_size) : _rows_pins(rows_pins), _rows_pins_size(rows_pins_size), _columns_pins(columns_pins), _columns_pins_size(columns_pins_size)
{
    int const SIZE = _rows_pins_size * _columns_pins_size;

    _buttons = new LowActivatedButton[SIZE];
    _states = new ButtonState[SIZE];

    for (int i = 0; i < SIZE; ++i)
    {
        _buttons[i] = LowActivatedButton(_rows_pins[i / _rows_pins_size]);
        _states[i] = ButtonState();
    }
}

Keypad::~Keypad()
{
    delete[] _buttons;
    _buttons = nullptr;

    delete[] _states;
    _states = nullptr;
}

const ButtonState* Keypad::update()
{
    for (int i = 0; i < _rows_pins_size; ++i)
        pinMode(_rows_pins[i], INPUT_PULLUP);
    
    for (int j = 0; j < _columns_pins_size; ++j)
    {
        pinMode(_columns_pins[j], OUTPUT);
        digitalWrite(_columns_pins[j], LOW);

        for (int i = 0; i < _rows_pins_size; ++i)
        {
            int mapped_index = map(i, j);
            _states[mapped_index] = _buttons[mapped_index].update();
        }
            
        digitalWrite(_columns_pins[j], HIGH);
        pinMode(_columns_pins[j], INPUT);
    }

    return _states;
}

const ButtonState* Keypad::get_last_states() const
{
    return _states;
}

const ButtonState& Keypad::get_last_state(int row_index, int column_index) const
{
    return _states[map(row_index, column_index)];
}