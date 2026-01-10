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

    double hoursPerDay = totalHours_ / days_;
    size_t totalChapters = 0;

    for(const auto& subject : subjects_){
        totalChapters += subject.chapters().size();
    }
    if (totalChapters == 0) {
        return plan;
    }

    double hoursPerChapter = totalHours_ / totalChapters;

    int currentDay = 0;                 
    double remainingDayHours = hoursPerDay;

    for (const auto& subject : subjects_) {
        for (const auto& chapter : subject.chapters()) {

            double remainingChapterHours = hoursPerChapter;

            while (remainingChapterHours > 0 && currentDay < days_) {
                double sessionHours;
                if (remainingChapterHours < remainingDayHours) {
                    sessionHours = remainingChapterHours;
                } else {
                    sessionHours = remainingDayHours;
                }

                plan[currentDay].sessions.push_back({
                    subject.name(),
                    chapter.name(),
                    sessionHours});

                remainingChapterHours -= sessionHours;
                remainingDayHours -= sessionHours;

                if (remainingDayHours <= 0.01) {
                    currentDay++;
                    if (currentDay < days_) {
                        remainingDayHours = hoursPerDay;
                    }
                }
            }
        }
    }
    return plan;
}
