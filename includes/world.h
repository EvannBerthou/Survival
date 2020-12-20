#pragma once

#include <SDL2/SDL.h>
#include "entity.h"
#include "camera.h"
#include "chunk.h"

#define MAX_WORLD_ENTITIES 100
#define MAX_CHUNKS 16

struct World {
    char *name;
    Entity player;
    Entity entities[MAX_WORLD_ENTITIES];
    Chunck chunks[MAX_CHUNKS];

    int entity_count = 1;

    void update();
    void render(SDL_Renderer *renderer, Camera &camera);

    void move_player(SDL_Keycode code);
    void stop_player(SDL_Keycode code);

    void generate(time_t seed);
};
