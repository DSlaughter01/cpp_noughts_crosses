#pragma once
#include "SDL2/SDL.h"
#include "BoardVariables.hpp"
#include "GUI.hpp"
#include "AI.hpp"

class Game : public BoardVariables {

    public:
        Game();
        ~Game();

        void HandleClick();
        void GameLoop();
        char FindWinner();
        void ChooseAISettings();
        void ReactToMove();
        
    public:

        Board board;

    private:

        AI ai;
        GUI gui;

        int gameState;
        bool isRunning;
        int takenSquares;  
        bool isOver;
        char playerTurn;
        char AIPlayer;
        bool isUsingAI;
};