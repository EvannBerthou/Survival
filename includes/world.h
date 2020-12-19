#pragma once

#include <SDL2/SDL.h>
#include "entity.h"

#define MAX_WORLD_ENTITIES 100

struct World {
    char *name;
    Entity player;
    Entity entities[MAX_WORLD_ENTITIES];
    int entity_count = 1;

    void update();
    void render(SDL_Renderer *renderer);

    void move_player(SDL_Keycode code);
    void stop_player(SDL_Keycode code);
};
