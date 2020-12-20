#pragma once

#include <SDL2/SDL.h>
#include "camera.h"
#include "maths.h"
#include "tile.h"

#define CHUNK_TILE_COUNT 16
#define TILE_SIZE 32
#define CHUNK_SIZE (CHUNK_TILE_COUNT * TILE_SIZE)

struct Chunk {
    vec2<int> pos;
    Tile ground[CHUNK_TILE_COUNT][CHUNK_TILE_COUNT];

    void generate();
    void render(SDL_Renderer *renderer, Camera &camera);
};
