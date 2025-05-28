#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component { // [cite: 64]
public:
    Bullet(GameObject& associated, float angleDeg, float speedScalar, int damage, float maxDistance); // [cite: 67]
    ~Bullet() override = default;

    void Update(float dt) override; // [cite: 70]
    void Render() override; // [cite: 71] (PDF says doesn't do anything)
    bool Is(std::string type) override; // [cite: 72]

    int GetDamage() const; // [cite: 73]

private:
    Vec2 speed; // Velocity vector [cite: 64, 68]
    float distanceLeft; // [cite: 64, 69]
    int damage; // [cite: 64]
};

#endif