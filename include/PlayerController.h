#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Component.h"
#include "Character.h" // For Character::Command

class PlayerController : public Component {
public:
    PlayerController(GameObject& associated); 
    ~PlayerController() override = default;

    void Start() override; 
    void Update(float dt) override; 
    void Render() override; 
    bool Is(std::string type) override; 

private:
    Character* ownerCharacter; // Cache pointer to Character component
};

#endif