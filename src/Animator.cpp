#include "Animator.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated) : Component(associated),
    frameStart(0), frameEnd(0), frameTime(0), currentFrame(0), timeElapsed(0.0f), currentAnimationName("")  {}

void Animator::Update(float dt) {
    if (animations.count(currentAnimationName)) {
        Animation& activeAnim = animations[currentAnimationName];
        if (activeAnim.frameTime > 0) {
            timeElapsed += dt;
            if (timeElapsed >= activeAnim.frameTime) {
                timeElapsed -= activeAnim.frameTime;
                currentFrame++;
                if (currentFrame > activeAnim.frameEnd) {
                    currentFrame = activeAnim.frameStart; 
                }

                SpriteRenderer* sprite = static_cast<SpriteRenderer*>(associated.GetComponent("SpriteRenderer"));
                if (sprite) {
                    sprite->SetFrame(currentFrame, activeAnim.flip);
                }
            }
        }
    }
}

void Animator::Render() {}

bool Animator::Is(std::string type) {
    return type == "Animator";
}

void Animator::SetAnimation(std::string name) {
    if (name == currentAnimationName && !name.empty()) { // [cite: 41] if same and not initial, do nothing
        return;
    }

    auto it = animations.find(name);
    if (it != animations.end()) {
        currentAnimationName = name; 
        Animation& newAnim = it->second;
        // frameStart = newAnim.frameStart; 
        // frameEnd = newAnim.frameEnd;
        // frameTime = newAnim.frameTime;
        currentFrame = newAnim.frameStart;
        timeElapsed = 0.0f;

        SpriteRenderer* sprite = static_cast<SpriteRenderer*>(associated.GetComponent("SpriteRenderer"));
        if (sprite) {
            sprite->SetFrame(currentFrame, newAnim.flip);
        }
    } else {
       
        currentAnimationName = ""; // Reset animação se não encontrada
    }
}

void Animator::AddAnimation(std::string name, Animation anim) {
    if(animations.find(name) == animations.end()) {
        animations[name] = anim;
    }
}