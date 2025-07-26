#include "Character.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
#include "Gun.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include <cmath>

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string spritePath) :
    Component(associated), linearSpeed(200.0f), hp(100), isMoving(false), animator(nullptr) {
    
    SpriteRenderer* sr = new SpriteRenderer(associated, spritePath, 4, 2);
    associated.AddComponent(sr);

    animator = new Animator(associated);
    // Animações: idle, walking e dead. Frames de exemplo, ajuste conforme sprite sheet.
    animator->AddAnimation("IDLE_RIGHT", Animation(0, 0, 0.0f, SDL_FLIP_NONE));
    animator->AddAnimation("IDLE_LEFT", Animation(0, 0, 0.0f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("WALKING_RIGHT", Animation(1, 4, 0.1f, SDL_FLIP_NONE));
    animator->AddAnimation("WALKING_LEFT", Animation(1, 4, 0.1f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("DEAD_RIGHT", Animation(5, 5, 0.0f, SDL_FLIP_NONE));
    animator->AddAnimation("DEAD_LEFT", Animation(5, 5, 0.0f, SDL_FLIP_HORIZONTAL));
    
    animator->SetAnimation("IDLE_RIGHT");
    associated.AddComponent(animator);
}

Character::~Character() {
    if (Character::player == this) {
        Character::player = nullptr;
    }
}

void Character::Start() {
    GameObject* gunGO = new GameObject();
    // Cria ponteiro fraco para o GameObject do personagem
    std::weak_ptr<GameObject> charWeakPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);
    
    Gun* gunComponent = new Gun(*gunGO, charWeakPtr);
    gunGO->AddComponent(gunComponent);
    
    // Posição inicial da arma será ajustada pelo Gun::Update
    gunGO->box.x = associated.box.GetCenter().x;
    gunGO->box.y = associated.box.GetCenter().y;

    this->gun = Game::GetInstance().GetState().AddObject(gunGO);
}

void Character::Update(float dt) {
    speedVec = Vec2(0,0);
    isMoving = false;

    if (hp <= 0) {
        deathTimer.Update(dt);
        // Define direção da animação de morte baseada na última direção
        bool facingRight = (animator->currentAnimationName.find("RIGHT") != std::string::npos || 
                            animator->currentAnimationName.find("IDLE") != std::string::npos);
        animator->SetAnimation(facingRight ? "DEAD_RIGHT" : "DEAD_LEFT");
        if (deathTimer.Get() > 2.0f) { // Espera 2 segundos para deletar após morrer
            associated.RequestDelete();
            if (!gun.expired()) {
                gun.lock()->RequestDelete();
            }
        }
        return;
    }

    // Processa comandos da fila
    if (!taskQueue.empty()) {
        Command cmd = taskQueue.front();
        taskQueue.pop();

        if (cmd.type == CommandType::MOVE) {
            // cmd.pos é um vetor direção. Normaliza e multiplica pela velocidade.
            Vec2 direction = cmd.pos.Normalized();
            speedVec = direction * linearSpeed;
            associated.box.x += speedVec.x * dt;
            associated.box.y += speedVec.y * dt;
            isMoving = true;
        } else if (cmd.type == CommandType::SHOOT) {
            if (!gun.expired()) {
                Gun* gunPtr = static_cast<Gun*>(gun.lock()->GetComponent("Gun"));
                if (gunPtr) {
                    gunPtr->Shoot(cmd.pos); // cmd.pos são coordenadas alvo no mundo
                }
            }
        }
    }

    // Controle de animação
    if (animator) {
        bool currentlyFacingRight = (speedVec.x > 0) || (speedVec.x == 0 && (animator->currentAnimationName.find("RIGHT") != std::string::npos || animator->currentAnimationName.find("IDLE_RIGHT") != std::string::npos ));
        if (speedVec.x < 0) currentlyFacingRight = false;

        if (isMoving) {
            animator->SetAnimation(currentlyFacingRight ? "WALKING_RIGHT" : "WALKING_LEFT");
        } else {
            animator->SetAnimation(currentlyFacingRight ? "IDLE_RIGHT" : "IDLE_LEFT");
        }
    }
}

void Character::Render() { 
}

bool Character::Is(std::string type) {
    return type == "Character";
}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

void Character::Damage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
    if (hp == 0) {
        deathTimer.Restart();
        // A animação de morte será definida no Update
    }
}
Vec2 Character::GetPosition() const {
    return associated.box.GetCenter();
}
