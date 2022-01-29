#include <Arduino.h>
#include <TM1637Display.h>
#include <math.h>

#define CLK 2
#define DIO 3
#define DELAY 1000
#define MINUS_SG 0b01000000
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

struct SecondOutputData
{
    bool is_negative;
    int whole;
    int fractal;
};

SecondOutputData convert_to_second_task(int number)
{
    bool has_sign = number < 0;
    int first_digit = abs(number) / 100;
    int second_digits = abs(number) % 100;

    return SecondOutputData { has_sign, first_digit, second_digits };
}

TM1637Display display(CLK, DIO);

void draw(TM1637Display &display, const SecondOutputData& data)
{
    display.clear();

    uint8_t segments[4];

    if (data.is_negative)
        segments[0] = MINUS_SG;

    uint8_t whole_digit = data.whole;
    while (whole_digit > 9)
        whole_digit /= 10;

    segments[1] = display.encodeDigit(whole_digit);

    uint8_t fractal_digits = data.fractal;
    while (whole_digit > 99)
        whole_digit /= 10;

    segments[2] = display.encodeDigit(fractal_digits / 10);
    segments[3] = display.encodeDigit(fractal_digits % 10);

    segments[1] |= 0b10000000;

    display.setSegments(segments, 4, 0);
}

void setup()
{
    display.setBrightness(5);
}

int get_segments_count(int number)
{
    int abs_number = abs(number);
    bool less_than_zero = number < 0;

    int log_result = abs_number ? log10(abs_number) : 0;

    return (int)(log_result + less_than_zero + 1);
}

void first_task()
{
    for (int i = 100; i >= -100; i -= 10)
    {
        display.clear();
        display.showNumberDec(i, false, get_segments_count(i), 0);
        delay(DELAY);
    }
    delay(DELAY);
}

void second_task()
{
    const uint8_t minus[] = { SEG_G };
    for (int i = 300; i >= -300; i -= 25)
    {
        display.clear();

        display.showNumberDecEx(abs(i), 0xff, true, 3, 1);

        if (i < 0)
            display.setSegments(minus, 1);

        delay(DELAY);
    }
    delay(DELAY);
}

void third_task()
{
    const int SIZE = 17;
    uint8_t segments[] = { LIT_SPACE, LIT_SPACE, LIT_SPACE, LIT_Q, LIT_U, LIT_E, LIT_U, LIT_E, LIT_SPACE, LIT_F, LIT_U, LIT_L, LIT_L, LIT_SPACE, LIT_SPACE, LIT_SPACE, LIT_SPACE };
    for (int i = 0; i < SIZE - 4; ++i)
    {
        display.setSegments(segments + i, 4);
        delay(DELAY);
    }
    delay(DELAY);
}

void loop()
{
    typedef void (*task_ptr)();
    display.clear();
    task_ptr funcs[] = { first_task, second_task, third_task };
    
    for (int i = 0;; i = (i + 1) % 3)
    {
        display.clear();
        funcs[i]();
    }
}
