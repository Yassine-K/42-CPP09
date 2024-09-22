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
			if (nums.size() > 1) {
				res = nums.back();
				nums.pop_back();
					switch (tokens.find(calc_elem[0])) {
						case 0:
							res = nums.back() + res;
							break;
						case 1:
							res = nums.back() * res;
							break;
						case 2:
							if (!res)
								throw("Can't divide by 0!");
							res = nums.back() / res;
							break;
						default:
							res = nums.back() - res;
							break;
					}
					nums.pop_back();
				nums.push_back(res);
			}
			else
				throw ("Reverse Polish Notation not respected!");
		}
		else {
			nums.push_back(std::strtod(const_cast<char *>(calc_elem.c_str()), &endp));
		}
		i++;
	}
	if (nums.size() > 1)
		throw ("Reverse Polish Notation not respected!");
	return res;
}