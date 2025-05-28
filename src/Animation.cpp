#include "Animation.h"

// Construtor padrão
Animation::Animation() : frameStart(0), frameEnd(0), frameTime(0), flip(SDL_FLIP_NONE)  {}

// Construtor com parâmetros
Animation::Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip f) :
    frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime), flip(f) {}