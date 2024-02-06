#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "BoardVariables.hpp"

class GUI : public BoardVariables {

    public:
        GUI();
        void ChangeText(const char* gameState);
        void CreateEndMessage(const char* res);
        void UpdateGraphicalArray();
        void RenderEndMessage();
        void RenderScreen();
        void RenderBoard();
        void Close();

    private:
        TTF_Font* GAME_FONT = nullptr;

        SDL_Texture* boardTextures[3][3] {};
        SDL_Rect boardRect[3][3] {};

        // Colours
        static const SDL_Color whiteRender;
        static const SDL_Color blackRender;
        
        // Window and renderer
        static SDL_Window* window;
        static SDL_Renderer* renderer;

        // Destination rectangle for text
        SDL_Rect destRectText;
        SDL_Texture* textTexture;
        SDL_Surface* textSurface;
};