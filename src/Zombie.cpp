#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Sound.h"


Zombie::Zombie(GameObject& associated) : 
    Component(associated), 
    hitpoints(100)  ,
    deathSound("recursos/audio/Dead.wav") ,
    deathTimer(0),
    isDead(false) {

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
    if(isDead) return; // Se já está morto, não faz nada
    
    hitpoints -= damage;
    if(hitpoints <= 0) {
        isDead = true;
        auto animator = (Animator*)associated.GetComponent("Animator");
        if(animator) {
            animator->SetAnimation("dead");
            deathSound.Play(1);
            deathTimer = 1.5f; // Configura o timer para 1.5 segundos
        }
    }
}

void Zombie::Update(float dt) {
    Damage(1);
    if(isDead && deathTimer > 0) {
        deathTimer -= dt;
        if(deathTimer <= 0) {
            deathSound.Stop(); // Para o som após 1.5 segundos
        }
    }
}

void Zombie::Render() {}

bool Zombie::Is(std::string type) {
    return type == "Zombie";
}