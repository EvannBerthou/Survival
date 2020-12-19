#include "entity.h"

void Entity::update() {
}

void Entity::render(SDL_Renderer *renderer, int *offset) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_Rect rect = {x + offset[0], y + offset[1], 50, 50};
    SDL_RenderFillRect(renderer, &rect);
}

