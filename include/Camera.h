#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Vec2.h"

class Camera {
private:
    static Camera* instance;
    
    GameObject* focus;
    Vec2 pos;
    
    Camera();
    
public:
    static Camera& GetInstance();
    
    void Follow(GameObject* newFocus);
    void Unfollow();
    void Update(float dt);
    Vec2 GetPos();
    void SetPos(Vec2 pos);
};

#endif