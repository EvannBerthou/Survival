#include <iostream>
#include "chunk.h"
#include "utils.h"
#include "perlin.h"

bool valid_water(vec2<int> pos) {
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

SDL_Color color_from_grey(vec2<int> pos, double grey) {
    // Eau et seulement si l'eau a 3 autres cellules d'eau autour (permet d'éviter les minis point d'eau d'une 1 ou 2 cases
    if (grey <= 0.3 && valid_water(pos)) {
        return {0, 0, (Uint8)(255 - grey * 200), 255};
    }

    // Dessine du sable uniquement si de l'eau est autour
    if (grey <= 0.37) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                vec2<int> tile_pos = {pos.x + x, pos.y + y};
                double grey = perlin2d(tile_pos.x, tile_pos.y, 0.05, 4);
                if (grey <= 0.3 && valid_water(tile_pos)) {
                    return {255, 255, 0, 255};
                }
            }
        }
    }

    // Herbe
    return {0, (Uint8)(grey * 255), 0, 255};
}

void Chunk::generate() {
    for (int y = 0; y < CHUNK_TILE_COUNT; y++) {
        for (int x = 0; x < CHUNK_TILE_COUNT; x++) {
            vec2<int> tile_pos = {pos.x * CHUNK_TILE_COUNT + x, pos.y * CHUNK_TILE_COUNT + y};
            double grey = perlin2d(tile_pos.x, tile_pos.y, 0.05, 4);
            ground[x][y] = color_from_grey(tile_pos, grey);
        }
    }
}

inline int to_world(int x, int dx) {
    return (x * CHUNK_SIZE + TILE_SIZE / 2 + dx * TILE_SIZE);
}

void Chunk::render(SDL_Renderer *renderer, Camera &camera) {
    for (int y = 0; y < CHUNK_TILE_COUNT; y++) {
        for (int x = 0; x < CHUNK_TILE_COUNT; x++) {
            SDL_Rect rect = {to_world(pos.x, x), to_world(pos.y, y), TILE_SIZE, TILE_SIZE};
            camera.render_to_cam(renderer, rect, ground[x][y]);
        }
    }

    SDL_Rect outline = {to_world(pos.x, 0) - TILE_SIZE / 2,
                        to_world(pos.y, 0) - TILE_SIZE / 2,
                        CHUNK_SIZE, CHUNK_SIZE};
    camera.render_draw_rect(renderer, outline, {255,255,255,255});
}
