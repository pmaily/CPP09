#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <time.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <map>

class BitcoinExchange{
    private:
        std::map<int,float> btc_value;
        static int          nb_day[12];
    public:
        BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange& src);
        ~BitcoinExchange(void);

        BitcoinExchange&   operator=(const BitcoinExchange& src);
        
        bool    readDatabase(void);
        void    parseLine(std::string line);
        int     checkDate(struct tm& date);
        void    findBtcValue(std::string line);
        bool    readSearchFile(std::string infile);

};

#endif