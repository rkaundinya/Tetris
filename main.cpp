#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "./Game.h"
#include "./Constants.h"

int main()
{
    Game* game = new Game();

    game->Initialize( SCREEN_WIDTH, SCREEN_HEIGHT );

    while ( game->IsRunning() )
    {
        game->ProcessEvents();
        game->Render();
    }

    game->Close();

    return 0;
}