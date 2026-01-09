#pragma once

#include <string>
#include <vector>

class Chapter {
public:
    explicit Chapter(std::string name, double weight = 1.0);

    const std::string& name() const;
    double weight() const;
    double allocated() const;
    double remaining() const;

    void setWeight(double w);
    void allocateHours(double h);
    void resetAllocation(double allocated);
    void study(double h);
    bool done() const;

private:
    std::string name_;
    double weight_;
    double allocated_;
    double remaining_;
};

class Subject {
public:
    explicit Subject(std::string name);

    const std::string& name() const;

    void addChapter(const Chapter& c);
    void addChapter(std::string chapterName, double weight = 1.0);

    std::vector<Chapter>& chapters();
    const std::vector<Chapter>& chapters() const;

    double totalWeight() const;
    double totalRemaining() const;

private:
    std::string name_;
    std::vector<Chapter> chapters_;
};