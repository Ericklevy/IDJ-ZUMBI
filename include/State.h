#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "GameObject.h"

#include "Sprite.h"
#include "Music.h"



class State {
private:
    std::vector<std::unique_ptr<GameObject>> objectArray;
    Sprite bg;
    Music music;
    bool quitRequested;
    float dt;
    
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void AddObject(GameObject* go);

};

#endif