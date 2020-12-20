#pragma once

#include <SDL2/SDL.h>
#include "maths.h"

#define ENTITY_SIZE 32

struct Entity {
    vec2<int> pos;
    vec2<int> vel;
    SDL_Color color;
    int speed = 1;

    void update();
    void render(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, int *offset);
    SDL_Rect to_rect();
};
