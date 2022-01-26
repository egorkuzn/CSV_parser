cmake_minimum_required(VERSION 3.16.3)
project(hello_csv)

#add_subdirectory(sandbox)

set(CMAKE_CXX_STANDARD 20)
#hi_user.hpp hi_user.cpp csv_parser.hpp my_tuple.hpp csv_exceptions.hpp
add_executable(hello_csv main.cpp hi_user.hpp hi_user.cpp)
