#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "Sprite.h"
#include<bits/stdc++.h>

class SpriteRenderer : public Component {
private:
    Sprite sprite;
    bool cameraFollower; //r; Novo membro
public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, 
                  int frameCountW = 1, int frameCountH = 1);
    
    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrame(int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void SetCameraFollower(bool follow);
    void SetScale(float scaleX, float scaleY); // [cite: 82]

    // Added for Gun reorientation logic
    void SetSpriteFlip(SDL_RendererFlip flip);
    Sprite* GetSprite(); // To allow direct manipulation if needed, e.g. for Gun reorientation

};

#endif