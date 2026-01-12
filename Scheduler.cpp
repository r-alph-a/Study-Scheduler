#include "Scheduler.h"
#include <algorithm>
#include <string>
#include <cmath>

static double roundUpToStep(double value, double step) {
    if (value <= 0.0) {
        return 0.0;
    }
    const double eps = 1e-10;
    double result = std::ceil((value - eps) / step) * step;
    
    if (result > value + eps) {
        result = std::floor((value + eps) / step) * step;
    }
    
    return result;
}

struct Task {
    std::string subjectName;
    std::string chapterName;
    double remainingHours;
};

bool hasTasksLeft(const std::vector<Task>& tasks) {
    for (const Task& t : tasks) {
        if (t.remainingHours > 0.01) {
            return true;
        }
    }
    return false;
}

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
    
    if (days_ <= 0 || totalHours_ <= 0.0) {
        return plan;
    }

    double hoursPerDay = totalHours_ / days_;
    double totalWeight =0.0;
    double remainingTotalHours = totalHours_;
    double step = 0.25;

    for(const auto& subject : subjects_){
        for (const auto& chapter : subject.chapters()) {
            totalWeight += chapter.weight();
        }
    }
    if (totalWeight<= 0.0) {
        return plan;
    }

    std::vector<Task> tasks;

    for (const auto& subject : subjects_) {
        for (const auto& chapter : subject.chapters()) {
            double chapterHours = 0.0;

            if (chapter.weight() > 0.0) {
                chapterHours = totalHours_ * (chapter.weight() / totalWeight);
            }
            if (chapterHours > 0.0) {
                tasks.push_back({ subject.name(), chapter.name(), chapterHours });
            }
        }
    }

    if (tasks.empty()) return plan;

    const double preferredChunk = std::max(step, std::min(1.0, hoursPerDay));

    std::size_t idx = 0;

    for (int day = 0; day < days_ && remainingTotalHours > 0.01 && hasTasksLeft(tasks); ++day) {
        double remainingDayHours = hoursPerDay;

        int guard = 0;
        while (remainingDayHours > 0.01 && remainingTotalHours > 0.01 && hasTasksLeft(tasks)) {
            if (++guard > 100000) return plan;

            std::size_t scanned = 0;
            while (scanned < tasks.size() && tasks[idx].remainingHours <= 0.01) {
                idx = (idx + 1) % tasks.size();
                ++scanned;
            }
            if (scanned >= tasks.size()) break;

            Task& t = tasks[idx];

            double roundedRemaining = roundUpToStep(t.remainingHours, step);
            roundedRemaining = std::min(roundedRemaining, t.remainingHours);
            
            double maxPossible = std::min({ preferredChunk, remainingDayHours, remainingTotalHours, roundedRemaining });
            
            double sessionHours = roundUpToStep(maxPossible, step);
            
            sessionHours = std::min({ sessionHours, remainingDayHours, remainingTotalHours, t.remainingHours });
            
            if (sessionHours < step && t.remainingHours >= step && remainingDayHours >= step && remainingTotalHours >= step) {
                sessionHours = step;
            }
            
            if (sessionHours <= 0.01) {
                idx = (idx + 1) % tasks.size();
                continue;
            }

            plan[day].sessions.push_back({ t.subjectName, t.chapterName, sessionHours });

            t.remainingHours -= sessionHours;
            remainingDayHours -= sessionHours;
            remainingTotalHours -= sessionHours;

            idx = (idx + 1) % tasks.size();
        }
    }
    return plan;
}
