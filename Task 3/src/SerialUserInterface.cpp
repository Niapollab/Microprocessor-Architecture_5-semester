#include "SerialUserInterface.h"

SerialUserInterface::SerialUserInterface()
{
}

SerialUserInterface::~SerialUserInterface()
{
}

void SerialUserInterface::init()
{
    Serial.begin(9600);
}

void SerialUserInterface::draw_calculator_menu_item()
{
    draw_separator();
    Serial.println("1. OR");
}

void SerialUserInterface::draw_memory_menu_item(int value)
{
    draw_separator();
    Serial.println("2. Memory");
    Serial.print(value);
    Serial.println();
}

void SerialUserInterface::draw_clear_menu_item()
{
    draw_separator();
    Serial.println("3. Clear");
}

void SerialUserInterface::draw_clear_dialog()
{
    draw_separator();
    Serial.println("Need clear?");
    Serial.println("D1 - YES; D2 - NO");
}

void SerialUserInterface::draw_save_dialog()
{
    draw_separator();
    Serial.println("Need save?");
    Serial.println("D1 - YES; D2 - NO");
}

void SerialUserInterface::draw_first_dialog(int number)
{
    draw_separator();
    Serial.println("Enter First:");
    Serial.println(number);
}

void SerialUserInterface::draw_second_dialog(int number)
{
    draw_separator();
    Serial.println("Enter Second:");
    Serial.println(number);
}

void SerialUserInterface::draw_result(int number)
{
    draw_separator();
    Serial.println("Result:");
    Serial.println(number);
}