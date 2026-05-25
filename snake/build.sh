#!/bin/bash
moc game.h -o moc_game.cpp
g++ -fPIC -o snake main.cpp game.cpp snake.cpp food.cpp moc_game.cpp $(pkg-config --cflags --libs Qt6Widgets Qt6Core Qt6Gui)
./snake
