#include "GameObject.h"
#include "Component.h"  // Agora podemos incluir Component.h aqui

#include <algorithm>
#include<bits/stdc++.h>


GameObject::GameObject() : isDead(false), started(false), angleDeg(0.0) {}

GameObject::~GameObject() {
    for(int i = static_cast<int>(components.size()) - 1; i >= 0; --i) {
        if (components[i]) {
            delete components[i];
        }
    }
    components.clear();
}

void GameObject::Start() {
    if (started) return; 

    for(size_t i = 0; i < components.size(); ++i) {
        if (components[i]) {
            components[i]->Start(); 
        }
    }
    started = true; 
}


void GameObject::Update(float dt) {
    for(size_t i = 0; i < components.size(); ++i) {
        if (components[i]) {
            components[i]->Update(dt);
        }
    }
}

void GameObject::Render() {
    for(size_t i = 0; i < components.size(); ++i) {
         if (components[i]) {
            components[i]->Render();
        }
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    if (cpt) {
        components.push_back(cpt);
        if (started) { 
            cpt->Start();
        }
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find(components.begin(), components.end(), cpt);
    if(it != components.end()) {
        // delete *it; // Deletion handled by GameObject destructor or if explicitly needed upon removal
        components.erase(it);
    }
}

Component* GameObject::GetComponent(std::string type) {
    for(const auto& comp : components) {
        if(comp && comp->Is(type)) {
            return comp;
        }
    }
    return nullptr;
}