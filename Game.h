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
        static SDL_Renderer* renderer;
        static AssetManager* assetManager;
        static SDL_Event event;

    private: 
        bool isRunning;
        SDL_Window* _window;
    
    public: 
        Game();
        bool IsRunning() const;
        void Initialize(int windowWidth, int windowHeight);
        void ProcessEvents();
        void Render();
        void Close();


};

#endif