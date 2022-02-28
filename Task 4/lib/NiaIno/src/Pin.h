#ifndef PIN_H
#define PIN_H
#include <stdint.h>
#include "PinMode.h"
#include "PinValue.h"

class Pin
{
private:
    volatile uint8_t& _direct_port_access_addr;
    volatile uint8_t& _port_in_addr;
    volatile uint8_t& _port_out_addr;
    const uint8_t _port_bit_mask;

    inline bool get_bit(const volatile uint8_t& mem) const
    {
        return mem & _port_bit_mask;
    }

    inline void off_bit(volatile uint8_t& mem)
    {
        mem &= ~_port_bit_mask;
    }

    inline void on_bit(volatile uint8_t& mem)
    {
        mem |= _port_bit_mask;
    }

    inline void switch_bit(volatile uint8_t& mem)
    {
        mem ^= _port_bit_mask;
    }

public:
    Pin(volatile uint8_t& direct_port_access_addr,
        volatile uint8_t& port_in_addr,
        volatile uint8_t& port_out_addr,
        const uint8_t pin_number)
        : _direct_port_access_addr(direct_port_access_addr),
          _port_in_addr(port_in_addr),
          _port_out_addr(port_out_addr),
          _port_bit_mask(1 << pin_number)
    {
    }

    inline PinMode get_mode() const
    {
        PinMode direct_port_access_status = (PinMode)get_bit(_direct_port_access_addr);
        PinValue port_out_status = read_output();

        if (direct_port_access_status == PinMode::OUTPUT)
            return PinMode::OUTPUT;

        if (port_out_status == PinValue::HIGH)
            return PinMode::INPUT_PULLUP;

        return PinMode::INPUT;
    }

    inline void set_mode(PinMode mode)
    {
        switch (mode)
        {
        case PinMode::INPUT:
            off_bit(_direct_port_access_addr);
            off_bit(_port_out_addr);
            break;
        case PinMode::INPUT_PULLUP:
            off_bit(_direct_port_access_addr);
            on_bit(_port_out_addr);
            break;
        case PinMode::OUTPUT:
            on_bit(_direct_port_access_addr);
            break;
        }
    }

    inline PinValue read_input() const
    {
        return (PinValue)get_bit(_port_in_addr);
    }

    inline PinValue read_output() const
    {
        return (PinValue)get_bit(_port_out_addr);
    }

    inline void switch_output()
    {
        switch_bit(_port_out_addr);
    }

    inline void set_output(PinValue value)
    {
        switch (value)
        {
        case PinValue::LOW:
            off_bit(_port_out_addr);
            break;
        case PinValue::HIGH:
            on_bit(_port_out_addr);
            break;
        }
    }
};

#endif // PIN_H