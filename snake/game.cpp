#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode({SCREEN_X, SCREEN_Y}), "Snake"),
               font("DejaVuSans.ttf"),
               scoreText(font)
{

    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});
    score = 0;
    isRunning = true;
    isGameOver = false;
}

void Game::init()
{
    isGameOver = false;
    foodRects.clear();
    food.x = -100;
    food.y = -100;
    int centerX = ((SCREEN_X / 2) / 10) * 10;
    int centerY = ((SCREEN_Y / 2) / 10) * 10;
    snake.reset(centerX, centerY);
    score = 0;
    scoreText.setString("Score: " + std::to_string(score));
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

            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;

                if (isGameOver && key == sf::Keyboard::Key::Space)
                {
                    init();
                    continue;
                }

                if (key == sf::Keyboard::Key::Up)
                    snake.setDirection(0, -1);
                else if (key == sf::Keyboard::Key::Down)
                    snake.setDirection(0, 1);
                else if (key == sf::Keyboard::Key::Left)
                    snake.setDirection(-1, 0);
                else if (key == sf::Keyboard::Key::Right)
                    snake.setDirection(1, 0);
            }
        }
        if (!isGameOver)
        {
            if (!snake.checkWallCollision(SCREEN_X, SCREEN_Y) && !snake.checkSelfCollision())
            {
                snake.move();
            }
            else
            {
                scoreText.setString("Press space to restart");
                isGameOver = true;
            }

            if (foodRects.size() < 1)
            {
                auto [foodX, foodY] = food.spawn(SCREEN_X, SCREEN_Y);
                if (foodX != -1 && foodY != -1)
                {
                    sf::RectangleShape newFood(sf::Vector2f(10.f, 10.f));
                    newFood.setFillColor(sf::Color::Red);
                    newFood.setPosition(sf::Vector2f(foodX, foodY));
                    food.x = foodX;
                    food.y = foodY;
                    foodRects.push_back(newFood);
                }
            }

            if (snake.checkFoodCollision(food.x, food.y) && !foodRects.empty())
            {
                snake.grow();
                score += 1;
                scoreText.setString("Score: " + std::to_string(score));
                foodRects.pop_back();
            }
        }

        update(); 
        sf::sleep(sf::milliseconds(REFRESH));
    }
}

void Game::update()
{
    std::deque<std::pair<int, int>> body = snake.getBody();
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
    for (auto &f : foodRects)
    {
        window.draw(f);
    }
    window.draw(scoreText);
    window.display();
}

int Game::getScore()
{
    return score;
}
