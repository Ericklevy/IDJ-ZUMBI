#include "WaveSpawner.h"
#include "Zombie.h"
#include "Game.h"
#include "State.h"
#include "Character.h"
#include <cstdlib>
#include <ctime>

WaveSpawner::WaveSpawner(GameObject& associated) 
    : Component(associated), currentWave(0), zombiesSpawned(0) {
    srand(static_cast<unsigned>(time(NULL)));
    waves = {{5, 1.5f}, {8, 1.2f}, {12, 1.0f}};
}

void WaveSpawner::Update(float dt) {
    spawnTimer.Update(dt);
    
    if (currentWave >= static_cast<int>(waves.size())) return;
    
    Wave& wave = waves[currentWave];
    if (zombiesSpawned < wave.zombieCount) {
        if (spawnTimer.Get() > wave.spawnCooldown) {
            GameObject* zombie = new GameObject();
            zombie->AddComponent(new Zombie(*zombie));
            
            float angle = rand() % 360 * (M_PI / 180.0f);
            float distance = 500 + rand() % 300;
            
            if (Character::player) {
                Vec2 spawnPos = Character::player->GetPosition() + 
                               Vec2(cos(angle), sin(angle)) * distance;
                
                zombie->box.x = spawnPos.x;
                zombie->box.y = spawnPos.y;
                
                State& state = Game::GetInstance().GetState();
                state.AddObject(zombie);
                
                zombiesSpawned++;
                spawnTimer.Restart();
            }
        }
    }
    else if (Zombie::GetZombieCount() == 0) {  // Agora usando o método correto
        currentWave++;
        zombiesSpawned = 0;
    }
}

void WaveSpawner::Render() {}

bool WaveSpawner::Is(std::string type) { 
    return type == "WaveSpawner"; 
}