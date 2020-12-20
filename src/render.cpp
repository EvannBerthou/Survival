#include "render.h"
#include "utils.h"

void render_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) {
    sec(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a), "Error while changing color");
    sec(SDL_RenderFillRect(renderer, &rect), "Error while filling rect");
}

void render_outline(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) {
    sec(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a), "Error while changing color");
    sec(SDL_RenderDrawRect(renderer, &rect), "Error while drawing outline");
}
