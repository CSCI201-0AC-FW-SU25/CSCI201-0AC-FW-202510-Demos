#include "clock.h"

timeType clockType::formats[2] = {TWELVE, TWENTYFOUR};
std::string clockType::formatToStr[2] = {"12 hour clock", "24 hour clock"};

clockType::clockType(int h, int m, int s)
{

    setTime(h, m, s);
}
void clockType::setTime(int hour, int minute, int second)
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
std::string clockType::toString() const
{
    std::ostringstream out;
    out << std::setfill('0');
    out << std::setw(2) << hr << ":" << std::setw(2) << min << ":" << std::setw(2) << sec;
    /* if (format == TWELVE)
    {
        out << " " << partToStr[static_cast<int>(partOfDay)];
    } */

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
void clockType::incrementHours()
{
    hr++;
    if (hr > 23)
    {
        hr = 0;
    }
    /* else if (format == TWELVE)
    {
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
    } */
}
void clockType::setHour(int hour)
{
    /* if (format == TWELVE)
    {
        if (hour >= 1 && hour <= 12)
        {
            hr = hour;
        }
        else
        {
            hr = 12;
        }
    }
    else
    { */
    if (hour >= 0 && hour <= 23)
    {
        hr = hour;
    }
    else
    {
        hr = 0;
    }
    //}
}
void clockType::setMinute(int minute)
{
    if (minute >= 0 && minute <= 59)
    {
        min = minute;
    }
    else
    {
        min = 0;
    }
}
void clockType::setSecond(int second)
{
    if (second >= 0 && second <= 59)
    {
        sec = second;
    }
    else
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

twelveHrClock::twelveHrClock(int h, int m, int s, partType part) : clockType(h, m, s)
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