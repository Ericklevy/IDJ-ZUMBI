#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<bits/stdc++.h>

#include <vector>
#include <memory>
#include "Component.h"
#include <string>
#include "Rect.h"

class Component;
class GameObject {
private:
    std::vector<Component*> components;
    bool isDead;
    bool started;
    
public:
    Rect box;
    double angleDeg;
    
    GameObject();
    ~GameObject();


    void Start();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();

    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);
};

#endif