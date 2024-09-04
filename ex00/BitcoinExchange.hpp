#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <map>
#include <ctime>

class BitcoinExchange {
	public:
		std::ifstream _my_file;
		std::string max;
		std::map<std::string, std::map<std::string, float> > _my_db;
		BitcoinExchange();
		BitcoinExchange(std::string);
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange & operator = (const BitcoinExchange &);
		~BitcoinExchange();
		void	fill_file(std::ifstream &, std::string);
		void	check_validty(std::string, std::string);
};