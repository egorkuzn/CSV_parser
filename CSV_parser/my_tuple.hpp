#pragma once

#include <tuple>
#include <fstream>
#include <sstream>

namespace csv_parser {
	template<size_t>
	struct _int{};

	template<class A, class B, class Tuple, size_t Pos>
	std::basic_ofstream<A, B>& print_tuple(std::basic_ofstream<A, B>& os, const Tuple& t, _int<Pos>) {
		os << std::get<std::tuple_size<Tuple>::value - Pos>(t) << '\t';
		return print_tuple(os, t, _int<Pos - 1>());
	}

	template<class A, class B, class Tuple>
	std::basic_ofstream<A, B>& print_tuple(std::basic_ofstream<A, B>& os, const Tuple& t, _int<1>) {
		os << std::get<std::tuple_size<Tuple>::value - 1>(t);
		return os;
	}

	template<class A, class B, class... Args>
	std::basic_ofstream<A, B>& operator<<(std::basic_ofstream<A, B>& os, const std::tuple<Args...>& t) {
		print_tuple(os, t, _int<sizeof ...(Args)>());
		return os;
	}

	template<class T>
	std::istringstream& read_elem(std::istringstream& is, T& a);

	

}