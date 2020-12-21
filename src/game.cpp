#include "game.h"
#include "utils.h"
#include "world.h"

void Game::init() {
    sec(SDL_Init(SDL_INIT_VIDEO), "Error while initializing SDL");
    window = sec(SDL_CreateWindow("Survival", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                800, 600, SDL_WINDOW_SHOWN),
                "Error while creating window");
    renderer = sec(SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED),
                                "Error while creating renderer");

    sec(TTF_Init(), "Error while loading TTF");
    font = sec(TTF_OpenFont("assets/font.ttf", 38), "Error while loading font");

    world = {};
    world.player = {{0, 150}, {0,0}, {255,0,0,255}};
    world.entities[0] = {{0, 0}, {0,0}, {255,255,0,255}};
    world.generate(0);
}

void Game::run() {
    SDL_Event ev;
    while(running) {
        event(&ev);
        update();
        render();
    }
}

void Game::event(SDL_Event *event) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
        case SDL_QUIT:
            this->running = false;
            break;
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_TAB) {
                debug = !debug;
            }
            else {
                world.move_player(event->key.keysym.sym);
            }
            break;
        case SDL_KEYUP:
            world.stop_player(event->key.keysym.sym);
            break;
        }
    }
}

void Game::update() {
    world.update();
    camera.center_on(world.player.pos);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    world.render(renderer, camera);

    if (debug) {
        render_debug();
    }

    SDL_RenderPresent(renderer);
}

void Game::render_debug() {
    for (int i = 0; i < world.chunk_count; i++) {
        Chunk *c = &world.chunks[i];
        vec2i pos = chunk_to_world(c->pos);
        for (int y = 0; y < CHUNK_TILE_COUNT; y++) {
            for (int x = 0; x < CHUNK_TILE_COUNT; x++) {
                SDL_Rect rect = Rect(pos + to_world(vec2i(x,y)), TILE_SIZE).to_sdl();
                camera.render_draw_rect(renderer, rect, {255,255,255,255});
            }
        }
        SDL_Rect outline = Rect(pos, CHUNK_SIZE).to_sdl();
        camera.render_draw_rect(renderer, outline, {255,0,0,255});
    }


    Entity &player = world.player;
    render_text(renderer, font,
            "Player : " + player.pos.to_str() +
                "(" + screenToGrid(world.player.pos).to_str() + ")",
            vec2i(0,0), {255,128,128,255});

    render_text(renderer, font,
            "Chunk : " + getChunkPos(screenToGrid(player.pos)).to_str() +
                "(" + posInChunk(screenToGrid(player.pos)).to_str() + ")",
            vec2i(0,40), {255,128,128,255});

    render_text(renderer, font,
            "Vel : " + player.vel.to_str(),
            vec2i(0,80), {255,128,128,255});
}

void Game::close() {
    std::cout << "Closing game" << std::endl;
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
