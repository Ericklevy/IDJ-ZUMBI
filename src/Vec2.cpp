#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

float Vec2::Magnitude() const {
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::Normalized() const {
    float mag = Magnitude();
    if(mag == 0) return Vec2();
    return Vec2(x/mag, y/mag);
}

float Vec2::Distance(const Vec2& other) const {
    return (*this - other).Magnitude();
}

float Vec2::Inclination() const {
    return std::atan2(y, x);
}

Vec2 Vec2::Rotate(float angle) const {
    float cs = std::cos(angle);
    float sn = std::sin(angle);
    return Vec2(x * cs - y * sn, x * sn + y * cs);
}