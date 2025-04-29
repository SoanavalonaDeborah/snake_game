#include "game.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int gridSize = 20;

    Game game(windowWidth, windowHeight, gridSize);
    game.run();

    return 0;
}
