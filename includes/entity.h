#pragma once

#include <SDL2/SDL.h>
#include "maths.h"
#include "camera.h"

#define ENTITY_SIZE 16

struct World;
struct Entity {
    vec2i pos;
    vec2i vel;
    SDL_Color color;
    int speed = 5;

    void update(World *world);
    void render(SDL_Renderer *renderer, Camera &camera);
    SDL_Rect to_rect();

    void collision(int cp, int gp, int *pp, int *vel);
};

#include "world.h"
