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
        x = (rand() % (maxX / 20)) * 20;
        y = (rand() % (maxY / 20)) * 20;
        return {x, y};
    }
    return {-1, -1}; 
}

bool Food::isBlocked(int x, int y)
{
    return false;
}