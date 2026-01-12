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

Subject createSubject(const std::string& text){
    Subject result(getString(text));
    int subjectLenght = getPosNum("How many Chapters in this Subject?");
    for(size_t i(0);i<subjectLenght;++i){
        std::stringstream ss;
        ss << "Name of Chapter " << i+1;
        std::string name = ss.str();
        std::string chapterName = getString(name);
        int chapterWeight = getPosNum("How important is this chapter?");
        Chapter c(chapterName,chapterWeight);
        result.addChapter(c);
    }
    return result;
}

std::vector<Subject> createSchedule(){
    std::vector<Subject> result;
    int materialLenght = getPosNum("Number of subjects:");
    for(size_t i(0);i<materialLenght;++i){
        std::stringstream ss;
        ss << "Name of Subject " << i+1;
        std::string name = ss.str();
        result.push_back(createSubject(name));
    }
    return result;
}

int displaySchedule(const std::vector<Subject>& subjects){
    for(size_t i(0);i<subjects.size();i++){
        std::cout << "-" << subjects[i].name() << std::endl;
        for(size_t j(0);j<subjects[i].chapters().size();j++){
            Chapter c = subjects[i].chapters()[j];
            std::cout << c.name() << std::endl;
            std::cout << c.weight() << std::endl;
        }
        std::cout << "\n";
    }
    return 0;
}