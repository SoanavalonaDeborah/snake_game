#include "snake.h"
#include <iostream>

Snake::Snake(int gridSize, int startX, int startY)
    : gridSize(gridSize), direction(Direction::Right), nextDirection(Direction::Right)
{
    body.push_back({startX, startY});       // Tête
    body.push_back({startX - 1, startY});   // Corps
    body.push_back({startX - 2, startY});   // Queue

    textures["snake_tail_up"].loadFromFile("assets/images/snake_tail_up.png");
    textures["snake_tail_down"].loadFromFile("assets/images/snake_tail_down.png");
    textures["snake_tail_left"].loadFromFile("assets/images/snake_tail_left.png");
    textures["snake_tail_right"].loadFromFile("assets/images/snake_tail_right.png");


    // Charger toutes les textures
    std::vector<std::string> textureNames = {
        "head_up", "head_down", "head_left", "head_right",
        "body_horizontal", "body_vertical",
        "body_turn_topleft", "body_turn_topright",
        "body_turn_bottomleft", "body_turn_bottomright",
        "tail_up", "tail_down", "tail_left", "tail_right"
    };
    

    for (const std::string& name : textureNames) {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/images/snake_" + name + ".png")) {
            std::cerr << "Erreur lors du chargement de snake_" << name << ".png" << std::endl;
            exit(1);
        }
        textures[name] = texture;
    }
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
    for (size_t i = 0; i < body.size(); ++i) {
        std::string textureName = getSegmentTextureName(i);
        sprite.setTexture(textures.at(textureName));
        sprite.setPosition(body[i].x * gridSize, body[i].y * gridSize);
        sprite.setScale(
            static_cast<float>(gridSize) / sprite.getTexture()->getSize().x,
            static_cast<float>(gridSize) / sprite.getTexture()->getSize().y
        );
        if (i == body.size() - 1) {  // Dernier segment : queue
            Point tail = body[i];
            Point beforeTail = body[i - 1];
        
            if (tail.x < beforeTail.x) {
                sprite.setTexture(textures["snake_tail_left"]);
            } else if (tail.x > beforeTail.x) {
                sprite.setTexture(textures["snake_tail_right"]);
            } else if (tail.y < beforeTail.y) {
                sprite.setTexture(textures["snake_tail_up"]);
            } else if (tail.y > beforeTail.y) {
                sprite.setTexture(textures["snake_tail_down"]);
            }
        
            sprite.setPosition(tail.x * gridSize, tail.y * gridSize);
            window.draw(sprite);
            continue;  // Passe au segment suivant
        }
        
        

        window.draw(sprite);        
    }
}


void Snake::reset() {
    body.clear();
    body.push_back({10, 10});
    body.push_back({9, 10});
    body.push_back({8, 10});
    direction = Direction::Right;
    nextDirection = Direction::Right;
}


std::string Snake::getSegmentTextureName(int index) const {
    if (index == 0) {
        switch (direction) {
            case Direction::Up: return "head_up";
            case Direction::Down: return "head_down";
            case Direction::Left: return "head_left";
            case Direction::Right: return "head_right";
        }
    } else if (index == body.size() - 1) {
        const Point& beforeTail = body[body.size() - 2];
        const Point& tail = body.back();
        if (tail.x < beforeTail.x) return "tail_right";
        if (tail.x > beforeTail.x) return "tail_left";
        if (tail.y < beforeTail.y) return "tail_down";
        if (tail.y > beforeTail.y) return "tail_up";
    } else {
        const Point& prev = body[index - 1];
        const Point& curr = body[index];
        const Point& next = body[index + 1];

        bool horizontal = (prev.y == curr.y && next.y == curr.y);
        bool vertical = (prev.x == curr.x && next.x == curr.x);

        if (horizontal) return "body_horizontal";
        if (vertical) return "body_vertical";

        // Détection des virages
        if ((prev.x < curr.x && next.y < curr.y) || (next.x < curr.x && prev.y < curr.y))
            return "body_turn_bottomright";
        if ((prev.x > curr.x && next.y < curr.y) || (next.x > curr.x && prev.y < curr.y))
            return "body_turn_bottomleft";
        if ((prev.x < curr.x && next.y > curr.y) || (next.x < curr.x && prev.y > curr.y))
            return "body_turn_topright";
        if ((prev.x > curr.x && next.y > curr.y) || (next.x > curr.x && prev.y > curr.y))
            return "body_turn_topleft";
    }
    return "body_vertical"; // fallback
}
