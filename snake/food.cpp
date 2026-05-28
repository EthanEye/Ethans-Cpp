#include "food.h"
#include <cstdlib>
#include <ctime>

Food::Food()
{
}

std::pair<int, int> Food::spawn(int maxX, int maxY)
{
    

    if (rand() % 100 < 10)
    {
        x = (rand() % (maxX / 10)) * 10;
        y = (rand() % (maxY / 10)) * 10;
        return {x, y};
    }
    return {-1, -1}; 
}

bool Food::isBlocked(int x, int y)
{
    return false;
}