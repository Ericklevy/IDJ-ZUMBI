#ifndef RECT_H
#define RECT_H

#include "Vec2.h"
#include<bits/stdc++.h>


class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);
    
    Vec2 GetCenter() const;
    float Distance(const Rect& other) const;
    bool Contains(const Vec2& point) const;
    Rect operator+(const Vec2& rhs) const;
};

#endif