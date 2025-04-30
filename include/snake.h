#pragma once

#include "point.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>


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
    
    // ✅ Ajoutés pour gérer les sprites selon le segment
    std::map<std::string, sf::Texture> textures;
    sf::Sprite sprite;

    // ✅ Ajoute cette méthode pour obtenir le bon nom de texture
    std::string getSegmentTextureName(int index) const;

    // Ancienne forme avec rectangle (encore utilisée si besoin)
    mutable sf::RectangleShape shape;
};
