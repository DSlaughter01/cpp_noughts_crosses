#pragma once
#include <iostream>
#include <cstring>
#include "BoardVariables.hpp"
#include <vector>

class AI : public BoardVariables {

    private:
        char AIPlayer;

        // Scores associated with the winners of various boards
        int O_WIN = -1;
        int DRAW_SCORE = 0;
        int X_WIN = 1;
        int NO_SCORE = 2; 

        struct CoordValuePair {
            BoardVariables::Coordinate coord {};
            int value {};
        };

    public:

        // Getter and setter for AI playerr selection
        char GetAIPlayer(char player);
        void SetAIPlayer(char player);

        // Returns the amended board with the best possible move for the current player
        Board MakeOptimalMove(Board &board, char currPlayer);
        
    private:

        // Assigns a score to the end result of a game. Only called when the game is over
        int AssignGameScore(Board board);

        // Returns a vector of all empty squares
        std::vector<Coordinate> ReturnPossibleMoves(Board &board);

        // Makes the move passed to it, and returns the resulting board. 
        // The board is copied (not referenced) in order to use in minimax without changing the original.
        Board MakeMove(Board board, Coordinate move, char currPlayer);

        // Implements the minimax algorithm to find the optimal move for the current player
        Coordinate Minimax(Board board, char currPlayer);

        // Finds the move that maximises the score of the current board
        CoordValuePair MaxValue(Board board);

        // Finds the move that minimises the score of the current board
        CoordValuePair MinValue(Board board);  
};
