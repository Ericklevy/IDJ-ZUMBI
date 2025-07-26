#ifndef VEC2_H
#define VEC2_H
#include<bits/stdc++.h>

class Vec2 {
public:
    float x, y;

    Vec2();
    Vec2(float x, float y);
    
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(float scalar) const;
    float Magnitude() const;
    Vec2 Normalized() const;
    float Distance(const Vec2& other) const;
    float Inclination() const;
    Vec2 Rotate(float angle) const;
    static Vec2 Rotate(const Vec2& vec, float angle);
};

#endif