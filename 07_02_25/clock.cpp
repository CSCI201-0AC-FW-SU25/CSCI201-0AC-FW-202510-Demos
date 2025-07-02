#include "clock.h"

timeType clockType::formats[2] = {TWELVE, TWENTYFOUR};
std::string clockType::formatToStr[2] = {"12 hour clock", "24 hour clock"};

void myFunc(const twelveHrClock &theClock)
{
    int hour = theClock.hr;
}

twentyFourHrClock::twentyFourHrClock(int h, int m, int s)
{
    setTime(h, m, s);
}
void twentyFourHrClock::setTime(int hour, int minute, int second)
{
    setHour(hour);
    setMinute(minute);
    setSecond(second);
}
void clockType::getTime(int &hour, int &minute, int &second) const
{
    hour = hr;
    minute = min;
    second = sec;
}
bool clockType::validMin() const
{
    return min >= 0 && min <= 59;
}
bool clockType::validSec() const
{
    return sec >= 0 && sec <= 59;
}
std::string clockType::toString() const
{
    std::ostringstream out;
    out << std::setfill('0');
    out << std::setw(2) << hr << ":" << std::setw(2) << min << ":" << std::setw(2) << sec;
    return out.str();
}
void clockType::incrementSeconds()
{
    sec++;
    if (sec > 59)
    {
        sec = 0;
        incrementMinutes();
    }
}
void clockType::incrementMinutes()
{
    min++;
    if (min > 59)
    {
        min = 0;
        incrementHours();
    }
}
void twentyFourHrClock::incrementHours()
{
    hr++;
    if (hr > 23)
    {
        hr = 0;
    }
}
void twentyFourHrClock::setHour(int hour)
{

    hr = hour;
    if (!validHr())
    {
        invalidHr();
    }
}

bool twentyFourHrClock::validHr() const
{
    return hr >= 0 && hr <= 23;
}
void twentyFourHrClock::invalidHr()
{
    std::cout << "Hours must be between 0 and 23." << std::endl;
    std::cout << "Defaulting to 0." << std::endl;
    hr = 0;
}
void clockType::setMinute(int minute)
{

    min = minute;
    if (!validMin())
    {
        min = 0;
    }
}

void clockType::setSecond(int second)
{

    sec = second;

    if (!validSec())
    {
        sec = 0;
    }
}
int clockType::getHour() const
{
    return hr;
}
int clockType::getMinute() const
{
    return min;
}
int clockType::getSecond() const
{
    return sec;
}
bool clockType::equalTime(const clockType &otherClock) const
{
    int standardHour = hr;
    int othStandardHour = otherClock.hr;
    /* if (format == TWELVE)
    {
        if (standardHour == 12)
        {
            standardHour = 0;
        }
        if (partOfDay == partType::PM)
        {
            standardHour += 12; // standardHour = standardHour + 12;
        }
    }
    if (otherClock.format == TWELVE)
    {
        if (othStandardHour == 12)
        {
            othStandardHour = 0;
        }
        if (otherClock.partOfDay == partType::PM)
        {
            othStandardHour += 12;
        }
    } */
    return standardHour == othStandardHour && min == otherClock.min && sec == otherClock.sec;
}

twelveHrClock::twelveHrClock(int h, int m, int s, partType part)
{
    setTime(h, m, s, part);
}

bool twelveHrClock::validHr() const
{
    return hr >= 1 && hr <= 12;
}

void twelveHrClock::invalidHr()
{
    std::cout << "Hours must be between 1 and 12." << std::endl;
    std::cout << "Defaulting to 12." << std::endl;
    hr = 12;
}

void twelveHrClock::setPartOfDay(partType p)
{
    partOfDay = p;
}

void twelveHrClock::setHour(int hour)
{

    hr = hour;
    if (!validHr())
    {
        invalidHr();
    }
}

void twelveHrClock::incrementHours()
{
    hr++;
    if (hr == 12)
    {
        if (partOfDay == partType::AM)
        {
            partOfDay = partType::PM;
        }
        else
        {
            partOfDay = partType::AM;
        }
    }
    if (hr > 12)
    {
        hr = 1;
    }
}
void twelveHrClock::setTime(int h, int m, int s, partType p)
{
    setHour(h);
    setMinute(m);
    setSecond(s);
    setPartOfDay(p);
}

std::string twelveHrClock::toString() const
{
    std::ostringstream out;
    out << clockType::toString();
    out << " " << partToStr[static_cast<int>(partOfDay)];
    return out.str();
}

void twelveHrClock::setTime(int hour, int minute, int second)
{
    setHour(hour);
    setMinute(minute);
    setSecond(second);
}

bool twentyFourHrClock::operator==(const twentyFourHrClock &rightHandClock)
{
    return this->hr == rightHandClock.hr && this->min == rightHandClock.min && this->sec == rightHandClock.sec;
}

clockType *twentyFourHrClock::makeCopy()
{
    return new twentyFourHrClock(*this);
}

twelveHrClock twelveHrClock::operator+(int secondsToAdd) const
{
    twelveHrClock tempClock = *this;
    for (int i = 0; i < secondsToAdd; i++)
    {
        tempClock.incrementSeconds();
    }
    return tempClock;
}

const twelveHrClock &twelveHrClock::operator=(const twelveHrClock &rightHandClock)
{
    this->hr = rightHandClock.hr;
    this->min = rightHandClock.min;
    this->sec = rightHandClock.sec;
    this->partOfDay = rightHandClock.partOfDay;
    return *this;
}

clockType *twelveHrClock::makeCopy()
{
    return new twelveHrClock(*this);
}
