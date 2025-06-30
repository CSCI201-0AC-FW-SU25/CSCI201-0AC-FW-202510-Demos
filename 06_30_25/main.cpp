#include <iostream>
#include <limits>
#include <cctype>
#include "clock.h"

clockType *makeClock();
void resetStream();
void clockTick(clockType &clockToTick);
bool validPositiveInt(int num);
int inputPositiveInt(std::string prompt, std::string err);
bool codeGradeLoopFix();

// lecture activity fill in input.txt with input that will create 20 clocks. Randomize between 12 and 24 hour clocks and randomize times.

int main()
{
    clockType **c = nullptr;
    int numClocks = 0;
    numClocks = inputPositiveInt("How many clocks do you want to make? ", "Please enter a positive number of clocks!");
    if (numClocks == -999)
    {
        return 0;
    }
    c = new clockType *[numClocks];
    for (int i = 0; i < numClocks; i++)
    {
        c[i] = makeClock();
        if (c[i] == nullptr)
        {
            return 0;
        }
    }
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
    }
    int hour;
    std::cout << "Enter the clock's hour: ";
    std::cin >> hour;
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
    std::cout << clockToTick.toString() << std::endl;
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