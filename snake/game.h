#pragma once
#include "snake.h"
#include "food.h"

class Game 
{

private:
    // screen dimensions
    static constexpr int SCREEN_X = 810;
    static constexpr int SCREEN_Y = 540;
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
    void init();
    void gameLoop();
    void reset();
    int getScore();


};