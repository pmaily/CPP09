#include "ValueBtc.hpp"

ValueBtc::ValueBtc(void)
{
}

ValueBtc::ValueBtc(std::string csv): database(csv, std::ifstream::in)
{

}

ValueBtc::ValueBtc(const ValueBtc& src) {}
ValueBtc::~ValueBtc(void) {}
ValueBtc&   ValueBtc::operator=(const ValueBtc& src) {return *this;}

void    ValueBtc::setDatabase(std::string csv)
{
    database.open(csv, std::ifstream::in);
}

void    ValueBtc::parseLine(std::string line)
{
    int         start = line.find_first_not_of("\t\n\v\f\r");
    int         end = line.find_first_not_of(",");
    std::string date(line.substr(0, end));

    if (end == std::string::npos)
        return ;
    for (int i, n = 0; i < line.size(); i++){
        
    }
}

void    ValueBtc::readDatabase(void)
{
    std::string line;
    char        *date;
    
    if (!database.is_open())
    {
        std::cerr << "Error: database required" << std::endl;
        return ;
    }
    while(!database.eof())
    {
        getline(database, line);
        
    }
}