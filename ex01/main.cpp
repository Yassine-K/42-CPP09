#include "RPN.hpp"
#include <string>

int main(int ac, char **av) {
	try {
		if (ac != 2)
			throw ("Invalid number of arguments!");
		std::string exp(av[1]);
		if (exp.find_first_not_of("0123456789+-*/ ") != std::string::npos)
			throw ("Invalid argument!");
		std::cout << calculator(exp) << std::endl;
	}
	catch (const char *s) {
		std::cout << "Error: " << s << std::endl;
	}
	return 0;
}