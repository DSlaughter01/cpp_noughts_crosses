#pragma once
#include "SDL2/SDL.h"
#include "BoardVariables.hpp"
#include "GUI.hpp"

class Game : public BoardVariables {

    public:
        Game();
        void InitGUI(GUI &gui);
        void HandleClick(GUI &gui);
        void GameLoop(GUI &gui, SDL_Event event);
        const char* CheckGameOver();
        void Close(GUI &gui);
        
    private:
        bool isRunning {};
        int takenSquares {};     
};