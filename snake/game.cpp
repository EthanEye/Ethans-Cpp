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
}

void Game::run()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }
}

void Game::reset()
{
}
int Game::getScore()
{
    return score;
}
