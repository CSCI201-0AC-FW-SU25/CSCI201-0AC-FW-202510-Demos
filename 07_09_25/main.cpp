#include <iostream>
#include <limits>
#include <chrono>
#include <random>
#include "clock.h"
#include "clockExcept.h"
// create invalid_minute and invalid_second in clockExcept.h and clockExcept.cpp
// update throws in clock.cpp to use new exceptions
// update main to catch new exceptions
void resetStream();
double inputNum(std::string prompt, std::string err, double high, double low);

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::vector<clockType *> timeClockIn;
    try
    {
        timeClockIn.at(1);
    }
    catch (std::out_of_range e)
    {
        std::cerr << e.what() << '\n';
    }

    std::uniform_int_distribution<int> distributionClock(0, 100);
    int numClocks = distributionClock(generator);
    int min;
    int sec;
    int hr;
    bool validMinute = false;
    bool validSecond = false;
    bool validHour = false;
    bool newClock = true;
    bool twelve;
    for (int i = 0; i < numClocks; i++)
    {
        try
        {
            clockType *clock;
            if (newClock)
            {
                twelve = distributionClock(generator) % 2 == 0;
            }
            if (!validMinute)
            {
                min = distributionClock(generator);
                validMinute = true;
            }
            if (!validSecond)
            {
                sec = distributionClock(generator);
                validSecond = true;
            }
            if (!validHour)
            {
                hr = distributionClock(generator);
                validHour = true;
            }
            if (twelve)
            {
                partType part = clockType::intToPartType.at(distributionClock(generator) % 2);
                clock = new twelveHrClock(hr, min, sec, part);
            }
            else
            {
                clock = new twentyFourHrClock(hr, min, sec);
            }
            timeClockIn.push_back(clock);
            validHour = false;
            validMinute = false;
            validSecond = false;
            newClock = true;
        }
        catch (invalid_hour e)
        {
            if (twelve)
            {
                std::cerr << "Twelve Hour Clock Failure: Valid hours are between 1 and 12" << std::endl;
            }
            else
            {
                std::cerr << "Twenty Four Hour Clock Failure: Valid hours are between 0 and 23" << std::endl;
            }
            std::cerr << e.what() << '\n';
            validHour = false;
            i--;
            continue;
        }
        catch (...)
        {
            validMinute = false;
            validSecond = false;
            i--;
            continue;
        }
    }

    for (int i = 0; i < timeClockIn.size(); i++)
    {
        std::cout << *timeClockIn[i] << std::endl;
        delete timeClockIn[i];
    }

    bool validNum = false;
    double num;
    while (!validNum)
    {
        try
        {
            num = inputNum("Enter a floating point number between 1 and 100. ", "That is not a number between 1 and 100.", 100, 1);
            validNum = true;
        }
        catch (const std::exception &e)
        {
            if (!std::cin)
            {
                resetStream();
            }
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}

void resetStream()
{
    std::cout << "You have entered non-numeric data! Please try again!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/* double inputNum(std::string prompt, std::string err, double high, double low)
{
    double num;
    std::cout << prompt;
    std::cin >> num;
    std::cout << std::endl;
    try
    {
        if (!std::cin || num < low || num > high)
        {
            throw std::runtime_error("Input Error");
            /* if (!std::cin)
            {
                resetStream();
            }
        }
    }
    catch (std::runtime_error e)
    {
        if (!std::cin)
        {
            resetStream();
        }
        else
        {
            std::cout << err << std::endl;
        }
        return inputNum(prompt, err, high, low);
    }
    return num;
} */

double inputNum(std::string prompt, std::string err, double high, double low)
{
    double num;
    std::cout << prompt;
    std::cin >> num;
    std::cout << std::endl;
    if (!std::cin || num < low || num > high)
    {
        throw std::runtime_error(err);
    }

    return num;
}