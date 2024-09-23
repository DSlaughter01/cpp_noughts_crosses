#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "BoardVariables.hpp"

class GUI : public BoardVariables {

    public:
        GUI();
        ~GUI();

        // Sets the initial screen for choosing AI settings
        void ChooseAISettings(int stage);

        // Calls all 4 of the private functions below to update the GUI
        void Update(Board &board, char result, char playerTurn, char AIPlayer);

    private:
        // Updates Xs and Os in the board array for display
        void UpdateGraphicalArray(Board &board);

        // Chooses the text to display at the top of the screen depending on current game details
        void SetText(char result, char playerTurn, char AIPlayer);

        // Creates the texture for the relevant text to be displayed
        void CreateTextTexture();

        // Renders all information to the screen
        void RenderScreen();

    private:
        TTF_Font* GAME_FONT = nullptr;

        SDL_Texture* boardTextures[3][3];
        SDL_Rect boardRect[3][3];

        // Colours
        const SDL_Color whiteRender = {230, 230, 230};
        
        // Window and renderer
        SDL_Window* window;
        SDL_Renderer* renderer;

        // Destination rectangle for text
        SDL_Rect destRectText;
        SDL_Texture* textTexture;
        SDL_Surface* textSurface;
};