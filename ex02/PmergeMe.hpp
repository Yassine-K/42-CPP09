#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>


template<typename T>
void	print_cont(T cont, std::string s) {
	std::cout << s;
	for (typename T::iterator it = cont.begin(); it != cont.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


template<typename T>
T	ford_container(T container) {
	int breakpoint = container.size() / 2;
	if (container.size() % 2)
		breakpoint++;

	T c1(container.begin(), container.begin() + breakpoint);
	T c2(container.begin() + breakpoint, container.end());
	std::pair<T, T> split_container(c1, c2);
	if (container.size() > 1) {
		split_container.first = ford_container(split_container.first);
		split_container.second = ford_container(split_container.second);
		size_t k = -1;
		for (size_t i = 0; i < split_container.second.size(); i++) {
			while (++k < split_container.first.size() && split_container.first[k] < split_container.second[i]);
			if (k == split_container.first.size())
				split_container.first.push_back(split_container.second[i]);
			else{
				split_container.first.insert(split_container.first.begin() + k, split_container.first[k]);
				split_container.first[k] = split_container.second[i];
			}
		}
		return split_container.first;
	}
	return container;
}

void	ford_john(std::vector<int> vec_sort, std::deque<int> deq_sort);