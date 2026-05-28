#pragma once
#include "snake.h"
#include "food.h"
#include <SFML/Graphics.hpp>

// ui built with SFML (simple and fast multimedia library)

class Game 
{

private:
    // screen dimensions
    static constexpr int SCREEN_X = 800;
    static constexpr int SCREEN_Y = 540;
    // refresh rate
    static constexpr int REFRESH = 100;

    // game state
    int score;
    bool isRunning;
    bool isGameOver;

    // game objects
    Snake snake;
    Food food;
    sf::RenderWindow window;
    sf::RectangleShape rect;
    sf::RectangleShape foodRect;
    sf::Font font;
    sf::Text scoreText;
    std::vector<sf::RectangleShape> foodRects;

public:
    // constructor
    Game();

    // methods
    void run();
    void init();
    void update();
    int getScore();


};