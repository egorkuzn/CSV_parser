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
        if(!errorDetected){
            std::cout << GRN "0%==";
            processFunction();  
        }
    }

    void HiUser::sleepcp(size_t seconds){
        clock_t time_end;
        time_end = clock() + seconds * CLOCKS_PER_SEC;
        while (clock() < time_end){}
    }

/*      void getInputFile(){
        if(in != "<>"){
            std::string command = "cd ..\n cd sandbox \n cat  " + in + " > test.csv";
            system(command); 
        }
    }
 */ 
/*      void HiUser::consoleOutput(){
        std::string getcontent;
        std::ifstream openfile ("../sandbox/output.txt");
        if(openfile.is_open()){
            while(! openfile.eof())
            {                
                std::string str;
                for(size_t i = 0; i < size + 1; ++i){
                openfile >> getcontent;
                str += getcontent;
                if(getcontent.back() != '|'){
                    while(getcontent.back() != '|')
                        str += getcontent;
                    break;
                    }

                }

                if(str.back() != '|')
                    std::cout << RED << str << NC <<std::endl;
                else
                    std::cout << CYN << str << NC << std::endl;
            }
        }
    }
 
 */    void HiUser::processFunction(){
        //getInputFile();
        std::string command = "sed '12a\\CSVParser<" + TStr + "> parser{ in, skip };' ../sandbox/main_pattern.txt > ../sandbox/main1.cpp";
        std::cout << "==";
        system(command.c_str());
        std::cout << "===" ;
        system("g++ ../sandbox/main1.cpp -o ../sandbox/a.out -std=c++2a");
        std::cout << "=====" ;
        sleepcp(0);
        system("cd .. \n cd sandbox \n ./a.out");
        std::cout << "========>100%" NC <<std::endl; 
        //consoleOutput();       
    }

    void HiUser::inputFunction(){
        std::string input;
        std:: cin >> input;
        if(input[0] == '<' && input.find(">") != std::string::npos)
            in = input.substr(1, input.find('>') - 2);
        else{
            std::cout << RED "BAD FNAME INPUT" NC << std::endl;
            errorDetected = true;
            return;
        }

        std::cin >> size;
        std::string str;

        for(size_t i = 0; i < size; ++i){
            std::cin >> str;            
            if(str[0] == '<'){
                std::cout << RED "COUNT OF TYPES FEWER THAN EXPECTED" NC << std::endl;
                errorDetected = true;
                return;
            }
            TStr += str + ", ";
        }

        TStr.pop_back(); TStr.pop_back();

        std::cin >> input;
        if(input == "console")
            console = true;
        else if(input[0] == '<' && input.find(">") != std::string::npos)
            out = input.substr(1, input.find('>') - 2);
        else {
            std::cout << RED "BAD FNAME INPUT OR COUNT OF TYPES MORE THAN ASKED" NC << std::endl;
            errorDetected = true;
            return;
        }
    }
}