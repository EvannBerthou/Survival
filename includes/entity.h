#pragma once

#include <SDL2/SDL.h>
#include "maths.h"
#include "camera.h"

#define ENTITY_SIZE 16

struct World;
struct Entity {
    vec2f pos;
    vec2f vel;
    SDL_Color color;
    float speed = 1;
    float max_speed = 5;

    void update(World *world);
    void render(SDL_Renderer *renderer, Camera &camera);
    SDL_Rect to_rect();

    void collision(int cp, int gp, float *pp, float *vel);
    void set_vel(int key, float *v);
};

#include "world.h"
