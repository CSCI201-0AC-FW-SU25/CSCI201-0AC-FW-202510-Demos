#include <iostream>
#include <limits>
#include "clock.h"

int main()
{
    try
    {
        twentyFourHrClock(155, 0, 0);
    }
    catch (int x)
    {
        std::cout << "Cannot create a clock " << x << " is an invalid value. " << std::endl;
    }
    catch (std::invalid_argument e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}