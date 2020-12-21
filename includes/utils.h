#pragma once

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "maths.h"
#include "world.h"

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

inline vec2i getChunkPos(vec2i pos) {
    return {(int)std::floor(pos.x / (float)CHUNK_TILE_COUNT), (int)std::floor(pos.y / (float)CHUNK_TILE_COUNT)};
}

inline vec2i screenToGrid(vec2i screen) {
    return {(int)std::floor(screen.x / (float)TILE_SIZE), (int)std::floor(screen.y / (float)TILE_SIZE)};
}

inline vec2i to_world(vec2i pos) {
    return (pos * TILE_SIZE);
}

inline vec2i chunk_to_world(vec2i pos) {
    return (pos * CHUNK_SIZE);
}

inline vec2i snap_to_grid(vec2i pos) {
    return screenToGrid(pos) * TILE_SIZE;
}

vec2i posInChunk(vec2i pos);
