#include "RPN.hpp"

RPN::RPN(void){}

RPN::RPN(const RPN& src){*this = src;}

RPN::~RPN(void){}

RPN& RPN::operator=(const RPN& src)
{
    value = src.value;
    return *this;
}


void    RPN::addValue(int value)
{
    this->value.push(value);
}

void    RPN::addoper(char oper)
{
    float result;

    if (value.size() < 2)
        throw std::logic_error("Error: too few values to proceed an operation");
    result = value.top();
    value.pop();
    if (oper == '+')
        value.top() += result;
    else if (oper == '-')
        value.top() -= result;
    else if (oper == '/')
        value.top() /= result;
    else if (oper == '*')
        value.top() *= result;
}

void    RPN::displayResult(void)
{
    if (value.size() != 1)
        throw std::logic_error("Error: wrong number of values to dispaly result");
    std::cout << value.top() << std::endl;
}