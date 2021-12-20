#include "Calculator.h"

Calculator::Calculator(int op1, int op2): _op1(op1), _op2(op2)
{
}

Calculator::Calculator(): Calculator(0, 0)
{
}

int Calculator::op1() const
{
    return _op1;
}

int& Calculator::op1()
{
    return _op1;
}

int Calculator::op2() const
{
    return _op2;
}

int& Calculator::op2()
{
    return _op2;
}

int Calculator::calculate_or() const
{
    return _op1 | _op2;
}

int Calculator::calculate_xor() const
{
    return _op1 ^ _op2;
}

int Calculator::calculate_and() const
{
    return _op1 & _op2;
}