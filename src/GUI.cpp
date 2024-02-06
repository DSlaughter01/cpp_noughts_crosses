#include "GUI.hpp"

SDL_Window* GUI::window = nullptr;
SDL_Renderer* GUI::renderer = nullptr;

// Initialise static colours
const SDL_Color GUI::whiteRender = {230, 230, 230};
const SDL_Color GUI::blackRender = {10, 10, 10};

GUI::GUI() {

    // Create window and renderer
    window = SDL_CreateWindow("Noughts and Crosses", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            WIN_WIDTH, 
                            WIN_HEIGHT, 
                            0);
    if (!window)
        std::cerr << "Window Error: " << SDL_GetError() << std::endl;
                     
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        std::cerr << "Renderer Error: " << SDL_GetError() << std::endl;

    // Initialise font library
    if (TTF_Init() == -1)
        std::cerr << "TTF Error: " << SDL_GetError() << std::endl;

    textTexture = nullptr;

    // Choose a font
    GAME_FONT = TTF_OpenFont("src/Roboto-Regular.ttf", 32); 
    if (GAME_FONT == nullptr)
        std::cout << "Game font not initialised" << std::endl;
}

void GUI::RenderBoard() {

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

    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 0);
}

void GUI::UpdateGraphicalArray() {

    // Render noughts and crosses
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            // Set x and y coordinates
            int x = SIDE_GAP + (i * SQUARE_DIM);
            int y = TOP_GAP + (j * SQUARE_DIM);

            // Create surfaces for each square
            SDL_Surface* squareSurface = TTF_RenderText_Solid(GAME_FONT, gameBoard[i][j], whiteRender);
            if (!squareSurface)
                std::cerr << "Square surface not created: " << SDL_GetError() << std::endl;

            // Create texture
            boardTextures[i][j] = SDL_CreateTextureFromSurface(renderer, squareSurface);
            if (!boardTextures[i][j])
                std::cerr << "Board texture not created: " << SDL_GetError() << std::endl;

            // Free surface
            SDL_FreeSurface(squareSurface);
            squareSurface = nullptr;

            // Destination rectangle height and width for the text
            boardRect[i][j].w = SQUARE_DIM - 4;
            boardRect[i][j].h = SQUARE_DIM - 4;

            // Centre the text based on its size
            boardRect[i][j].x = x + 2;
            boardRect[i][j].y = y + 2;
        }
    }
}

// The gameState is the player or game over
void GUI::ChangeText(const char* gameState) {

    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    };

    // Choose text to display
    if (strcmp(gameState, "X") == 0)
        currText = "Player X's turn";
    else if (strcmp(gameState, "O") == 0)
        currText = "Player O's turn";

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

    // Destination rectangle height and width for the text
    destRectText.w = BOARD_DIM;
    destRectText.h = SIDE_GAP;

    // Centre the text based on its size
    destRectText.x = (WIN_WIDTH - destRectText.w) / 2;
    destRectText.y = (SIDE_GAP + destRectText.h) / 2;
}

void GUI::CreateEndMessage(const char* res) {

    // Decide which text to put in
    if (strcmp(res, X) == 0)
        currText = "Player X wins!";
    else if (strcmp(res, O) == 0)
        currText = "Player O wins!";
    else
        currText = "It's a draw!";

    // Create a surface and texture
    textSurface = TTF_RenderText_Solid(GAME_FONT, currText, whiteRender);
    if (!textSurface)
        std::cout << "Surface not created: " << SDL_GetError() << std::endl;
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
        std::cerr << "Texture not created: " << SDL_GetError() << std::endl;
    
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;

    // Placement on the screen
    destRectText.w = BOARD_DIM;
    destRectText.h = SIDE_GAP;
    destRectText.x = (WIN_WIDTH - destRectText.w) / 2;
    destRectText.y = (WIN_HEIGHT - destRectText.h) / 2;
}

void GUI::RenderScreen() {

    SDL_RenderClear(renderer);
    RenderBoard();
    SDL_RenderCopy(renderer, textTexture, NULL, &destRectText);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            SDL_RenderCopy(renderer, boardTextures[i][j], NULL, &boardRect[i][j]);
        }
    }
    SDL_RenderPresent(renderer);
}

void GUI::RenderEndMessage() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textTexture, NULL, &destRectText);
    SDL_RenderPresent(renderer);
}

void GUI::Close() {

    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++) {
            SDL_DestroyTexture(boardTextures[i][j]);
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
}