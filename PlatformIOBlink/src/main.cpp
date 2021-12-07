#include <Arduino.h>
#ifdef __PLATFORMIO_BUILD_DEBUG__
#include <avr_debugger.h>
#endif

#define BLINK_DELAY 2000

void setup()
{
#ifdef __PLATFORMIO_BUILD_DEBUG__
    debug_init();
#endif
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(BLINK_DELAY);
}