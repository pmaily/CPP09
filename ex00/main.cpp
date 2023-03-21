#include <time.h>
#include <iostream>
#include <cstring>

int main(int ac, char **av)
{
    std::string test("2016-02-31,1fef,");
    struct tm tm;


    if (!strptime(test.c_str(), "%F", &tm))
        std::cerr << "invalide date" << std::endl;

    char buff[16];
    strftime(buff, 16, "%F", &tm);
    std::cout << buff << std::endl;
    
}