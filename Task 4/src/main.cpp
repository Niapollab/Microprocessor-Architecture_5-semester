#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <Pin.h>
#ifdef __PLATFORMIO_BUILD_DEBUG__
#include <avr_debugger.h>
#endif

#define BLINK_DELAY 1000

void off_all_leds(Pin* leds, const uint8_t leds_count)
{
    for (int i = 0; i < leds_count; ++i)
        leds[i].set_output(PinValue::HIGH);
}

int main()
{
#ifdef __PLATFORMIO_BUILD_DEBUG__
    debug_init();
#endif
    const uint8_t LEDS_COUNT = 4;     

    Pin LEDs[] = {
        Pin(DDRB, PINB, PORTB, PINB5),
        Pin(DDRB, PINB, PORTB, PINB4),
        Pin(DDRB, PINB, PORTB, PINB3),
        Pin(DDRB, PINB, PORTB, PINB2)
    };
    for (int i = 0; i < LEDS_COUNT; ++i)
        LEDs[i].set_mode(PinMode::OUTPUT);
    off_all_leds(LEDs, LEDS_COUNT);

    Pin button(DDRC, PINC, PORTC, PINC1);
    button.set_mode(PinMode::INPUT_PULLUP);
    
    bool need_light = false;

    while (true)
    {
        bool current_button_state = (bool)button.read_input();
        off_all_leds(LEDs, LEDS_COUNT);

        if (need_light)
            for (int i = current_button_state; i < LEDS_COUNT; i += 2)
                LEDs[i].set_output(PinValue::LOW);

        _delay_ms(BLINK_DELAY);
        need_light = !need_light;
    }

    return 0;
}