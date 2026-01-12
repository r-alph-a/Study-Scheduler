#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include "input.h"
#include "Models.h"

#include <limits>

double getPosNum(const std::string& text){
    double positifNumber;

    while (true) {
        std::cout << text;
        if (std::cin >> positifNumber && positifNumber > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return positifNumber;
        }
        std::cout << "Please enter a POSITIVE number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getString(const std::string& text){
    std::string strg;
    std::cout << text << " ";
    std::getline(std::cin, strg);
    return strg;
}

Subject createSubject(const std::string& text){
    Subject result(getString(text));
    double subjectLenght = getPosNum("How many Chapters in this Subject?");
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