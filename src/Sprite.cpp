#include "Sprite.h"
#include "Game.h"

#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

Sprite::Sprite() : texture(nullptr), width(0), height(0) {
    clipRect = {0, 0, 0, 0};
}

Sprite::Sprite(std::string file) : Sprite() {
    Open(file);
}

Sprite::~Sprite() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    
    Game& game = Game::GetInstance();
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
    
    if(texture == nullptr) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        exit(1);
    }
    
    if(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        std::cerr << "SDL_QueryTexture Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect = {x, y, clipRect.w, clipRect.h};
    Game& game = Game::GetInstance();
    SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dstrect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}