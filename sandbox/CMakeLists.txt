cmake_minimum_required(VERSION 3.16.3)
project(my_csv)

set (CMAKE_CXX_STANDARD 20)

add_executable(my_csv main1.cpp csv_exceptions.hpp csv_parser.hpp my_tuple.hpp)

