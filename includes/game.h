#pragma once

#include <SDL2/SDL.h>
#include "world.h"

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    World world;

    bool running = true;

    void init();
    void run();
    void event(SDL_Event *event);
    void update();
    void render();
    void close();
};
