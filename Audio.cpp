#include "./Audio.h"

Audio::~Audio()
{
    SDL_CloseAudioDevice(deviceID);
    SDL_FreeWAV(wavBuffer);
}

void Audio::Load(const char * filename)
{
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::Play()
{
    SDL_QueueAudio(deviceID, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceID, 0);
}

void Audio::Stop()
{
    SDL_CloseAudioDevice(deviceID);
}