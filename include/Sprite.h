#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_include.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "Rect.h"



class Sprite {
private:
    SDL_Texture* texture;
    int textureWidth;  // Actual width of the loaded texture
    int textureHeight; // Actual height of the loaded texture
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;

    Vec2 scale;             // [cite: 82]
    SDL_RendererFlip flip;  // [cite: 82]
   

    
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();
    
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, float angle = 0.0f);

    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool cameraFollower;
    // Novos métodos para animação
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetCameraFollower(bool follow);

    void SetScale(float scaleX, float scaleY); // [cite: 82]
    Vec2 GetScale() const; // [cite: 82] Added const
    void SetFlip(SDL_RendererFlip flip); // [cite: 82]


};

#endif