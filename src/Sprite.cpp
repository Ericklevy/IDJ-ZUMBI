#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "SpriteRenderer.h"
#include "Camera.h"

#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>


Sprite::Sprite() : texture(nullptr), 
textureWidth(0), 
textureHeight(0), 
frameCountW(1), 
frameCountH(1),
scale(1.0f, 1.0f), 
flip(SDL_FLIP_NONE),
cameraFollower(false){
    clipRect = {0, 0, 0, 0};
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) : Sprite() {
    frameCountW = (frameCountW > 0) ? frameCountW : 1; // Ensure at least 1 frame
    frameCountH = (frameCountH > 0) ? frameCountH : 1; // Ensure at least 1 frame
    Open(file);
}

Sprite::~Sprite() {
    // A textura é gerenciada pela classe Resources, então o Sprite não deve destruí-la a menos que seja o único dono.
    // O código original tinha SDL_DestroyTexture(texture) aqui.
    // Se Resources::GetImage retorna um ponteiro do cache, destruir aqui pode causar problemas.
    // Vamos assumir que Resources faz a limpeza. Se Sprite SEMPRE recebe uma nova textura ou é o único dono, então poderia destruir.
    // Considerando a classe Resources, é mais seguro deixar Resources gerenciar o tempo de vida.
    // No entanto, o destrutor original do Sprite chamava SDL_DestroyTexture.
    // Vamos seguir o destrutor original do Sprite se ele não usava Resources para limpar.
    // O Resources::ClearImages sugere que Resources faz a limpeza.
    // Portanto, o Sprite NÃO deve destruir a textura se ela veio do Resources.
    // Por enquanto, comentando, assumindo que Resources faz a limpeza.
    // if(texture != nullptr) {
    //     SDL_DestroyTexture(texture); // Isso pode estar errado se a textura veio do cache do Resources
    // }
    texture = nullptr; // Apenas libera o ponteiro
}

void Sprite::Open(std::string file) {
    std::cout << "[Sprite::Open] Attempting to load: " << file << std::endl;
    texture = Resources::GetImage(file); // GetImage handles caching AND prints its own errors

    if(texture == nullptr) {
        std::cerr << "[Sprite::Open] CRITICAL ERROR: Resources::GetImage returned NULL for: " << file << std::endl;
        std::cerr << "[Sprite::Open] SDL_GetError after GetImage (if relevant to texture loading): " << SDL_GetError() << std::endl;
        textureWidth = 0; // Ensure these are zeroed if load fails
        textureHeight = 0;
        return;
    }
    std::cout << "[Sprite::Open] Texture pointer is NOT NULL for: " << file << std::endl;

    int queryResult = SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    if(queryResult != 0) {
        std::cerr << "[Sprite::Open] CRITICAL ERROR: SDL_QueryTexture failed for: " << file << " - Error: " << SDL_GetError() << std::endl;
        textureWidth = 0;
        textureHeight = 0;
        // texture = nullptr; // Don't null it here if Resources still holds it, but mark as unusable
        return;
    }
    std::cout << "[Sprite::Open] SDL_QueryTexture success for: " << file << " - Original W=" << textureWidth << ", H=" << textureHeight << std::endl;

    if (frameCountW == 0) frameCountW = 1; // Prevent division by zero
    if (frameCountH == 0) frameCountH = 1;

    SetClip(0, 0, textureWidth / frameCountW, textureHeight / frameCountH);
    std::cout << "[Sprite::Open] ClipRect set for: " << file << " - clipX=" << clipRect.x << ", clipY=" << clipRect.y << ", clipW=" << clipRect.w << ", clipH=" << clipRect.h << std::endl;
}

