#ifndef HIGHACTIVATEDBUTTON_H
#define HIGHACTIVATEDBUTTON_H
#include "HardwareButton.h"

class HighActivatedButton : public HardwareButton
{
protected:
    virtual bool get_raw_state() const;

public:
    HighActivatedButton(int pin, bool use_pullup = true);
    HighActivatedButton();
};

#endif // HIGHACTIVATEDBUTTON_H
