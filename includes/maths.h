#pragma once
#include <iostream>

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

    bool operator==(const vec2<T>& other) {
        return (x == other.x && y == other.y);
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& os, vec2<T> v) {
    os << "[" << v.x << "," << v.y << "]";
    return os;
}
