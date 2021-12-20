#ifndef SERIALUSERINTERFACE_H
#define SERIALUSERINTERFACE_H
#include "IUserInterface.h"
#include <Arduino.h>

class SerialUserInterface : public IUserInterface
{
private:
    inline void draw_separator();

public:
    SerialUserInterface();
    ~SerialUserInterface();

    virtual void draw_calculator_menu_item();
    virtual void draw_memory_menu_item(int value);
    virtual void draw_clear_menu_item();

    virtual void draw_clear_dialog();
    virtual void draw_save_dialog();

    virtual void draw_first_dialog(int number);
    virtual void draw_second_dialog(int number);
    virtual void draw_result(int number);
};

inline void SerialUserInterface::draw_separator()
{
    Serial.println("----------");
}

#endif // SERIALUSERINTERFACE_H
