#ifndef VALUEBTC_HPP
# define VALUEBTC_HPP

#include <time.h>
#include <iostream>
#include <ofstream>

class ValueBtc{
    private:
        std::map<std::string,float> btc_value;
        std::ifstream               database;
    public:
        ValueBtc(void);
        ValueBtc(std::string csv);
        ValueBtc(const ValueBtc& src);
        ~ValueBtc(void);

        ValueBtc&   operator=(const ValueBtc& src);
        
        void    setDatabase(std::string csv);
};

#endif