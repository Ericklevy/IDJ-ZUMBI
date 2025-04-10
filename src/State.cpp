#include "State.h"
#include "Game.h"
#include <iostream>
#include "Zombie.h"
#include "SDL_include.h"  // Inclui todos os cabeçalhos necessários da SDL
#include "SpriteRenderer.h"

#include <SDL2/SDL_events.h>

State::State() : quitRequested(false) {
    LoadAssets();
}

State::~State() {
    objectArray.clear();
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
    
    // Zombie

    auto zombie = new GameObject();
    zombie->box.x = 600;
    zombie->box.y = 450;
    zombie->AddComponent(new Zombie(*zombie));
    AddObject(zombie);
}

void State::Update(float dt) {
    // Verifica se o usuário quer sair
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }
    }
    
    // Atualiza objetos
    for(auto& obj : objectArray) {
        obj->Update(dt);
    }
    
    // Remove objetos mortos
    for(int i = objectArray.size()-1; i >= 0; i--) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}


void State::Render() {
    bg.Render(0, 0);
    for(auto& obj : objectArray) {
        obj->Render();
    }
    
    
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}