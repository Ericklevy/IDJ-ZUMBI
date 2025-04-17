#include "State.h"
#include "Game.h"
#include <iostream>
#include "Zombie.h"
#include "SDL_include.h"  // Inclui todos os cabeçalhos necessários da SDL
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"

#include <SDL2/SDL_events.h>

State::State() : quitRequested(false) {
    LoadAssets();
}

State::~State() {
    objectArray.clear();
}


void State::LoadAssets() {

    auto bg = new GameObject();
    bg->AddComponent(new SpriteRenderer(*bg, "recursos/img/Background.png"));
    bg->box.x = 0;
    bg->box.y = 0;
    bg->box.w = 1200;  // Largura da janela
    bg->box.h = 900;   // Altura da janela
    AddObject(bg);
    
    // Carrega e toca a música
    music.Open("recursos/audio/BGM.wav");
    if(!music.IsOpen()) {
        std::cerr << "Erro ao carregar música!" << std::endl;
        exit(1);
    }
    music.Play(-1); // -1 para loop infinito
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // Define o volume da música para 25%
    

     // TileMap - ajustado para o mapa 40x40 com tiles 64x64
    auto mapGO = new GameObject();
    auto tileSet = new TileSet(64, 64, "recursos/img/Tileset.png");
    mapGO->AddComponent(new TileMap(*mapGO, "recursos/map/map.txt", tileSet));
    mapGO->box.x = 0;
    mapGO->box.y = 0;
    AddObject(mapGO);

    // Zombies - posicionados dentro dos limites do mapa
    auto zombie1 = new GameObject();
    zombie1->box.x = 600;  // Ajuste conforme necessário
    zombie1->box.y = 450;  // Ajuste conforme necessário
    zombie1->AddComponent(new Zombie(*zombie1));
    AddObject(zombie1);

    auto zombie2 = new GameObject();
    zombie2->box.x = 300;
    zombie2->box.y = 300;
    zombie2->AddComponent(new Zombie(*zombie2));
    AddObject(zombie2);
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
