#include "snake.h"

// moving right
// dirX = 1, dirY = 0

// moving left
// dirX = -1, dirY = 0

// // moving down
// dirX = 0, dirY = 1

// moving up
// dirX = 0, dirY = -1
Snake::Snake()
{
}

void Snake::move()
{
    int dirX = direction.first;
    int dirY = direction.second;
    int newHeadX = getHeadX() + (dirX * 10);
    int newHeadY = getHeadY() + (dirY * 10);
    body.push_front({newHeadX, newHeadY}); // add new head
    body.pop_back();                        // remove tail
}
void Snake::grow()
{
}
void Snake::reset(int spawnX, int spawnY)
{
    body.clear();
    length = 1;
    body.push_back({spawnX, spawnY});
    setDirection(1, 0);
}
void Snake::setDirection(int dirX, int dirY)
{
     direction = {dirX, dirY};
}
std::pair<int, int> Snake::getDirection()
{
    return direction;
}
bool Snake::checkWallCollision(int maxX, int maxY)
{
    int headX = getHeadX();
    int headY = getHeadY();

    if (headX < 0 || headX >= maxX)
        return true;
    if (headY < 0 || headY >= maxY)
        return true;

    return false;
    return false;
}
bool Snake::checkSelfCollision()
{
    return false;
}
bool Snake::checkFoodCollision(int foodX, int foodY)
{
    return false;
}
int Snake::getHeadX()
{
    return body[0].first;
}
int Snake::getHeadY()
{
    return body[0].second;
}
int Snake::getLength()
{
    return 0;
}
std::deque<std::pair<int,int>> Snake::getBody()
{
    return body;
}