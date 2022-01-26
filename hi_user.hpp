#pragma once
#include <iostream>
#include <map>
#include "stdlib.h"

namespace csv_parser{
    class HiUser{
        public:
        HiUser(std::string os);
        private:
        void sleepcp(size_t seconds);
        void inputFunction();
        void processFunction();
        std::string TStr;
        std::string in;
        std::string out;
        bool errorDetected = false;
        bool console = false;
    };
}