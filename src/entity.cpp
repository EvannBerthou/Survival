#include "entity.h"
#include "render.h"

void Entity::update() {
    pos += vel;
}

void Entity::render(SDL_Renderer *renderer, int *offset) {
    render_rect(renderer, {pos.x + offset[0], pos.y + offset[1], 50, 50}, color);
}

SDL_Rect Entity::to_rect() {
    return {pos.x, pos.y, 50, 50};
}

