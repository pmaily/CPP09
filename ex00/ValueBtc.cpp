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

int    checkDate(struct tm& date)
{
    int     year = date.tm_year + 1900;
    int     totaldate;
    bool    leap_year = 0;
    

    leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    nb_months[1] += leap_year;
    if (day > nb_day[date.tm_mon])
        return 0;
    nb_months[1] -= leap_year;
    totaldate = year * 10000 + date.tm_mon * 100 + date.tm_day;
    if (totaldate < 20090103)
        return 0;
    return totaldate;
}

void    ValueBtc::parseLine(std::string line)
{
    int         sep(line.find_first__of(","));
    std::string date(line.substr(0, sep));
    std::string value(line.erase(0,sep));
    struct tm   tm;

    if (sep == std::string::npos || date.size() != 10 || !strptime(date.c_str(), "%F", &tm))
        return ;
    checkDate(tm);
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
    getline(database, line);
    if (line != "date,exchange_rate")
        return ;
    while(!database.eof())
    {
        getline(database, line);
    }
}

int ValueBtc::nb_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};