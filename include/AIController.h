// AIController.h
#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "Component.h"
#include "Timer.h"

class AIController : public Component {
public:
    enum AIState { MOVING, RESTING };
    
    AIController(GameObject& associated);
    void Update(float dt) override;
    bool Is(std::string type) override;

private:
    AIState state;
    Timer restTimer;
    Vec2 destination;
};

#endif // AICONTROLLER_H

