#include <tuple>
#include "csv_parser.hpp"
#include "my_tuple.hpp"
#include "hi_user.hpp"

using namespace csv_parser;

int main() {
    int skip = 0;

    std::ifstream in("test.csv");
    std::ofstream out("output.txt");
    CSVParser<int, double, std::string> parser{ in, skip };

    for (auto& iter : parser) {
        out << iter << '\n';
    }
    return 0;
}