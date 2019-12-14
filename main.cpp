#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <time.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Starts SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Loads image as texture
SDL_Texture* loadTexture(std::string filePath);

SDL_Window *window = NULL;
SDL_Renderer* renderer = NULL;
// Current displayed texture
SDL_Texture* texture = NULL;
SDL_Rect sourceRect = { 0, 0, 18, 18 };
SDL_Rect destRect = { 0, 0, 18, 18 };

// Size of tetris board
const int boardX = 10;
const int boardY = 20;

// Create board and initialize all to 0
int board[boardX][boardY] = {0};

// Create a struct of x and y points
// and creates two objects a and b of type Point
// a - stores x,y coord of each box in tetris shape
// 
struct Point
{int x,y;} a[4], b[4]; 

// Create the grid size and shapes for each tile
int figures[7][4] = 
{
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

// Store ticks since last frame
int ticksLastFrame = 0;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
        if (window == NULL)
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            // Create renderer for the window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load PNG Texture
    texture = loadTexture( "./images/tiles.png");
    if (texture == NULL)
    {
        std::cout << "Failed to load texture image!" << std::endl;
        success = false;
    }

    return success;
}

SDL_Texture* loadTexture(std::string path)
{
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if (loadedSurface == NULL)
    {
        printf ("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), 
            IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if (newTexture == NULL)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", 
                path.c_str(), SDL_GetError() );
        }

        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void close()
{
    SDL_DestroyTexture(texture);
    texture = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main()
{    
    // Start SDL and create window
    if (init() == false)
    {
        std::cout << "Failed to initialize!\n";
    }
    else
    {
        // Load media
        if ( !loadMedia() )
        {
            std::cout << "Failed to load media!\n";
        }
        else
        {
            bool quit = false;

            SDL_Event event;

            int dx = 0;
            bool rotate = 0;
            bool rotateCalledOnce = false;
            int colorNum = 1;
            float timer = 0;
            float delay = 0.3f;

            while (!quit)
            {
                float time = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
                ticksLastFrame = SDL_GetTicks();
                timer += time;

                SDL_PollEvent(&event);
                
                switch (event.type)
                {
                    case SDL_QUIT:
                    {
                        quit = true;
                        break;
                    }
                    case SDL_KEYDOWN:
                    {
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                            quit = true;
                        else if (event.key.keysym.sym == SDLK_UP)
                        {
                            if (!rotateCalledOnce)
                            {
                                rotate = true;
                                rotateCalledOnce = true;
                            }
                            std::cout << "Called rotate" << std::endl;
                        }
                        else if (event.key.keysym.sym == SDLK_LEFT)
                            dx = -1;
                        else if (event.key.keysym.sym == SDLK_RIGHT)
                            dx = 1;
                    }
                    case SDL_KEYUP:
                    {
                        rotateCalledOnce = false;
                    }
                    default:
                    {
                        break;
                    }
                }

                // Move Tiles
                for (int i = 0; i < 4; ++i)
                {
                    a[i].x += dx;
                }

                // Rotate Tiles
                if (rotate)
                {
                    Point centerOfRotation = a[1]; 
                    for (int i = 0; i < 4; ++i)
                    {
                        int x = a[i].y - centerOfRotation.y;
                        int y = a[i].x - centerOfRotation.x;
                        a[i].x = centerOfRotation.x - x;
                        a[i].y = centerOfRotation.y + y;
                    }
                }

                // Tick
                if (timer > delay)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        a[i].y += 1;
                    }
                    timer = 0;
                }

                int n = 3;
                if (a[0].x == 0)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        a[i].x = figures[n][i] % 2;
                        a[i].y = figures[n][i] / 2;
                    }
                }

                dx = 0;
                rotate = 0;


                // Clear screen
                SDL_RenderClear( renderer );

                for (int i = 0; i < 4; ++i)
                {
                    destRect.x = a[i].x * 18;
                    destRect.y = a[i].y * 18;
                    SDL_RenderCopyEx( renderer, texture, &sourceRect, &destRect, 
                        0, NULL, SDL_FLIP_NONE);
                }
                
                // Render texture to screen
                // SDL_RenderCopyEx( renderer, texture, &sourceRect, &destRect, 0, NULL, SDL_FLIP_NONE);

                // Update screen
                SDL_RenderPresent( renderer );
            }
        }
    }

    close();

    return 0;
}