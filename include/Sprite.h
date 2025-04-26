#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_include.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include<bits/stdc++.h>
#include "Resources.h"
#include "Camera.h"
#include "Rect.h"
#include "Timer.h"


class Sprite {
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;
   

    
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();
    
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool cameraFollower;
    // Novos métodos para animação
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetCameraFollower(bool follow);

};

#endif