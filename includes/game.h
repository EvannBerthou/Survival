#pragma once

#include <SDL2/SDL.h>

struct Game {
    SDL_Window *window;

    void init();
    void run();
    void close();
};
