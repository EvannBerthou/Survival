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
    world = {};
    world.player = {{20, 20}, {0,0}, {255,0,0,255}};
    world.entities[0] = {{0, 0}, {0,0}, {255,255,0,255}};
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
            world.move_player(event->key.keysym.sym);
            break;
        case SDL_KEYUP:
            world.stop_player(event->key.keysym.sym);
            break;
        }
    }
}

void Game::update() {
    world.update();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    world.render(renderer);

    SDL_RenderPresent(renderer);
}


void Game::close() {
    std::cout << "Closing game" << std::endl;
    SDL_Quit();
}
