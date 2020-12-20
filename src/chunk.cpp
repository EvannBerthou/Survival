#include <iostream>
#include "chunk.h"
#include "utils.h"

void Chunk::generate() {
    for (int y = 0; y < CHUNK_TILE_COUNT; y++) {
        for (int x = 0; x < CHUNK_TILE_COUNT; x++) {
            ground[x][y] = random(0,255);
        }
    }
}

inline int to_world(int x, int dx) {
    return (x * CHUNK_SIZE + TILE_SIZE / 2 + dx * TILE_SIZE);
}

void Chunk::render(SDL_Renderer *renderer, Camera &camera) {
    for (int y = 0; y < CHUNK_TILE_COUNT; y++) {
        for (int x = 0; x < CHUNK_TILE_COUNT; x++) {
            SDL_Rect rect = {to_world(pos.x, x), to_world(pos.y, y),
                             TILE_SIZE, TILE_SIZE};
            SDL_Color color = {0, (Uint8)ground[x][y], 0, 255};
            camera.render_to_cam(renderer, rect, color);
        }
    }

    SDL_Rect outline = {to_world(pos.x, 0) - TILE_SIZE / 2,
                        to_world(pos.y, 0) - TILE_SIZE / 2,
                        CHUNK_SIZE, CHUNK_SIZE};
    camera.render_draw_rect(renderer, outline, {255,255,255,255});
}
