#include "Gun.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
#include "Bullet.h"
#include "Game.h"   
#include "State.h"  
#include "Camera.h" 
#include "InputManager.h"
#include "Character.h" 
#include <cmath> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> ownerGO) :
    Component(associated), characterGO(ownerGO),
    shotSound("recursos/audio/Range.wav"),
    reloadSound("recursos/audio/PumpAction.mp3"),
    cooldownTime(0.5f), angle(0.0f), isReloading(false) {

    SpriteRenderer* sr = new SpriteRenderer(associated, "recursos/img/Gun.png", 1, 1); // Supondo 1x1 ou defina frames
    associated.AddComponent(sr);

    Animator* gunAnimator = new Animator(associated);
    // Animações "idle" e "reloading"
    gunAnimator->AddAnimation("IDLE", Animation(0, 0, 0.0f));
    // gunAnimator->AddAnimation("RELOADING", Animation(1, 1, 0.5f)); // Exemplo para animação de recarregamento
    gunAnimator->SetAnimation("IDLE");
    associated.AddComponent(gunAnimator);

    // Garante que o sprite está carregado e as dimensões são conhecidas antes de acessar GetWidth/Height
    if (sr->GetSprite() && sr->GetSprite()->IsOpen()) {
        associated.box.w = static_cast<float>(sr->GetSprite()->GetWidth());
        associated.box.h = static_cast<float>(sr->GetSprite()->GetHeight());
    } else {
        // Alternativa ou erro se o sprite não foi carregado, dimensões podem ser 0
        // std::cerr << "Aviso: Sprite da arma não carregado ou dimensões desconhecidas na construção." << std::endl;
    }
}

void Gun::Start() {
    // Inicialização se necessário após todos os GameObjects estarem prontos
}

void Gun::Update(float dt) {
    cdTimer.Update(dt);

    if (characterGO.expired()) {
        associated.RequestDelete();
        return;
    }

    std::shared_ptr<GameObject> ownerShared = characterGO.lock();
    if (!ownerShared) { // Garante que o dono ainda é válido
        associated.RequestDelete();
        return;
    }
    Vec2 ownerCenter = ownerShared->box.GetCenter();

    // Lógica de mira: Aponta a arma para o cursor do mouse
    Vec2 mouseScreenPos(static_cast<float>(InputManager::GetInstance().GetMouseX()),
                        static_cast<float>(InputManager::GetInstance().GetMouseY()));
    Vec2 cameraWorldCenter = Camera::GetInstance().GetPos(); // Coordenadas do mundo no centro da tela
    float screenWidth = static_cast<float>(Game::GetInstance().GetWindowWidth());
    float screenHeight = static_cast<float>(Game::GetInstance().GetWindowHeight());
    Vec2 screenCenter(screenWidth / 2.0f, screenHeight / 2.0f);

    // Converte as coordenadas do mouse na tela para coordenadas do mundo
    Vec2 mouseWorldPos = mouseScreenPos - screenCenter + cameraWorldCenter;

    Vec2 directionToMouse = (mouseWorldPos - ownerCenter).Normalized(); // Direção do dono até o mouse
    if (directionToMouse.Magnitude() > 0) { // Evita atan2(0,0)
         angle = static_cast<float>(atan2(directionToMouse.y, directionToMouse.x) * (180.0 / M_PI));
    }
    associated.angleDeg = angle; // Define o ângulo do GameObject para o SpriteRenderer usar

    // Reposiciona a arma a uma certa distância à frente do personagem, ao longo do novo ângulo
    float gunOffsetDistance = 30.0f; // Distância do centro do personagem até o pivô da arma
    float angleRad = static_cast<float>(angle * (M_PI / 180.0));

    // Chamada corrigida de Vec2::Rotate
    Vec2 baseOffset(gunOffsetDistance, 0); // Offset base ao longo do eixo X
    Vec2 rotatedOffset = baseOffset.Rotate(angleRad); // Rotaciona esse offset pelo ângulo da arma

    // Posiciona o centro da arma baseado no centro do dono + offset rotacionado
    associated.box.x = ownerCenter.x + rotatedOffset.x - associated.box.w / 2.0f;
    associated.box.y = ownerCenter.y + rotatedOffset.y - associated.box.h / 2.0f;


    SpriteRenderer* sr = static_cast<SpriteRenderer*>(associated.GetComponent("SpriteRenderer"));
    if (sr) {
        SDL_RendererFlip currentFlip = SDL_FLIP_NONE;
        float normalizedAngle = angle;
        while (normalizedAngle <= -180.0f) normalizedAngle += 360.0f;
        while (normalizedAngle > 180.0f) normalizedAngle -= 360.0f;

        if (normalizedAngle > 90.0f || normalizedAngle < -90.0f) {
            currentFlip = SDL_FLIP_VERTICAL;
        }
        sr->SetSpriteFlip(currentFlip);
    }

  
}

void Gun::Render() {}

bool Gun::Is(std::string type) {
    return type == "Gun";
}

void Gun::Shoot(Vec2 targetWorldPos) {
    if (cdTimer.Get() >= cooldownTime) {
        cdTimer.Restart();
        shotSound.Play(1);

        Vec2 gunCenter = associated.box.GetCenter();
        float gunAngleRad = static_cast<float>(associated.angleDeg * (M_PI / 180.0)); // Usa o ângulo visual da arma
        float muzzleOffsetDistance = associated.box.w / 2.0f; // Offset do pivô da arma até sua ponta

        Vec2 muzzlePos;
        muzzlePos.x = gunCenter.x + muzzleOffsetDistance * std::cos(gunAngleRad);
        muzzlePos.y = gunCenter.y + muzzleOffsetDistance * std::sin(gunAngleRad);

        Vec2 bulletDirection = (targetWorldPos - muzzlePos).Normalized();
        float bulletAngleDeg = static_cast<float>(atan2(bulletDirection.y, bulletDirection.x) * (180.0 / M_PI));
        if (bulletDirection.Magnitude() == 0) { // Se o alvo está exatamente na boca da arma, usa o ângulo atual da arma
            bulletAngleDeg = static_cast<float>(associated.angleDeg);
        }


        GameObject* bulletGO = new GameObject();


        // Parâmetros do projétil
        float bulletSpeed = 500.0f;
        int bulletDamage = 10;
        float bulletMaxDistance = 1000.0f;

        Bullet* bulletComponent = new Bullet(*bulletGO, bulletAngleDeg, bulletSpeed, bulletDamage, bulletMaxDistance);
        bulletGO->AddComponent(bulletComponent);
        
        bulletGO->box.x = muzzlePos.x - bulletGO->box.w / 2.0f;
        bulletGO->box.y = muzzlePos.y - bulletGO->box.h / 2.0f;


        Game::GetInstance().GetState().AddObject(bulletGO);
    }
}
