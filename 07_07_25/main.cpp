#include <iostream>
#include <limits>
#include <string>
#include <random>
#include "clock.h"

void resetStream();
template <class Type>
Type inputNum(std::string prompt, std::string err, Type high, Type low);
// double inputNum(std::string prompt, std::string err, double high, double low);

int main()
{
    double x;
    x = inputNum<double>("Enter a number", "That is not what I wanted~!", 100.5, 0.25);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> hrDist(0, 23);
    std::uniform_int_distribution<int> minSecDist(0, 59);
    twentyFourHrClock clock;
    twentyFourHrClock clock1;
    clock1.setTime(hrDist(generator), minSecDist(generator), minSecDist(generator));

    twentyFourHrClock clock2;
    clock2.setTime(hrDist(generator), minSecDist(generator), minSecDist(generator));
    if (clock1 < clock2)
    {
        clock = inputNum<twentyFourHrClock>("Enter the hour minutes seconds for the clock.", "Soomething went wrong try again.", clock2, clock1);
    }
    else
    {
        clock = inputNum<twentyFourHrClock>("Enter the hour minutes seconds for the clock.", "Soomething went wrong try again.", clock1, clock2);
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
