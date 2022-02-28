#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <Pin.h>
#ifdef __PLATFORMIO_BUILD_DEBUG__
#include <avr_debugger.h>
#endif

#define BLINK_DELAY 2000

Pin led(DDRB, PINB, PORTB, 5);

int main()
{
#ifdef __PLATFORMIO_BUILD_DEBUG__
    debug_init();
#endif
    led.set_mode(PinMode::OUTPUT);

    while (true)
    {
        led.switch_output();
        _delay_ms(BLINK_DELAY);
    }

    return 0;
}