#include "SpriteRenderer.h"
#include "Game.h"
#include "GameObject.h"
#include "Camera.h"
#include "Sprite.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, 
                             int frameCountW, int frameCountH) : Component(associated) {
    Open(file);
    SetFrameCount(frameCountW, frameCountH);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
    sprite.Render(associated.box.x, associated.box.y);
}

bool SpriteRenderer::Is(std::string type) {
    return type == "SpriteRenderer";
}

void SpriteRenderer::SetCameraFollower(bool follow) {
    sprite.SetCameraFollower(follow);
}
