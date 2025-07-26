#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF


#include<bits/stdc++.h>


#include <string>
#include "SDL_include.h"


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
    int GetWindowWidth() const;
    int GetWindowHeight() const;
};

#endif