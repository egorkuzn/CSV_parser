#include "csv_parser.hpp"
//sed '10a\\tCSVParser<int, float, std::string > parser{ in, skip };' main_pattern.cpp > main1.cpp
using namespace csv_parser;

int main() {
    int skip = 0;

    std::ifstream in("test.csv");
    std::ofstream out("output.txt");
    if(!in.is_open())
        return 1;
    //CSVParser<int, float, std::string > parser{ in, skip };
CSVParser<int, int, std::string, std::string> parser{ in, skip };

    for (auto& iter : parser) {
        out << iter << '\n';
    }
    return 0;
}
