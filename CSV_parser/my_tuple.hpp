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
	std::istringstream& read_elem(std::istringstream& is, T& a) {
		std::string data;
		getline(is, data, ',');
		std::istringstream(data) >> a;
		if (!is)
			throw std::exception();
		return is;
	}

	template<>
	std::istringstream& read_elem(std::istringstream& is, std::string& a) {
		getline(is, a, ',');
		return is;
	}

	template<class Tuple, size_t Pos>
	std::istringstream& read_tuple(std::istringstream& is, Tuple& t, _int<Pos>) {
		read_elem(is, std::get<std::tuple_size<Tuple>::value - 1>(t));
		return is;
	}

	template<class A, class B, class... Args>
	std::basic_ifstream<A, B>& operator>>(std::basic_ifstream<A, B>& is, std::tuple<Args...>& t) {
		std::string line;
		getline(is, line);
		if (line.empty())
			return is;
		std::istringstream str(line);
		read_tuple(str, t, _int<sizeof ...(Args)>());

		return is;
	}
}