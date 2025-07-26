// WaveSpawner.h
#ifndef WAVESPAWNER_H
#define WAVESPAWNER_H

#include "Component.h"
#include "Timer.h"
#include <vector>

struct Wave {
    int zombieCount;
    float spawnCooldown;
};

class WaveSpawner : public Component {
public:
    WaveSpawner(GameObject& associated);
    void Update(float dt) override;
    void Render() override;  // Adicionado
    bool Is(std::string type) override;

private:
    std::vector<Wave> waves;
    int currentWave;
    int zombiesSpawned;
    Timer spawnTimer;
};

#endif // WAVESPAWNER_H