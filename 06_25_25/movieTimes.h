#ifndef MOVIE_H
#define MOVIE_H
#include "clock.h"

class MovieTimes
{
    MovieTimes(std::string title, int runtime, std::string rating);
    void enterTimes();
    std::string tostring();
    std::string getTitle();
    int getRuntime();
    std::string getRating();

private:
    clockType **times;
    int numTimes;
    std::string title;
    int runtime;
    std::string rating;
};

#endif