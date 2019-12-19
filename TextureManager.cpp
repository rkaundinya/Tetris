#include "./TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filepath)
{
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( filepath );

    if (loadedSurface == NULL)
    {
        printf ("Unable to load image %s! SDL_image Error: %s\n", filepath, 
            IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Game::renderer, loadedSurface );

        if (newTexture == NULL)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", 
                filepath, SDL_GetError() );
        }

        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

/* bool TextureManager::CopyLoadedTexture(const char* filepath, SDL_Texture* &texture)
{
    // Loading success flag
    bool success = true;

    // Load PNG Texture
    texture = LoadTexture( filepath );
    if (texture == NULL)
    {
        printf("Failed to load texture image!");
        success = false;
    }

    return success;
} */