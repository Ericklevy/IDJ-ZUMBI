#include "SpriteRenderer.h"
#include "Game.h"
#include "GameObject.h"
#include "Camera.h"
#include "Sprite.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file,
                             int frameCountW, int frameCountH) : Component(associated) {
    sprite.SetFrameCount(frameCountW, frameCountH); // Set frame count before Open
    sprite.Open(file);
    if (sprite.IsOpen()) {
        associated.box.w = static_cast<float>(sprite.GetWidth());
        associated.box.h = static_cast<float>(sprite.GetHeight());
    }
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    if(sprite.IsOpen()) {
        associated.box.w = static_cast<float>(sprite.GetWidth());
        associated.box.h = static_cast<float>(sprite.GetHeight());
    }
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
    if (sprite.IsOpen()) {
        associated.box.w = static_cast<float>(sprite.GetWidth());
        associated.box.h = static_cast<float>(sprite.GetHeight());
    }
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) { // [cite: 89]
    sprite.SetFrame(frame);
    sprite.SetFlip(flip); // [cite: 89] Call SetFlip of its sprite
}

void SpriteRenderer::Update(float dt) {}


void SpriteRenderer::Render() {
    
    if (!sprite.IsOpen()) {
        std::cerr << "ERRO: Sprite nao carregado!" << std::endl;
        return;
    }
    sprite.Render(static_cast<int>(associated.box.x), 
                 static_cast<int>(associated.box.y), 
                 associated.angleDeg);
}


bool SpriteRenderer::Is(std::string type) {
    return type == "SpriteRenderer";
}


void SpriteRenderer::SetCameraFollower(bool follow) {
    sprite.SetCameraFollower(follow);
}


void SpriteRenderer::SetScale(float scaleX, float scaleY) { // [cite: 87]
    Vec2 oldCenter = associated.box.GetCenter();
    float oldW = associated.box.w;
    float oldH = associated.box.h;

    sprite.SetScale(scaleX, scaleY);
    associated.box.w = static_cast<float>(sprite.GetWidth());
    associated.box.h = static_cast<float>(sprite.GetHeight());

    // Adjust box position to keep center [cite: 88]
    associated.box.x = oldCenter.x - associated.box.w / 2.0f;
    associated.box.y = oldCenter.y - associated.box.h / 2.0f;
}

void SpriteRenderer::SetSpriteFlip(SDL_RendererFlip flip) {
    sprite.SetFlip(flip);
}

Sprite* SpriteRenderer::GetSprite() {
    return &sprite;
}
