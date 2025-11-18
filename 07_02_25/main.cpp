#include <iostream>
#include <limits>
#include <cctype>
#include "clock.h"
#include "movieTimes.h"

clockType *makeClock();
void resetStream();
void clockTick(clockType &clockToTick);
bool validPositiveInt(int num);
int inputPositiveInt(std::string prompt, std::string err);
bool codeGradeLoopFix();

// lecture activity in clock.h

//fall 25 add typeid from <typeinfo> into lecture to check the clock type before doing the == operator.

int main()
{
    int x = 7;

    int y = x++;
    twelveHrClock clock(12, 59, 59, partType::PM);
    twelveHrClock clock2 = clock + 1;
    MovieTimes dragon("How to Train Your Dragon", 125, "PG");

    dragon.enterTimes();
    std::cout << dragon.tostring();

    return 0;
}

clockType *makeClock()
{
    clockType *clockPtr = nullptr;
    int type;
    std::cout << "Do you want a 12 or 24 hour clock? ";
    std::cin >> type;
    std::cout << std::endl;
    // input validation loop goes here
    while (!std::cin || (type != 12 && type != 24))
    {
        if (codeGradeLoopFix())
        {
            return nullptr;
        }
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
        std::cout << std::endl;
    }
    int hour;
    std::cout << "Enter the clock's hour: ";
    std::cin >> hour;
    std::cout << std::endl;
    // input validation loop
    while (!std::cin || (type == 12 && (hour < 1 || hour > 12)) || (type == 24 && (hour < 0 || hour > 23)))
    {
        if (codeGradeLoopFix())
        {
            return nullptr;
        }
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
        std::cout << std::endl;
    }
    int minute;
    std::cout << "Enter the clock's minutes: ";
    std::cin >> minute;
    std::cout << std::endl;
    // validation loop input failure and 0 - 59

    int second;
    std::cout << "Enter the clock's seconds: ";
    std::cin >> second;
    std::cout << std::endl;
    // validation loop same as minutes
    if (type == 12)
    {
        int amPM;
        std::cout << "Is it 1. AM or 2. PM? ";
        std::cin >> amPM;
        std::cout << std::endl;
        // validation loop input failure or not 1 and not 2

        clockPtr = new twelveHrClock(hour, minute, second, parts[amPM - 1]);
    }
    else
    {
        clockPtr = new twentyFourHrClock(hour, minute, second);
    }
    return clockPtr;
}

void resetStream()
{
    std::cout << "You have entered non-numeric data! Please try again!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clockTick(clockType &clockToTick)
{
    clockToTick.incrementHours();
    std::cout << clockToTick << std::endl;
}

bool validPositiveInt(int num)
{
    return num > 0;
}

int inputPositiveInt(std::string prompt, std::string err)
{
    int input;
    std::cout << prompt;
    std::cin >> input;
    while (!std::cin || !validPositiveInt(input))
    {
        if (codeGradeLoopFix())
        {
            return -999;
        }
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << err << std::endl;
        std::cout << prompt;
        std::cin >> input;
    }
    return input;
}

bool codeGradeLoopFix()
{
    if (std::cin.eof())
    {
        std::cout << "Infinite loop detected. Out of input ending program." << std::endl;
        return true;
    }
    return false;
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

void addTimeToMovie(MovieTimes &theMovie)
{
    // clockType c(TWELVE);
    // theMovie.addTime(c);
}
