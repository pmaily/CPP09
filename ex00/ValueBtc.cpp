#include "ValueBtc.hpp"

ValueBtc::ValueBtc(void)
{
}

ValueBtc::ValueBtc(std::string csv): database(csv, std::ifstream::in)
{

}

ValueBtc::ValueBtc(const ValueBtc& src);
ValueBtc::~ValueBtc(void)
ValueBtc&   ValueBtc::operator=(const ValueBtc& src);

void    ValueBtc::setDatabase(std::string csv)
{
    database.open(csv, std::ifstream::in);
}

void    ValueBtc::readDatabase(void)
{
    std::string line;
    char        *date;
    
    if (!btc_value.is_open())
    {
        std::cerr << "Error: database required" << std::endl;
        return ;
    }
    while(!database.eof())
    {
        line = database.getline();
        
    }
}