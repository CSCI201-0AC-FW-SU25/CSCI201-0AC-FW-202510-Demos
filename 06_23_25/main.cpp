#include <iostream>
#include "clock.h"

int main()
{
    int *p = nullptr;
    int x = 7;
    // p = &x;
    p = new int[x];
    int list[10];
    std::cout << list << std::endl;
    clockType c(timeType::TWENTYFOUR);
    clockType *clockPtr = nullptr;
    int type;
    std::cout << "Do you want a 12 or 24 hour clock? ";
    std::cin >> type;
    // input validation loop goes here
    if (type == 12)
    {
        clockPtr = new clockType(timeType::TWELVE);
    }
    else
    {
        clockPtr = new clockType(timeType::TWENTYFOUR);
    }
    std::cout << clockPtr->printTime() << std::endl;
    // clockPtr->getHour();
    clockPtr = &c;
    clockPtr->getHour();
    clockPtr->getMinute();
    return 0;
}