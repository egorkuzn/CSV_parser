#pragma once

#include <tuple>
#include <fstream>
#include <sstream>
#include <regex>
#include "csv_exceptions.hpp"
#include <typeinfo>
#include <iomanip>


template<std::size_t>
struct int_ {};

uint8_t getSize(std::string TName){
    if(TName == "i" || TName == "f" || TName == "d")
        return 5;
    else 
        return 20;
}

template<class CharT, class Traits, class Tuple, size_t Pos>
std::basic_ofstream<CharT, Traits>& print_tuple(std::basic_ofstream<CharT, Traits>& os, const Tuple& t, int_<Pos>) {
    if(csv_error::isInputFailure()){
        os << csv_error::exceptionComment();
        return os;
    }
    uint8_t size = getSize(typeid(std::get<std::tuple_size<Tuple>::value - Pos>(t)).name());
    os << std::setw(size) << std::get<std::tuple_size<Tuple>::value - Pos>(t) << '|';
    return print_tuple(os, t, int_<Pos - 1>());
}

template<class CharT, class Traits, class Tuple>
std::basic_ofstream<CharT, Traits>& print_tuple(std::basic_ofstream<CharT, Traits>& os, const Tuple& t, int_<1>) {
    if(csv_error::isInputFailure()){
        os << csv_error::exceptionComment();
        return os;
    }
    uint8_t size = getSize(typeid(std::get<std::tuple_size<Tuple>::value - 1>(t)).name());
    os << std::setw(size) << std::get<std::tuple_size<Tuple>::value - 1>(t) << '|';// taking from the exception stack buffer
    csv_error::outPointer++;     
    return os;
}

template<class CharT, class Traits, class... Args>
std::basic_ofstream<CharT, Traits>& operator<<(std::basic_ofstream<CharT, Traits>& os, const std::tuple<Args...>& t) {
    os << '|';
    print_tuple(os, t, int_<sizeof ...(Args)>());
    return os;
}

template<class T>
std::istringstream& read_element(std::istringstream& is, T& a) {
    std::string subStr;
    getline(is, subStr, ',');
    std::istringstream(subStr) >> a;
    csv_error::numbInStr++;    
    std::string TName = typeid(T).name();
    if(!is)
        csv_error::typeDismatching();
    else if(TName == "f" || TName == "d"){
        csv_error::numberCheck(subStr);
    }
    else if (not(std::to_string(a) == subStr) && not(' ' + std::to_string(a) == subStr))
        csv_error::typeDismatching();
    return is;
}

template<>
std::istringstream& read_element(std::istringstream& is, std::string& a) {
    getline(is, a, ',');
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
    if(csv_error::isLengthMatching(str, sizeof ...(Args)))
        read_tuple(instr, t, int_<sizeof ...(Args)>());        

    return is;
}

