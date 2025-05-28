#ifndef GUN_H
#define GUN_H

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include "Sound.h"
#include <memory> // For std::weak_ptr

class GameObject; // Forward declaration
class Character;  // Forward declaration for type hint, not direct use from header

class Gun : public Component {
public:
    Gun(GameObject& associated, std::weak_ptr<GameObject> characterGO); // [cite: 20, 29]
    ~Gun() override = default;

    void Start() override;
    void Update(float dt) override; // [cite: 42]
    void Render() override; // [cite: 48]
    bool Is(std::string type) override; // [cite: 49]

    void Shoot(Vec2 targetWorldPos); // [cite: 50]

private:
    std::weak_ptr<GameObject> characterGO; // The GameObject Character component is attached to [cite: 20]
    Sound shotSound;      // [cite: 20]
    Sound reloadSound;    // [cite: 20]
    Timer cdTimer;        // [cite: 20]
    float cooldownTime;   // Actual duration of cooldown
    float angle;          // Current angle of the gun in degrees [cite: 20]
    bool isReloading;
    // Animator* animator; // Cache animator
};

#endif