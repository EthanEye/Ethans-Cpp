#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode({SCREEN_X, SCREEN_Y}), "Snake"),
               font("DejaVuSans.ttf"),
               scoreText(font),
               recordText(font),
               db("mydb.db")
{

    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});

    recordText.setString("Record: 0");
    recordText.setCharacterSize(24);
    recordText.setFillColor(sf::Color::White);
    recordText.setPosition({350.f, 10.f});

    score = 0;
    isGameOver = false;
}

void Game::init()
{
    updateScore();
    isGameOver = false;
    foodRects.clear();
    food.x = -100;
    food.y = -100;
    int centerX = ((SCREEN_X / 2) / 20) * 20;
    int centerY = ((SCREEN_Y / 2) / 20) * 20;
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
                updateScore();
                isGameOver = true;
            }

            if (foodRects.size() < 20)
            {
                auto [foodX, foodY] = food.spawn(SCREEN_X, SCREEN_Y);
                if (foodX != -1 && foodY != -1)
                {
                    sf::RectangleShape newFood(sf::Vector2f(20.f, 20.f));
                    newFood.setFillColor(sf::Color::Red);
                    newFood.setPosition(sf::Vector2f(foodX, foodY));
                    food.x = foodX;
                    food.y = foodY;
                    foodRects.push_back(newFood);
                }
            }
            for (int i = 0; i < foodRects.size(); i++)
            {
                sf::Vector2f pos = foodRects[i].getPosition();
                if (snake.checkFoodCollision(pos.x, pos.y))
                {
                    snake.grow();
                    score += 1;
                    scoreText.setString("Score: " + std::to_string(score));
                    foodRects.erase(foodRects.begin() + i);
                    i--; // adjust index after erase
                    break;
                }
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
        rect = sf::RectangleShape(sf::Vector2f(20.f, 20.f));
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(sf::Vector2f(x, y));
        window.draw(rect);
    }
    for (auto &f : foodRects)
    {
        window.draw(f);
    }
    window.draw(scoreText);
    window.draw(recordText);
    window.display();
}

void Game::updateScore()
{
    db.query("CREATE TABLE IF NOT EXISTS leaderboard (id INTEGER PRIMARY KEY, player TEXT UNIQUE, high_score INTEGER DEFAULT 0);");
    db.query("INSERT OR IGNORE INTO leaderboard (player, high_score) VALUES ('player1', 0);");

    // only update if its a new high score
    int currentHigh = db.getHighScore("player1");
    recordText.setString("Record: " + std::to_string(currentHigh));
    if (score > currentHigh)
    {
        std::string sql = "UPDATE leaderboard SET high_score = " + std::to_string(score) + " WHERE player = 'player1';";
        db.query(sql);
    }
}
int Game::getScore()
{
    return score;
}
