#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include "Rect.h"

class Collider : public Component {
public:
    Collider(GameObject& associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    Rect GetBox() const;

private:
    Vec2 scale;
    Vec2 offset;
    Rect box;
};

#endif // COLLIDER_H