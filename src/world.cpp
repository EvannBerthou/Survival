#include <iostream>
#include <time.h>
#include <cmath>
#include <stdlib.h>
#include "world.h"
#include "chunk.h"
#include "perlin.h"
#include "utils.h"

void World::generate(time_t seed) {
    srand(seed);
    set_seed(seed);
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            addChunk({x,y});
        }
    }
}

void World::addChunk(vec2i pos) {
    std::cout << "New chunk at " << pos << std::endl;
    if (chunk_count < MAX_CHUNKS) {
        chunks[chunk_count].pos = pos;
        chunks[chunk_count].generate();
        chunk_count++;
    }
}

Chunk *World::getChunkAt(vec2i pos) {
    for (int i = 0; i < MAX_CHUNKS; i++) {
        if (chunks[i].pos == pos) {
            return &chunks[i];
        }
    }

    return nullptr;
}

Tile *World::getTileAt(vec2i pos) {
    Chunk *chunk = getChunkAt(getChunkPos(pos));
    vec2i v = posInChunk(pos);
    return &chunk->ground[v.x][v.y];
}

void World::update() {
    player.update(this);
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            auto chunkPos = getChunkPos(screenToGrid(player.pos)) + vec2i(x,y);
            if (getChunkAt(chunkPos) == nullptr) {
                addChunk(chunkPos);
            }
        }
    }
}

void World::render(SDL_Renderer *renderer, Camera &camera) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            auto chunkPos = getChunkPos(screenToGrid(player.pos)) + vec2i(x,y);
            getChunkAt(chunkPos)->render(renderer, camera);
        }
    }

    for (int i = 0; i < entity_count; i++) {
        entities[i].render(renderer, camera);
    }
    player.render(renderer, camera);
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

// Returns true if there is a collision otherwise returns false
bool World::check_collision(SDL_Rect rect) {
    vec2i p = screenToGrid(vec2i(rect.x, rect.y));
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            auto tile_pos = p + vec2i(x,y);
            Rect r(tile_pos * TILE_SIZE, TILE_SIZE);
            if (rect_collide(rect, r.to_sdl()) && getTileAt(tile_pos)->collide) {
                return true;
            }
        }
    }
    return false;
}
