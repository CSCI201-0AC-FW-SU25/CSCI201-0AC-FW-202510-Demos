#include <iostream>
#include <limits>
#include <cctype>
#include <string>
#include "clock.h"
#include "movieTimes.h"

int main()
{

    MovieTimes elio("Elio", 99, "PG");
    {
        MovieTimes dragon("How to Train Your Dragon", 125, "PG");
        dragon.enterTimes();
        std::cout << dragon.tostring() << std::endl;
        elio = dragon;
    }
    std::cout << elio.tostring() << std::endl;
    return 0;
}

clockType *makeClock()
{
    clockType *clockPtr = nullptr;
    int type;
    type = inputInt("Do you want a 12 or 24 hour clock? ", "Please enter 12 or 24: ", isAorB, 12, 24);

    int hour;
    std::string hourPrompt = "Enter the clock's hour: ";
    if (type == 12)
    {
        hour = inputInt(hourPrompt, "The hour must be between 1 and 12", isInRange, 1, 12);
    }
    else
    {
        hour = inputInt(hourPrompt, "The hour must be between 0 and 23", isInRange, 0, 23);
    }

    int minute = inputInt("Enter the clock's minutes: ", "The minute must be between 0 and 59", isInRange, 0, 59);

    int second = inputInt("Enter the clock's seconds: ", "The second must be between 0 and 59", isInRange, 0, 59);

    if (type == 12)
    {
        int amPM = inputInt("Is it 1. AM or 2. PM? ", "Please enter 1 or AM or 2 for PM.", isAorB, 1, 2);

        clockPtr = new clockType(timeType::TWELVE, hour, minute, second, parts[amPM - 1]);
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

int inputInt(std::string prompt, std::string err, bool (*valid)(int, int, int), int valid1, int valid2)
{
    int num;
    std::cout << prompt;
    std::cin >> num;
    while (!std::cin || !valid(num, valid1, valid2))
    {
        if (!std::cin)
        {
            resetStream();
        }
        else
        {
            std::cout << err << std::endl;
        }
        std::cout << prompt;
        std::cin >> num;
    }
    return num;
}

bool isAorB(int num, int a, int b)
{
    if (num == a)
        return true;
    if (num == b)
        return true;

    return false;
}

bool isInRange(int num, int low, int high)
{

    return low <= num && num <= high;
}
