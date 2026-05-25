#!/bin/bash
g++ -o snake main.cpp game.cpp snake.cpp food.cpp -lsfml-graphics -lsfml-window -lsfml-system
./snake
