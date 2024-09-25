#include "AI.hpp"

void AI::SetAIPlayer(char player) {
    AIPlayer = player;
}


char AI::GetAIPlayer(char player) {
    return AIPlayer;
}


std::vector<AI::Coordinate> AI::ReturnPossibleMoves(Board &board) {

    std::vector<AI::Coordinate> possibleMoves{};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (board.b[i][j] == EMPTY) {

                AI::Coordinate newCoord;
                newCoord.x = i;
                newCoord.y = j;
                possibleMoves.emplace_back(newCoord);
            }
        }
    }

    return possibleMoves;
}

BoardVariables::Board AI::MakeMove(Board board, Coordinate move, char currPlayer) {

    Board newBoard = board;
    newBoard.b[move.x][move.y] = currPlayer;

    return newBoard;
}


BoardVariables::Board AI::MakeOptimalMove(Board &board, char currPlayer) {

    Coordinate move = Minimax(board, currPlayer);

    if (move.x != NO_COORD.x && move.y != NO_COORD.y)
        board.b[move.x][move.y] = currPlayer;

    return board;
}


int AI::AssignGameScore(Board board) {

    int takenSquares = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (board.b[i][j] != EMPTY) {
                takenSquares++;
            }
        }
    }

    char winner = EMPTY; 
  
    // Check rows and columns
    for (int i = 0; i < 3; i++) {

        if ((board.b[i][0] == board.b[i][1]) && (board.b[i][1] == board.b[i][2]) && board.b[i][0] != EMPTY) {
            winner = board.b[i][0];
            break;
        }
        else if ((board.b[0][i] == board.b[1][i]) && (board.b[1][i] == board.b[2][i]) && board.b[0][i] != EMPTY) {
            winner = board.b[0][i];
            break;
        }
    }

    if (winner == X)
        return X_WIN;
    if (winner == O)
        return O_WIN;

    // Check diagonals
    if ((board.b[0][0] == board.b[1][1]) && (board.b[1][1] == board.b[2][2]) && board.b[0][0] != EMPTY) 
        winner = board.b[0][0];

    else if ((board.b[0][2] == board.b[1][1]) && (board.b[1][1] == board.b[2][0]) && board.b[0][2] != EMPTY) 
        winner = board.b[0][2];
    
    if (winner == X)
        return X_WIN;
    if (winner == O)
        return O_WIN;

    // If no winner and board full, draw
    if (takenSquares == 9)
        return DRAW_SCORE;
    else 
        return NO_SCORE;
}


BoardVariables::Coordinate AI::Minimax(BoardVariables::Board board, char currPlayer) {

    Coordinate bestAction = NO_COORD;

    // Find the best action: X maximises, O minimises
    if (currPlayer == X)
        bestAction = MaxValue(board, INT_MIN, INT_MAX).coord;
    else if (currPlayer == O) 
        bestAction = MinValue(board, INT_MIN, INT_MAX).coord;

    std::cout << "Move made." << std::endl;
    return bestAction;
}


AI::CoordValuePair AI::MaxValue(BoardVariables::Board board, int alpha, int beta) {

    CoordValuePair result {};

    // Check if the board is terminal.
    Coordinate bestAction = NO_COORD;
    int bestScore = AssignGameScore(board);

    // If it is terminal, return a default, and board score
    if (bestScore != NO_SCORE) {
        result = {bestAction, bestScore};
        return result;
    }

    // If not, set a score to maximise, lower than any possible score
    bestScore = INT_MIN;

    // Get possible actions
    std::vector<Coordinate> possibleActions = ReturnPossibleMoves(board);

    for (auto & action : possibleActions) {

        // Apply the action, and get a new board
        Board newBoard = MakeMove(board, action, X);

        // Get the new score by applying the min function
        CoordValuePair newPair = MinValue(newBoard, alpha, beta);
        int newScore = newPair.value;

        // If the new score is better than the current score
        if (newScore >= bestScore) {

            // Change the best score
            bestScore = newScore;

            // Set the best action to the most recent action
            bestAction = action;
        }

        // Check if the value is better than beta
        if (newScore >= beta) {
            break;
        }

        // Update alpha
        alpha = std::max(alpha, newScore);
    }

    // Return the best action, and the best score
    result = {bestAction, bestScore};
    std::cout << "Alpha in max: " << alpha << std::endl;

    return result;
}


AI::CoordValuePair AI::MinValue(BoardVariables::Board board, int alpha, int beta) {

    CoordValuePair result {};

    // Check if the board is terminal.
    Coordinate bestAction = NO_COORD;
    int bestScore = AssignGameScore(board);

    // If it is terminal, return a default, and board score
    if (bestScore != NO_SCORE) {
        result = {bestAction, bestScore};
        return result;
    }

    // If not, set a score to minimise, higher than any possible score
    bestScore = INT_MAX;

    // Get possible actions
    std::vector<Coordinate> possibleActions = ReturnPossibleMoves(board);

    for (auto & action : possibleActions) {

        // Apply the action, and get a new board
        Board newBoard = MakeMove(board, action, O);

        // Get the new score by applying the max function
        CoordValuePair newPair = MaxValue(newBoard, alpha, beta);
        int newScore = newPair.value;

        // If the new score is better than the current score,
        if (newScore <= bestScore) {

            // Change the best score
            bestScore = newScore;

            // Set the best action to the most recent actions
            bestAction = action;
        }

        // Check if the value is better than beta
        if (newScore <= alpha) {
            break;
        }

        // Update beta
        beta = std::min(beta, newScore);
    }

    // Return the best action, and the best score
    result = {bestAction, bestScore};

    std::cout << "Beta in min: " << beta << std::endl;

    return result;
}


