#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(int windowWidth, int windowHeight, sf::Font& font);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    bool handleEvent(const sf::Event& event, sf::RenderWindow& window);


private:
    int selectedIndex;
    sf::Text title;
    sf::Text options[2];
};
