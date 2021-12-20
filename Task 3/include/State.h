#ifndef STATE_H
#define STATE_H

enum class State
{
    // Main menu
    MAIN_MENU_CALCULATOR_SELECTED = 0,
    MAIN_MENU_MEMORY_SELECTED = 1,
    MAIN_MENU_CLEAR_SELECTED = 2,

    // Calculator
    CALCULATOR_INPUT_FIRST = 3,
    CALCULATOR_INPUT_SECOND = 4,
    CALCULATOR_RESULT = 5,

    // Save result dialog
    CALCULATOR_SAVE_RESULT_DIALOG = 6,

    // Clear memory dialog
    CLEAR_MEMORY_DIALOG = 7
};

#endif // STATE_H
