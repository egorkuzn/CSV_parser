#include "hi_user.hpp"

using namespace csv_parser;

int main(){
    /* system("sed '10a\\\tCSVParser<int, float, std::string > parser{ in, skip };' sandbox/main_pattern.txt > sandbox/main1.cpp");
    system("g++ sandbox/main1.cpp -o sandbox/a.out -std=c++2a");
    system("./sandbox/a.out"); */
    HiUser obj(std::string("linux"));
    
    return 0;
}