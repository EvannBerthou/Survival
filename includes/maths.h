#pragma once
#include <iostream>
#include <SDL2/SDL.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define CLAMP(x, a, b) (MAX(a, MIN(x, b)))
#define sign(x) (((x) < 0) ? (-1) : 1)
#define abs(x) ((x) * sign(x))

template <typename T>
struct vec2 {
    T x,y;

    vec2<T>() = default;
    vec2<T>(T _x, T _y) : x(_x), y(_y) {}

    vec2<T> operator+(const vec2<T>& other) {
        return {x + other.x, y + other.y};
    }

    vec2<T> operator-(const vec2<T>& other) {
        return {x - other.x, y - other.y};
    }


    vec2<T> operator+=(const vec2<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2<T> operator*(T s) {
        return {x * s, y * s};
    }

    vec2<T> operator/(T s) {
        return {x / s, y / s};
    }

    vec2<T> operator*=(T s) {
        x *= s;
        y *= s;
        return *this;
    }

    bool operator==(const vec2<T>& other) {
        return (x == other.x && y == other.y);
    }

    std::string to_str() {
        return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
    }
};

using vec2i = vec2<int>;
using vec2f = vec2<float>;

struct Rect {
    int x,y,w,h;
    Rect() = default;
    Rect(vec2i _p, vec2i _s) : x(_p.x), y(_p.y), w(_s.x), h(_s.y) {}
    Rect(vec2i _p, int _s) : x(_p.x), y(_p.y), w(_s), h(_s) {}
    Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
    Rect(int _x, int _y, int _s) : x(_x), y(_y), w(_s), h(_s) {}

    Rect(vec2f _p, vec2f _s) : x((int)_p.x), y((int)_p.y), w((int)_s.x), h((int)_s.y) {}
    Rect(vec2f _p, float _s) : x((int)_p.x), y((int)_p.y), w((int)_s), h((int)_s) {}
    Rect(float _x, float _y, float _w, float _h) : x((int)_x), y((int)_y), w((int)_w), h((int)_h) {}
    Rect(float _x, float _y, float _s) : x((int)_x), y((int)_y), w((int)_s), h((int)_s) {}

    std::string to_str() {
        return "[" + std::to_string(x) + "," + std::to_string(y) + std::to_string(w) + "," + std::to_string(h) + "]";
    }

    SDL_Rect to_sdl() {
        return {x,y,w,h};
    }
};

template <typename T>
struct Maybe {
    bool has;
    T val;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, vec2<T> v) {
    os << v.to_str();
    return os;
}

inline bool rect_collide(SDL_Rect a, SDL_Rect b) {
   return (a.x <= b.x + b.w &&
           a.x + a.w >= b.x &&
           a.y <= b.y + b.h &&
           a.y + a.h >= b.y);
}
