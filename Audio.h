#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>

class Audio
{
    public: 
        ~Audio();
        void Load(const char* filename);
        void Play();
        void Stop();

    private: 
        SDL_AudioSpec wavSpec; 
        Uint32 wavLength;
        Uint8 *wavBuffer;
        SDL_AudioDeviceID deviceID;

};

#endif