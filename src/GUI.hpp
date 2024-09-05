#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "BoardVariables.hpp"

class GUI : public BoardVariables {

    public:
        GUI();
        ~GUI();

        void Update(Board board, char result, char playerTurn, char AIPlayer);

    private:
        void UpdateGraphicalArray(Board board);

        void SetText(char result, char playerTurn, char AIPlayer);
        
        // Creates the texture for the relevant text to be displayed
        void CreateTextTexture();

        void RenderScreen();

    private:
        TTF_Font* GAME_FONT = nullptr;

        SDL_Texture* boardTextures[3][3];
        SDL_Rect boardRect[3][3];

        // Colours
        const SDL_Color whiteRender = {230, 230, 230};
        const SDL_Color blackRender = {10, 10, 10};
        
        // Window and renderer
        SDL_Window* window;
        SDL_Renderer* renderer;

        // Destination rectangle for text
        SDL_Rect destRectText;
        SDL_Texture* textTexture;
        SDL_Surface* textSurface;
};