#include "hi_user.hpp"

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

namespace csv_parser{
    HiUser::HiUser(std::string os){
        std::cout << GRN "CSV_Parser || NSU FIT 2022" NC << std::endl;
        std::cout << "Input example: " << std::endl;
        std::cout << CYN "<in.csv>\n3\nint\nfloat\nstd::string" << std::endl;
        std::cout << "<out.txt>" << NC "OR YOU CAN ALSO USE" CYN << "console" NC<< std::endl;
        inputFunction();
        processFunction();  
    }

    void HiUser::sleepcp(size_t seconds){
        clock_t time_end;
        time_end = clock() + seconds * CLOCKS_PER_SEC/1000;
        while (clock() < time_end){}
    }

    void HiUser::processFunction(){
        //sed '10a\\tCSVParser<int, float, std::string > parser{ in, skip };' main_pattern.cpp > main1.cpp
        std::string command = "sed '10a\\CSVParser<" + TStr + "> parser{ in, skip };' ../sandbox/main_pattern.cpp > ../sandbox/main1.cpp";
        system(command.c_str());
        system("g++ ../sandbox/main1.cpp -o ../sandbox/a.out -std=c++2a");
        sleepcp(10);
        system("./../sandbox/a.out");
    }

    void HiUser::inputFunction(){
        std::string input;
        std:: cin >> input;
        if(input[0] == '<' && input.find(">") != std::string::npos)
            in = input.substr(1, input.find('>') - 2);
        else{
            std::cout << RED "BAD FNAME INPUT" NC << std::endl;
            return;
        }

        size_t size;
        std::cin >> size;
        std::string str;

        for(size_t i; i < size; ++i){
            std::cin >> str;            
            if(str[0] == '<'){
                std::cout << RED "COUNT OF TYPES FEWER THAN EXPECTED" NC << std::endl;
                return;
            }
            TStr += str + ", ";
        }

        TStr.pop_back(); TStr.pop_back();

        std::string input;
        std::cin >> input;
        if(input == "console")
            console = true;
        else if(input[0] == '<' && input.find(">") != std::string::npos)
            out = input.substr(1, input.find('>') - 2);
        else {
            std::cout << RED "BAD FNAME INPUT OR COUNT OF TYPES MORE THAN ASKED" NC << std::endl;
            return;
        }
    }
}