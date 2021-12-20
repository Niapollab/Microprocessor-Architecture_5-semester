#ifndef IUSERINTERFACE_H
#define IUSERINTERFACE_H

class IUserInterface
{
public:
    virtual ~IUserInterface() {};

    virtual void init() = 0;

    virtual void draw_calculator_menu_item() = 0;
    virtual void draw_memory_menu_item(int value) = 0;
    virtual void draw_clear_menu_item() = 0;

    virtual void draw_clear_dialog() = 0;
    virtual void draw_save_dialog() = 0;

    virtual void draw_first_dialog(int number) = 0;
    virtual void draw_second_dialog(int number) = 0;
    virtual void draw_result(int number) = 0;
};

#endif // IUSERINTERFACE_H
