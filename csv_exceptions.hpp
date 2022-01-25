#pragma once
#include <map>

namespace csv_error{
    std::map<size_t, std::string> stringExeptionsBuffer;

    size_t outPointer = 0;

    size_t inPointer = -1;

    size_t numbInStr = 0;

    bool isInputFailure(){
        return stringExeptionsBuffer.contains(outPointer);
    }

    std::string exceptionComment(){
        std::string s = stringExeptionsBuffer.begin()->second;
        stringExeptionsBuffer.extract(outPointer);
        outPointer++;
        return s;         
    }

    size_t countCh(std::string& input, char ch){
        size_t pos = 0, count = 0;

        while(input.find(ch, pos) != std::string::npos){
            pos = input.find(ch, pos) + 1;
            count++;
        }

        return count;
    }

    bool isLengthMatching(std::string& input, size_t tupleLength){
        inPointer++;
        numbInStr = 0;
        if(countCh(input, ',') + 1> tupleLength)
            stringExeptionsBuffer[inPointer] = "inputed more than expected";
        else if(countCh(input, ',') + 1< tupleLength)
            stringExeptionsBuffer[inPointer] = "inputed fewer than expected";
        else
            return true;

        return false;  
    }

    void typeDismatching(){
        stringExeptionsBuffer[inPointer] += "| " + std::to_string(numbInStr) + " element no matches with given type |"; 
        numbInStr++;
    }

    void numberCheck(std::string& input){
        if(!input.empty() && input[0] == ' ')
            input.erase(0, 1);
        if(!input.empty() && input[0] == '-')
            input.erase(0, 1);
        if(input.empty() || input[0] == '.' || countCh(input, '.') > 1){
            typeDismatching();
            return;
        }
        for(char ch : input){
            if(ch >= '0' && ch <= '9' || ch == '.')
                continue;
            typeDismatching();
            break;
        }
    }
}