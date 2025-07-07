#include <iostream>
#include <limits>
#include <string>
#include <random>
#include <vector>
#include <cctype>
#include "clock.h"
#include "drink.h"

void resetStream();
template <class Type>
Type inputNum(std::string prompt, std::string err, Type high, Type low);
// double inputNum(std::string prompt, std::string err, double high, double low);
// lecture activity create size maps for the drink class.
drink::sizeType inputDrinkSize();
drink::baseType inputDrinkBase();
drink::tempType inputDrinkTemp();
std::string inputDrinkFlavor();
std::string inputDrinkDairy();
std::string convertToUpperCase(std::string str);

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
    drink::baseType base = inputDrinkBase();
    drink::tempType temp = inputDrinkTemp();

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

drink::sizeType inputDrinkSize()
{
    return drink::LARGE;
}

drink::baseType inputDrinkBase()
{
    drink::baseType base;
    std::string inputBase;
    std::cout << "Would you like ";
    std::map<drink::baseType, std::string>::const_iterator it = drink::baseToStr.begin();
    std::cout << it->second;
    for (++it; it != drink::baseToStr.end(); ++it)
    {
        auto itCpy = it;
        ++itCpy;
        if (itCpy == drink::baseToStr.end())
        {
            std::cout << ", or ";
        }
        else
        {
            std::cout << ", ";
        }
        std::cout << it->second;
    }
    std::cout << "? ";
    std::cin >> std::ws;
    getline(std::cin, inputBase);
    inputBase = convertToUpperCase(inputBase);
    while (!drink::strToBase.count(inputBase))
    {
        std::cout << inputBase << " is not a valid choice." << std::endl;
        it = drink::baseToStr.begin();
        std::cout << it->second;
        for (++it; it != drink::baseToStr.end(); ++it)
        {
            auto itCpy = it;
            ++itCpy;
            if (itCpy == drink::baseToStr.end())
            {
                std::cout << ", or ";
            }
            else
            {
                std::cout << ", ";
            }
            std::cout << it->second;
        }
        std::cout << "? ";
        std::cin >> std::ws;
        getline(std::cin, inputBase);
        inputBase = convertToUpperCase(inputBase);
    }
    base = drink::strToBase.at(inputBase);
    return base;
}

drink::tempType inputDrinkTemp()
{
    std::string inputTemp;
    std::string cpyInputTemp;
    do
    {
        if (!inputTemp.empty())
        {
            std::cout << inputTemp << " is not a valid choice." << std::endl;
        }
        std::cout << "Would you like ";
        std::map<drink::tempType, std::string>::const_iterator it = drink::tempToStr.begin();
        std::cout << it->second;
        for (++it; it != drink::tempToStr.end(); ++it)
        {
            auto itCpy = it;
            ++itCpy;
            if (itCpy == drink::tempToStr.end())
            {
                std::cout << ", or ";
            }
            else
            {
                std::cout << ", ";
            }
            std::cout << it->second;
        }
        std::cout << "? ";
        std::cin >> std::ws;
        getline(std::cin, inputTemp);
        cpyInputTemp = inputTemp;
        std::transform(cpyInputTemp.begin(), cpyInputTemp.end(), cpyInputTemp.begin(), ::tolower);

    } while (!drink::strToTemp.count(cpyInputTemp));

    return drink::strToTemp.at(cpyInputTemp);
}

std::string inputDrinkFlavor()
{
    return "Mocha";
}

std::string inputDrinkDairy()
{
    return "Whole Milk";
}

std::string convertToUpperCase(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}
