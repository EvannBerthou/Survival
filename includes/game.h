#pragma once

#include <SDL2/SDL.h>
#include "world.h"
#include "camera.h"

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera camera;
    World world;

    bool running = true;
    bool debug = false;

    void init();
    void run();
    void event(SDL_Event *event);
    void update();
    void render();
    void close();
};
