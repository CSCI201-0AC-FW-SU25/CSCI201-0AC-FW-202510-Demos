#ifndef MOVIE_H
#define MOVIE_H
#include "clock.h"
#include <iostream>
#include <sstream>
#include <iomanip>

class MovieTimes
{
public:
    MovieTimes(std::string title, int runtime, std::string rating);
    MovieTimes(const MovieTimes &otherObject);
    void enterTimes();
    std::string tostring();
    std::string getTitle();
    int getRuntime();
    std::string getRating();
    void addTime(clockType *timeAdd);
    ~MovieTimes();
    const MovieTimes &operator=(const MovieTimes &rightHandSide);

private:
    clockType **times;
    int numTimes;
    std::string title;
    int runtime;
    std::string rating;
    void copyMovie(const MovieTimes &otherMovie);
};

clockType *makeClock();
void resetStream();
int inputInt(std::string prompt, std::string err, bool (*valid)(int, int, int), int valid1 = 0, int valid2 = 0);
bool isAorB(int num, int a, int b);
bool isInRange(int num, int low, int high);
bool isGreaterThan0(int num, int = 0, int = 0);

#endif