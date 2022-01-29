#include <Arduino.h>
#ifdef __PLATFORMIO_BUILD_DEBUG__
#include <avr_debugger.h>
#endif
#include "Digit.h"
#include "State.h"
// FIXME: 5 or 7 != 0
#include <LiquidCrystal_I2C.h>
#include "LCDSerialUserInterface.h"
#include "NumberBuilder.h"
#include "Calculator.h"
#include "InterruptUtils.h"
#include <Keypad.h>
#include <EEPROM.h>

volatile bool need_redraw = false;

const int LCD_TYPE = 0x27;
const int LCD_WIDTH = 16;
const int LCD_HEIGHT = 2;
const int MAX_DIGITS_COUNT = 8;
const int KEYPAD_ROWS_COUNT = 4;
const int KEYPAD_COLUMNS_COUNT = 4;

State current_state = State::MAIN_MENU_CALCULATOR_SELECTED;

NumberBuilder numberBuilder(MAX_DIGITS_COUNT);

Calculator calculator;

int stored_value;

const int KEYPAD_ROWS[] = { 2, 3, 4, 5 };
const int KEYPAD_COLUMNS[] = { 6, 7, 8, 9 };

Keypad keypad(KEYPAD_ROWS, KEYPAD_ROWS_COUNT, KEYPAD_COLUMNS, KEYPAD_COLUMNS_COUNT);

const ButtonState* numpad_states[]
{
    &keypad.get_last_state(3, 1), // 0
    &keypad.get_last_state(0, 0), // 1
    &keypad.get_last_state(0, 1), // 2
    &keypad.get_last_state(0, 2), // 3
    &keypad.get_last_state(1, 0), // 4
    &keypad.get_last_state(1, 1), // 5
    &keypad.get_last_state(1, 2), // 6
    &keypad.get_last_state(2, 0), // 7
    &keypad.get_last_state(2, 1), // 8
    &keypad.get_last_state(2, 2)  // 9
};

const ButtonState* additional_states[]
{
    &keypad.get_last_state(0, 3), // D1
    &keypad.get_last_state(1, 3), // D2
    &keypad.get_last_state(2, 3), // D3
    &keypad.get_last_state(3, 3)  // D4
};

const ButtonState* star_state = &keypad.get_last_state(3, 0);  // *
const ButtonState* sharp_state = &keypad.get_last_state(3, 2); // #

const ButtonState* calculator_backspace = additional_states[1];
const ButtonState* calculator_enter = additional_states[2];

const ButtonState* dialog_yes = additional_states[1];
const ButtonState* dialog_no = additional_states[2];

IUserInterface* ui = new LCDSerialUserInterface(LiquidCrystal_I2C(LCD_TYPE, LCD_WIDTH, LCD_HEIGHT));

void redraw()
{
    switch (current_state)
    {
        case State::MAIN_MENU_CALCULATOR_SELECTED:
            ui->draw_calculator_menu_item();
        break;
        case State::MAIN_MENU_MEMORY_SELECTED:
            ui->draw_memory_menu_item(stored_value);
        break;
        case State::MAIN_MENU_CLEAR_SELECTED:
            ui->draw_clear_menu_item();
        break;
        case State::CALCULATOR_INPUT_FIRST:
            ui->draw_first_dialog(numberBuilder.number());
        break;
        case State::CALCULATOR_INPUT_SECOND:
            ui->draw_second_dialog(numberBuilder.number());
        break;
        case State::CALCULATOR_RESULT:
            ui->draw_result(calculator.calculate_or());
        break;
        case State::CALCULATOR_SAVE_RESULT_DIALOG:
            ui->draw_save_dialog();
        break;
        case State::CLEAR_MEMORY_DIALOG:
            ui->draw_clear_dialog();
        break;
    }
    
    need_redraw = false;
}

void menu_down_handler()
{
    const int SIZE = 3;

    int next = (int)current_state + 1;
        
    if (next >= SIZE)
        next = 0;

    current_state = (State)next;

    need_redraw = true;
}

