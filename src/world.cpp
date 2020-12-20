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

void World::addChunk(vec2i pos) {
    std::cout << "New chunk at " << pos << std::endl;
    if (chunk_count < MAX_CHUNKS) {
        chunks[chunk_count].pos = pos;
        chunks[chunk_count].generate();
        chunk_count++;
    }
}

vec2i getChunkPos(vec2i pos) {
    return {(int)std::floor(pos.x / (float)CHUNK_TILE_COUNT), (int)std::floor(pos.y / (float)CHUNK_TILE_COUNT)};
}

vec2i screenToGrid(vec2i screen) {
    return {(int)std::floor(screen.x / (float)TILE_SIZE), (int)std::floor(screen.y / (float)TILE_SIZE)};
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
    int x = pos.x;
    int y = pos.y;

    if (pos.x < 0) {
        x = CHUNK_TILE_COUNT - ((-pos.x) % CHUNK_TILE_COUNT);
    }

    if (pos.y < 0) {
        y = CHUNK_TILE_COUNT - ((-pos.y) % CHUNK_TILE_COUNT);
    }

    x %= CHUNK_TILE_COUNT;
    y %= CHUNK_TILE_COUNT;

    return &chunk->ground[x][y];
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

void World::render(SDL_Renderer *renderer, Camera &camera, bool debug) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            auto chunkPos = getChunkPos(screenToGrid(player.pos)) + vec2i(x,y);
            getChunkAt(chunkPos)->render(renderer, camera, debug);
        }
    }

    for (int i = 0; i < entity_count; i++) {
        camera.render_to_cam(renderer, entities[i].to_rect(), entities[i].color);
    }


    camera.render_to_cam(renderer, player.to_rect(), player.color);
    if (debug) {
        vec2i p((player.pos.x / TILE_SIZE), (player.pos.y / TILE_SIZE));
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                auto tile_pos = p + vec2i(x,y);
                SDL_Rect tile_rect = {tile_pos.x * TILE_SIZE, tile_pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                camera.render_to_cam(renderer, tile_rect, {255,0,255,255});
                if (rect_collide(player.to_rect(), tile_rect)) {
                    camera.render_to_cam(renderer, tile_rect, {255,255,0,255});
                }
            }
        }

        camera.render_draw_rect(renderer, player.to_rect(), {255,255,255,255});
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

// Returns true if there is a collision otherwise returns false
bool World::check_collision(SDL_Rect rect) {
    vec2i p = screenToGrid(vec2i(rect.x, rect.y));
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            auto tile_pos = p + vec2i(x,y);
            SDL_Rect tile_rect = {tile_pos.x * TILE_SIZE, tile_pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (rect_collide(rect, tile_rect) && getTileAt(tile_pos)->collide) {
                return true;
            }
        }
    }
    return false;
}
