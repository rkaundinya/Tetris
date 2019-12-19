#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "./Game.h"

class TextureManager
{
    public: 
        static SDL_Texture* LoadTexture(const char* filepath);
};

#endif