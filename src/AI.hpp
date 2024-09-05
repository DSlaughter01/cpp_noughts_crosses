#pragma once
#include <iostream>
#include <cstring>
#include "BoardVariables.hpp"
#include <vector>

class AI : public BoardVariables {

    public: 

        struct CoordValuePair {
            BoardVariables::Coordinate coord {};
            int value {};
        };

    private:
        char AIPlayer;
        int X_WIN = 1;
        int O_WIN = -1;
        int DRAW_SCORE = 0;
        int NO_SCORE = 2; 

    public:

        char GetAIPlayer(char player);
        void SetAIPlayer(char player);

        // Assigns a score to the end result of a game. Only called when the game is over
        int AssignGameScore(Board board);

        std::vector<Coordinate> ReturnPossibleMoves(Board &board);
        Board MakeOptimalMove(Board &board, char currPlayer);
        Board MakeMove(Board board, Coordinate move, char currPlayer);

        Coordinate Minimax(Board board, char currPlayer);
        CoordValuePair MaxValue(Board board);
        CoordValuePair MinValue(Board board);
        
};
