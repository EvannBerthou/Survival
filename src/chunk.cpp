#include <iostream>
#include "chunk.h"
#include "utils.h"

void Chunck::generate() {
    for (int y = 0; y < CHUNCK_SIZE; y++) {
        for (int x = 0; x < CHUNCK_SIZE; x++) {
            ground[x][y] = random(0,255);
        }
    }
}

inline int to_world(int x, int dx) {
    return (x * CHUNCK_SIZE * TILE_SIZE + TILE_SIZE / 2 + dx * TILE_SIZE);
}

void Chunck::render(SDL_Renderer *renderer, Camera &camera) {
    for (int y = 0; y < CHUNCK_SIZE; y++) {
        for (int x = 0; x < CHUNCK_SIZE; x++) {
            SDL_Rect rect = {to_world(pos.x, x), to_world(pos.y, y),
                             TILE_SIZE, TILE_SIZE};
            SDL_Color color = {0, (Uint8)ground[x][y], 0, 255};
            camera.render_to_cam(renderer, rect, color);
        }
    }

    SDL_Rect outline = {to_world(pos.x, 0) - TILE_SIZE / 2,
                        to_world(pos.y, 0) - TILE_SIZE / 2,
                        TILE_SIZE * CHUNCK_SIZE, TILE_SIZE * CHUNCK_SIZE};
    camera.render_draw_rect(renderer, outline, {255,255,255,255});
}
