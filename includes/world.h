#pragma once

#include <SDL2/SDL.h>
#include "entity.h"
#include "camera.h"
#include "chunk.h"

#define MAX_WORLD_ENTITIES 100
#define MAX_CHUNKS 1024

struct World {
    char *name;
    Entity player;
    Entity entities[MAX_WORLD_ENTITIES];
    Chunk chunks[MAX_CHUNKS];

    int entity_count = 1;
    int chunk_count  = 0;

    void update();
    void render(SDL_Renderer *renderer, Camera &camera);

    void move_player(SDL_Keycode code);
    void stop_player(SDL_Keycode code);

    void generate(time_t seed);
    void addChunk(vec2<int> pos);
    Chunk *getChunkAt(vec2<int> pos);
};