void menu_enter_handler()
{   
    if (current_state != State::MAIN_MENU_MEMORY_SELECTED)
    {
        switch (current_state)
        {
            case State::MAIN_MENU_CALCULATOR_SELECTED:
                current_state = State::CALCULATOR_INPUT_FIRST;
                stop_interrupt();
            break;
            case State::MAIN_MENU_CLEAR_SELECTED:
                current_state = State::CLEAR_MEMORY_DIALOG;
                stop_interrupt();
            break;
            default:
            break;
        }

        need_redraw = true;
    }
}

int restore_value_form_memory()
{
    int restored_value = 0;
    EEPROM.get(0, restored_value);
    return restored_value;
}

void store_new_value(int value)
{
    stored_value = value;
    EEPROM.put(0, stored_value);
}

void setup()
{
#ifdef __PLATFORMIO_BUILD_DEBUG__
    debug_init();
#endif
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    init_interrupt();

    set_handler(0, menu_down_handler);
    set_handler(1, menu_enter_handler);

    start_interrupt();

    ui->init();

    stored_value = restore_value_form_memory();
    need_redraw = true;
}

bool pressed_any_key(const ButtonState* states, int size)
{
    for (int i = 0; i < size; ++i)
        if (states[i].click_count() > 0)
            return true;
    
    return false;
}

bool is_clicked_or_pressed(const ButtonState& state)
{
    return state.click_count() > 0 || state.is_on_pressed();
}

void main_menu_loop()
{
    invoke_interrupts();
}

void internal_save_dialog(int saved_value)
{
    keypad.update();

    if (dialog_yes->click_count() > 0)
    {
        store_new_value(saved_value);

        current_state = State::MAIN_MENU_CALCULATOR_SELECTED;
        start_interrupt();

        need_redraw = true;
    } else if (dialog_no->click_count() > 0)
    {
        current_state = State::MAIN_MENU_CALCULATOR_SELECTED;
        start_interrupt();

        need_redraw = true;
    }
}

void clear_dialog_loop()
{
    internal_save_dialog(0);
}

void save_dialog_loop()
{
    internal_save_dialog(calculator.calculate_or());
}

void calculator_loop()
{
    const int DIGITS_COUNT = 10;
    keypad.update();

    if (current_state == State::CALCULATOR_RESULT)
    {
        if (pressed_any_key(keypad.get_last_states(), KEYPAD_ROWS_COUNT * KEYPAD_COLUMNS_COUNT))
        {
            current_state = State::CALCULATOR_SAVE_RESULT_DIALOG;
            need_redraw = true;
        }
        
        return;
    }

    for (int i = 0; i < DIGITS_COUNT; ++i)
        if (is_clicked_or_pressed(*numpad_states[i]))
        {
            if (!numberBuilder.can_add_digit())
                break;
            
            numberBuilder.add_digit((Digit)i);
            need_redraw = true;
        }
    
    if (is_clicked_or_pressed(*calculator_backspace))
    {
        if (numberBuilder.can_backspace())
        {
            numberBuilder.backspace();
            need_redraw = true;
        }
    } else if (calculator_enter->click_count() > 0)
    {
        switch (current_state)
        {
            case State::CALCULATOR_INPUT_FIRST:
                calculator.op1() = numberBuilder.number();
            break;
            case State::CALCULATOR_INPUT_SECOND:
                calculator.op2() = numberBuilder.number();
            break;
            default:
            break;
        }
        numberBuilder.clear();
        current_state = (State)((int)current_state + 1);
        need_redraw = true;
    }
}

void loop()
{
    if (need_redraw)
        redraw();
    
    switch (current_state)
    {
        case State::MAIN_MENU_CALCULATOR_SELECTED:
        case State::MAIN_MENU_MEMORY_SELECTED:
        case State::MAIN_MENU_CLEAR_SELECTED:
            main_menu_loop();
        break;
        case State::CALCULATOR_INPUT_FIRST:
        case State::CALCULATOR_INPUT_SECOND:
        case State::CALCULATOR_RESULT:
            calculator_loop();
        break;
        case State::CALCULATOR_SAVE_RESULT_DIALOG:
            save_dialog_loop();
        case State::CLEAR_MEMORY_DIALOG:
            clear_dialog_loop();
        break;
    }
}