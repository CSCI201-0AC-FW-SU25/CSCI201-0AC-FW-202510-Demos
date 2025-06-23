#include <iostream>
#include <limits>
#include "clock.h"

clockType *makeClock();
void resetStream();

// lecture activity fill in validation loops in make clock + tbd

int main()
{
    int *p = nullptr;
    int x = 7;
    // p = &x;
    p = new int[x];
    p[0] = 9;
    p[6] = 10;
    int distance = p[6] - p[0];
    int list[10];
    std::cout << list << std::endl;
    clockType c(timeType::TWENTYFOUR);
    clockType *clockPtr = nullptr;
    int type;
    clockPtr = makeClock();
    /* std::cout << "Do you want a 12 or 24 hour clock? ";
    std::cin >> type;
    // input validation loop goes here
    if (type == 12)
    {
        clockPtr = new clockType(timeType::TWELVE);
    }
    else
    {
        clockPtr = new clockType(timeType::TWENTYFOUR);
    } */
    std::cout << clockPtr->printTime() << std::endl;
    // clockPtr->getHour();
    // clockPtr = &c;
    clockPtr->getHour();
    clockPtr->getMinute();

    delete[] p;
    delete clockPtr;
    return 0;
}

clockType *makeClock()
{
    clockType *clockPtr = nullptr;
    int type;
    std::cout << "Do you want a 12 or 24 hour clock? ";
    std::cin >> type;
    // input validation loop goes here
    while (!std::cin || (type != 12 && type != 24))
    {
        if (!std::cin)
        {
            resetStream();
        }
        else
        {
            std::cout << "Please enter 12 or 24: ";
        }
        std::cout << "Do you want a 12 or 24 hour clock? ";
        std::cin >> type;
    }
    int hour;
    std::cout << "Enter the clock's hour: ";
    std::cin >> hour;
    // input validation loop
    while (!std::cin || (type == 12 && (hour < 1 || hour > 12)) || (type == 24 && (hour < 0 || hour > 23)))
    {
        if (!std::cin)
        {
            resetStream();
        }
        else if (type == 12)
        {
            std::cout << "The hour must be between 1 and 12" << std::endl;
        }
        else
        {
            std::cout << "The hour must be between 0 and 23" << std::endl;
        }
        std::cout << "Enter the clock's hour: ";
        std::cin >> hour;
    }
    int minute;
    std::cout << "Enter the clock's minutes: ";
    std::cin >> minute;
    // validation loop input failure and 0 - 59

    int second;
    std::cout << "Enter the clock's seconds: ";
    std::cin >> second;
    // validation loop same as minutes
    if (type == 12)
    {
        int amPM;
        std::cout << "Is it 1. AM or 2. PM? ";
        std::cin >> amPM;
        // validation loop input failure or not 1 and not 2
        partType part;
        if (amPM == 1)
        {
            part = partType::AM;
        }
        else
        {
            part = partType::PM;
        }
        clockPtr = new clockType(timeType::TWELVE, hour, minute, second, part);
    }
    else
    {
        clockPtr = new clockType(timeType::TWENTYFOUR, hour, minute, second);
    }
    return clockPtr;
}

void resetStream()
{
    std::cout << "You have entered non-numeric data! Please try again!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}