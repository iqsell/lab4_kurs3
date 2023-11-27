#include "classes.h"

Dailytern::Dailytern(int start, int end, std::string desc)
        : start_time(start), end_time(end), description(desc), is_completed(false) {}


const std::vector<Dailytern> &Person::getSchedule() const {
    return schedule;
}


void Person::addWork(int start, int end, std::string desc) {
    if (isFreeTime(start, end)) {
        schedule.push_back(Dailytern(start, end, desc));
        std::sort(schedule.begin(), schedule.end(), [](const Dailytern &a, const Dailytern &b) {
            return a.start_time < b.start_time;
        });
    } else {
        std::cout << "Invalid time frame, there is a conflict with existing work." << std::endl;
    }
}

void Person::removeWork(int start) {
    schedule.erase(std::remove_if(schedule.begin(), schedule.end(), [start](const Dailytern &work) {
        return work.start_time == start;
    }), schedule.end());
}

void Person::changeWork(int start, int new_start, int new_end, std::string new_desc) {
    if (isFreeTime(new_start, new_end)) {
        std::replace_if(schedule.begin(), schedule.end(), [start](const Dailytern &work) {
            return work.start_time == start;
        }, Dailytern(new_start, new_end, new_desc));
    } else {
        std::cout << "Invalid time frame, there is a conflict with existing work." << std::endl;
    }
}


bool Person::isFreeTime(int start, int end) const {
    for (const auto &work: schedule) {
        if ((start >= work.start_time && start < work.end_time) ||
            (end > work.start_time && end <= work.end_time) || (start <= work.start_time && end >= work.end_time)) {
            return false;
        }
    }
    return true;
}

Dailytern Person::findFreeTime(int start, int end) {
    if (schedule.empty() || (start <= schedule[0].start_time && end <= schedule[0].start_time)) {
        return Dailytern(start, end, "");
    }
    for (int i = 0; i < schedule.size() - 1; i++) {
        if (schedule[i + 1].start_time - schedule[i].end_time >= end - start) {
            return Dailytern(schedule[i].end_time, schedule[i].end_time + end - start,
                             "");
        }
    }
    if (start >= schedule.back().end_time) {
        return Dailytern(start, end, "");
    }
    return Dailytern(-1, -1, "");
}

void Person::generateRedo() const {
    std::vector<Dailytern> redo;
    for (const auto &work: schedule) {
        if (!work.is_completed) {
            redo.push_back(work);
        }
    }
    std::cout << "Redo list:" << std::endl;
    for (const auto &work: redo) {
        std::cout << work.description << " (from " << work.start_time << " to " << work.end_time << ")"
                  << std::endl;
    }
}

