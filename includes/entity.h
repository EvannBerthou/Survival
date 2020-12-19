#pragma once

#include <SDL2/SDL.h>
#include "maths.h"

struct Entity {
    vec2<int> pos;
    vec2<int> vel;
    int speed = 5;

    void update();
    void render(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, int *offset);
};
