#include "Collider.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) 
    : Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    box = associated.box;
    box.w *= scale.x;
    box.h *= scale.y;
    
    Vec2 center = associated.box.GetCenter();
    float angle = associated.angleDeg * (M_PI / 180.0f);
    Vec2 rotatedOffset = offset.Rotate(angle);
    
    box.x = center.x - box.w / 2 + rotatedOffset.x;
    box.y = center.y - box.h / 2 + rotatedOffset.y;
}

void Collider::Render() {
    #ifdef DEBUG
    Vec2 center(box.GetCenter());
    SDL_Point points[5];
    
    // Cálculo dos pontos do polígono (implementação do PDF)
    // ... [código para desenhar a caixa de colisão]
    #endif
}

bool Collider::Is(std::string type) { return type == "Collider"; }
void Collider::SetScale(Vec2 scale) { this->scale = scale; }
void Collider::SetOffset(Vec2 offset) { this->offset = offset; }
Rect Collider::GetBox() const { return box; }