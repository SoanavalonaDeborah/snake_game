#pragma once

#include <SFML/Graphics.hpp>
#include "snake.h"
#include "food.h"


class Game {
public:
    Game(int windowWidth, int windowHeight, int gridSize);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void reset();
    void drawGrid();
    sf::Font font;
    sf::Text gameOverText;




    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;
    int gridSize;
    bool isRunning;

    Snake snake;
    Food food;
};
