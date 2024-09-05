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

    // Reflect changes in GUI
    gui.UpdateGraphicalArray(board.b);
    char result = FindWinner();

    gui.SetText(result, playerTurn, AIPlayer);

    // Check if this results in Game Over, and display end message if so
    bool isTerminal = (result == EMPTY ? false : true);

    if (isTerminal) {
        gameState = s_END;
    }

    // Render the screen when it changes
    gui.RenderScreen();
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

void Game::ChooseAISettings() {

    // Choose whether to use AI, and if so, for which player
    char usingAI = EMPTY;

    while (usingAI != 'y' && usingAI != 'n') {
        std::cout << "Using AI? (y/n)" << std::endl;
        std::cin >> usingAI;
    }

    if (usingAI == 'y') {

        isUsingAI = true;

        while (AIPlayer != X && AIPlayer != O) {
            std::cout << "Please select AI side (X/O)" << std::endl;
            std::cin >> AIPlayer;
        }

        ai.SetAIPlayer(AIPlayer);
    }
}

void Game::GameLoop() {

    ChooseAISettings();

    // Only render the screen when the screen changes. This line brings up the empty board
    gui.SetText(EMPTY, playerTurn, AIPlayer);
    gui.RenderScreen();

    SDL_Event event;

    gameState = s_IN_PLAY;
    isRunning = true;

    while (isRunning) {
 
        if (isUsingAI && playerTurn == AIPlayer && gameState == s_IN_PLAY) {

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