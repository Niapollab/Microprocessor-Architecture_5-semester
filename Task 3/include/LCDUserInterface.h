#ifndef LCDUSERINTERFACE_H
#define LCDUSERINTERFACE_H
#include <LiquidCrystal_I2C.h>
#include "IUserInterface.h"

class LCDUserInterface : public IUserInterface
{
private:
    LiquidCrystal_I2C _lcd;

    void to_new_line();

public:
    LCDUserInterface(const LiquidCrystal_I2C& lcd);
    ~LCDUserInterface();

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

#endif // LCDUSERINTERFACE_H
