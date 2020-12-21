#pragma once

#include <SDL2/SDL.h>
#include <maths.h>


struct Camera {
    vec2i pos;

    void center_on(vec2i center);
    void render_to_cam(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
    void render_draw_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);

    vec2i project(vec2i screen);
};
