#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include "SDL2/SDL.h"
#include "./TextureManager.h"

class AssetManager
{
    private: 
        std::map<std::string, SDL_Texture*> _textures;
        bool _successfullyLoadedAssets;

    public: 
        AssetManager();
        ~AssetManager();
        void ClearData();

        void AddTexture(std::string textureID, const char* filepath);

        SDL_Texture* GetTexture(std::string textureID);

        bool CheckIfAllAssetsLoaded();
};

#endif