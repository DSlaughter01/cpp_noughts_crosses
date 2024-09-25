#include "Game.hpp"

Game::Game() 
    : isOver(false), isRunning(false), playerTurn(X), takenSquares(0), AIPlayer(EMPTY), 
    isUsingAI(false), gameState(s_PRELIM) {

    // Initialise SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
    }

    // Initialise all of the gameBoard squares
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board.b[i][j] = EMPTY;
        }
    }
}

Game::~Game() {
    SDL_Quit();
}

// Handle the user clicking on the screen
void Game::HandleClick() {

    // Don't allow clicks if it is the AI's turn
    if (isUsingAI && playerTurn == AIPlayer) 
        return;

    // Get the position of the mouse
    int x, y;
    SDL_GetMouseState(&x, &y);

    // If the click is on the board
    if (x > SIDE_PADDING && x < SIDE_PADDING + BOARD_DIM && y > TOP_PADDING && y < WIN_HEIGHT - BOTTOM_PADDING) {

        // Get which square the mouse has clicked on
        x = (x - SIDE_PADDING) / SQUARE_DIM;
        y = (y - TOP_PADDING) / SQUARE_DIM;
        
        // If the square is empty, assign to the player and change the player
        if (board.b[x][y] == EMPTY) {

            board.b[x][y] = playerTurn;
            ReactToMove();
        }
    }
}


void Game::ReactToMove() { 

    takenSquares++;

    // Switch player
    playerTurn = (playerTurn == X) ? O : X;

    // See if there is a winner
    char result = FindWinner();

    // Check if this results in Game Over, and display end message if so
    bool isTerminal = (result == EMPTY ? false : true);

    // Change game state if the game is over
    if (isTerminal) 
        gameState = s_GAME_OVER;
    
    // Render the screen when it changes
    gui.Update(board, result, playerTurn, AIPlayer);
}


char Game::FindWinner() {

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board.b[i][0] == board.b[i][1]) && (board.b[i][1] == board.b[i][2]) && board.b[i][0] != EMPTY) 
            return board.b[i][0];
        
        else if ((board.b[0][i] == board.b[1][i]) && (board.b[1][i] == board.b[2][i]) && board.b[0][i] != EMPTY) 
            return board.b[0][i];
    }

    // Check diagonals
    if ((board.b[0][0] == board.b[1][1]) && (board.b[1][1] == board.b[2][2]) && board.b[0][0] != EMPTY) 
        return board.b[0][0];

    else if ((board.b[0][2] == board.b[1][1]) && (board.b[1][1] == board.b[2][0]) && board.b[0][2] != EMPTY) 
        return board.b[0][2];
    
    // If no winner and board full, draw
    if (takenSquares == 9)
        return DRAW;
    else 
        return EMPTY;
}

void Game::ChooseAISettings(SDL_Event &event) {

    // Choose whether to use AI, and if so, for which player
    char AIChoice = EMPTY;

    while (AIChoice == EMPTY && isRunning) {        
        
        gui.ChooseAISettings(1);
    
        while (SDL_WaitEvent(&event)) {

            if (event.type == SDL_QUIT) {
                isRunning = false;
                break;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                // Get the position of the mouse
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (x >= leftButtonRect.x && x <= leftButtonRect.x + leftButtonRect.w &&
                    y >= leftButtonRect.y && y <= leftButtonRect.y + leftButtonRect.h) {
                    
                    AIChoice = 'y';
                    break;
                }

                if (x >= rightButtonRect.x && x <= rightButtonRect.x + rightButtonRect.w &&
                    y >= rightButtonRect.y && y <= rightButtonRect.y + rightButtonRect.h) {
                    
                    AIChoice = 'n';
                    break;
                }
            }
        }

    }

    if (AIChoice == 'y') {

        gui.ChooseAISettings(2);

        isUsingAI= true;

        while (AIPlayer == EMPTY) {

            while (SDL_WaitEvent(&event)) {
               
                if (event.type == SDL_QUIT) {
                    isRunning = false;
                    break;
                }

                if (event.type == SDL_MOUSEBUTTONDOWN) {

                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    if (x >= leftButtonRect.x && x <= leftButtonRect.x + leftButtonRect.w &&
                        y >= leftButtonRect.y && y <= leftButtonRect.y + leftButtonRect.h) {
                        
                        AIPlayer = X;
                        break;
                    }

                    if (x >= rightButtonRect.x && x <= rightButtonRect.x + rightButtonRect.w &&
                        y >= rightButtonRect.y && y <= rightButtonRect.y + rightButtonRect.h) {
                        
                        AIPlayer = O;
                        break;
                    }
                }
            }
        }

        ai.SetAIPlayer(AIPlayer);
    }
}

void Game::GameLoop() {

    SDL_Event event;
    isRunning = true;

    ChooseAISettings(event);

    // Set up initial parameters for the game
    gameState = s_IN_PLAY;

    // Only render the screen when the screen changes
    gui.Update(board, EMPTY, playerTurn, AIPlayer);

    while (isRunning) {
        
        if (isUsingAI == true && playerTurn == AIPlayer && gameState == s_IN_PLAY) {

            board = ai.MakeOptimalMove(board, playerTurn);
            ReactToMove();
        }

        // Test for game quit and click in a square
        if (SDL_WaitEvent(&event)) {

            if (event.type == SDL_QUIT) {
                isRunning = false;
                break;
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN)
                Game::HandleClick();
        }
    }
}