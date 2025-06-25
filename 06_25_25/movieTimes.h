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
    void enterTimes();
    std::string tostring();
    std::string getTitle();
    int getRuntime();
    std::string getRating();
    ~MovieTimes();

private:
    clockType **times;
    int numTimes;
    std::string title;
    int runtime;
    std::string rating;
};

clockType *makeClock();
void resetStream();
int inputInt(std::string prompt, std::string err, bool (*valid)(int, int, int), int valid1 = 0, int valid2 = 0);
bool isAorB(int num, int a, int b);
bool isInRange(int num, int low, int high);
bool isGreaterThan0(int num, int = 0, int = 0);

#endif