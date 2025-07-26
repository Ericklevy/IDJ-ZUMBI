#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angleDeg, float speedScalar, int damage, float maxDistance);
    ~Bullet() override = default;

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    int GetDamage() const;

private:
    float distanceLeft;  // Reordenado para ficar primeiro
    Vec2 speed;
    int damage;
};

#endif