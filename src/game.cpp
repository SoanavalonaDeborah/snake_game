#include <iostream>
#include "game.h"
#include <ctime>

Game::Game(int windowWidth, int windowHeight, int gridSize)
    : window(sf::VideoMode(windowWidth, windowHeight), "Snake Game"),
      windowWidth(windowWidth), windowHeight(windowHeight), gridSize(gridSize),
      snake(gridSize, 10, 10), food(gridSize, windowWidth, windowHeight),
      isRunning(true)
{
    window.setFramerateLimit(10);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Initialiser la police
    if (!font.loadFromFile("assets/fonts/Lusitana-Regular.ttf")) {  // Assure-toi d'avoir arial.ttf dans ton dossier racine
        // Si la police échoue, on termine ici
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
        exit(1);
    }

    // Initialiser le texte "Game Over"
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);  // Taille du texte
    gameOverText.setFillColor(sf::Color::Red);  // Couleur rouge
    gameOverText.setPosition(windowWidth / 4, windowHeight / 3);  // Centré
}


void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (!isRunning) {
                if (event.key.code == sf::Keyboard::Space) {  // Appuyez sur espace pour recommencer
                    reset();
                }
            } else {
                switch (event.key.code) {
                    case sf::Keyboard::Up:    snake.changeDirection(Direction::Up); break;
                    case sf::Keyboard::Down:  snake.changeDirection(Direction::Down); break;
                    case sf::Keyboard::Left:  snake.changeDirection(Direction::Left); break;
                    case sf::Keyboard::Right: snake.changeDirection(Direction::Right); break;
                    default: break;
                }
            }
        }
    }
}

void Game::update() {
    if (isRunning) {
        snake.move();

        // Vérification si le serpent mange la nourriture
        if (snake.eats(food.getPosition())) {
            snake.grow();
            food.generate();
        }

        Point head = snake.getHeadPosition();

        // Vérification si le serpent sort de la grille
        if (head.x < 0 || head.y < 0 ||
            head.x >= windowWidth / gridSize || head.y >= windowHeight / gridSize ||
            snake.checkSelfCollision()) {
            isRunning = false;  // Fin du jeu
        }
    }
}



void Game::drawGrid() {
    sf::Color gridColor(245, 245, 220); // beige

    for (int x = 0; x < windowWidth; x += gridSize) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, 0), gridColor),
            sf::Vertex(sf::Vector2f(x, windowHeight), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    for (int y = 0; y < windowHeight; y += gridSize) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, y), gridColor),
            sf::Vertex(sf::Vector2f(windowWidth, y), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
}

void Game::render() {
    window.clear(sf::Color(255, 248, 220)); // Fond beige clair

    drawGrid();         // Dessiner la grille
    food.draw(window);  // Dessiner la nourriture
    snake.draw(window); // Dessiner le serpent

    if (!isRunning) {   // Si le jeu est terminé, afficher Game Over
        window.draw(gameOverText);
    }

    window.display();
}



void Game::reset() {
    snake.reset();        // Réinitialise le serpent
    food.generate();      // Regénère la nourriture
    isRunning = true;     // Relance le jeu
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}


