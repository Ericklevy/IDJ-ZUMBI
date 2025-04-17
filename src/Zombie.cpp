#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Sound.h"


Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100)  ,deathSound("recursos/audio/Dead.wav"){
    auto sprite = new SpriteRenderer(associated, "recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(sprite);
    
    auto animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
    associated.AddComponent(animator);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= 0) {
        auto animator = (Animator*)associated.GetComponent("Animator");
        if(animator) {
            animator->SetAnimation("dead");
            deathSound.Play(1);
        }
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {}

bool Zombie::Is(std::string type) {
    return type == "Zombie";
}