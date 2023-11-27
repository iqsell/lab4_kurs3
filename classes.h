#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

struct Dailytern {
    int start_time;
    int end_time;
    std::string description;
    bool is_completed;

    Dailytern(int start, int end, std::string desc);
};


class Person {
protected:
    std::vector<Dailytern> schedule;

public:
    const std::vector<Dailytern> &getSchedule() const;
    void addWork(int start, int end, std::string desc);
    void removeWork(int start);
    void changeWork(int start, int new_start, int new_end, std::string new_desc);
    bool isFreeTime(int start, int end) const;
    Dailytern findFreeTime(int start, int end);
    void generateRedo() const;
    Dailytern& operator[](size_t index);
    std::vector<Dailytern> unionWith(const Person &other);
    std::vector<Dailytern> operator+(const Person& other) const;
    std::vector<Dailytern> operator-(const Person& other) const;
    std::vector<Dailytern> operator/(const Person& other) const;
};

class SecondPerson : public Person {
private:
    std::vector<Dailytern> schedule_second;

public:
    void addWork(int start, int end, std::string desc);
    void generateRedo() const;
    void removeWork(int start);
    void changeWork(int start, int newStart, int newEnd, std::string desc);
    bool isFreeTime(int start, int end, const std::vector<Dailytern> &schedule) const;
    std::vector<Dailytern> unionWith(const Person &other);
    std::vector<Dailytern> operator+(const SecondPerson& other) const;
    std::vector<Dailytern> operator-(const SecondPerson& other) const;
    int min(int a, int b) const;
    int max(int a, int b) const;
    std::vector<Dailytern> operator/(const SecondPerson& other) const;
};

bool checkTimeFormat(std::string time);
int convertTimeToInt(std::string time);
