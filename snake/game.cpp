#include "game.h"
#include <QScreen>
#include <QApplication>
#include <iostream>

// constructor
Game::Game() : QWidget(nullptr), score(0), level(1), isRunning(true), isGameOver(false)
{
    // size
    setFixedSize(SCREEN_X, SCREEN_Y);
    
    // title
    setWindowTitle("Snake");
    
    // background color
    setStyleSheet("background-color: black;");
    
    // center on screen
    move(QApplication::primaryScreen()->geometry().center() - rect().center());
}

// methods
void Game::run()
{
    std::cout << "Starting game\n";
        init();
    while (isRunning)
    {
        update();
        render();
    }
}
void Game::init(){

}
void Game::update()
{
}
void Game::render()
{
}
void Game::reset()
{
}
int Game::getScore()
{
    return score;
}
