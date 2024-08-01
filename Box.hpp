#pragma once
#include "SFML/Graphics.hpp"

class Box{
public:
    Box(int, int);
    sf::RectangleShape body;

    int value;
    int type;
    int xLocation;
    int yLocation;
    bool visited;
    Box* prev;
};