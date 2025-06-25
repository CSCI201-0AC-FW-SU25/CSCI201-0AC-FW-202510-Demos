#include <iostream>
#include <limits>
#include <cctype>
#include <string>
#include "clock.h"

clockType *makeClock();
void resetStream();
int inputInt(std::string prompt, std::string err, bool (*valid)(int, int, int), int valid1, int valid2);
bool isAorB(int num, int a, int b);
bool isInRange(int num, int low, int high);

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
    clockType **clockPtrs = nullptr;
    int numClocks = 0;
    clockPtrs = new clockType *[numClocks];
    char cont = 'Y';
    while (cont == 'Y')
    {
        numClocks++;
        clockType **tempClocks = clockPtrs;
        clockPtrs = new clockType *[numClocks];
        for (int i = 0; i < numClocks - 1; i++)
        {
            clockPtrs[i] = tempClocks[i];
        }
        clockPtrs[numClocks - 1] = makeClock();
        std::cout << "Do you want to add another clock? ";
        std::cin >> cont;
        cont = toupper(cont);
        delete[] tempClocks;
    }

    std::cout << clockPtrs[0]->printTime() << std::endl;

    clockPtrs[0]->getHour();
    clockPtrs[0]->getMinute();

    delete[] p;
    for (int i = 0; i < numClocks; i++)
    {
        delete clockPtrs[i];
    }
    delete[] clockPtrs;
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
