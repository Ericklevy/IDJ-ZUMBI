#include "Animation.h"

// Construtor padrão
Animation::Animation() : frameStart(0), frameEnd(0), frameTime(0) {}

// Construtor com parâmetros
Animation::Animation(int frameStart, int frameEnd, float frameTime) :
    frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime) {}