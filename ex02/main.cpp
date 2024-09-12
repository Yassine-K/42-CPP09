#include "PmergeMe.hpp"

int main(int ac, char **av) {
	std::vector<int> vec_sort;
	std::deque<int> deq_sort;
	char * endp;

	try {
		if (ac < 2)
			throw ("Empty sequence!");
		if (ac < 3)
			throw ("Nothing to be sorted!");
		for (int i = 1; i < ac; i++) {
			std::string tmp = av[i];
			if (tmp.empty() || tmp.find_first_not_of("0123456789") != std::string::npos)
				throw ("Invalid argument!");
			int val = std::strtod(tmp.c_str(), &endp);
			if (std::find(vec_sort.begin(), vec_sort.end(), val) != vec_sort.end())
				throw ("Duplicated number!");
			vec_sort.push_back(val);
			deq_sort.push_back(val);
		}
		ford_john(vec_sort, deq_sort);
	}
	catch (const char *e) {
		std::cout << "Error: " << e << std::endl;
	}
	return 0;
}