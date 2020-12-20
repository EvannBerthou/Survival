#include "entity.h"
#include "render.h"

void Entity::update() {
    pos += vel;
}

void Entity::render(SDL_Renderer *renderer, int *offset) {
    render_rect(renderer, {pos.x + offset[0], pos.y + offset[1], 0, 0}, color);
}

SDL_Rect Entity::to_rect() {
    return {pos.x, pos.y, 0, 0};
}

