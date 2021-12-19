#ifndef KEYPAD_H
#define KEYPAD_H
#include <LowActivatedButton.h>

class Keypad
{
private:
    const int* _rows_pins;
    int _rows_pins_size;
    const int* _columns_pins;
    int _columns_pins_size;
    LowActivatedButton* _buttons;
    ButtonState* _states;

    inline int map(int row_index, int column_index) const;

public:
    Keypad(const int* rows_pins, int rows_pins_size, const int* columns_pins, int columns_pins_size);
    ~Keypad();

    const ButtonState* update();
    const ButtonState* get_last_states() const;
    const ButtonState& get_last_state(int row_index, int column_index) const;
};

inline int Keypad::map(int row_index, int column_index) const
{
    return column_index + row_index * _rows_pins_size;
}

#endif // KEYPAD_H
