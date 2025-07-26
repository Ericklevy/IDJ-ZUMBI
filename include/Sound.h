#ifndef SOUND_H
#define SOUND_H
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <string>
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
    Mix_Chunk* GetChunk() const { return chunk; }

};

#endif