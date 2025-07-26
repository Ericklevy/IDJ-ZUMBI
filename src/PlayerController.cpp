#include "PlayerController.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Game.h" 
#include "Camera.h" 

PlayerController::PlayerController(GameObject& associated) : Component(associated), ownerCharacter(nullptr) {
}

void PlayerController::Start() {
    ownerCharacter = static_cast<Character*>(associated.GetComponent("Character"));
    if (!ownerCharacter) {
        return;
    }
}

void PlayerController::Update(float dt) { 
    if (!ownerCharacter) {
        return;
    }

    InputManager& input = InputManager::GetInstance();
    Vec2 moveDirection(0.0f, 0.0f);
    bool moved = false;

    if (input.IsKeyDown(UP_ARROW_KEY) || input.IsKeyDown('w')) { 
        moveDirection.y -= 1.0f;
        moved = true;
    }
    if (input.IsKeyDown(DOWN_ARROW_KEY) || input.IsKeyDown('s')) {
        moveDirection.y += 1.0f;
        moved = true;
    }
    if (input.IsKeyDown(LEFT_ARROW_KEY) || input.IsKeyDown('a')) {
        moveDirection.x -= 1.0f;
        moved = true;
    }
    if (input.IsKeyDown(RIGHT_ARROW_KEY) || input.IsKeyDown('d')) {
        moveDirection.x += 1.0f;
        moved = true;
    }

    if (moved) {
        ownerCharacter->Issue(Character::Command(Character::CommandType::MOVE, moveDirection)); 
    }

    // Atira ao pressionar o botão esquerdo do mouse
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        Vec2 mouseScreenPos(static_cast<float>(input.GetMouseX()),
                            static_cast<float>(input.GetMouseY()));
        Vec2 cameraPos = Camera::GetInstance().GetPos();
        float screenWidth = static_cast<float>(Game::GetInstance().GetWindowWidth());
        float screenHeight = static_cast<float>(Game::GetInstance().GetWindowHeight());
        Vec2 targetWorldPos = mouseScreenPos + (cameraPos - Vec2(screenWidth / 2, screenHeight / 2));

        ownerCharacter->Issue(Character::Command(Character::CommandType::SHOOT, targetWorldPos));
    }
}

void PlayerController::Render() {
    // Vazio
}

bool PlayerController::Is(std::string type) {
    return type == "PlayerController";
}