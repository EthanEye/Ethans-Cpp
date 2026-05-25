#pragma once
#include <QWidget>
#include <QScreen>
#include "snake.h" 
#include "food.h"

class Game : public QWidget {
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
    void update();
    void render();
    void reset();
    int getScore();
};