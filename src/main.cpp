#include <iostream>
#include "GUI.hpp"
#include "Game.hpp"

int main(int argv, char** args) {

    GUI gui;
    Game game;
    SDL_Event event;

    game.InitGUI(gui);
    game.GameLoop(gui, event);

    return 0;
}