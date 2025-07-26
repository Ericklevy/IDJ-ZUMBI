#ifndef ANIMATION_H
#define ANIMATION_H
#include<bits/stdc++.h>

#include <SDL2/SDL.h> 
#include "SDL_include.h"
class Animation {
public:
    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_RendererFlip flip; 
    
    Animation();  // Adicionando construtor padrão
    Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE); 
};

#endif