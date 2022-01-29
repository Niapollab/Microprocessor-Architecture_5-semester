#ifndef HARDWAREBUTTON_H
#define HARDWAREBUTTON_H
#include "BaseButton.h"

class HardwareButton : public BaseButton
{
protected:
    int _pin;
    bool _use_pullup;

public:
    HardwareButton(int pin, bool use_pullup = true);
    HardwareButton();

    int pin() const;
    int& pin();
    bool use_pullup() const;
    bool& use_pullup();

    virtual ButtonState update();
};

#endif // HARDWAREBUTTON_H
