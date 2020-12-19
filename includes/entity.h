#pragma once

#include <SDL2/SDL.h>

struct Entity {
    int x,y;
    int v_x = 0, v_y = 0;
    int speed = 5;

    void update();
    void render(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, int *offset);
};
