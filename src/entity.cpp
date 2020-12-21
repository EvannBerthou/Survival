#include "entity.h"
#include "render.h"

void Entity::update(World *world) {
    vec2<int> nextPos = pos + vel;
    Rect rect(nextPos, ENTITY_SIZE);
    if (world->check_collision(rect.to_sdl())) {
        return;
    }

    pos = nextPos;
}

void Entity::render(SDL_Renderer *renderer, Camera &camera) {
    camera.render_to_cam(renderer, to_rect(), color);
}

SDL_Rect Entity::to_rect() {
    return Rect(pos, ENTITY_SIZE).to_sdl();
}

