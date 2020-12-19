#pragma once

template <typename T>
struct vec2 {
    T x,y;

    vec2<T> operator+(const vec2<T>& other) {
        return {x + other.x, y + other.y};
    }

    vec2<T> operator+=(const vec2<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};
