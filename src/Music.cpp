#include "Music.h"
#include <iostream>

Music::Music() : music(nullptr) {}

Music::Music(std::string file) : Music() {
    Open(file);
}

Music::~Music() {
    Stop(0);
    if(music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Open(std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr) {
        std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
}

void Music::Play(int times) {
    if(music != nullptr) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

bool Music::IsOpen() {
    return music != nullptr;
}