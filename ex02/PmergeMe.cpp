#include "PmergeMe.hpp"

// int x = 0;

void	ford_john(std::vector<int> vec_sort, std::deque<int> deq_sort) {
	int i = 0;
	int j = 0;
	long cont_time[2][2];
    timeval tv;
	
    gettimeofday(&tv, NULL);
	::print_cont(vec_sort, "Before: ");
    cont_time[vect][0] = tv.tv_usec;
	std::vector<int> res_vect = ::ford_container(vec_sort, &i);
    gettimeofday(&tv, NULL);
    cont_time[vect][1] = tv.tv_usec;
	// i += x;
	// x = 0;
    gettimeofday(&tv, NULL);
    cont_time[deq][0] = tv.tv_usec;
	std::deque<int> res_deq = ::ford_container(deq_sort, &j);
    gettimeofday(&tv, NULL);
    cont_time[deq][1] = tv.tv_usec;
	::print_cont(res_vect, "After: ");
	::print_cont(res_deq, "After: ");
	std::cout << "Time to process a range of " << vec_sort.size() << " elements with std::vector : " << cont_time[vect][1] - cont_time[vect][0] << " us" << std::endl;
	std::cout << "Time to process a range of " << vec_sort.size() << " elements with std::deque : " << cont_time[deq][1] - cont_time[deq][0] << " us" << std::endl;
	// std::cout << "A: " << i  << std::endl;
	// std::cout << "B: " << j + x << std::endl;
}

size_t jacob_sthal(size_t i, size_t len) {
	size_t res = (std::pow(2, i) - std::pow(-1, i)) / 3;
	if (res >= len)
		res = len - 1;
	return res;
}