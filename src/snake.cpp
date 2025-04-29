#include "snake.h"
#include <iostream>

Snake::Snake(int gridSize, int startX, int startY)
    : gridSize(gridSize), direction(Direction::Right), nextDirection(Direction::Right)
{
    body.push_back({startX, startY});

    // Charger la texture du serpent
    if (!texture.loadFromFile("assets/images/snake.png")) {
        std::cerr << "Erreur lors du chargement de la texture du serpent." << std::endl;
        exit(1);
    }
    

    // Assure-toi que le sprite est de la bonne taille
    sprite.setTexture(texture);
    sprite.setScale(static_cast<float>(gridSize) / texture.getSize().x,
                    static_cast<float>(gridSize) / texture.getSize().y); // Mise à l'échelle pour correspondre à la taille de la grille
}


void Snake::move() {
    direction = nextDirection; // Changement effectif à chaque frame

    Point head = body.front();

    switch (direction) {
        case Direction::Up:    head.y--; break;
        case Direction::Down:  head.y++; break;
        case Direction::Left:  head.x--; break;
        case Direction::Right: head.x++; break;
    }

    body.insert(body.begin(), head);
    body.pop_back(); // Supprimer la dernière cellule sauf si on grandit
}

void Snake::changeDirection(Direction newDirection) {
    // Empêche les demi-tours instantanés
    if ((direction == Direction::Up && newDirection != Direction::Down) ||
        (direction == Direction::Down && newDirection != Direction::Up) ||
        (direction == Direction::Left && newDirection != Direction::Right) ||
        (direction == Direction::Right && newDirection != Direction::Left)) {
        nextDirection = newDirection;
    }
}

void Snake::grow() {
    body.push_back(body.back()); // ajoute un segment au même endroit que la queue
}


bool Snake::checkSelfCollision() const {
    if (body.size() <= 3) return false; // Trop court pour se cogner

    const Point& head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (head == body[i])
            return true;
    }
    return false;
}


bool Snake::eats(const Point& foodPosition) const {
    return getHeadPosition() == foodPosition;
}


Point Snake::getHeadPosition() const {
    return body.front();
}


void Snake::draw(sf::RenderWindow& window) {
    for (const Point& segment : body) {
        sprite.setPosition(static_cast<float>(segment.x * gridSize), 
                           static_cast<float>(segment.y * gridSize));  // Conversion explicite en float
        window.draw(sprite);  // Dessiner le sprite
    }
}



void Snake::reset() {
    body.clear();
    body.push_back({10, 10});
    direction = Direction::Right;
    nextDirection = Direction::Right;
}
