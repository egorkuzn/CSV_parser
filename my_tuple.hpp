#pragma once

#include <tuple>
#include <fstream>
#include <sstream>
#include <regex>

template<std::size_t>
struct int_ {};

template<class CharT, class Traits, class Tuple, size_t Pos>
std::basic_ofstream<CharT, Traits>& print_tuple(std::basic_ofstream<CharT, Traits>& os, const Tuple& t, int_<Pos>) {
    os << std::get<std::tuple_size<Tuple>::value - Pos>(t) << '\t';
    return print_tuple(os, t, int_<Pos - 1>());
}

template<class CharT, class Traits, class Tuple>
std::basic_ofstream<CharT, Traits>& print_tuple(std::basic_ofstream<CharT, Traits>& os, const Tuple& t, int_<1>) {
    os << std::get<std::tuple_size<Tuple>::value - 1>(t);
    return os;
}

template<class CharT, class Traits, class... Args>
std::basic_ofstream<CharT, Traits>& operator<<(std::basic_ofstream<CharT, Traits>& os, const std::tuple<Args...>& t) {
    print_tuple(os, t, int_<sizeof ...(Args)>());
    return os;
}

template<class T>
std::istringstream& read_element(std::istringstream& is, T& a) {
    std::string data;
    getline(is, data, ',');
    std::istringstream(data) >> a;
    if (!is)
        throw std::exception();
    return is;
}

template<>
std::istringstream& read_element(std::istringstream& is, std::string& a) {
    getline(is, a, ',');
    if(a.find("_comma_") != std::string::npos)
        a = std::regex_replace(a, std::regex("__comma__"), ",");
    return is;
}


template<class Tuple, size_t Pos>
std::istringstream& read_tuple(std::istringstream& is, Tuple& t, int_<Pos>) {
    read_element(is, std::get<std::tuple_size<Tuple>::value - Pos>(t));
    return read_tuple(is, t, int_<Pos - 1>());
}

template<class Tuple>
std::istringstream& read_tuple(std::istringstream& is, Tuple& t, int_<1>) {
    read_element(is, std::get<std::tuple_size<Tuple>::value - 1>(t));
    return is;
}

template<class CharT, class Traits, class... Args>
std::basic_ifstream<CharT, Traits>& operator>>(std::basic_ifstream<CharT, Traits>& is, std::tuple<Args...>& t) {
    std::string str;
    getline(is, str);
    if (str.empty())
        return is;
    std::istringstream instr(str);
    read_tuple(instr, t, int_<sizeof ...(Args)>());

    return is;
}

