#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Models.h"

int getPosNum(const std::string& text){
    int positifNumber(-1);
    bool flag = positifNumber<=0;
    while(flag) {
        std::cout << text;
        std::cin >> positifNumber;
        flag = positifNumber <= 0;
        if(flag){
            std::cout << "Number must be positive" << std::endl;
        }
    }
    return positifNumber;
}

std::string getString(const std::string& text){
    std::string strg;
    std::cout << text << " ";
    std::cin >> strg;
    return strg;
}

Subject createSubject(){
    Subject result(getString("Name of Subject"));
    int subjectLenght = getPosNum("Number of chapters:");
    for(size_t i(0);i<subjectLenght;++i){
        std::stringstream ss;
        ss << "Name of Chapter " << i;
        std::string name = ss.str();
        Chapter c(getString(name),getPosNum("How important is this chapter?"));
        result.addChapter(c);
    }
}

int main(){
    int dur = getPosNum("How many days until test?");
    std::cout << dur;
    return 0;
}