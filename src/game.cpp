#include "game.h"
#include "utils.h"

void Game::init() {
    sec(SDL_Init(SDL_INIT_VIDEO), "Error while initializing SDL");
    window = sec(SDL_CreateWindow("Survival", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                800, 600, SDL_WINDOW_SHOWN),
                "Error while creating window");
    renderer = sec(SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED),
                                "Error while creating renderer");
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
        case SDL_QUIT: running = false; break;
        }
    }
}

void Game::update() {
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}


void Game::close() {
    free(window);
    SDL_Quit();
    std::cout << "Closing game" << std::endl;
}
