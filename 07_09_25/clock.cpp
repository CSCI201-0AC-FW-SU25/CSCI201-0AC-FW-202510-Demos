#include "clock.h"

timeType clockType::formats[2] = {TWELVE, TWENTYFOUR};
std::string clockType::formatToStr[2] = {"12 hour clock", "24 hour clock"};

int convertTo24Hr(int hr, partType part)
{
    int standardHour = hr;

    if (standardHour == 12)
    {
        standardHour = 0;
    }
    if (part == partType::PM)
    {
        standardHour = standardHour + 12;
    }
    return standardHour;
}

void convertTo12Hr(int hr, int &convertHr, partType &part)
{
    convertHr = hr;
    if (hr >= 12)
    {
        part = partType::PM;
        if (hr != 12)
        {
            convertHr -= 12;
        }
    }
    else
    {
        part = partType::AM;
    }
}

std::ostream &operator<<(std::ostream &outputStream, const clockType &clockToPrint)
{
    outputStream << clockToPrint.toString();
    return outputStream;
}

std::istream &operator>>(std::istream &inputStream, clockType &clockToFill)
{
    inputStream >> clockToFill.hr >> clockToFill.min >> clockToFill.sec;
    return inputStream;
}

const clockType &operator++(clockType &c, int)
{
    clockType *temp = c.makeCopy();
    c.incrementSeconds();
    return *temp;
}

bool operator<(const twentyFourHrClock &left, const twentyFourHrClock &right)
{
    bool lessThan = false;
    if (left.hr < right.hr)
    {
        lessThan = true;
    }
    else if (left.hr == right.hr)
    {
        if (left.min < right.min)
        {
            lessThan = true;
        }
        else if (left.min == right.min)
        {
            if (left.sec < right.sec)
            {
                lessThan = true;
            }
        }
    }

    return lessThan;
}

bool operator<(const twentyFourHrClock &left, const twelveHrClock &right)
{
    twentyFourHrClock temp(right);
    return left < temp;
}

bool operator<(const twelveHrClock &left, const twentyFourHrClock &right)
{

    return right > left;
}

twentyFourHrClock operator+(int leftSecondsToAdd, const twentyFourHrClock &rightHandClock)
{
    return rightHandClock + leftSecondsToAdd;
}

void myFunc(const twelveHrClock &theClock)
{
    int hour = theClock.hr;
}

twelveHrClock operator+(int leftSecondsToAdd, const twelveHrClock &rightHandClock)
{
    return rightHandClock + leftSecondsToAdd;
}

std::ostream &operator<<(std::ostream &outputStream, const twelveHrClock &clockToCopy)
{
    outputStream << clockToCopy.toString();
    return outputStream;
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
    if (hour >= 0 && hour <= 23)
    {
        hr = hour;
    }
    else
    {
        throw std::invalid_argument(std::to_string(hour) + " is not a valid hour.");
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

    if (minute >= 0 && minute <= 59)
    {
        min = minute;
    }
    else
    {
        throw minute;
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
        throw second;
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
    if (hr >= 1 && hr <= 12)
    {
        hr = hour;
    }
    else
    {
        throw hour;
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

bool twentyFourHrClock::operator==(const twentyFourHrClock &rightHandClock) const
{
    return this->hr == rightHandClock.hr && this->min == rightHandClock.min && this->sec == rightHandClock.sec;
}

bool twentyFourHrClock::operator==(const twelveHrClock &right) const
{
    twentyFourHrClock temp(right);
    return *this == temp;
}

bool twentyFourHrClock::operator!=(const twentyFourHrClock &right) const
{
    return !(*this == right);
}

bool twentyFourHrClock::operator!=(const twelveHrClock &right) const
{
    return !(*this == right);
}

bool twentyFourHrClock::operator>(const twentyFourHrClock &right) const
{
    bool greaterThan = false;
    if (this->hr > right.hr)
    {
        greaterThan = true;
    }
    else if (this->hr == right.hr)
    {
        if (this->min > right.min)
        {
            greaterThan = true;
        }
        else if (this->min == right.min)
        {
            if (this->sec > right.sec)
            {
                greaterThan = true;
            }
        }
    }

    return greaterThan;
}

bool twentyFourHrClock::operator>(const twelveHrClock &right) const
{
    twentyFourHrClock temp(right);
    return *this > temp;
}

bool twentyFourHrClock::operator>=(const twentyFourHrClock &right) const
{
    return (*this > right) || (*this == right);
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

twentyFourHrClock twentyFourHrClock::operator+(int secondsToAdd) const
{
    twentyFourHrClock tempClock = *this;
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

twentyFourHrClock::twentyFourHrClock(const twelveHrClock &clockToConvert)
{
    this->hr = convertTo24Hr(clockToConvert.getHour(), clockToConvert.getPart());
    this->min = clockToConvert.getMinute();
    this->sec = clockToConvert.getSecond();
}

const twentyFourHrClock &twentyFourHrClock::operator=(const twelveHrClock &rightClock)
{
    this->hr = convertTo24Hr(rightClock.getHour(), rightClock.getPart());
    this->min = rightClock.getMinute();
    this->sec = rightClock.getSecond();
    return *this;
}

const clockType &clockType::operator++()
{
    this->incrementSeconds();
    return *this;
}
