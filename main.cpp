#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include "Game.h"
#include "Audio.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 480;
const int offsetX = 28;
const int offsetY = 31;
const int numOfAudioClips = 7;

// Starts SDL and creates window
bool init();

// Loads media
bool loadMedia(std::string filepath, SDL_Texture* &texture);

// Frees media and shuts down SDL
void close();

// Loads image as texture
SDL_Texture* loadTexture(std::string filePath);

// Outputs audio filepath name according to number inputted
std::string musicFilepathUpdater(int trackNumber);

// Plays backgorund music with number indicated
void playBackgroundMusicNumber(int number);

SDL_Window *window = NULL;
SDL_Renderer* renderer = NULL;
// Current displayed texture
SDL_Texture* tiles = NULL;
SDL_Texture* background = NULL;
SDL_Texture* frame = NULL;
SDL_Rect sourceRect = { 0, 0, 18, 18 };
SDL_Rect destRect = { 0, 0, 18, 18 };

// Size of tetris board
const int boardY = 20;
const int boardX = 10;

// Create board and initialize all to 0
int board[boardY][boardX] = {0};

// Audio Files
Audio backgroundMusic, backgroundMusic2, backgroundMusic3, backgroundMusic4, 
    backgroundMusic5, backgroundMusic6, backgroundMusic7, rotateSFX;

// Num of Line Counter
int linesAchieved = 0;

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

// Check that tile is not on edge of board or touching another tile
// If either of those are true, then return false
bool check()
{
    for (int i = 0; i < 4; ++i)
    {
        if (a[i].x < 0 || a[i].x >= boardX || a[i].y >= boardY)
            return false;
        else if (board[a[i].y][a[i].x])
            return false;
    }
    
    return true;
};

// Store ticks since last frame
int ticksLastFrame = 0;

bool init()
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

