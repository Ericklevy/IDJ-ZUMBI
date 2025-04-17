#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include<bits/stdc++.h>
#include "Sound.h"
#include <ctime>

class Zombie : public Component {
private:
    int hitpoints;
    Sound deathSound;
    float deathTimer;  // Tempo de morte
    bool isDead;      // Flag para controle
    
public:
    Zombie(GameObject& associated);
    
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
};

#endif