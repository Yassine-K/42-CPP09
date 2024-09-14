#include "PmergeMe.hpp"
#include <iostream>
#include <sys/_types/_size_t.h>
#include <vector>

int x = 0;

void	ford_john(std::vector<int> vec_sort, std::deque<int> deq_sort) {
	int i = 0;
	int j = 0;
	::print_cont(vec_sort, "Before: ");
	std::vector<int> res_vect = ::ford_container(vec_sort, &i);
	i += x;
	x = 0;
	std::deque<int> res_deq = ::ford_container(deq_sort, &j);
	::print_cont(res_vect, "After: ");
	::print_cont(res_deq, "After: ");
	std::cout << "Time to process a range of " << vec_sort.size() << " elements with std::vector : " << "" << " us" << std::endl;
	std::cout << "Time to process a range of " << vec_sort.size() << " elements with std::deque : " << "" << " us" << std::endl;
	std::cout << "A: " << i  << std::endl;
	std::cout << "B: " << j + x << std::endl;
}