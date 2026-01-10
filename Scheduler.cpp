#include "Scheduler.h"

Scheduler::Scheduler(std::vector<Subject>& subjects) : subjects_(subjects), days_(0), totalHours_(0.0) {}

void Scheduler::setDays(int days) {
    days_ = days;
}

void Scheduler::setTotalHours(double hours) {
    totalHours_ = hours;
}

std::vector<DayPlan> Scheduler::generate() {
    std::vector<DayPlan> plan;

    for (int i = 1; i <= days_; ++i) {
        DayPlan day;
        day.day = i;
        plan.push_back(day);
    }

    return plan;
}
