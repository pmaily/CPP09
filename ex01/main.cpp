#include "RPN.hpp"
#include <cstring>

bool    SendToRpn(RPN& rpn_calculator, const std::string& str)
{
    int i = 0;

    while (str[i])
    {
        if (strchr("+-*/",str[i]))
            rpn_calculator.addoper(str[i]);
        else if (std::isdigit(str[i]))
            rpn_calculator.addValue(str[i] - '0');
        else
        {
            std::cerr << "Error: bad character in the string" << std::endl;
            return 0;
        }
        i++;
    }
    return 1;
}

bool    ParseEntry(RPN& rpn_calculator, std::string str)
{
    size_t		start = 0;
	size_t		end = 0;

	while (str[end])
    {
		start = str.find_first_not_of(" \t\n\v\f\r", end);
		end = str.find_first_of(" \t\n\v\f\r", start);
        if (end == std::string::npos)
            end = str.length();
		if (start >= str.length())
			break;
        if (!SendToRpn(rpn_calculator, str.substr(start, end - start)))
            return 0;
    }
    return 1;
}

int main(int ac, char **av)
{
    RPN test;

    if (ac != 2)
    {
        std::cerr << "Error: wrong number of arguments" << std::endl;
        return 1;
    }
    try{
        if (!ParseEntry(test, av[1]))
            return 0;
        test.displayResult();
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }


}