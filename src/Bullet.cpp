#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h" 
#include <cmath> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


Bullet::Bullet(GameObject& associated, float angleDeg, float speedScalar, int dmg, float maxDist) :
    Component(associated), distanceLeft(maxDist), damage(dmg) { 


    SpriteRenderer* sr = new SpriteRenderer(associated, "recursos/img/Bullet.png", 1, 1); 
    associated.AddComponent(sr);
    associated.box.w = sr->GetSprite()->GetWidth();  
    associated.box.h = sr->GetSprite()->GetHeight();
    associated.angleDeg = angleDeg; 


    float angleRad = static_cast<float>(angleDeg * (M_PI / 180.0));
    speed.x = speedScalar * std::cos(angleRad);
    speed.y = speedScalar * std::sin(angleRad);
}

void Bullet::Update(float dt) { 
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    float distanceMoved = std::sqrt( (speed.x * dt) * (speed.x * dt) + (speed.y * dt) * (speed.y * dt) );
    distanceLeft -= distanceMoved; 

    if (distanceLeft <= 0) { 
        associated.RequestDelete();
    }
}

void Bullet::Render() { }

bool Bullet::Is(std::string type) { 
    return type == "Bullet";
}

int Bullet::GetDamage() const { 
    return damage;
}