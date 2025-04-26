#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include<bits/stdc++.h>
#include "Sound.h"
#include <ctime>
#include "Timer.h"

class Zombie : public Component {
private:
    int hitpoints;
    Sound deathSound;
    Sound hitSound; 
    float deathTimerr;  // Tempo de morte
    bool isDead;      // Flag para controle
    bool hit;        // Flag para controle de dano
    Timer hitTimer; // Timer para controle de dano
    Timer deathTimer; // Timer para controle de morte
    
public:
    Zombie(GameObject& associated);
    
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
};

#endif