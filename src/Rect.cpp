#include "Rect.h"
#include<bits/stdc++.h>

Rect::Rect() : x(0), y(0), w(0), h(0) {}
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Vec2 Rect::GetCenter() const {
    return Vec2(x + w/2, y + h/2);
}

float Rect::Distance(const Rect& other) const {
    return GetCenter().Distance(other.GetCenter());
}

bool Rect::Contains(const Vec2& point) const {
    return (point.x >= x && point.x <= x + w &&
            point.y >= y && point.y <= y + h);
}

Rect Rect::operator+(const Vec2& rhs) const {
    return Rect(x + rhs.x, y + rhs.y, w, h);
}