#ifndef CLOCKEXCEPT_H
#define CLOCKEXCEPT_H
#include <stdexcept>

class invalid_hour : public std::invalid_argument
{
public:
    invalid_hour(int hour);
};

#endif