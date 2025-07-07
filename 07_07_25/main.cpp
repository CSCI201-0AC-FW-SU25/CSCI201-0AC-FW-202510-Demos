#include <iostream>
#include <limits>
#include <string>
#include <random>
#include <vector>
#include "clock.h"

void resetStream();
template <class Type>
Type inputNum(std::string prompt, std::string err, Type high, Type low);
// double inputNum(std::string prompt, std::string err, double high, double low);
// lecture activity create size maps for the drink class.

int main()
{
    // double x;
    // x = inputNum<double>("Enter a number", "That is not what I wanted~!", 100.5, 0.25);
    std::vector<twentyFourHrClock> clocks;
    std::vector<clockType *> clocksAgain;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> hrDist(0, 23);
    std::uniform_int_distribution<int> minSecDist(0, 59);
    std::uniform_int_distribution<int> boolDist(0, 1);
    std::uniform_int_distribution<int> twelveHrDist(1, 12);
    twentyFourHrClock clock;
    for (int i = 0; i < 2; i++)
    {
        clocks.push_back(twentyFourHrClock(hrDist(generator), minSecDist(generator), minSecDist(generator)));
    }
    int moreClocks = 1;
    while (moreClocks == 1)
    {
        if (boolDist(generator))
        {
            clocksAgain.push_back(new twentyFourHrClock(hrDist(generator), minSecDist(generator), minSecDist(generator)));
        }
        else
        {
            clocksAgain.push_back(new twelveHrClock(twelveHrDist(generator), minSecDist(generator), minSecDist(generator), boolDist(generator) == 0 ? partType::AM : partType::PM)); //?: does if-else on boolDist(generator)
        }
        moreClocks = boolDist(generator);
    }
    // clock1.setTime(hrDist(generator), minSecDist(generator), minSecDist(generator));

    // clock2.setTime(hrDist(generator), minSecDist(generator), minSecDist(generator));
    if (clocks[0] < clocks[1])
    {
        clock = inputNum<twentyFourHrClock>("Enter the hour minutes seconds for the clock.", "Soomething went wrong try again.", clocks[1], clocks[0]);
    }
    else
    {
        clock = inputNum<twentyFourHrClock>("Enter the hour minutes seconds for the clock.", "Soomething went wrong try again.", clocks[0], clocks[1]);
    }

    for (int i = 0; i < clocksAgain.size(); i++)
    {
        std::cout << *clocksAgain[i] << std::endl;
        delete clocksAgain[i];
    }

    return 0;
}
template <class Type>
Type inputNum(std::string prompt, std::string err, Type high, Type low)
{
    Type num;
    std::cout << prompt;
    std::cin >> num;
    std::cout << std::endl;
    while (!std::cin || num < low || num > high)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << err << std::endl;
        std::cout << prompt;
        std::cin >> num;
        std::cout << std::endl;
    }
    return num;
}

/* double inputNum(std::string prompt, std::string err, double high, double low)
{
    double num;
    std::cout << prompt;
    std::cin >> num;
    std::cout << std::endl;
    while (!std::cin || num < low || num > high)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << err << std::endl;
        std::cout << prompt;
        std::cin >> num;
        std::cout << std::endl;
    }
    return num;
} */

void resetStream()
{
    std::cout << "You have entered non-numeric data! Please try again!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
