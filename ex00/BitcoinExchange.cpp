#include "BitcoinExchange.hpp"
#include <cstddef>
#include <cstring>
#include <sstream>
#include <string>

std::string trim_whitespace(std::string str) {
	size_t start = str.find_first_not_of(" \t\r\v\n");
	if (start == str.find_last_not_of(" \t\r\v\n") && start == std::string::npos)
		return "";
	if (start != std::string::npos)
		str = str.std::string::substr(start, str.find_last_not_of(" \t\r\v\n") - start + 1);
	return str;
}

int valid_date(std::string date) {
	struct tm my_time;
	std::stringstream ss(date);
	std::string str;
	int i = 0;
	char *endp;
	bool is_leap;
	int date_elem[3] = {0,0,0};

    if (date.length() < 10 || strptime(date.c_str(), "%Y-%m-%d", &my_time) == nullptr)
		return 0;

	while (std::getline(ss, str, '-')) {
		date_elem[i] = std::strtod(str.c_str(), &endp);
		if (!date_elem[i])
			return 0;
		i++;
	}
	is_leap = (!(date_elem[0] % 4) && date_elem[0] % 100) || !(date_elem[0] % 400);
	if (date_elem[1] == 2 && ((is_leap && date_elem[2] > 29) || (!(is_leap) && date_elem[2] > 28)))
		return 0;
	if (date_elem[1] != 2 && date_elem[1] < 8 && !(date_elem[1] % 2) && date_elem[2] > 30)
		return 0;
	if (date_elem[1] > 7 && date_elem[1] % 2 && date_elem[2] > 30)
		return 0;
	return 1;
}

void	BitcoinExchange::check_validty(std::string line, std::string sep) {
	std::string tmp = trim_whitespace(sep);
	std::stringstream ss(line);
	std::string parts;
	std::string tmp_date;
	std::string tmp_date_range;
	std::string search_tmp_date;
	std::string search_tmp_date_range;
	char *endp;
	int i = 0;
	std::map<std::string, std::map<std::string, float> >::iterator cont_it;
	std::map<std::string, float>::iterator member_it;

	if (line.find(sep) != 10 || line.find_first_of(tmp) == std::string::npos || line.find_first_of(tmp) != line.find_last_of(tmp)) {
		if (tmp == ",")
			throw ("Error: invalid file structure!");
		else
			std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	while (std::getline(ss, parts, tmp[0])) {
		if (!i) {
			tmp_date = trim_whitespace(parts);
			tmp_date_range = tmp_date.substr(0, 7);
			if (valid_date(tmp_date)) {
				if (sep == ",")
					_my_db[tmp_date.substr(0, 7)][tmp_date] = 0;
			}
			else {
				if (sep == ",")
					throw ("Error: invalid file structure!");
				else
					std::cout << "Error: bad input => " << line << std::endl;
				return;
			}
			if (sep == "," && !tmp_date.empty())
				max = tmp_date;
		}
		else {
			int not_begin = 0;
			double val = std::strtod(trim_whitespace(parts).c_str(), &endp);
			if (endp[0] || (tmp == "|" && (val > 1000 || val < 0))) {
				if (sep == ",")
					throw ("Error: invalid file structure!");
				else {
					if (val > 1000)
						std::cout << "Error: too large a number" << std::endl;
					else if (val < 0)
						std::cout << "Error: not a positive number" << std::endl;
					else
						std::cout << "Error: bad input => " << line << std::endl;
				}
				return;
			}
			else {
				if (sep == ",")
					_my_db[tmp_date_range][tmp_date] = val;
				else {
					search_tmp_date_range = tmp_date_range;
					search_tmp_date = tmp_date;
					if (_my_db.find(tmp_date_range) != _my_db.end()) {
						if (_my_db[tmp_date_range].find(tmp_date) == _my_db[tmp_date_range].end()) {
							for (member_it = _my_db[tmp_date_range].begin(); member_it != _my_db[tmp_date_range].end(); ++member_it) {
								if (std::strcmp(tmp_date.c_str(), member_it->first.c_str()) < 0)
									break;
							}
							if (member_it != _my_db[tmp_date_range].end()) {
								if (member_it != _my_db[tmp_date_range].begin())
									member_it--;
								else
									not_begin++;
								search_tmp_date = member_it->first;
							}
							if (not_begin || member_it == _my_db[tmp_date_range].end()) {
								cont_it = _my_db.find(tmp_date_range);
								cont_it--;
								search_tmp_date_range = cont_it->first;
								search_tmp_date = cont_it->second.rbegin()->first;
							}
						}
				 		std::cout << tmp_date << " => " << val << " = " << _my_db[search_tmp_date_range][search_tmp_date] * val << std::endl;
					}
					else {
				 		std::cout << "not found " << tmp_date << std::endl;
					}
				}
			}
		}
		i++;
	}
}

void	BitcoinExchange::fill_file(std::ifstream &my_file, std::string sep) {
	std::string line;
	int i = 0;

	while (std::getline(my_file, line)) {
		line  = trim_whitespace(line);
		if (!i) {
			if ((sep == " | " && line != "date | value") || (sep == "," && line != "date,exchange_rate"))
				throw ("Error: invalid file structure!");
		}
		else if (i && !line.empty()) {
			check_validty(line, sep);
		}
		else
			std::cout << "Error: bad input => " << line << std::endl;
		i++;
	}
}

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(std::string path) : _my_file(path){
	std::ifstream db("data.csv");
	if (!_my_file.is_open() || !db.is_open())
		throw ("Error: could not open file.");
	fill_file(db, ",");
	fill_file(_my_file, " | ");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &) {
}

BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange &) {
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
}