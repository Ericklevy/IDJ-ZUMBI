#ifndef MUSIC_H
#define MUSIC_H
#include<bits/stdc++.h>

#include "SDL_include.h"
#include <string>
#include <SDL2/SDL_mixer.h>

class Music {
private:
    Mix_Music* music;
    
public:
    Music();
    Music(std::string file);
    ~Music();
    
    void Open(std::string file);
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    bool IsOpen();
};

#endif