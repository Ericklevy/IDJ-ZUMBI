#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    int frameStart;
    int frameEnd;
    float frameTime;
    
    Animation();  // Adicionando construtor padrão
    Animation(int frameStart, int frameEnd, float frameTime);
};

#endif