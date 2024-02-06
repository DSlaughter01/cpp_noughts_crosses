#include "Game.hpp"

const char* BoardVariables::playerTurn;
const char* BoardVariables::gameBoard[3][3];

Game::Game() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
    }

    isOver = false;
    isRunning = true;
    playerTurn = X;
    takenSquares = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j] = EMPTY;
        }
    }
}

// Starts off the GUI top display text
void Game::InitGUI(GUI &gui) {
    gui.ChangeText(playerTurn);
}

// Handle the user clicking on the screen
void Game::HandleClick(GUI &gui) {

    // Get the position of the mouse
    int x, y;
    SDL_GetMouseState( &x, &y );

    // If the click is on the board
    if (x > SIDE_GAP && x < SIDE_GAP + BOARD_DIM && y > TOP_GAP && y < WIN_HEIGHT - BOTTOM_GAP) {

        // Get which square the mouse has clicked on
        x = (x - SIDE_GAP) / SQUARE_DIM;
        y = (y - TOP_GAP) / SQUARE_DIM;

        // If the square is empty, assign to the player and change the player
        if (gameBoard[x][y] == EMPTY) {
            gameBoard[x][y] = playerTurn;
            takenSquares++;
            
            // Switch player
            if (playerTurn == X)
                playerTurn = O;
            else
                playerTurn = X;

            // Reflect changes in GUI
            gui.UpdateGraphicalArray();
            gui.ChangeText(playerTurn);

            // Check if this results in Game Over, and display end message if so
            const char* res = CheckGameOver();
            if (strcmp(res, EMPTY) != 0) {
                isOver = true;
                gui.CreateEndMessage(res);
            }
        }
    }
}

void Game::GameLoop(GUI &gui, SDL_Event event) {

    while (isRunning) {

        // Test for game quit and click in a square
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                Game::HandleClick(gui);
            }
        }

        if (isOver == false)
            gui.RenderScreen();
        else
            gui.RenderEndMessage();
    }
}

const char* Game::CheckGameOver() {

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((gameBoard[i][0] == gameBoard[i][1]) && (gameBoard[i][1] == gameBoard[i][2]) && strcmp(gameBoard[i][0], EMPTY) != 0) 
            return gameBoard[i][0];
        
        else if ((gameBoard[0][i] == gameBoard[1][i]) && (gameBoard[1][i] == gameBoard[2][i]) && strcmp(gameBoard[0][i], EMPTY) != 0) 
            return gameBoard[0][i];
    }

    // Check diagonals
    if ((gameBoard[0][0] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[2][2]) && strcmp(gameBoard[0][0], EMPTY) != 0) 
        return gameBoard[0][0];
    else if ((gameBoard[0][2] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[2][0]) && strcmp(gameBoard[0][2], EMPTY) != 0) 
        return gameBoard[0][2];
    
    // If no winner and board full, draw
    if (takenSquares == 9)
        return DRAW;
    
    else 
        return EMPTY;
}

void Game::Close(GUI &gui) {
    gui.Close();
    SDL_Quit();
}