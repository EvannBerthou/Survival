#include "game.h"
#include "utils.h"

void Game::init() {
    sec(SDL_Init(SDL_INIT_VIDEO), "Error while initializing SDL");
    window = sec(SDL_CreateWindow("Survival", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                800, 600, SDL_WINDOW_SHOWN),
                "Error while creating window");
    SDL_Renderer *renderer = sec(SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED),
                                "Error while creating renderer");
    (void) renderer;
}

void Game::run() {
    SDL_Event event;
    bool running = true;
    while(running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: running = false; break;
            }
        }
    }
}


void Game::close() {
    std::cout << "Closing game" << std::endl;
    free(window);
}
