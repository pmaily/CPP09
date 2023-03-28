#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    BitcoinExchange test;
    
    if (ac != 2)
    {
        std::cerr << "Error: need one argument" << std::endl;
        return 1; 
    }
    if (test.readDatabase() || test.readSearchFile(av[1]))
        return 1;
    return 0;
}