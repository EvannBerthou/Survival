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

Tile *World::getTileAt(vec2<int> pos) {
    Chunk *chunk = getChunkAt(getChunkPos(pos));
    int x = pos.x % CHUNK_TILE_COUNT;
    int y = pos.y % CHUNK_TILE_COUNT;
    return &chunk->ground[x][y];
}

void World::update() {
    player.update(this);
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


    vec2<int> p = {player.pos.x / TILE_SIZE, player.pos.y / TILE_SIZE};
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            vec2<int> offset = {x,y};
            auto tile_pos = p + offset;
            std::cout << p << tile_pos << std::endl;
            SDL_Rect tile_rect = {tile_pos.x * TILE_SIZE + TILE_SIZE / 2, tile_pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE};
            camera.render_to_cam(renderer, tile_rect, {255,0,255,255});
            if (rect_collide(player.to_rect(), tile_rect)) {
                camera.render_to_cam(renderer, tile_rect, {255,255,0,255});
            }
        }
    }

    camera.render_to_cam(renderer, player.to_rect(), player.color);
    camera.render_draw_rect(renderer, player.to_rect(), {255,255,255,255});
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
    vec2<int> p = {rect.x / TILE_SIZE, rect.y / TILE_SIZE};
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            vec2<int> offset = {x,y};
            auto tile_pos = p + offset;
            SDL_Rect tile_rect = {tile_pos.x * TILE_SIZE + TILE_SIZE / 2, tile_pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE};
            if (rect_collide(rect, tile_rect) && getTileAt(tile_pos)->collide) {
                return true;
            }
        }
    }
    return false;
}
