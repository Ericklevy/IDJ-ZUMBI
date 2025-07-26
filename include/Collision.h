#ifndef COLLISION_H
#define COLLISION_H

#include "Rect.h"
#include <cmath>

inline float dot(const Vec2& a, const Vec2& b) {
    return a.x * b.x + a.y * b.y;
}

inline Vec2 rotate(const Vec2& p, float angle) {
    float cs = cos(angle);
    float sn = sin(angle);
    return Vec2(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
}

inline bool IsColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB) {
    Vec2 A[] = { Vec2(a.x, a.y + a.h),
                 Vec2(a.x + a.w, a.y + a.h),
                 Vec2(a.x + a.w, a.y),
                 Vec2(a.x, a.y) };
    
    Vec2 B[] = { Vec2(b.x, b.y + b.h),
                 Vec2(b.x + b.w, b.y + b.h),
                 Vec2(b.x + b.w, b.y),
                 Vec2(b.x, b.y) };

    for (auto& v : A)
        v = rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
    
    for (auto& v : B)
        v = rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();

    Vec2 axes[] = { (A[0] - A[1]).Normalized(),
                    (A[1] - A[2]).Normalized(),
                    (B[0] - B[1]).Normalized(),
                    (B[1] - B[2]).Normalized() };

    for (auto& axis : axes) {
        float P[4];
        for (int i = 0; i < 4; ++i) P[i] = dot(A[i], axis);
        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);
        
        for (int i = 0; i < 4; ++i) P[i] = dot(B[i], axis);
        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);
        
        if (maxA < minB || minA > maxB)
            return false;
    }
    return true;
}

#endif // COLLISION_H