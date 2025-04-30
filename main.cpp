#include "menu.h"
#include "game.h"
#include <iostream>

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake Game");

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Lusitana-Regular.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return 1;
    }

    while (window.isOpen()) {
        // MENU
        Menu menu(windowWidth, windowHeight, font);
        bool startGame = false;

        while (window.isOpen() && !startGame) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (menu.handleEvent(event, window)) {
                    startGame = true;
                }
            }

            window.clear(sf::Color::Black);
            menu.draw(window);
            window.display();
        }

        // GAME
        int gridSize = 25;
        sf::Vector2u windowSize = window.getSize();  // Récupère taille de la fenêtre
        Game game(windowSize.x, windowSize.y, gridSize);  // ✅ Appel correct avec 3 entiers
        game.run();  // À la fin du jeu, on revient au menu
    }

    return 0;
}

