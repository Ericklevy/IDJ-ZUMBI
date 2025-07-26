#include "Sound.h"
#include <iostream>

Sound::Sound() : chunk(nullptr), channel(-1) {}

Sound::Sound(std::string file) : Sound() {
    Open(file);
}

Sound::~Sound() {
    if(chunk != nullptr) {
        Stop();
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times) {
    if(chunk != nullptr) {
        channel = Mix_PlayChannel(-1, chunk, times - 1);
        if(channel == -1) {
            std::cerr << "Mix_PlayChannel Error: " << Mix_GetError() << std::endl;
        }
    }
}

void Sound::Stop() {
    if(channel != -1) {
        Mix_HaltChannel(channel);
        channel = -1;
    }
}

void Sound::Open(std::string file) {
    chunk = Mix_LoadWAV(file.c_str());
    if(chunk == nullptr) {
        std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}