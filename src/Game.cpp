#include "Game.h"
#include "State.h"
#include "Music.h"
#include "Sprite.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL.h>
#include <iostream>
#include<bits/stdc++.h>
#include <Resources.h>
#include "InputManager.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
    if(instance != nullptr) {
        std::cerr << "Erro: Tentativa de criar múltiplas instâncias de Game!" << std::endl;
        exit(1);
    }
    instance = this;
    
    // Inicializa SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    // Inicializa SDL_image
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        exit(1);
    }
    
    // Inicializa SDL_mixer
    int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    if(!(Mix_Init(mixFlags) & mixFlags)) {
        std::cerr << "Mix_Init Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
    
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
    
    Mix_AllocateChannels(32);
    
    // Cria janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                             width, height, 0);
    if(window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    // Cria renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    // Cria estado inicial
    state = new State();
}

Game::~Game() {
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game& Game::GetInstance() {
    if(instance == nullptr) {
        new Game("Erick Levy Barbosa dos Santos -180016067", 1200, 900);
    }
    return *instance;
}

void Game::CalculateDeltaTime() {
    int currentFrame = SDL_GetTicks();
    dt = (currentFrame - frameStart) / 1000.0f;
    frameStart = currentFrame;
}

float Game::GetDeltaTime() {
    return dt;
}


void Game::Run() {
    frameStart = SDL_GetTicks();

    if (state) {
        state->Start();
    }

    // Game loop
    while(!state->QuitRequested()) {
            CalculateDeltaTime();
            InputManager::GetInstance().Update();
            state->Update(GetDeltaTime());  // ← Atualiza primeiro
            state->Render();                // ← Renderiza depois
            SDL_RenderPresent(renderer);
            SDL_Delay(33);
        }
    // ...
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}

int Game::GetWindowWidth() const {
    int w = 0;
    if (window) { 
        SDL_GetWindowSize(window, &w, nullptr);
    }
    return w;
}

int Game::GetWindowHeight() const {
    int h = 0;
    if (window) { 
        SDL_GetWindowSize(window, nullptr, &h);
    }
    return h;
}