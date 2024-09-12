#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <sys/_types/_size_t.h>
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

// template<typename T>
// T	ford_container(T container, int *incr) {
// 	int breakpoint = container.size() / 2;
// 	if (container.size() % 2)
// 		breakpoint++;

// 	T c1(container.begin(), container.begin() + breakpoint);
// 	T c2(container.begin() + breakpoint, container.end());
// 	std::pair<T, T> split_container(c1, c2);
// 	if (container.size() > 1) {
// 		split_container.first = ford_container(split_container.first, incr);
// 		split_container.second = ford_container(split_container.second, incr);
// 		size_t k = -1;
// 		for (size_t i = 0; i < split_container.second.size(); i++) {
// 			while (++k < split_container.first.size() && split_container.first[k] < split_container.second[i]){(*incr)++;};
// 			if (k == split_container.first.size())
// 				split_container.first.push_back(split_container.second[i]);
// 			else{
// 				split_container.first.insert(split_container.first.begin() + k, split_container.first[k]);
// 				split_container.first[k] = split_container.second[i];
// 			}
// 		}
// 		return split_container.first;
// 	}
// 	return container;
// }

template<typename T>
std::vector<T> split_cont(T container, int cont_size) {
	std::vector<T> groups;
	size_t i = 0;

	while (i < container.size()) {
		T tmp(container.begin() + i, container.begin() + i + cont_size);
		groups.push_back(tmp);
		i += cont_size;
		// std::cout << tmp.size() << std::endl;
		// print_cont(groups.back(), "=========> ");
	}
	i = 0;
	while (i < groups.size() && i + 1 < groups.size()) {
		if (groups[i].back() > groups[i + 1].back()){
			// ::print_cont(groups[i], "Old groups[i]: ");
			// ::print_cont(groups[i + 1], "Old groups[i + 1]: ");
			std::swap(groups[i], groups[i + 1]);
			// ::print_cont(groups[i], "groups[i]: ");
			// ::print_cont(groups[i + 1], "groups[i + 1]: ");
		}
		i += 2;
	}
	return groups;
}

template<typename T>
T join_cont(std::vector<T> groups) {
	T ret;
	size_t i = 0;
	while (i < groups.size()) {
		ret.insert(ret.end(), groups[i].begin(), groups[i].end());
		i++;
	}
	return ret;
}

template<typename T>
T	ford_container(T &container, int cont_size = 1) {
	std::vector<T> groups(split_cont(container, cont_size));

	container = join_cont(groups);
	if (groups.size() > 4 || (groups.size() == 4 && groups.back().size() == groups.front().size()))
		ford_container(container, cont_size * 2);
	return container;
}

void	ford_john(std::vector<int> vec_sort, std::deque<int> deq_sort);