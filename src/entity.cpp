#include "entity.h"
#include "render.h"

void Entity::update(World *world) {
    vec2<int> nextPos = pos + vel;
    SDL_Rect rect = {nextPos.x, nextPos.y, ENTITY_SIZE, ENTITY_SIZE};
    if (world->check_collision(rect)) {
        return;
    }

    pos = nextPos;
}

void Entity::render(SDL_Renderer *renderer, int *offset) {
    render_rect(renderer, {pos.x + offset[0], pos.y + offset[1], ENTITY_SIZE, ENTITY_SIZE}, color);
}

SDL_Rect Entity::to_rect() {
    return {pos.x, pos.y, ENTITY_SIZE, ENTITY_SIZE};
}

