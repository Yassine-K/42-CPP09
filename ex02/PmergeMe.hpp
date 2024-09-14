#pragma once
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
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
std::vector<T> split_cont(T container, int cont_size, bool sort, int *k) {
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
	size_t i = 0;
	while (i < groups.size()) {
		ret.insert(ret.end(), groups[i].begin(), groups[i].end());
		i++;
	}
	return ret;
}

template<typename T>
bool compareByPos(const T& a, const T& b) {
	return a.back() < b.back();
}

template<typename T>
T	sort_cont(std::vector<T> groups, size_t cont_size) {
	std::vector<T> main_chain;
	size_t i = 0;

	while (i < groups.size()) {
		if(i < 2) {
			if (groups[i].size() == cont_size)
				main_chain.push_back(groups[i]);
		}
		else if (i % 2)
			main_chain.push_back(groups[i]);
		else if (groups[i].size() == cont_size){
			typename std::vector<T>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), groups[i], compareByPos<T>);
			main_chain.insert(it, groups[i]);
		}
		i++;
	}
	if (main_chain.size() < groups.size())
		main_chain.push_back(groups[i - 1]);
	return join_cont(main_chain);
}

template<typename T>
T	ford_container(T container, int * k, size_t cont_size = 1) {
	std::vector<T> groups(split_cont(container, cont_size, 1, k));

	container = join_cont(groups);
	if (groups.size() > 4 || (groups.size() == 4 && groups.back().size() == groups.front().size()))
		container = ford_container(container, k, cont_size * 2);
	groups = (split_cont(container, cont_size, 0, k));
	return sort_cont(groups, cont_size);
}

void	ford_john(std::vector<int> vec_sort, std::deque<int> deq_sort);