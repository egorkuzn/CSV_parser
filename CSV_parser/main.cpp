#include "csv_parser.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream file("test.csv");
    csv_parser::CSVParser<int, std::string> parser(file, 0 /*skip first lines count*/);
    for (std::tuple<int, std::string> rs : parser) {
        std::cout << rs << std::endl;
    }
}
