#include <iostream>
#include "world.h"

void World::update() {
    player.x += player.v_x;
    player.y += player.v_y;
}

void World::render(SDL_Renderer *renderer) {
    int offset[2];
    offset[0] = 800 / 2 - player.x - 25;
    offset[1] = 600 / 2 - player.y - 25;
    player.render(renderer, offset);
    for (int i = 0; i < entity_count; i++) {
        entities[i].render(renderer, offset);
    }
}

void World::move_player(SDL_Keycode code) {
    switch (code) {
    case SDLK_q: player.v_x = -player.speed; break;
    case SDLK_d: player.v_x = player.speed; break;
    case SDLK_z: player.v_y = -player.speed; break;
    case SDLK_s: player.v_y = player.speed; break;
    default: break;
    }
}

void World::stop_player(SDL_Keycode code) {
    switch(code) {
    case SDLK_q: case SDLK_d: player.v_x = 0; break;
    case SDLK_z: case SDLK_s: player.v_y = 0; break;
    default: break;
    }
}
