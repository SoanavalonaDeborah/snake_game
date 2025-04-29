#pragma once

#include "point.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>



enum class Direction { Up, Down, Left, Right };

class Snake {
public:
    Snake(int gridSize, int startX, int startY);
    
    void move();
    void changeDirection(Direction newDirection);
    void grow();
    bool checkSelfCollision() const;
    void draw(sf::RenderWindow& window);
    Point getHeadPosition() const;
    bool eats(const Point& foodPosition) const;
    void reset();

private:
    std::vector<Point> body;
    Direction direction;
    Direction nextDirection;
    int gridSize;
    sf::Texture texture;
    sf::Sprite sprite;

    // Ajoute `mutable` ici :
    mutable sf::RectangleShape shape;
};
