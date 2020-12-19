#include <iostream>
#include "game.h"

int main() {
    Game game = {};
    game.init();
    game.run();
    game.close();
}
