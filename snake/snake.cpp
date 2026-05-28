#include "snake.h"
#include "food.h"

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
    if (shouldGrow) {
        shouldGrow = false;
    } else {
        body.pop_back();
    }
}
void Snake::grow()
{
    shouldGrow = true;

}
void Snake::reset(int spawnX, int spawnY)
{
    shouldGrow = false;
    body.clear();
    body.push_back({spawnX, spawnY});
    length = 1;
    setDirection(1, 0);
}
void Snake::setDirection(int dirX, int dirY)
{
    if (dirX == -direction.first && dirY == -direction.second)
        return;
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
}
bool Snake::checkSelfCollision()
{
    int headX = getHeadX();
    int headY = getHeadY();
    for (int i = 1; i < body.size(); i++)
    {
        if (headX == body[i].first && headY == body[i].second)
            return true;
    }
    return false;
}
bool Snake::checkFoodCollision(int foodX, int foodY)
{
    if(getHeadX() == foodX && getHeadY() == foodY){
        return true;
    }
        
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
    return body.size();
}
std::deque<std::pair<int, int>> Snake::getBody()
{
    return body;
}