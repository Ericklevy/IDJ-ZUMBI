#include "State.h"
#include "Game.h"
#include <iostream>
#include "Zombie.h"
#include "SDL_include.h"  // Inclui todos os cabeçalhos necessários da SDL
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"

#include <SDL2/SDL_events.h>

State::State() : quitRequested(false) {
    LoadAssets();
}

State::~State() {
    objectArray.clear();
}


void State::LoadAssets() {

    // Background (cameraFollower = true)
    auto bg = new GameObject();
    auto bgSprite = new SpriteRenderer(*bg, "recursos/img/Background.png");
    bgSprite->SetCameraFollower(true);
    bg->AddComponent(bgSprite);
    bg->box.w = 1200;
    bg->box.h = 900;
    AddObject(bg);
    
    // TileMap
    auto mapGO = new GameObject();
    auto tileSet = new TileSet(64, 64, "recursos/img/Tileset.png");
    mapGO->AddComponent(new TileMap(*mapGO, "recursos/map/map.txt", tileSet));
    mapGO->box.x = 0;
    mapGO->box.y = 0;

    
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
     // Verifica saída do jogo
     InputManager& input = InputManager::GetInstance();
     if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
         quitRequested = true;
     }
     
     // Atualiza a câmera
     Camera::GetInstance().Update(dt);
     
     // Cria novos zombies com espaço
     if(input.KeyPress(SPACE_KEY)) {
         Vec2 mousePos(input.GetMouseX(), input.GetMouseY());
         Vec2 cameraPos = Camera::GetInstance().GetPos();
         
         auto zombie = new GameObject();
         zombie->box.x = mousePos.x + cameraPos.x - 32; // Centraliza
         zombie->box.y = mousePos.y + cameraPos.y - 32; // Centraliza
         zombie->AddComponent(new Zombie(*zombie));
         AddObject(zombie);
     }


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
