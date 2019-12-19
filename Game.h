#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "./AssetManager.h"

class AssetManager;

class Game
{
    public: 
        const static int SCREEN_WIDTH = 800;
        const static int SCREEN_HEIGHT = 800;
        static SDL_Renderer* renderer;
        static AssetManager* assetManager;

    private: 
        SDL_Window* _window;
    
    public: 
        Game();
        bool Initialize();
        // void Update();
        bool ProcessEvents();
        void Close();


};

#endif