#pragma once
#include <iostream>
#include <SDL2/SDL.h>

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
