#pragma once
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <deque>
#include <cmath>

extern int x;

void	ford_john(std::vector<int> vec_sort, std::deque<int> deq_sort);
size_t jacob_sthal(size_t i, size_t len);

template<typename T>
void	print_cont(T cont, std::string s) {
	std::cout << s;
	for (typename T::iterator it = cont.begin(); it != cont.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template<typename T>
std::vector<T> split_cont(T container, size_t cont_size, bool sort, int *k) {
	std::vector<T> groups;
	size_t i = 0;
	
	while (i < container.size()) {
		typename T::iterator it = container.begin() + i + cont_size;
		if (i + cont_size > container.size())
			it = container.end();
		T tmp(container.begin() + i, it);
		groups.push_back(tmp);
		i += cont_size;
	}
	i = 0;
	while (sort && i < groups.size() && i + 1 < groups.size() && groups[i].size() == groups[i + 1].size()) {
			(*k)++;
		if (groups[i].back() > groups[i + 1].back()){
			std::swap(groups[i], groups[i + 1]);
		}
		i += 2;
	}
	return groups;
}

template<typename T>
T join_cont(std::vector<T> groups) {
	T ret;
	for (typename std::vector<T>::iterator i = groups.begin(); i != groups.end(); ++i) {
		ret.insert(ret.end(), (*i).begin(), (*i).end());
	}
	return ret;
}

template<typename T>
bool compareByPos(const T& a, const T& b) {
	x++;
	return a.back() < b.back();
}

template<typename T>
T	sort_cont(T container, size_t cont_size, int *k) {
	std::vector<T> main_chain;
	size_t i = 3;
	std::vector<T> groups(split_cont(container, cont_size, 0, k));
	size_t jacob;
	main_chain.insert(main_chain.end(), groups.begin(), groups.begin() + 2);

	for (size_t it = 3; it < groups.size(); it += 2) {
			if (groups[it].size() == cont_size) {
				main_chain.push_back(groups[it]);
			}
	}
	while (main_chain.size() < groups.size() && i < groups.size()) {
		if (groups[i].size() == cont_size) {
			jacob = jacob_sthal(i, groups.size());
			while (jacob > 1) {
				if (groups[jacob].size() == cont_size && std::find(main_chain.begin(), main_chain.end(), groups[jacob]) == main_chain.end()) {
					if (!(jacob % 2)) {
						typename std::vector<T>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), groups[jacob], compareByPos<T>);
						main_chain.insert(it, groups[jacob]);
					}
				}
				jacob--;
			}
		}
		i++;
		if (groups.back().size() != main_chain.front().size() && main_chain.size() + 1 == groups.size())
			break;
	}
	if (main_chain.size() < groups.size())
		main_chain.push_back(groups.back());

	// for(typename std::vector<T>::iterator f = main_chain.begin(); f != main_chain.end(); ++f)
	// 	::print_cont(*f, "main: ");
	// std::cout << "============" << std::endl;
	return join_cont(main_chain);
}

// template<typename T>
// T	sort_cont(T container, size_t cont_size, int *k) {
// 	std::vector<T> main_chain;
// 	size_t i = 0;
// 	std::vector<T> groups(split_cont(container, cont_size, 0, k));

// 	while (i < groups.size()) {
// 		if(i < 2) {
// 			if (groups[i].size() == cont_size)
// 				main_chain.push_back(groups[i]);
// 		}
// 		else if (i % 2)
// 			main_chain.push_back(groups[i]);
// 		else if (groups[i].size() == cont_size){
// 			typename std::vector<T>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), groups[i], compareByPos<T>);
// 			main_chain.insert(it, groups[i]);
// 		}
// 		i++;
// 	}
// 	if (main_chain.size() < groups.size())
// 		main_chain.push_back(groups[i - 1]);
// 	return join_cont(main_chain);
// }

template<typename T>
T	ford_container(T container, int *k, size_t cont_size = 1) {
	std::vector<T> groups(split_cont(container, cont_size, 1, k));

	container = join_cont(groups);
	if (groups.size() > 4 || (groups.size() == 4 && groups.back().size() == groups.front().size()))
		container = ford_container(container, k, cont_size * 2);
	return sort_cont(container, cont_size, k);
}