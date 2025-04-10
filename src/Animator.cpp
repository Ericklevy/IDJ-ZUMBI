#include "Animator.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated) : Component(associated),
    frameStart(0), frameEnd(0), frameTime(0), currentFrame(0), timeElapsed(0) {}

void Animator::Update(float dt) {
    if(frameTime != 0) {
        timeElapsed += dt;
        if(timeElapsed > frameTime) {
            currentFrame++;
            timeElapsed -= frameTime;
            if(currentFrame > frameEnd) {
                currentFrame = frameStart;
            }
            
            auto sprite = (SpriteRenderer*)associated.GetComponent("SpriteRenderer");
            if(sprite) {
                sprite->SetFrame(currentFrame);
            }
        }
    }
}

void Animator::Render() {}

bool Animator::Is(std::string type) {
    return type == "Animator";
}

void Animator::SetAnimation(std::string name) {
    auto it = animations.find(name);
    if(it != animations.end()) {
        frameStart = it->second.frameStart;
        frameEnd = it->second.frameEnd;
        frameTime = it->second.frameTime;
        currentFrame = frameStart;
        timeElapsed = 0;
        
        auto sprite = (SpriteRenderer*)associated.GetComponent("SpriteRenderer");
        if(sprite) {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::AddAnimation(std::string name, Animation anim) {
    if(animations.find(name) == animations.end()) {
        animations[name] = anim;
    }
}