#ifndef CLOCK_H
#define CLOCK_H
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

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
class clockType
{
public:
    // clockType(int h = 0, int m = 0, int s = 0);
    virtual void setTime(int hour, int minute, int second) = 0;
    void getTime(int &hour, int &minute, int &second) const;
    bool validMin() const;
    bool validSec() const;
    virtual std::string toString() const;
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

protected:
    int hr;
    int min;
    int sec;
};
class twentyFourHrClock : public clockType
{
public:
    twentyFourHrClock(int h = 0, int m = 0, int s = 0);
    bool validHr() const;
    void invalidHr();
    void incrementHours();
    void setHour(int hour);
    void setTime(int h, int m, int s);
    bool operator==(const twentyFourHrClock &rightHandClock);
    clockType *makeCopy();
};

class twelveHrClock : public clockType
{
public:
    twelveHrClock(int h, int m, int s, partType part);
    bool validHr() const;
    void invalidHr();
    void setPartOfDay(partType part);
    std::string toString() const;
    void setHour(int h);
    void incrementHours();
    // std::string getPartOfDay();
    partType getPart() const { return partOfDay; };
    // void setPartOfDay(std::string);
    void setTime(int h, int m, int s, partType p);
    void setTime(int h, int m, int s);
    friend void myFunc(const twelveHrClock &theClock);
    twelveHrClock operator+(int rightHandSide) const;
    const twelveHrClock &operator=(const twelveHrClock &rightHandClock);
    clockType *makeCopy();

private:
    partType partOfDay;
};
#endif