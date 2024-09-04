#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	try {
		if (ac == 2) {
			BitcoinExchange wall_street(av[1]);
		}
		else 
			throw ("Error: could not open file.");
	}
	catch (const char *e) {
		std::cout << e << std::endl;
	}
	return 0;
}