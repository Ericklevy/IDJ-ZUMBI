#ifndef GUN_H
#define GUN_H

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include "Sound.h"
#include <memory> 

class GameObject;
class Character;  

class Gun : public Component {
public:
    Gun(GameObject& associated, std::weak_ptr<GameObject> characterGO);
    ~Gun() override = default;

    void Start() override;
    void Update(float dt) override;
    void Render() override; 
    bool Is(std::string type) override; 

    void Shoot(Vec2 targetWorldPos); 

private:
    std::weak_ptr<GameObject> characterGO; 
    Sound shotSound;      
    Sound reloadSound;    
    Timer cdTimer;       
    float cooldownTime;   
    float angle;         
    bool isReloading;
};

#endif