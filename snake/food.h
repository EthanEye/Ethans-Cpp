#pragma once
#include <vector>
#include <utility>

class Food{
    public:
    int spawnRate;
    int x, y;
    std::vector<std::pair<int,int>> blockedLocations;

    Food();
    std::pair<int,int> spawn(int maxX, int maxY);
    bool isBlocked(int x, int y);

};