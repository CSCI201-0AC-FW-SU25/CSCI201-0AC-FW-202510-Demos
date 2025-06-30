#ifndef CLOCK_H
#define CLOCK_H
#include <string>
#include <sstream>
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
    clockType(int h = 0, int m = 0, int s = 0);
    void setTime(int hour, int minute, int second);
    void getTime(int &hour, int &minute, int &second) const;
    bool validHr() const;
    bool validMin() const;
    bool validSec() const;
    std::string toString() const;
    void incrementSeconds();
    void incrementMinutes();
    virtual void incrementHours();
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);
    void setPartOfDay(partType p);
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    bool equalTime(const clockType &) const;
    static timeType formats[2];
    static std::string formatToStr[2];

protected:
    int hr;
    int min;
    int sec;
};

class twelveHrClock : public clockType
{
public:
    twelveHrClock(int h, int m, int s, partType part);
    bool validHr() const;
    void setPartOfDay(partType part);
    std::string toString() const;
    void setHour(int h);
    void incrementHours();
    std::string getPartOfDay();
    partType getPart() const { return partOfDay; };
    void setPartOfDay(std::string);
    void setTime(int h, int m, int s, partType p);

private:
    partType partOfDay;
};
#endif