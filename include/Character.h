#ifndef CHARACTER_H
#define CHARACTER_H

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include "SDL_include.h"
#include <string>
#include <queue>
#include <memory>

class GameObject;
class Animator;

class Character : public Component {
public:
    enum class CommandType { MOVE, SHOOT };
    class Command {
    public:
        CommandType type;
        Vec2 pos;
        Command(CommandType type, float x, float y) : type(type), pos(x, y) {}
        Command(CommandType type, Vec2 p) : type(type), pos(p) {}
    };

    static Character* player;

    Character(GameObject& associated, std::string spritePath);
    ~Character() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void Issue(Command task);
    void Damage(int damage);

    Vec2 GetPosition() const;

private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speedVec;
    float linearSpeed;
    int hp;
    Timer deathTimer;
    bool isMoving;
    Animator* animator;
};

#endif
