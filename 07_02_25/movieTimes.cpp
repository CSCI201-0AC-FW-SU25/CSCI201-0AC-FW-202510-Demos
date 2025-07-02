#include "movieTimes.h"

MovieTimes::MovieTimes(std::string title, int runtime, std::string rating)
{
    this->title = title;
    if (runtime <= 0)
    {
        runtime = 1;
    }
    this->runtime = runtime;
    this->rating = rating;
    this->times = nullptr;
    this->numTimes = 0;
}
MovieTimes::MovieTimes(const MovieTimes &otherObject)
{
    this->times = nullptr;
    this->numTimes = 0;
    copyMovie(otherObject);
}
void MovieTimes::enterTimes()
{
    if (this->numTimes > 0)
    {
        for (int i = 0; i < this->numTimes; i++)
        {
            delete this->times[i];
        }
        delete[] this->times;
    }
    this->numTimes = inputInt("Enter the number of showtimes: ", "Please enter a number greater than 0.", isGreaterThan0);

    this->times = new clockType *[numTimes];
    for (int i = 0; i < numTimes; i++)
    {
        std::cout << "Filling in clock for showtime #" << i + 1 << std::endl;
        clockType *c = makeClock();
        this->times[i] = c;
    }
}
std::string MovieTimes::tostring()
{
    std::ostringstream out;
    out << std::left;
    out << "| " << std::setw(40) << this->title << " | " << std::setw(5) << this->rating << " | " << std::setw(3) << this->runtime << " mins | ";
    for (int i = 0; i < numTimes; i++)
    {
        out << times[i]->printTime() << " ";
    }
    return out.str();
}
std::string MovieTimes::getTitle()
{
    return title;
}
int MovieTimes::getRuntime()
{
    return runtime;
}
std::string MovieTimes::getRating()
{
    return rating;
}

MovieTimes::~MovieTimes()
{
    for (int i = 0; i < this->numTimes; i++)
    {
        delete this->times[i];
        this->times[i] = nullptr;
    }
    delete[] this->times;
    this->times = nullptr;
}

void MovieTimes::copyMovie(const MovieTimes &otherMovie)
{
    this->title = otherMovie.title;
    this->rating = otherMovie.rating;
    this->runtime = otherMovie.runtime;
    if (this->numTimes > 0)
    {
        for (int i = 0; i < this->numTimes; i++)
        {
            delete this->times[i];
        }
        delete[] times;
    }
    // this->times = otherMovie.times; don't do this shallow copy
    this->numTimes = otherMovie.numTimes;
    this->times = new clockType *[numTimes];
    for (int i = 0; i < numTimes; i++)
    {
        // this->times[i]= otherMovie.times[i]; don't do this shallow copy
        this->times[i] = new clockType(*otherMovie.times[i]);
    }
}

void MovieTimes::addTime(clockType timeAdd)
{
    numTimes++;
    clockType **temp = times;
    times = new clockType *[numTimes];
    for (int i = 0; i < numTimes - 1; i++)
    {
        times[i] = temp[i];
    }
    times[numTimes - 1] = new clockType(timeAdd);
    delete[] temp;
}

bool isGreaterThan0(int num, int, int)
{
    return num > 0;
}