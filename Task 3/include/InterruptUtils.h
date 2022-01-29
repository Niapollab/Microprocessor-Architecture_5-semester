#ifndef INTERRUPTUTILS_H
#define INTERRUPTUTILS_H

typedef void (*InterruptHandler)();

void set_handler(int row_index, InterruptHandler handler);

void init_interrupt();

void start_interrupt();

void stop_interrupt();

void invoke_interrupts();

#endif // INTERRUPTUTILS_H