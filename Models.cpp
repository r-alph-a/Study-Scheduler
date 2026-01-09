#include "Models.h"

#include <utility>
#include <algorithm>

Chapter::Chapter(std::string name, double weight)
    : name_(std::move(name)),
      weight_(std::max(0.0, weight)),
      allocated_(0.0),
      remaining_(0.0) {}

const std::string& Chapter::name() const { return name_; }
double Chapter::weight() const { return weight_; }
double Chapter::allocated() const { return allocated_; }
double Chapter::remaining() const { return remaining_; }

void Chapter::setWeight(double w) {
    weight_ = std::max(0.0, w);
}

void Chapter::allocateHours(double h) {
    h = std::max(0.0, h);
    allocated_ += h;
    remaining_ += h;
}

void Chapter::resetAllocation(double allocated) {
    allocated_ = std::max(0.0, allocated);
    remaining_ = allocated_;
}

void Chapter::study(double h) {
    h = std::max(0.0, h);
    remaining_ = std::max(0.0, remaining_ - h);
}

bool Chapter::done() const {
    return remaining_ <= 0.01;
}

Subject::Subject(std::string name)
    : name_(std::move(name)) {}

const std::string& Subject::name() const { return name_; }

void Subject::addChapter(const Chapter& c) {
    chapters_.push_back(c);
}

void Subject::addChapter(std::string chapterName, double weight) {
    chapters_.emplace_back(std::move(chapterName), weight);
}

std::vector<Chapter>& Subject::chapters() { return chapters_; }
const std::vector<Chapter>& Subject::chapters() const { return chapters_; }

double Subject::totalWeight() const {
    double sum = 0.0;
    for (const auto& c : chapters_) sum += c.weight();
    return sum;
}

double Subject::totalRemaining() const {
    double sum = 0.0;
    for (const auto& c : chapters_) sum += c.remaining();
    return sum;
}
