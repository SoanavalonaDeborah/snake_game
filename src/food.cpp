#include "food.h"
#include <cstdlib>
#include <iostream>

Food::Food(int gridSize, int windowWidth, int windowHeight)
    : gridSize(gridSize), windowWidth(windowWidth), windowHeight(windowHeight)
{
    if (!texture.loadFromFile("assets/images/apple.png")) {  // Charger l'image de la pomme
        std::cerr << "Erreur lors du chargement de la texture de la pomme." << std::endl;
        exit(1);
    }

    // Créer le sprite pour la pomme
    sprite.setTexture(texture);
    sprite.setScale(static_cast<float>(gridSize) / texture.getSize().x,
                    static_cast<float>(gridSize) / texture.getSize().y); // Adapter la taille du sprite
}

void Food::generate() {
    position.x = rand() % (windowWidth / gridSize);
    position.y = rand() % (windowHeight / gridSize);
}


void Food::draw(sf::RenderWindow& window) {
    sprite.setPosition(position.x * gridSize, position.y * gridSize);
    window.draw(sprite);  // Dessiner la pomme
}

const Point& Food::getPosition() const {
    return position;  // Retourner une référence constante à la position
}
