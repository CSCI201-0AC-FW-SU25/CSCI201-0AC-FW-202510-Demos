#ifndef CLOCK_H
#define CLOCK_H
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <map>
#include "clockExcept.h"

enum class partType
{
    AM,
    PM
};
enum timeType
{
    TWELVE,
    TWENTYFOUR
};
const partType parts[2] = {partType::AM, partType::PM};
const std::string partToStr[2] = {"AM", "PM"};
int convertTo24Hr(int hr, partType part);
void convertTo12Hr(int hr, int &convertHr, partType &part);
class clockType
{
public:
    // clockType(int h = 0, int m = 0, int s = 0);
    virtual void setTime(int hour, int minute, int second) = 0;
    void getTime(int &hour, int &minute, int &second) const;
    bool validMin() const;
    bool validSec() const;

    void incrementSeconds();
    void incrementMinutes();
    void setMinute(int minute);
    void setSecond(int second);
    void setPartOfDay(partType p);
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    bool equalTime(const clockType &) const;
    virtual bool validHr() const = 0;
    virtual void invalidHr() = 0;
    virtual void incrementHours() = 0;
    virtual void setHour(int hour) = 0;
    static timeType formats[2];
    static std::string formatToStr[2];
    virtual clockType *makeCopy() = 0;
    friend std::ostream &operator<<(std::ostream &outputStream, const clockType &);
    friend std::istream &operator>>(std::istream &inputStream, clockType &clockToFill);
    const clockType &operator++();
    friend const clockType &operator++(clockType &, int);
    static std::map<int, partType> intToPartType;

protected:
    int hr;
    int min;
    int sec;
    virtual std::string toString() const;
};
class twelveHrClock;
class twentyFourHrClock : public clockType
{
public:
    twentyFourHrClock(int h = 0, int m = 0, int s = 0);
    twentyFourHrClock(const twelveHrClock &);
    const twentyFourHrClock &operator=(const twelveHrClock &rightClock);
    bool validHr() const;
    void invalidHr();
    void incrementHours();
    void setHour(int hour);
    void setTime(int h, int m, int s);
    bool operator==(const twentyFourHrClock &rightHandClock) const;
    bool operator==(const twelveHrClock &right) const;
    bool operator!=(const twentyFourHrClock &right) const;
    bool operator!=(const twelveHrClock &right) const;
    bool operator>(const twentyFourHrClock &right) const;
    bool operator>(const twelveHrClock &right) const;
    bool operator>=(const twentyFourHrClock &right) const;
    friend bool operator<(const twentyFourHrClock &left, const twentyFourHrClock &right);
    friend bool operator<(const twentyFourHrClock &left, const twelveHrClock &right);
    friend bool operator<(const twelveHrClock &left, const twentyFourHrClock &right);
    twentyFourHrClock operator+(int rightHandSide) const;
    friend twentyFourHrClock operator+(int leftSecondsToAdd, const twentyFourHrClock &rightHandClock);
    clockType *makeCopy();
};

class twelveHrClock : public clockType
{
public:
    twelveHrClock(int h, int m, int s, partType part);
    bool validHr() const;
    void invalidHr();
    void setPartOfDay(partType part);

    void setHour(int h);
    void incrementHours();
    // std::string getPartOfDay();
    partType getPart() const { return partOfDay; };
    // void setPartOfDay(std::string);
    void setTime(int h, int m, int s, partType p);
    void setTime(int h, int m, int s);
    friend void myFunc(const twelveHrClock &theClock);
    twelveHrClock operator+(int rightHandSide) const;
    friend twelveHrClock operator+(int leftSecondsToAdd, const twelveHrClock &rightHandClock);
    const twelveHrClock &operator=(const twelveHrClock &rightHandClock);
    clockType *makeCopy();
    friend std::ostream &operator<<(std::ostream &outputStream, const twelveHrClock &clockToCopy);
    friend bool operator<(const twentyFourHrClock &left, const twelveHrClock &right);
    friend bool operator<(const twelveHrClock &left, const twentyFourHrClock &right);
    // lecture activity
    // create overloaded >, ==, !=, >=, <= operators for the twelveHrClockClass

private:
    partType partOfDay;
    std::string toString() const;
};
#endif