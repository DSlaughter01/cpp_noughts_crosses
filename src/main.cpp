#include <iostream>
#include "GUI.hpp"
#include "Game.hpp"

int main(int argv, char** args) {

    // Create objects from classes, all sharing base structure BoardVariables
    Game game;

    // Run the game loop
    game.GameLoop();

    // Destructors take care of clearup

    return 0;
}