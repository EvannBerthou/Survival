#include <iostream>
#include "world.h"

void World::update() {
    player.update();
}

void World::render(SDL_Renderer *renderer) {
    int offset[2] = {800 / 2 - player.pos.x - 25, 600 / 2 - player.pos.y - 25}; // Centers on the player
    player.render(renderer, offset);
    for (int i = 0; i < entity_count; i++) {
        entities[i].render(renderer, offset);
    }
}

void World::move_player(SDL_Keycode code) {
    switch (code) {
    case SDLK_q: player.vel.x = -player.speed; break;
    case SDLK_d: player.vel.x = player.speed; break;
    case SDLK_z: player.vel.y = -player.speed; break;
    case SDLK_s: player.vel.y = player.speed; break;
    default: break;
    }
}

void World::stop_player(SDL_Keycode code) {
    switch(code) {
    case SDLK_q: case SDLK_d: player.vel.x = 0; break;
    case SDLK_z: case SDLK_s: player.vel.y = 0; break;
    default: break;
    }
}
