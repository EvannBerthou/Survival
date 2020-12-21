#pragma once

#include <SDL2/SDL.h>
#include "camera.h"
#include "entity.h"
#include "chunk.h"
#include "utils.h"

#define MAX_WORLD_ENTITIES 100
#define MAX_CHUNKS 1024

struct Entity;
struct World {
    char *name;
    Entity player;
    Entity entities[MAX_WORLD_ENTITIES];
    Chunk chunks[MAX_CHUNKS];

    int entity_count = 0;
    int chunk_count  = 0;

    void update();
    void render(SDL_Renderer *renderer, Camera &camera);

    void move_player();

    void generate(time_t seed);
    void addChunk(vec2i pos);
    Chunk *getChunkAt(vec2i pos);
    Tile *getTileAt(vec2i pos);

    Maybe<vec2i> check_collision(SDL_Rect rect);
};


