#include <iostream>
#include "input.h"
#include "Scheduler.h"

int main(){
    std::vector<Subject> schedule = createSchedule();
    Scheduler scheduler(schedule);
    scheduler.setDays(getPosNum("How many days do you have? "));
    scheduler.setTotalHours(getPosNum("How many hours can you study? "));
    std::vector<DayPlan> plan = scheduler.generate();

    for (const auto& day:plan){
        std::cout << "Day" << day.day << ":\n";
        for (const auto& s: day.sessions){
            std::cout << " - " << s.subject << "/" << s.chapter << " (" << s.hours << "h)" << "\n";
        }
    }
    return 0;
}