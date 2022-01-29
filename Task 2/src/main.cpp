#include <Arduino.h>
#ifdef __PLATFORMIO_BUILD_DEBUG__
#include <avr_debugger.h>
#endif
#include <DHT.h>
#include <TM1637Display.h>

#define DELAY 2000
#define CLK 2
#define DIO 3
#define DHT_PIN 4
#define LIT_A SEG_E | SEG_F | SEG_A | SEG_B | SEG_C | SEG_G
#define LIT_B SEG_F | SEG_E | SEG_D | SEG_C | SEG_G
#define LIT_C SEG_D | SEG_E | SEG_F | SEG_A
#define LIT_D SEG_G | SEG_E | SEG_D | SEG_C | SEG_B
#define LIT_E SEG_A | SEG_F | SEG_G | SEG_E | SEG_D
#define LIT_F SEG_A | SEG_F | SEG_G | SEG_E
#define LIT_G SEG_A | SEG_F | SEG_E | SEG_D | SEG_C
#define LIT_H (SEG_F | SEG_G | SEG_B | SEG_E | SEG_C)
#define LIT_I SEG_F | SEG_E
#define LIT_J SEG_D | SEG_C | SEG_B
#define LIT_L SEG_F | SEG_E | SEG_D
#define LIT_N SEG_E | SEG_G | SEG_C
#define LIT_O SEG_E | SEG_G | SEG_C | SEG_D
#define LIT_P SEG_E | SEG_F | SEG_A | SEG_B | SEG_G
#define LIT_Q SEG_F | SEG_A | SEG_B | SEG_G | SEG_C
#define LIT_R SEG_E | SEG_G
#define LIT_T SEG_F | SEG_G | SEG_E | SEG_D
#define LIT_U SEG_F | SEG_E | SEG_D | SEG_C | SEG_B
#define LIT_Y SEG_F | SEG_G | SEG_B | SEG_C | SEG_D
#define LIT_SPACE 0

DHT sensor(DHT_PIN, DHT11);
TM1637Display display(CLK, DIO);

void setup()
{
#ifdef __PLATFORMIO_BUILD_DEBUG__
    debug_init();
#endif
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    sensor.begin();
    display.setBrightness(5);
}

void print_temperature(TM1637Display& display, DHT& sensor, bool fahrenheit = false)
{
    const uint8_t CELSIUS_TIP[] = {
        LIT_SPACE,
        LIT_C
    };

    const uint8_t FAHRENHEIT_TIP[] = {
        LIT_SPACE,
        LIT_F
    };

    display.clear();
    int temperature_c = sensor.readTemperature(fahrenheit);
    display.showNumberDec(temperature_c, false, 2, 0);
    display.setSegments(fahrenheit ? FAHRENHEIT_TIP : CELSIUS_TIP, 2, 2);
}

void print_humidity(TM1637Display& display, DHT& sensor)
{
    const uint8_t HUMIDITY_TIP[] = {
        SEG_A | SEG_F | SEG_G | SEG_B,
        LIT_O
    };

    display.clear();
    int humidity = sensor.readHumidity();
    display.showNumberDec(humidity, false, 2, 0);
    display.setSegments(HUMIDITY_TIP, 2, 2);
}

void loop()
{
    print_temperature(display, sensor);
    delay(DELAY);
    print_humidity(display, sensor);
    delay(DELAY);
}