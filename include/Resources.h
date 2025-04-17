#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_include.h"
#include <unordered_map>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include<bits/stdc++.h>


class Resources {
private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
    
public:
    static SDL_Texture* GetImage(std::string file);
    static void ClearImages();
    
    static Mix_Music* GetMusic(std::string file);
    static void ClearMusics();
    
    static Mix_Chunk* GetSound(std::string file);
    static void ClearSounds();
};

#endif