void Sprite::Render(int x, int y, float angle) {
    // std::cout << "[Sprite::Render] Called for texture: " << (texture ? "VALID" : "NULL") << " at x=" << x << ", y=" << y << ", angle=" << angle << ", cameraFollower=" << cameraFollower << std::endl;

    if(texture == nullptr) {
        // std::cerr << "[Sprite::Render] Attempted to render a NULL texture. Aborting render." << std::endl;
        return;
    }
    if(clipRect.w == 0 || clipRect.h == 0) {
        // std::cerr << "[Sprite::Render] clipRect has zero width or height. Aborting render. W=" << clipRect.w << ", H=" << clipRect.h << std::endl;
        return;
    }

    SDL_Rect dstRect;
    int renderX = x;
    int renderY = y;

    if (cameraFollower) {
        // For camera follower, x and y are direct screen coordinates.
        // Typically, the GameObject's box.x/y would be 0,0 for a full-screen background.
        // std::cout << "[Sprite::Render] cameraFollower=TRUE. Using x=" << x << ", y=" << y << " as screen coords." << std::endl;
        dstRect.x = renderX;
        dstRect.y = renderY;
        dstRect.w = static_cast<int>(clipRect.w * scale.x);
        dstRect.h = static_cast<int>(clipRect.h * scale.y);
    } else {
        // Non-camera follower: x, y are world coordinates. Transform them.
        Vec2 camPos = Camera::GetInstance().GetPos(); // World coordinate at screen center
        int windowW = Game::GetInstance().GetWindowWidth();
        int windowH = Game::GetInstance().GetWindowHeight();

        if (windowW == 0 || windowH == 0) {
            // std::cerr << "[Sprite::Render] WARNING: Window width or height is 0. This will affect rendering." << std::endl;
            // Default to not offsetting if window dimensions are invalid
        }

        renderX = x - static_cast<int>(camPos.x - windowW / 2.0f);
        renderY = y - static_cast<int>(camPos.y - windowH / 2.0f);
        // std::cout << "[Sprite::Render] cameraFollower=FALSE. World(" << x << "," << y
        //           << ") -> Screen(" << renderX << "," << renderY << ") CamPos(" << camPos.x << "," << camPos.y
        //           << ") Win(" << windowW << "," << windowH << ")" << std::endl;

        dstRect.x = renderX;
        dstRect.y = renderY;
        dstRect.w = static_cast<int>(clipRect.w * scale.x);
        dstRect.h = static_cast<int>(clipRect.h * scale.y);
    }

    // std::cout << "[Sprite::Render] Final DstRect: x=" << dstRect.x << ", y=" << dstRect.y << ", w=" << dstRect.w << ", h=" << dstRect.h << std::endl;
    // std::cout << "[Sprite::Render] Final ClipRect: x=" << clipRect.x << ", y=" << clipRect.y << ", w=" << clipRect.w << ", h=" << clipRect.h << std::endl;
    // std::cout << "[Sprite::Render] Scale: x=" << scale.x << ", y=" << scale.y << " Flip: " << (int)flip << std::endl;


    SDL_Point* renderCenter = nullptr; // Rotates around dstRect center
    // int renderResult = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angle, renderCenter, flip);
    // if (renderResult != 0) {
    //    std::cerr << "[Sprite::Render] SDL_RenderCopyEx failed: " << SDL_GetError() << std::endl;
    // } else {
    //    std::cout << "[Sprite::Render] SDL_RenderCopyEx SUCCEEDED." << std::endl;
    // }

    // --- TEMPORARY SIMPLIFIED RENDER CALL FOR BACKGROUND TEST ---
    if (cameraFollower) { // Only apply this simplification if it's the background
        SDL_Rect simpleDest = {0, 0, 0, 0}; // Draw at screen 0,0
        // Use actual loaded texture width/height if scale is 1,1
        // Or, if we want to force it to window size for testing:
        simpleDest.w = Game::GetInstance().GetWindowWidth(); // Attempt to fill screen
        simpleDest.h = Game::GetInstance().GetWindowHeight();

        // Use the *entire texture* for cliprect, ignoring sprite sheet logic for this test
        SDL_Rect* fullTextureClip = nullptr; // Passing NULL uses the entire texture

        // std::cout << "[Sprite::Render cameraFollower SIMPLIFIED] Drawing full texture to screen W=" << simpleDest.w << ", H=" << simpleDest.h << std::endl;
        SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, fullTextureClip, &simpleDest);
    } else {
        // For non-camera followers, use the normal RenderCopyEx
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angle, renderCenter, flip);
    }

}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x, y, w, h};
}




int Sprite::GetWidth() {
    if(frameCountW == 0) return 0; // Avoid division by zero
    return static_cast<int>((textureWidth / frameCountW) * scale.x); // Apply scale to width;
}

int Sprite::GetHeight() {
    if(frameCountH == 0) return 0; // Avoid division by zero
    return static_cast<int>((textureHeight / frameCountH) * scale.y); // Apply scale to height
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::SetFrame(int frame) {
    int frameWidth = textureWidth/frameCountW;
    int frameHeight = textureHeight/frameCountH;
    
    int currentColumn = frame % frameCountW;
    int currentRow = frame / frameCountW; 

    SetClip(currentColumn * frameWidth, currentRow * frameHeight, frameWidth, frameHeight);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
}

void Sprite::SetCameraFollower(bool follow) {
    cameraFollower = follow;
}


void Sprite::SetScale(float scaleX, float scaleY) { 
    if (scaleX != 0) { 
        scale.x = scaleX;
    }
    if (scaleY != 0) { 
        scale.y = scaleY;
    }
}

Vec2 Sprite::GetScale() const { 
    return scale;
}

void Sprite::SetFlip(SDL_RendererFlip f) { 
    this->flip = f;
}