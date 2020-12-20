#pragma once

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "maths.h"

// SDL Error Checker
inline int sec(int code, const char *msg) {
    if (code < 0) {
        std::cerr << msg << " " << SDL_GetError() << std::endl;
        exit(1);
    }
    return code;
}

template <typename T>
inline T *sec(T *ptr, const char *msg) {
    if (ptr == nullptr) {
        std::cerr << msg << SDL_GetError() << std::endl;
        exit(1);
    }
    return ptr;
}

inline int random(int a, int b) {
    return (rand() % (b - a + 1) + a);
}


int render_text(SDL_Renderer *renderer, TTF_Font *font,
                std::string str, vec2i pos, SDL_Color color);
