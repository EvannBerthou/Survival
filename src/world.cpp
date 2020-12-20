#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "world.h"
#include "chunk.h"

void World::generate(time_t seed) {
    srand(seed);
    int index = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            chunks[index].pos = {x,y};
            chunks[index].generate();
            index++;
        }
    }
}

void World::update() {
    player.update();
}

void World::render(SDL_Renderer *renderer, Camera &camera) {
    for (int i = 0; i < 9; i++) {
        chunks[i].render(renderer, camera);
    }

    for (int i = 0; i < entity_count; i++) {
        camera.render_to_cam(renderer, entities[i].to_rect(), entities[i].color);
    }
    camera.render_to_cam(renderer, player.to_rect(), player.color);
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
