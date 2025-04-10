#include "GameObject.h"
#include "Component.h"  // Agora podemos incluir Component.h aqui

#include <algorithm>

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    for(int i = components.size()-1; i >= 0; i--) {
        delete components[i];
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for(auto& cpt : components) {
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for(auto& cpt : components) {
        cpt->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find(components.begin(), components.end(), cpt);
    if(it != components.end()) {
        delete *it;
        components.erase(it);
    }
}

Component* GameObject::GetComponent(std::string type) {
    for(auto& cpt : components) {
        if(cpt->Is(type)) {
            return cpt;
        }
    }
    return nullptr;
}