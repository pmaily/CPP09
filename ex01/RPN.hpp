#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>

class RPN{
    private:
        std::stack<float>     value;

    public:
        RPN(void);
        RPN(const RPN& src);
        ~RPN(void);

        RPN& operator=(const RPN& src);

        void    addValue(int value);
        void    addoper(char oper);

        void    displayResult(void);

};

#endif