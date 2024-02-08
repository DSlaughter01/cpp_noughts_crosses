#include "Game.hpp"

const char* BoardVariables::playerTurn;
const char* BoardVariables::gameBoard[3][3];

Game::Game() {

    // Initialise SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
    }

    // Initialise game variables
    isOver = false;
    isRunning = true;
    playerTurn = X;
    takenSquares = 0;

    // Initialise all of te gameBoard squares
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j] = EMPTY;
        }
    }
}

Game::~Game() {
    SDL_Quit();
}

// Starts off the GUI top display text
void Game::InitGUI(GUI &gui) {
    gui.ChangeText(playerTurn);
    gui.RenderScreen();
}

// Handle the user clicking on the screen
void Game::HandleClick(GUI &gui) {

    // Get the position of the mouse
    int x, y;
    SDL_GetMouseState( &x, &y );

    // If the click is on the board
    if (x > SIDE_PADDING && x < SIDE_PADDING + BOARD_DIM && y > TOP_PADDING && y < WIN_HEIGHT - BOTTOM_PADDING) {

        // Get which square the mouse has clicked on
        x = (x - SIDE_PADDING) / SQUARE_DIM;
        y = (y - TOP_PADDING) / SQUARE_DIM;

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
            const char* res = CheckGameOver(gameBoard);
            if (strcmp(res, EMPTY) != 0) {
                isOver = true;
                gui.CreateEndMessage(res);
            }

            // Render the screen when it changes
            if (isOver == false)
                gui.RenderScreen();
            else
                gui.RenderEndMessage();
        }
    }
}

void Game::GameLoop(GUI &gui, SDL_Event event) {

    // Only render the screen when the screen changes. This line brings up the empty board
    InitGUI(gui);

    while (isRunning) {

        // Test for game quit and click in a square
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                break;
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                Game::HandleClick(gui);
            }
        }
    }
}

const char* Game::CheckGameOver(const char* board[3][3]) {

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && strcmp(board[i][0], EMPTY) != 0) 
            return board[i][0];
        
        else if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && strcmp(board[0][i], EMPTY) != 0) 
            return board[0][i];
    }

    // Check diagonals
    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && strcmp(board[0][0], EMPTY) != 0) 
        return board[0][0];
    else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && strcmp(board[0][2], EMPTY) != 0) 
        return board[0][2];
    
    // If no winner and board full, draw
    if (takenSquares == 9)
        return DRAW;
    
    else 
        return EMPTY;
}