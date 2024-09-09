#include "PmergeMe.hpp"
#include <iostream>
#include <sys/_types/_size_t.h>
#include <vector>

std::vector<int>	ford_vect(std::vector<int> vec) {
	int breakpoint = vec.size() / 2;
	if (vec.size() % 2)
		breakpoint++;

	std::vector<int> v1(vec.begin(), vec.begin() + breakpoint);
	std::vector<int> v2(vec.begin() + breakpoint, vec.end());
	std::pair<std::vector<int>, std::vector<int> > split_vector(v1, v2);
	if (vec.size() > 1) {
		split_vector.first = ford_vect(split_vector.first);
		split_vector.second = ford_vect(split_vector.second);
		size_t k = -1;
		for (size_t i = 0; i < split_vector.second.size(); i++) {
			while (++k < split_vector.first.size() && split_vector.first[k] < split_vector.second[i]);
			if (k == split_vector.first.size())
				split_vector.first.push_back(split_vector.second[i]);
			else{
				split_vector.first.insert(split_vector.first.begin() + k, split_vector.first[k]);
				split_vector.first[k] = split_vector.second[i];
			}
		}
		return split_vector.first;
	}
	return vec;
}

std::deque<int>	ford_deq(std::deque<int> deq) {
	int breakpoint = deq	.size() / 2;
	if (deq	.size() % 2)
		breakpoint++;

	std::deque<int> d1(deq.begin(), deq.begin() + breakpoint);
	std::deque<int> d2(deq.begin() + breakpoint, deq.end());
	std::pair<std::deque<int>, std::deque<int> > split_deque(d1, d2);
	if (deq.size() > 1) {
		split_deque.first = ford_deq(split_deque.first);
		split_deque.second = ford_deq(split_deque.second);
		size_t k = -1;
		for (size_t i = 0; i < split_deque.second.size(); i++) {
			while (++k < split_deque.first.size() && split_deque.first[k] < split_deque.second[i]);
			if (k == split_deque.first.size())
				split_deque.first.push_back(split_deque.second[i]);
			else{
				split_deque.first.insert(split_deque.first.begin() + k, split_deque.first[k]);
				split_deque.first[k] = split_deque.second[i];
			}
		}
		return split_deque.first;
	}
	return deq;
}

// void	print_cont(std::vector<int> vec, std::string s) {
// 	std::cout << s;
// 	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
// 		std::cout << *it << " ";
// 	}
// 	std::cout << std::endl;
// }

void	ford_john(std::vector<int> vec_sort, std::deque<int> deq_sort) {
	std::vector<int> res_vect = ::ford_container(vec_sort);
	std::deque<int> res_deq = ::ford_container(deq_sort);
	::print_cont(vec_sort, "Before: ");
	::print_cont(res_vect, "After: ");
	::print_cont(res_deq, "After: ");
	std::cout << "Time to process a range of " << vec_sort.size() << " elements with std::vector : " << "" << " us" << std::endl;
	std::cout << "Time to process a range of " << vec_sort.size() << " elements with std::deque : " << "" << " us" << std::endl;
}