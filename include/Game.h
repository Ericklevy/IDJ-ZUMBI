#ifndef GAME_H
#define GAME_H
#include<bits/stdc++.h>

#include <string>
#include "SDL_include.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class State;

class Game {
private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    int frameStart;
    float dt;
    
    void CalculateDeltaTime();
    
    Game(std::string title, int width, int height);
    
public:
    ~Game();
    
    static Game& GetInstance();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    float GetDeltaTime();
};

#endif