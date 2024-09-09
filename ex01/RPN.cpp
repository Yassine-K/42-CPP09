#include "RPN.hpp"

int calculator (std::string exp) {
	int res = 0;
	std::list<int> nums;
	std::list<char> op;
	std::stringstream s(exp);
	std::string calc_elem;
	char *endp;
	std::string tokens = "+*/-";

	int i = 0;
	while (s >> calc_elem) {
		if (calc_elem.length() > 1)
			throw ("Invalid argument!");
		size_t op_i = calc_elem.find_first_of(tokens);
		if (op_i != std::string::npos && !i)
			throw ("Reverse Polish Notation not respected!");
		if (i && op_i != std::string::npos) {
			op.push_back(tokens[tokens.find(calc_elem[0])]);
		}
		else if (i) {
			nums.push_back(std::strtod(const_cast<char *>(calc_elem.c_str()), &endp));
		}
		else
			res = std::strtod(const_cast<char *>(calc_elem.c_str()), &endp);
		i++;
	}
	if (nums.size() != op.size())
		throw ("Reverse Polish Notation not respected!");
	std::list<char>::iterator op_it = op.begin();
	for (std::list<int>::iterator it = nums.begin(); it != nums.end(); ++it) {
	// std::cout << "Current op: " << res << *op_it << *it<< std::endl;
		switch (tokens.find(*op_it)) {
			case 0:
				res += *it;
				break;
			case 1:
				res *= *it;
				break;
			case 2:
				res /= *it;
				break;
			default:
				res -= *it;
				break;
		}
		++op_it;
	}
	return res;
}