bool loadMedia(std::string filepath, SDL_Texture* &texture)
{
    // Loading success flag
    bool success = true;

    // Load PNG Texture
    texture = loadTexture( filepath );
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
    SDL_DestroyTexture(tiles);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(frame);
    tiles = NULL;
    background = NULL;
    frame = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::string musicFilepathUpdater(int trackNumber)
{
    std::stringstream filepathStringStream;
    std::string filepathToOutput;

    filepathStringStream << "./Audio/Track";
    filepathStringStream << trackNumber;
    filepathStringStream << ".wav";

    filepathToOutput = filepathStringStream.str();

    return filepathToOutput;
}

void playBackgroundMusicNumber(int number)
{
    switch (number)
    {
        case 2:
            backgroundMusic.Stop();
            backgroundMusic2.Play();
            break;
        case 3:
            backgroundMusic2.Stop();
            backgroundMusic3.Play();
        case 4: 
            backgroundMusic3.Stop();
            backgroundMusic4.Play();
            break;
        case 5: 
            backgroundMusic4.Stop();
            backgroundMusic5.Play();
            break;
        case 6:
            backgroundMusic5.Stop();
            backgroundMusic6.Play();
            break;
        case 7:
            backgroundMusic6.Stop();
            backgroundMusic7.Play();
        default:
            break;
    }
}

int main()
{
    srand(time(0));

    Game* game = new Game;

    // Start SDL and create window
    if ( init() == false )
    {
        std::cout << "Failed to initialize!\n";
    }
    else
    {
        // Load media
        if ( !loadMedia( "./images/tiles.png", tiles ) || 
            !loadMedia( "./images/background.png", background ) || 
            !loadMedia( "./images/frame.png", frame ))
        {
            std::cout << "Failed to load media!\n";
        }
        else
        {
            backgroundMusic.Load(musicFilepathUpdater(1).c_str());
            backgroundMusic2.Load(musicFilepathUpdater(2).c_str());
            backgroundMusic3.Load(musicFilepathUpdater(3).c_str());
            backgroundMusic4.Load(musicFilepathUpdater(4).c_str());
            backgroundMusic5.Load(musicFilepathUpdater(5).c_str());
            backgroundMusic6.Load(musicFilepathUpdater(6).c_str());
            backgroundMusic7.Load(musicFilepathUpdater(7).c_str());
            rotateSFX.Load("./Audio/RotateAudio.wav");
            backgroundMusic.Play();

            bool quit = false;

            SDL_Event event;

            const Uint8 *keystate = SDL_GetKeyboardState(NULL);
            int dx = 0;
            bool rotate = 0;
            int colorNum = 1;
            float timer = 0;
            float delay = 0.3f;
            bool firstTile = true;

            while (!quit)
            {
                float time = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
                ticksLastFrame = SDL_GetTicks();
                timer += time;

                while ( SDL_PollEvent(&event) )
                {
                    switch (event.type)
                    {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_KEYDOWN:
                        {
                            switch ( event.key.keysym.sym )
                            {
                                case SDLK_ESCAPE: 
                                    quit = true;
                                    break;
                                case SDLK_UP: 
                                    rotate = true;
                                    break;
                                case SDLK_LEFT:
                                    dx = -1;
                                    break;
                                case SDLK_RIGHT: 
                                    dx = 1;
                                    break;
                            }
                        }
                        default:
                        {
                            break;
                        }
                    }
                }

                if (firstTile == true)
                {
                    int randSeed = rand()%7;
                    colorNum = 1 + randSeed;
                    for (int i = 0; i < 4; ++i)
                    {
                        a[i].x = figures[randSeed][i] % 2;
                        a[i].y = figures[randSeed][i] / 2;
                    }
                    firstTile = false;
                }

                if (keystate[SDL_SCANCODE_DOWN])
                {
                    delay = 0.05;
                }

                // Move Tiles
                for (int i = 0; i < 4; ++i)
                {
                    b[i] = a[i];
                    a[i].x += dx;
                }

                // If tiles collided with edge or another tile, then reset 
                // tile value to temporarily stored b[i] which stores the pre-collision
                // tile location
                if ( !check() )
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        a[i] = b[i];
                    }
                }

                // Rotate Tiles
                if (rotate)
                {
                    rotateSFX.Play();
                    Point centerOfRotation = a[1]; 
                    for (int i = 0; i < 4; ++i)
                    {
                        int x = a[i].y - centerOfRotation.y;
                        int y = a[i].x - centerOfRotation.x;
                        a[i].x = centerOfRotation.x - x;
                        a[i].y = centerOfRotation.y + y;
                    }
                    // If tiles collided with edge or another tile, then reset 
                    // tile value to temporarily stored b[i] which stores the pre-collision
                    // tile location
                    if ( !check() )
                    {
                        for (int i = 0; i < 4; ++i)
                        {
                            a[i] = b[i];
                        }
                    }
                }

                // Tick
                if (timer > delay)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        b[i] = a[i];
                        a[i].y += 1;
                    }    
                    
                    if ( !check() )
                    {
                        for (int i = 0; i < 4; ++i)
                        {
                            board[b[i].y][b[i].x] = colorNum;
                        }

                        colorNum = 1 + rand()%7;
                        int n = rand()%7;

                        for (int i = 0; i < 4; ++i)
                        {
                            a[i].x = figures[n][i] % 2;
                            a[i].y = figures[n][i] / 2;
                        }
                    }

                    timer = 0;
                }

                // Check for lines
                int line = boardY - 1;
                for (int i = boardY - 1; i > 0; --i)
                {
                    int count = 0;
                    for (int j = 0; j < boardX; ++j)
                    {
                        // if board tile is anything but 0 then increase count
                        if (board[i][j])
                            count++;
                        board[line][j] = board[i][j];
                    }
                    if (count < boardX)
                    {
                        --line;
                    }
                    else
                    {
                        linesAchieved++;
                        playBackgroundMusicNumber(linesAchieved + 1);
                    }
                    
                }

                dx = 0;
                rotate = 0;
                delay = 0.3f;

                // Clear screen
                SDL_RenderClear( renderer );
                SDL_RenderCopy( renderer, background, NULL, NULL );

                // If current board position is empty, continue to draw rect 
                // in next board position
                for (int i = 0; i < boardY; ++i)
                {
                    for (int j = 0; j < boardX; ++j)
                    {
                        if (board[i][j] == 0)
                            continue;
                        // b/c board stores colorNums, accessing element will
                        // give number 1-7 * 18 which gives x coord of color tile
                        // in original tile sheet png
                        sourceRect.x = board[i][j] * 18;
                        destRect.x = j * 18 + offsetX;
                        destRect.y = i * 18 + offsetY;
                        SDL_RenderCopyEx( renderer, tiles, &sourceRect, &destRect,
                            0, NULL, SDL_FLIP_NONE);
                    }
                }
                
                // Render all cubes of tile on screen
                for (int i = 0; i < 4; ++i)
                {
                    sourceRect.x = colorNum * 18;
                    destRect.x = a[i].x * 18 + offsetX;
                    destRect.y = a[i].y * 18 + offsetY;
                    SDL_RenderCopyEx( renderer, tiles, &sourceRect, &destRect, 
                        0, NULL, SDL_FLIP_NONE);
                }
                
                // Render texture to screen
                // SDL_RenderCopyEx( renderer, texture, &sourceRect, &destRect, 0, NULL, SDL_FLIP_NONE);

                SDL_RenderCopy( renderer, frame, NULL, NULL );
                // Update screen
                SDL_RenderPresent( renderer );
            }
        }
    }

    close();

    return 0;
}