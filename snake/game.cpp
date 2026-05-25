#include "game.h"
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <iostream>


    // constructor
    Game::Game(){
        
    }

    // methods
    void Game::run(){
        std::cout << "Starting game\n";
    }
    void Game::update(){
        

    }
    void Game::render(){

    }
    void Game::reset(){

    }
    int Game::getScore(){
        return score;

    }
