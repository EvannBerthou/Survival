#include <iostream>
#include <time.h>
#include <cmath>
#include <stdlib.h>
#include "world.h"
#include "chunk.h"
#include "perlin.h"

void World::generate(time_t seed) {
    srand(seed);
    set_seed(seed);
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            addChunk({x,y});
        }
    }
}

void World::addChunk(vec2<int> pos) {
    std::cout << "New chunk at " << pos << std::endl;
    if (chunk_count < MAX_CHUNKS) {
        chunks[chunk_count].pos = pos;
        chunks[chunk_count].generate();
        chunk_count++;
    }
}

vec2<int> getChunkPos(vec2<int> pos) {
    return {(int)std::floor((pos.x / (float)CHUNK_SIZE)),
            (int)std::floor((pos.y / (float)CHUNK_SIZE))};
}

Chunk *World::getChunkAt(vec2<int> pos) {
    for (int i = 0; i < MAX_CHUNKS; i++) {
        if (chunks[i].pos == pos) {
            return &chunks[i];
        }
    }

    return nullptr;
}

// TODO: Lorsqu'un nouveau chunk est affiché à l'écran, s'il n'est pas généré, alors le générer, sinon juste l'activer
void World::update() {
    player.update();
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            vec2<int> offset = {x,y};
            vec2<int> chunkPos = getChunkPos(player.pos) + offset;
            if (getChunkAt(chunkPos) == nullptr) {
                addChunk(chunkPos);
            }
        }
    }
}

void World::render(SDL_Renderer *renderer, Camera &camera) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            vec2<int> offset = {x,y};
            vec2<int> chunkPos = getChunkPos(player.pos) + offset;
            getChunkAt(chunkPos)->render(renderer, camera);
        }
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
