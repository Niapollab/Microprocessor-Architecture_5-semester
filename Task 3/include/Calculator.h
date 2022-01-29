#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator
{
private:
    int _op1;
    int _op2;

public:
    Calculator(int op1, int op2);
    Calculator();

    int op1() const;
    int& op1();

    int op2() const;
    int& op2();

    int calculate_or() const;
    int calculate_xor() const;
    int calculate_and() const;
};

#endif // CALCULATOR_H
