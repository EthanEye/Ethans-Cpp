#pragma once
#include <vector>
#include <utility>

class Food{
    public:
    int spawnRate;
    int x, y;
    std::vector<std::pair<int,int>> blockedLocations;

    Food();
    void spawn(int maxX, int maxY);
    void addBlockedLocation(int x, int y);
    bool isBlocked(int x, int y);

};