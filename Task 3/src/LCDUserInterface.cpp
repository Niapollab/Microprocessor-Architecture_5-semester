#include "LCDUserInterface.h"

LCDUserInterface::LCDUserInterface(const LiquidCrystal_I2C& lcd) : _lcd(lcd)
{
}

LCDUserInterface::~LCDUserInterface()
{
}

void LCDUserInterface::to_new_line()
{
    _lcd.setCursor(0, 1);
}

void LCDUserInterface::init()
{
    _lcd.init();
    _lcd.backlight();
    _lcd.noBlink();
}

void LCDUserInterface::draw_calculator_menu_item()
{
    _lcd.clear();
    _lcd.print("1. OR");
}

void LCDUserInterface::draw_memory_menu_item(int value)
{
    _lcd.clear();
    _lcd.print("2. Memory");
    to_new_line();
    _lcd.print(value);
}

void LCDUserInterface::draw_clear_menu_item()
{
    _lcd.clear();
    _lcd.print("3. Clear");
}

void LCDUserInterface::draw_clear_dialog()
{
    _lcd.clear();
    _lcd.print("Need clear?");
    to_new_line();
    _lcd.print("D2 - YES; D3 - NO");
}

void LCDUserInterface::draw_save_dialog()
{
    _lcd.clear();
    _lcd.print("Need save?");
    to_new_line();
    _lcd.print("D2 - YES; D3 - NO");
}

void LCDUserInterface::draw_first_dialog(int number)
{
    _lcd.clear();
    _lcd.print("Enter First:");
    to_new_line();
    _lcd.print(number);
}

void LCDUserInterface::draw_second_dialog(int number)
{
    _lcd.clear();
    _lcd.print("Enter Second:");
    to_new_line();
    _lcd.print(number);
}

void LCDUserInterface::draw_result(int number)
{
    _lcd.clear();
    _lcd.print("Result:");
    to_new_line();
    _lcd.print(number);
}