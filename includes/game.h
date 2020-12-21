#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "world.h"
#include "camera.h"

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera camera;
    World world;
    TTF_Font *font;

    bool running = true;
    bool debug = true;

    void init();
    void run();
    void event(SDL_Event *event);
    void update();
    void render();
    void render_debug();
    void close();
};
