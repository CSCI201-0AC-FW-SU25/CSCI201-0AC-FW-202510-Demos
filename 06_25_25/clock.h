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
    clockType(timeType f, int h = 0, int m = 0, int s = 0, partType p = partType::PM);
    void setTime(int hour, int minute, int second, partType p = partType::PM);
    void getTime(int &hour, int &minute, int &second) const;
    std::string printTime() const;
    void incrementSeconds();
    void incrementMinutes();
    void incrementHours();
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

private:
    int hr;
    int min;
    int sec;
    partType partOfDay;
    timeType format;
};
#endif