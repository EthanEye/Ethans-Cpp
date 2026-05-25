#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode({SCREEN_X, SCREEN_Y}), "Snake")
{
    score = 0;
    level = 1;
    isRunning = true;
    isGameOver = false;
}

void Game::init()
{
    int centerX = (SCREEN_X / 2) - 5;
    int centerY = (SCREEN_Y / 2) - 5;
    snake.reset(centerX, centerY);
}

void Game::run()
{
    init();
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        update();
        if (!snake.checkWallCollision(SCREEN_X, SCREEN_Y))
        {
            snake.move();
        }
        else
        {
            isGameOver = true;
            window.close();
        }

        sf::sleep(sf::milliseconds(REFRESH));
    }
}

void Game::update()
{
    std::deque<std::pair<int,int>> body = snake.getBody();
    window.clear(sf::Color::Black);

    for (auto &segment : snake.getBody())
    {
        int x = segment.first;
        int y = segment.second;
        rect = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(sf::Vector2f(x, y));
        window.draw(rect);
    }
    window.display();
}

void Game::reset()
{
}
int Game::getScore()
{
    return score;
}
