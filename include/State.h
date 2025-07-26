#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "GameObject.h"

#include "Sprite.h"
#include "Music.h"
#include<bits/stdc++.h>



class State {
private:
    std::vector<std::shared_ptr<GameObject>> objectArray;
    Sprite bg;
    Music music;
    bool quitRequested;
    float dt;
    bool started;
    
public:
    State();
    ~State();

    
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    //entrega 5
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go); 
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go); 


};

#endif