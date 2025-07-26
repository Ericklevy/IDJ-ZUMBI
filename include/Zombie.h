#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component {
private:
    static int zombieCount;  // Contador estático de zumbis
    int hitpoints;
    Sound deathSound;
    Sound hitSound;
    float deathTimerr;
    bool isDead;
    bool hit;
    Timer hitTimer;
    Timer deathTimer;
    
public:
    Zombie(GameObject& associated);
    ~Zombie();
    
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    
    // Método estático para acessar o contador
    static int GetZombieCount() { return zombieCount; }
};

#endif