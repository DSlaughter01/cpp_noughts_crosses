#include "GUI.hpp"

// Constructor
GUI::GUI() 
    : textSurface(nullptr), textTexture(nullptr) {

    // Initialise font library
    if (TTF_Init() == -1) {
        std::cerr << "TTF Initialisation Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        return;
    }

    // Choose a font
    GAME_FONT = TTF_OpenFont("src/Roboto-Regular.ttf", 32); 
    if (!GAME_FONT)
        std::cerr << "Game font could not be opened" << TTF_GetError() << std::endl;

    // Create window and renderer
    window = SDL_CreateWindow("Noughts and Crosses", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            WIN_WIDTH, 
                            WIN_HEIGHT, 
                            0);

    if (!window) {
        std::cerr << "Window Initialisation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
                     
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Renderer Initialisation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Background colour dark grey
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

    // Initialise boardTextures and boardRect
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            boardTextures[i][j] = nullptr;
            boardRect[i][j] = {};
        }
    }
}

// Destructor
GUI::~GUI() {
    
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++) {
            if (boardTextures[i][j])
                SDL_DestroyTexture(boardTextures[i][j]);
                boardTextures[i][j] = nullptr;
        }
    }

    SDL_DestroyTexture(textTexture);
    textTexture = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_CloseFont(GAME_FONT);
    GAME_FONT = nullptr;

    TTF_Quit();
    SDL_Quit();
}


// Update boardTextures based on what is in gameBoard
void GUI::UpdateGraphicalArray(Board board) {

    // Render noughts and crosses
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            const char gBSquare = board.b[i][j];
            char text[2] = {gBSquare, '\0'};

            // Set x and y coordinates
            int x = SIDE_PADDING + (i * SQUARE_DIM);
            int y = TOP_PADDING + (j * SQUARE_DIM);

            // Create surfaces for each square
            SDL_Surface* squareSurface = TTF_RenderText_Solid(GAME_FONT, text, whiteRender);
            if (!squareSurface)
                std::cerr << "Square surface not created: " << SDL_GetError() << std::endl;

            // Create texture
            boardTextures[i][j] = SDL_CreateTextureFromSurface(renderer, squareSurface);
            if (!boardTextures[i][j])
                std::cerr << "Board texture not created: " << SDL_GetError() << std::endl;

            // Free surface
            SDL_FreeSurface(squareSurface);
            squareSurface = nullptr;

            // Destination rectangle
            boardRect[i][j].w = SQUARE_DIM - 4;
            boardRect[i][j].h = SQUARE_DIM - 4;
            boardRect[i][j].x = x + 2;
            boardRect[i][j].y = y + 2;
        }
    }
}


void GUI::CreateTextTexture() {

    // Destroy any preexisting textTexture to replace it later on
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    };

    // To create a text: first create a surface
    textSurface = TTF_RenderText_Solid(GAME_FONT, currText, whiteRender);
    if (!textSurface)
        std::cout << "Surface not created: " << SDL_GetError() << std::endl;

    // Then create a texture from the surface
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
        std::cerr << "Texture not created: " << SDL_GetError() << std::endl;

    // No longer need the surface
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;

    // Destination rectangle
    destRectText.w = BOARD_DIM;
    destRectText.h = SIDE_PADDING;
    destRectText.x = (WIN_WIDTH - destRectText.w) / 2;
    destRectText.y = (SIDE_PADDING + destRectText.h) / 2;
}


void GUI::SetText(char result, char playerTurn, char AIPlayer) {

    // If the game is over
    if (result == X)
        currText = "Player X wins!";
    else if (result == O)
        currText = "Player O wins!";
    else if (result == DRAW)
        currText = "It's a draw!";

    // If the game is not over
    else if (result == EMPTY) {

        // Choose text to display based on player turn and AI
        if (playerTurn == AIPlayer)
            currText = "AI thinking";
        else if (playerTurn == X)
            currText = "Player X's turn";
        else if (playerTurn == O)
            currText = "Player O's turn";
    }

    CreateTextTexture();
}


void GUI::RenderScreen() {

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 0);

    // Vertical lines 
    SDL_RenderDrawLine(renderer, vertLineX1, horLineY1, vertLineX1, horLineY4);
    SDL_RenderDrawLine(renderer, vertLineX2, horLineY1, vertLineX2, horLineY4);
    SDL_RenderDrawLine(renderer, vertLineX3, horLineY1, vertLineX3, horLineY4);
    SDL_RenderDrawLine(renderer, vertLineX4, horLineY1, vertLineX4, horLineY4);

    // Horizontal lines
    SDL_RenderDrawLine(renderer, vertLineX1, horLineY1, vertLineX4, horLineY1);
    SDL_RenderDrawLine(renderer, vertLineX1, horLineY2, vertLineX4, horLineY2);
    SDL_RenderDrawLine(renderer, vertLineX1, horLineY3, vertLineX4, horLineY3);
    SDL_RenderDrawLine(renderer, vertLineX1, horLineY4, vertLineX4, horLineY4);

    // Render the contents of each square
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            SDL_RenderCopy(renderer, boardTextures[i][j], NULL, &boardRect[i][j]);
        }
    }

    // Render top text
    SDL_RenderCopy(renderer, textTexture, NULL, &destRectText);
    
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 0);
    
    SDL_RenderPresent(renderer);
}

void GUI::Update(Board board, char result, char playerTurn, char AIPlayer) {

    UpdateGraphicalArray(board);
    SetText(result, playerTurn, AIPlayer);
    CreateTextTexture();
    RenderScreen();
}