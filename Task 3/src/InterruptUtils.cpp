#include "InterruptUtils.h"
#include <Arduino.h>

const int CLICK_DELAY = 400;
volatile bool ignore_interrupts = true;

const int INTERRUPT_COLUMN = 9;
const int INTERRUPT_ROWS[] = { 2, 3 };

unsigned long first_scan_millis = 0;
unsigned long second_scan_millis = 0;

InterruptHandler handlers[2];

void set_handler(int row_index, InterruptHandler handler)
{
    handlers[row_index] = handler;
}

void start_interrupt()
{
    ignore_interrupts = false;
}

void stop_interrupt()
{
    ignore_interrupts = true;
}

void handle_first_interrupt()
{
    if (!ignore_interrupts)
    {
        if (millis() - first_scan_millis >= 400)
        {
            first_scan_millis = millis();
            if (handlers[0])
                handlers[0]();
        }
    }
}

void handle_second_interrupt()
{
    if (!ignore_interrupts)
    {
        if (millis() - second_scan_millis >= 400)
            {
                second_scan_millis = millis();
                if (handlers[1])
                    handlers[1]();
            }
    }
}

void invoke_interrupts()
{
    if (!ignore_interrupts)
    {
        pinMode(INTERRUPT_COLUMN, OUTPUT);
        digitalWrite(INTERRUPT_COLUMN, LOW);
        
        digitalWrite(INTERRUPT_COLUMN, HIGH);
        pinMode(INTERRUPT_COLUMN, INPUT);
    }
}

void init_interrupt()
{
    pinMode(INTERRUPT_ROWS[0], INPUT_PULLUP);
    pinMode(INTERRUPT_ROWS[1], INPUT_PULLUP);

    handlers[0] = nullptr;
    handlers[1] = nullptr;

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_ROWS[0]), handle_first_interrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_ROWS[1]), handle_second_interrupt, CHANGE);
}