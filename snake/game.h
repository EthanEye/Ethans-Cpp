#pragma once
#include "snake.h" 
#include "food.h"

class Game {
private:
    // screen dimensions
    static constexpr int SCREEN_X = 80;
    static constexpr int SCREEN_Y = 24;
    // refresh rate
    static constexpr int REFRESH = 60;

    // game state
    int score;
    int level;
    bool isRunning;
    bool isGameOver;

    // game objects
    Snake snake;
    Food food;

public:
    // constructor
    Game();

    // methods
    void run();
    void update();
    void render();
    void reset();
    int getScore();
};