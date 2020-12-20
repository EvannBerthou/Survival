#pragma once

#include <SDL2/SDL.h>
#include "maths.h"

#define ENTITY_SIZE 16

struct World;
struct Entity {
    vec2<int> pos;
    vec2<int> vel;
    SDL_Color color;
    int speed = 1;

    void update(World *world);
    void render(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, int *offset);
    SDL_Rect to_rect();
};

#include "world.h"
