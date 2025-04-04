#include "State.h"
#include "Game.h"
#include <iostream>
#include "SDL_include.h"  // Inclui todos os cabeçalhos necessários da SDL

#include <SDL2/SDL_events.h>

State::State() : quitRequested(false) {
    LoadAssets();
}

void State::LoadAssets() {
    // Carrega o background
    bg.Open("recursos/img/Background.png");
    if(!bg.IsOpen()) {
        std::cerr << "Erro ao carregar background!" << std::endl;
        exit(1);
    }
    
    // Carrega e toca a música
    music.Open("recursos/audio/BGM.wav");
    if(!music.IsOpen()) {
        std::cerr << "Erro ao carregar música!" << std::endl;
        exit(1);
    }
    music.Play(-1); // -1 para loop infinito
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // Define o volume da música para 25%
}

void State::Update(float dt) {
    // Verifica se o usuário quer sair (clicou no X da janela)
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }
    }
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}