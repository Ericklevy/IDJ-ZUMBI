#ifndef SOUND_H
#define SOUND_H

#include "SDL_include.h"
#include <string>
#include <SDL2/SDL_mixer.h>
#include<bits/stdc++.h>

class Sound {
private:
    Mix_Chunk* chunk;
    int channel;
    
public:
    Sound();
    Sound(std::string file);
    ~Sound();
    
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
};

#endif