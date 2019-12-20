#include "./Game.h"
#include "./Constants.h"

AssetManager* Game::assetManager = new AssetManager();
SDL_Renderer* Game::renderer;
SDL_Event Game::event;

Game::Game() : _window(NULL), isRunning(false) {}

bool Game::IsRunning() const
{
    return this->isRunning;
}

void Game::Initialize(int windowWidth, int windowHeight)
{
    // Initialization flag
    isRunning = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        isRunning = false;
    }   
    else
    {
        if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Create window
        _window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    
        if (_window == NULL)
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            isRunning = false;
        }
        else
        {
            // Create renderer for the window
            renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                isRunning = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
}

void Game::ProcessEvents()
{
    SDL_PollEvent( &event );
    switch (event.type)
    {
        case SDL_QUIT:
        {
            isRunning = false;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
        }
        default:
        {
            break;
        }
    }
}

void Game::Render()
{
    SDL_RenderClear( renderer );
    SDL_RenderPresent( renderer );
}

void Game::Close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}