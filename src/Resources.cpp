#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);
    if(it != imageTable.end()) {
        return it->second;
    }
    
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(texture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    imageTable[file] = texture;
    return texture;
}

void Resources::ClearImages() {
    for(auto& pair : imageTable) {
        SDL_DestroyTexture(pair.second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);
    if(it != musicTable.end()) {
        return it->second;
    }
    
    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if(music == nullptr) {
        std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    
    musicTable[file] = music;
    return music;
}

void Resources::ClearMusics() {
    for(auto& pair : musicTable) {
        Mix_FreeMusic(pair.second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    if(it != soundTable.end()) {
        return it->second;
    }
    
    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if(chunk == nullptr) {
        std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    
    soundTable[file] = chunk;
    return chunk;
}

void Resources::ClearSounds() {
    for(auto& pair : soundTable) {
        Mix_FreeChunk(pair.second);
    }
    soundTable.clear();
}