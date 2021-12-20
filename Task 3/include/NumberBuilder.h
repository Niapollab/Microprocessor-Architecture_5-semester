#ifndef NUMBERBUILDER_H
#define NUMBERBUILDER_H
#include "Digit.h"

class NumberBuilder
{
private:
    int _max_digit_count;
    int _current_pos;
    int _number;

public:
    NumberBuilder(int max_digit_count);

    bool can_add_digit() const;
    bool can_backspace() const;
    
    void add_digit(Digit digit);
    void backspace();
    void clear();
    int number() const;
};

#endif // NUMBERBUILDER_H
