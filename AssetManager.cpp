#include "./AssetManager.h"

AssetManager::AssetManager() : _successfullyLoadedAssets(true) {}

void AssetManager::ClearData()
{
    _textures.clear();
}

void AssetManager::AddTexture(std::string textureID, const char* filepath)
{
    SDL_Texture* newTexture = TextureManager::LoadTexture( filepath );

    if ( newTexture == NULL)
    {
        printf( "Failed to load file %s\n", filepath );
        _successfullyLoadedAssets = true;
    }

    _textures.emplace( textureID, TextureManager::LoadTexture( filepath ) );
}

SDL_Texture* AssetManager::GetTexture(std::string textureID)
{
    return _textures[textureID];
}

bool AssetManager::CheckIfAllAssetsLoaded()
{
    return _successfullyLoadedAssets;
}