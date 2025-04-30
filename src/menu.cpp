#include "menu.h"

Menu::Menu(int windowWidth, int windowHeight, sf::Font& font) {
    selectedIndex = 0;

    title.setFont(font);
    title.setString("Snake Game");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Green);
    title.setPosition(windowWidth / 2.f - 140, 100);

    options[0].setFont(font);
    options[0].setString("Jouer");
    options[0].setCharacterSize(36);
    options[0].setFillColor(sf::Color::Yellow);
    options[0].setPosition(windowWidth / 2.f - 60, 200);

    options[1].setFont(font);
    options[1].setString("Quitter");
    options[1].setCharacterSize(36);
    options[1].setFillColor(sf::Color::White);
    options[1].setPosition(windowWidth / 2.f - 60, 260);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    for (int i = 0; i < 2; ++i)
        window.draw(options[i]);
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        options[selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (selectedIndex < 1) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        options[selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}

bool Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            moveUp();
        } else if (event.key.code == sf::Keyboard::Down) {
            moveDown();
        } else if (event.key.code == sf::Keyboard::Enter) {
            return true;  // valide le choix
        }
    }
    return false;
}
