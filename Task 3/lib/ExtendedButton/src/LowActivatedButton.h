#ifndef LOWACTIVATEDBUTTON_H
#define LOWACTIVATEDBUTTON_H
#include "HardwareButton.h"

class LowActivatedButton : public HardwareButton
{
protected:
    virtual bool get_raw_state() const;

public:
    LowActivatedButton(int pin, bool use_pullup = true);
    LowActivatedButton();
};

#endif // LOWACTIVATEDBUTTON_H
