#pragma once
#include <deque>
#include <utility>

class Snake {
private:
    int length;
    std::pair<int,int> direction;
    std::deque<std::pair<int,int>> body;

public:
    Snake();
    std::deque<std::pair<int,int>> getBody();
    void move();
    void grow();
    void reset(int headX, int headY);
    void setDirection(int dirX, int dirY);
    std::pair<int,int> getDirection();
    bool checkWallCollision(int maxX, int maxY);
    bool checkSelfCollision();
    bool checkFoodCollision(int foodX, int foodY);
    int getHeadX();
    int getHeadY();
    int getLength();
};