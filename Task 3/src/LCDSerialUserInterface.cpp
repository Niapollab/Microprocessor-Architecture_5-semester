#include "LCDSerialUserInterface.h"

LCDSerialUserInterface::LCDSerialUserInterface(const LiquidCrystal_I2C& lcd) :_lcd(lcd)
{
}

LCDSerialUserInterface::~LCDSerialUserInterface()
{
}

void LCDSerialUserInterface::init()
{
    _serial.init();
    _lcd.init();
}

void LCDSerialUserInterface::draw_calculator_menu_item()
{
    _serial.draw_calculator_menu_item();
    _lcd.draw_calculator_menu_item();
}

void LCDSerialUserInterface::draw_memory_menu_item(int value)
{
    _serial.draw_memory_menu_item(value);
    _lcd.draw_memory_menu_item(value);
}

void LCDSerialUserInterface::draw_clear_menu_item()
{
    _serial.draw_clear_menu_item();
    _lcd.draw_clear_menu_item();
}

void LCDSerialUserInterface::draw_clear_dialog()
{
    _serial.draw_clear_dialog();
    _lcd.draw_clear_dialog();
}

void LCDSerialUserInterface::draw_save_dialog()
{
    _serial.draw_save_dialog();
    _lcd.draw_save_dialog();
}

void LCDSerialUserInterface::draw_first_dialog(int number)
{
    _serial.draw_first_dialog(number);
    _lcd.draw_first_dialog(number);
}

void LCDSerialUserInterface::draw_second_dialog(int number)
{
    _serial.draw_second_dialog(number);
    _lcd.draw_second_dialog(number);
}

void LCDSerialUserInterface::draw_result(int number)
{
    _serial.draw_result(number);
    _lcd.draw_result(number);
}