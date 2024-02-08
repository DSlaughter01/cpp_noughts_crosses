#include <iostream>
#include "GUI.hpp"
#include "Game.hpp"

int main(int argv, char** args) {

    // Create objects from classes, all sharing base structure BoardVariables
    GUI gui;
    Game game;
    SDL_Event event;

    // Run the game loop
    game.GameLoop(gui, event);

    // Destructors take care of clearup

    return 0;
}