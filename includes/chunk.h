#pragma once

#include <SDL2/SDL.h>
#include "camera.h"
#include "maths.h"

#define CHUNCK_SIZE 16
#define TILE_SIZE 32

struct Chunck {
    vec2<int> pos;
    int ground[CHUNCK_SIZE][CHUNCK_SIZE];

    void generate();
    void render(SDL_Renderer *renderer, Camera &camera);
};
