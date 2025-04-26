#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"


Zombie::Zombie(GameObject& associated) : 
    Component(associated), 
    hitpoints(100)  ,
    deathSound("recursos/audio/Dead.wav") ,
    hitSound("recursos/audio/Hit0.wav"),
    deathTimerr(0),
    hit(false), isDead(false) {

    Mix_VolumeChunk(deathSound.GetChunk(), MIX_MAX_VOLUME / 4);
    auto sprite = new SpriteRenderer(associated, "recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(sprite);
    
    auto animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
    associated.AddComponent(animator);
}

void Zombie::Damage(int damage) {
    if(isDead) return;
    
    hitpoints -= damage;
    hitSound.Play(1);
    
    if(hitpoints <= 0) {
        isDead = true;
        auto animator = (Animator*)associated.GetComponent("Animator");
        if(animator) {
            animator->SetAnimation("dead");
            deathSound.Play(1);
            deathTimer.Restart();
        }
    } else {
        hit = true;
        hitTimer.Restart();
        auto animator = (Animator*)associated.GetComponent("Animator");
        if(animator) {
            animator->SetAnimation("hit");
        }
    }
}

void Zombie::Update(float dt) {
    if(isDead) {
        deathTimer.Update(dt);
        if(deathTimer.Get() > 5.0f) {
            associated.RequestDelete();
        }
        return;
    }
    
    if(hit) {
        hitTimer.Update(dt);
        if(hitTimer.Get() > 0.5f) {
            hit = false;
            auto animator = (Animator*)associated.GetComponent("Animator");
            if(animator) {
                animator->SetAnimation("walking");
            }
        }
    }
    
    // Verifica clique do mouse
    InputManager& input = InputManager::GetInstance();
    if(input.MousePress(LEFT_MOUSE_BUTTON)) {
        Vec2 mousePos(input.GetMouseX(), input.GetMouseY());
        Vec2 cameraPos = Camera::GetInstance().GetPos();
        
        // Ajusta posição do mouse para coordenadas do mundo
        Vec2 worldPos = mousePos + cameraPos;
        
        if(worldPos.x >= associated.box.x && 
           worldPos.x <= associated.box.x + associated.box.w &&
           worldPos.y >= associated.box.y && 
           worldPos.y <= associated.box.y + associated.box.h) {
            Damage(10);
        }
    }
}

void Zombie::Render() {}

bool Zombie::Is(std::string type) {
    return type == "Zombie";
}