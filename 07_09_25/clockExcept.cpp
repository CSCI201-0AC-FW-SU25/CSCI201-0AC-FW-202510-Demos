#include "clockExcept.h"

invalid_hour::invalid_hour(int hour) : std::invalid_argument(std::to_string(hour) + " is not a valid hour.")
{
}