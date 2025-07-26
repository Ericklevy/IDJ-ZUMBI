#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"

Camera* Camera::instance = nullptr;

Camera::Camera() : focus(nullptr), pos(0, 0)  {}

Camera& Camera::GetInstance() {
    static Camera instance;
    return instance;
}


void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus != nullptr) {
        // Centraliza o foco usando GetCenter()
        Vec2 focusCenter = focus->box.GetCenter();
        pos = focusCenter;

        
    } else {
        // Movimento livre pela cena
        InputManager& input = InputManager::GetInstance();
        
        int speed = 200; // pixels por segundo
        float dx = 0, dy = 0;
        
        if(input.IsKeyDown(LEFT_ARROW_KEY)) dx -= speed * dt;
        if(input.IsKeyDown(RIGHT_ARROW_KEY)) dx += speed * dt;
        if(input.IsKeyDown(UP_ARROW_KEY)) dy -= speed * dt;
        if(input.IsKeyDown(DOWN_ARROW_KEY)) dy += speed * dt;
        
        pos.x += dx;
        pos.y += dy;
    }
}

Vec2 Camera::GetPos() {
    return pos;
}

void Camera::SetPos(Vec2 pos) {
    this->pos = pos;
}

