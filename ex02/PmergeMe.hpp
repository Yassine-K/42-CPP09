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
								::print_cont(a, "A == ");
								::print_cont(b, "B == ");
	return a.back() < b.back();
}

template<typename T>
T	sort_cont(T container, size_t cont_size, int *k) {
	std::vector<T> main_chain;
	size_t i = 4;
	size_t end = 1;
	std::vector<T> groups(split_cont(container, cont_size, 0, k));
	size_t jacob;

	main_chain.insert(main_chain.end(), groups.begin(), groups.begin() + 2);

	for (size_t it = 3; it < groups.size(); it += 2) {
		if (groups[it].size() == cont_size) {
			main_chain.push_back(groups[it]);
		}
	}
	// std::cout << "-------------------------start-------------------------" << std::endl;
	while (main_chain.size() < groups.size() && i < groups.size()) {
		if (groups[i].size() == cont_size) {
				jacob = jacob_sthal(i, groups.size());
				while ( jacob > end) {
					if (!(jacob % 2) && groups[jacob].size() == cont_size) {
						std::cout << "-------------------------Before: " << x << std::endl;
							for(typename std::vector<T>::iterator f = main_chain.begin(); f != main_chain.end(); ++f)
								::print_cont(*f, "main: ");
							typename std::vector<T>::iterator it_end = std::find(main_chain.begin(), main_chain.end(), groups[jacob + 1]);
							typename std::vector<T>::iterator it = std::lower_bound(main_chain.begin(), it_end, groups[jacob], compareByPos<T>);
								::print_cont(*(it), "res==========: ");
						std::cout << "-------------------------After: " << x << std::endl;
							main_chain.insert(it, groups[jacob]);
					}
					jacob--;
				}
				end = jacob_sthal(i, groups.size());
		}
		i++;
		if (groups.back().size() != main_chain.front().size() && main_chain.size() + 1 == groups.size())
			break;
	}
	if (main_chain.size() < groups.size())
		main_chain.push_back(groups.back());
	return join_cont(main_chain);
}

template<typename T>
T	ford_container(T container, int *k, size_t cont_size = 1) {
	std::vector<T> groups(split_cont(container, cont_size, 1, k));

	container = join_cont(groups);
	if (groups.size() > 4 || (groups.size() == 4 && groups.back().size() == groups.front().size()))
		container = ford_container(container, k, cont_size * 2);
	return sort_cont(container, cont_size, k);
}