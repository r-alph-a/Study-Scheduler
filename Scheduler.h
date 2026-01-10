#pragma once

#include <vector>
#include <string>
#include "Models.h"

struct Session{
    std::string subject;
    std::string chapter;
    double hours;
};

struct DayPlan {
    int day;
    std::vector<Session> sessions;
};

class Scheduler {
public:
    Scheduler(std::vector<Subject>& subjects);

    void setDays(int days);
    void setTotalHours(double hours);

    std::vector<DayPlan> generate();

private:
    std::vector<Subject>& subjects_;
    int days_;
    double totalHours_;
};
