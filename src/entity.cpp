#include "entity.h"
#include "render.h"

// cp : Collision pos, gp : grid pos; pp : entity pos
void Entity::collision(int cp, int gp, float *ep, float *vel) {
    // Move the entity to the left or top of the tile
    if (cp > gp) {
        *ep = cp * TILE_SIZE - ENTITY_SIZE - 1;
    }
    // Move the entity to the right or bottom of the tile
    else if (cp < gp) {
        *ep = cp * TILE_SIZE + TILE_SIZE + 1;
    }
    *vel = 0;
}

void Entity::update(World *world) {
    auto gridPos = screenToGrid(pos);

    // Check x collisions
    auto coll_x = world->check_collision(Rect(pos + vec2f(vel.x, 0), ENTITY_SIZE).to_sdl());
    // If there is a collision
    if (coll_x.has) {
        // Correct the position of the entity
        collision(coll_x.val.x, gridPos.x, &pos.x, &vel.x);
    }

    // Same but for y axis
    auto coll_y = world->check_collision(Rect(pos + vec2f(0, vel.y), ENTITY_SIZE).to_sdl());
    if (coll_y.has) {
        collision(coll_y.val.y, gridPos.y, &pos.y, &vel.y);
    }

    // Move the player after the vel has been modify in order to not go through colliders
    pos += vel;
}

void Entity::render(SDL_Renderer *renderer, Camera &camera) {
    camera.render_to_cam(renderer, to_rect(), color);
}

SDL_Rect Entity::to_rect() {
    return Rect(pos, ENTITY_SIZE).to_sdl();
}

void Entity::set_vel(int key, float *v) {
    if (sign(*v) != sign(key)) {
        *v = 0;
    }
    if (key == 0) {
        if (*v != 0) {
            *v -= 1 * sign(*v);
        }
        if (abs(*v) < 1)  {
            *v = 0;
        }
    }
    else {
        *v = CLAMP(*v + key * speed, -max_speed, +max_speed);
    }
}
