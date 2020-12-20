#pragma once
#include <iostream>
#include <SDL2/SDL.h>

template <typename T>
struct vec2 {
    T x,y;

    vec2<T>() = default;
    vec2<T>(T _x, T _y) : x(_x), y(_y)
    {}

    vec2<T> operator+(const vec2<T>& other) {
        return {x + other.x, y + other.y};
    }

    vec2<T> operator+=(const vec2<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    bool operator==(const vec2<T>& other) {
        return (x == other.x && y == other.y);
    }
};

using vec2i = vec2<int>;
using vec2f = vec2<float>;

template <typename T>
std::ostream& operator<<(std::ostream& os, vec2<T> v) {
    os << "[" << v.x << "," << v.y << "]";
    return os;
}

inline bool rect_collide(SDL_Rect a, SDL_Rect b) {
   return (a.x <= b.x + b.w &&
           a.x + a.w >= b.x &&
           a.y <= b.y + b.h &&
           a.y + a.h >= b.y);
}
