#include <avr/io.h>
#include <util/delay.h>
#ifdef __PLATFORMIO_BUILD_DEBUG__
#include <avr_debugger.h>
#endif

#define BLINK_DELAY 2000

int main(void)
{
#ifdef __PLATFORMIO_BUILD_DEBUG__
    debug_init();
#endif

    DDRB = 1 << 5;

    while (true)
    {
        _delay_ms(2000);

        PORTB ^= 1 << 5;
    }

    return 0;
}