#include <iostream>
#include "chunk.h"
#include "utils.h"
#include "perlin.h"
#include "tile.h"

bool valid_water(vec2i pos) {
    int n = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (perlin2d(pos.x + x, pos.y + y, 0.05, 4) <= 0.3) {
                if (n++ == 3) {
                    return true;
                }
            }
        }
    }
    return false;
}

Tile tile_from_grey(vec2i pos, double grey) {
    // Eau et seulement si l'eau a 3 autres cellules d'eau autour (permet d'éviter les minis point d'eau d'une 1 ou 2 cases
    if (grey <= 0.3 && valid_water(pos)) {
        return {{0, 0, (Uint8)(255 - grey * 200), 255}, 1};
    }

    // Dessine du sable uniquement si de l'eau est autour
    if (grey <= 0.37) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                vec2i tile_pos = {pos.x + x, pos.y + y};
                double grey = perlin2d(tile_pos.x, tile_pos.y, 0.05, 4);
                if (grey <= 0.3 && valid_water(tile_pos)) {
                    return {{200, 200, 0, 255}, 0};
                }
            }
        }
    }

    // Herbe
    return {{0, (Uint8)(grey * 255), 0, 255}, 0};
}

void Chunk::generate() {
    for (int y = 0; y < CHUNK_TILE_COUNT; y++) {
        for (int x = 0; x < CHUNK_TILE_COUNT; x++) {
            vec2i tile_pos = {pos.x * CHUNK_TILE_COUNT + x, pos.y * CHUNK_TILE_COUNT + y};
            double grey = perlin2d(tile_pos.x, tile_pos.y, 0.05, 4);
            ground[x][y] = tile_from_grey(tile_pos, grey);
        }
    }
}

void Chunk::render(SDL_Renderer *renderer, Camera &camera) {
    for (int y = 0; y < CHUNK_TILE_COUNT; y++) {
        for (int x = 0; x < CHUNK_TILE_COUNT; x++) {
            SDL_Rect rect = Rect(chunk_to_world(pos) + to_world(vec2i(x,y)), TILE_SIZE).to_sdl();
            camera.render_to_cam(renderer, rect, ground[x][y].color);
        }
    }
}
