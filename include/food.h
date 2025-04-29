#pragma once

#include "point.h"
#include <SFML/Graphics.hpp>

class Food {
    public:
        Food(int gridSize, int windowWidth, int windowHeight); // Constructeur avec les dimensions de la fenêtre
        void generate();           // Générer une nouvelle position pour la nourriture
        void draw(sf::RenderWindow& window); // Dessiner la pomme
        const Point& getPosition() const;
    
    private:
        int gridSize;
        int windowWidth;  // Ajout de windowWidth
        int windowHeight; // Ajout de windowHeight
        Point position;
        
        sf::Texture texture;
        sf::Sprite sprite;
    };