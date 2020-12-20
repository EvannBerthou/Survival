#pragma once

#include <SDL2/SDL.h>
#include "maths.h"

#define ENTITY_SIZE 16

struct World;
struct Entity {
    vec2i pos;
    vec2i vel;
    SDL_Color color;
    int speed = 5;

    void update(World *world);
    void render(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, int *offset);
    SDL_Rect to_rect();
};

#include "world.h"
