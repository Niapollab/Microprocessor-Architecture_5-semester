#ifndef LCDSERIALUSERINTERFACE_H
#define LCDSERIALUSERINTERFACE_H
#include "SerialUserInterface.h"
#include "LCDUserInterface.h"

class LCDSerialUserInterface : public IUserInterface
{
    LCDUserInterface _lcd;
    SerialUserInterface _serial;
    
public:
    LCDSerialUserInterface(const LiquidCrystal_I2C& lcd);
    ~LCDSerialUserInterface();

    virtual void init();

    virtual void draw_calculator_menu_item();
    virtual void draw_memory_menu_item(int value);
    virtual void draw_clear_menu_item();

    virtual void draw_clear_dialog();
    virtual void draw_save_dialog();

    virtual void draw_first_dialog(int number);
    virtual void draw_second_dialog(int number);
    virtual void draw_result(int number);
};

#endif // LCDSERIALUSERINTERFACE_H