Dailytern &Person::operator[](size_t index) {
    if (index < schedule.size()) {
        return schedule[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}


std::vector<Dailytern> Person::unionWith(const Person &other) {
    std::vector<Dailytern> unionSchedule = this->schedule;
    for (const auto &work: other.schedule) {
        if (std::find_if(unionSchedule.begin(), unionSchedule.end(), [&](const Dailytern &unionWork) {
            return unionWork.start_time == work.start_time && unionWork.end_time == work.end_time;
        }) == unionSchedule.end()) {
            unionSchedule.push_back(work);
        }
    }
    return unionSchedule;
}

std::vector<Dailytern> Person::operator+(const Person &other) const {
    std::vector<Dailytern> unionSchedule = this->schedule;
    unionSchedule.insert(unionSchedule.end(), other.schedule.begin(), other.schedule.end());
    return unionSchedule;
}

std::vector<Dailytern> Person::operator-(const Person &other) const {
    std::vector<Dailytern> differenceSchedule = this->schedule;
    for (const auto &work: other.schedule) {
        for (auto it = differenceSchedule.begin(); it != differenceSchedule.end();) {
            if (it->start_time == work.start_time && it->end_time == work.end_time) {
                it = differenceSchedule.erase(it);
            } else {
                ++it;
            }
        }
    }
    return differenceSchedule;
}

std::vector<Dailytern> Person::operator/(const Person &other) const {
    std::vector<Dailytern> intersectionSchedule;
    for (const auto &work: this->schedule) {
        for (const auto &otherWork: other.schedule) {
            if (otherWork.start_time == work.start_time && otherWork.end_time == work.end_time) {
                intersectionSchedule.push_back(work);
            }
        }
    }
    return intersectionSchedule;
}


bool checkTimeFormat(std::string time) {
    if (time.length() != 5 || time[2] != ':') {
        return false;
    }
    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(3, 2));
    return hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}

int convertTimeToInt(std::string time) {
    return std::stoi(time.substr(0, 2)) * 100 + std::stoi(time.substr(3, 2));
}


void SecondPerson::addWork(int start, int end, std::string desc) {
    if (isFreeTime(start, end, schedule_second)) {
        schedule_second.push_back(Dailytern(start, end, desc));
    } else {
        std::cout << "Invalid time frame, there is a conflict with existing work." << std::endl;
    }
}

void SecondPerson::generateRedo() const {
    std::vector<Dailytern> redo;
    for (const auto &work: schedule_second) {
        if (!work.is_completed) {
            redo.push_back(work);
        }
    }
    std::cout << "Redo list:" << std::endl;
    for (const auto &work: redo) {
        std::cout << work.description << " (from " << work.start_time << " to " << work.end_time << ")"
                  << std::endl;
    }
}

void SecondPerson::removeWork(int start) {
    schedule_second.erase(
            std::remove_if(schedule_second.begin(), schedule_second.end(), [start](const Dailytern &work) {
                return work.start_time == start;
            }), schedule_second.end());
}

void SecondPerson::changeWork(int start, int newStart, int newEnd, std::string desc) {
    for (auto &work: schedule_second) {
        if (work.start_time == start) {
            work.start_time = newStart;
            work.end_time = newEnd;
            work.description = desc;
            return;
        }
    }
    std::cout << "Task with the specified start time not found." << std::endl;
}

bool SecondPerson::isFreeTime(int start, int end, const std::vector<Dailytern> &schedule) const {
    for (const auto &work: schedule) {
        if ((start >= work.start_time && start < work.end_time) ||
            (end > work.start_time && end <= work.end_time) || (start <= work.start_time && end >= work.end_time)) {
            return false;
        }
    }
    return true;
}

std::vector<Dailytern> SecondPerson::unionWith(const Person &other) {
    std::vector<Dailytern> unionSchedule = this->schedule_second;
    for (const auto &work: other.getSchedule()) {
        unionSchedule.push_back(work);
    }
    return unionSchedule;
}

std::vector<Dailytern> SecondPerson::operator+(const SecondPerson &other) const {
    std::vector<Dailytern> unionSchedule = this->schedule_second;
    unionSchedule.insert(unionSchedule.end(), other.schedule_second.begin(), other.schedule_second.end());

    std::sort(unionSchedule.begin(), unionSchedule.end(), [](const Dailytern& lhs, const Dailytern& rhs) {
        return std::tie(lhs.start_time, lhs.end_time) < std::tie(rhs.start_time, rhs.end_time);
    });

    auto last = std::unique(unionSchedule.begin(), unionSchedule.end(), [](const Dailytern& lhs, const Dailytern& rhs) {
        return lhs.start_time == rhs.start_time && lhs.end_time == rhs.end_time;
    });
    unionSchedule.erase(last, unionSchedule.end());

    return unionSchedule;
}


std::vector<Dailytern> SecondPerson::operator-(const SecondPerson &other) const {
    std::vector<Dailytern> differenceSchedule = this->schedule_second;
    for (const auto &work: other.schedule_second) {
        for (auto it = differenceSchedule.begin(); it != differenceSchedule.end();) {
            if (it->start_time == work.start_time && it->end_time == work.end_time) {
                it = differenceSchedule.erase(it);
            } else {
                ++it;
            }
        }
    }
    return differenceSchedule;
}

int SecondPerson::min(int a, int b) const {
    return (a < b) ? a : b;
}

int SecondPerson::max(int a, int b) const {
    return (a > b) ? a : b;
}


std::vector<Dailytern> SecondPerson::operator/(const SecondPerson &other) const {
    std::vector<Dailytern> intersectionSchedule;
    for (const auto &work: this->schedule_second) {
        for (const auto &otherWork: other.schedule_second) {
            if (max(work.start_time, otherWork.start_time) < min(work.end_time, otherWork.end_time)) {
                intersectionSchedule.push_back(Dailytern(max(work.start_time, otherWork.start_time),
                                                         min(work.end_time, otherWork.end_time), "Intersection"));
            }
        }
    }
    return intersectionSchedule;
}





