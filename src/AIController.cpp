// AIController.cpp
#include "AIController.h"
#include "Character.h"
#include "Gun.h"

AIController::AIController(GameObject& associated) 
    : Component(associated), state(RESTING) {
    restTimer.Restart();
}

void AIController::Update(float dt) {
    if (!Character::player) return;

    switch (state) {
        case RESTING:
            restTimer.Update(dt);
            if (restTimer.Get() > 2.0f) {
                state = MOVING;
                destination = Character::player->GetPosition();
            }
            break;
            
        case MOVING: {
            Vec2 npcPos = associated.box.GetCenter();
            Vec2 direction = (destination - npcPos).Normalized();
            float speed = 100.0f;
            
            associated.box.x += direction.x * speed * dt;
            associated.box.y += direction.y * speed * dt;
            
            if (npcPos.Distance(destination) < 10.0f) {
                // Atirar no jogador
                Gun* gun = static_cast<Gun*>(associated.GetComponent("Gun"));
                if (gun) {
                    gun->Shoot(Character::player->GetPosition());
                }
                
                state = RESTING;
                restTimer.Restart();
            }
            break;
        }
    }
}

bool AIController::Is(std::string type) { 
    return type == "AIController"; 
}