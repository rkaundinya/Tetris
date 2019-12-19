#include "./Game.h"

AssetManager* Game::assetManager = new AssetManager();
SDL_Renderer* Game::renderer;

Game::Game() : _window(NULL) {}

bool Game::Initialize()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }   
    else
    {
        if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Create window
        _window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
        if (_window == NULL)
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            // Create renderer for the window
            renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return success;
}

bool Game::ProcessEvents()
{
    SDL_Event event;
        
    switch (event.type)
    {
        case SDL_QUIT:
        {
            return false;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return false;
        }
        default:
        {
            break;
        }
    }

    return true;
}

void Game::Close()
{
    
}