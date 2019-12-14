#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Screen
{
    public: 
        const static int SCREEN_WIDTH = 800;
        const static int SCREEN_HEIGHT = 800;

    private: 
        SDL_Window* m_window;
        SDL_Renderer* m_renderer = NULL;
        SDL_Texture* m_texture = NULL;
    
    public: 
        Screen();
        bool Initialize();
        // void Update();
        bool ProcessEvents();
        void Close();


};

#endif