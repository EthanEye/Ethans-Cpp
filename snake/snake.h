#pragma once
#include <vector>
#include <utility>

class Snake {
private:
    int dirX, dirY;
    int length;
    std::vector<std::pair<int,int>> body;

public:
    Snake();
    void move();
    void grow();
    void reset();
    void setDirection(int dirX, int dirY);
    bool checkWallCollision(int maxX, int maxY);
    bool checkSelfCollision();
    bool checkFoodCollision(int foodX, int foodY);
    int getHeadX();
    int getHeadY();
    int getLength();
};