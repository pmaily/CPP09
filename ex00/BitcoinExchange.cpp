#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
    *this = src;
}

BitcoinExchange::~BitcoinExchange(void) {}
BitcoinExchange&   BitcoinExchange::operator=(const BitcoinExchange& src)
{
    btc_value = src.btc_value;
    return *this;
}

int    BitcoinExchange::checkDate(struct tm& date)
{
    int     year = date.tm_year + 1900;
    int     totaldate;
    bool    leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    
    nb_day[1] += leap_year;
    if (date.tm_mday > nb_day[date.tm_mon])
        return 0;
    nb_day[1] -= leap_year;
    totaldate = year * 10000 + date.tm_mon * 100 + date.tm_mday;
    if (totaldate < 20090003)
        return 0;
    return totaldate;
}

bool    BitcoinExchange::readSearchFile(std::string infile_str)
{
    std::ifstream   infile;
    std::string     line;
    
    infile.open(infile_str.c_str(), std::ifstream::in);
    if (!infile.is_open())
    {
        std::cerr << "Error: cannot open infile" << std::endl;
        return 1;
    }
    if (btc_value.empty())
    {
        std::cerr << "Error: database required" << std::endl;
        return 1;
    }
    getline(infile, line);
    if (line != "date | value")
    {
        std::cout << "Error: bad input" << std::endl;
        return 1;
    }
    while(!infile.eof())
    {
        getline(infile, line);
        if (line.size())
            findBtcValue(line);
    }
    return 0;
}

void    BitcoinExchange::findBtcValue(std::string line)
{
    int         key;
    float       value;
    char        *ptr;
    size_t      sep(line.find_first_of(" "));
    std::string date(line.substr(0, sep));
    std::string valuestr;
    std::map<int,float>::iterator it;
    struct tm   tm;

    if (sep == std::string::npos || date.size() != 10 || !strptime(date.c_str(), "%F", &tm) || line.compare(sep, 3, " | ") || line.size() < 14)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return ;
    }
    valuestr = line.substr(13, line.size() - 13);
    key = checkDate(tm);
    value = strtod(valuestr.c_str(), &ptr);
    if (!key || (ptr && ptr[0]))
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return ;
    }
    if (value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return ;
    }
    if (value > 1000)
    {    
        std::cerr << "Error: too large a number." << std::endl;
        return ;
    }    
    it = btc_value.upper_bound(key);
    if ((it->first > key || it == btc_value.end()) && it != btc_value.begin())
        it--;
    if (it == btc_value.begin() && key < btc_value.begin()->first)
    {
        std::cerr << "Error: unkown value for this date" << std::endl;
        return ;
    }
    std::cout << date << " => " << value << " = " << value * it->second << '\n';
}        

void    BitcoinExchange::parseLine(std::string line)
{
    int         key;
    float       value;
    char        *ptr;
    size_t      sep(line.find_first_of(","));
    std::string date(line.substr(0, sep));
    std::string valuestr(line.erase(0,sep + 1));
    struct tm   tm;

    if (sep == std::string::npos || date.size() != 10 || !strptime(date.c_str(), "%F", &tm))
        return ;
    key = checkDate(tm);
    value = strtod(valuestr.c_str(), &ptr);
    if (!key || (ptr && ptr[0]) || value < 0 || value == std::numeric_limits<float>::infinity())
        return ;
    btc_value.insert(std::pair<int, float>(key, value));
}

bool    BitcoinExchange::readDatabase(void)
{
    std::string     line;
    std::ifstream   database("data.csv", std::ifstream::in);
    
    if (!database.is_open())
    {
        std::cerr << "Error: database required" << std::endl;
        return 1;
    }
    getline(database, line);
    if (line != "date,exchange_rate")
        return 1;
    while(!database.eof())
    {
        getline(database, line);
        parseLine(line);
    }
    return 0;
}

int BitcoinExchange::nb_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};