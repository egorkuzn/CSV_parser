#pragma once
#include <iostream>
#include <map>
#include "stdlib.h"
#include <fstream>
#include <regex>

namespace csv_parser{
    class HiUser{
        public:
        HiUser(std::string os);
        private:
        void sleepcp(size_t seconds);
        void inputFunction();
        //void consoleOutput();
        void processFunction();
        std::string TStr;
        size_t size = 0;
        std::string in;
        std::string out;
        bool errorDetected = false;
        bool console = false;
    };
}