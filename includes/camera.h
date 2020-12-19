#pragma once

#include <SDL2/SDL.h>
#include <maths.h>


struct Camera {
    vec2<int> pos;

    void center_on(vec2<int> center);
    void render_to_cam(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
};
