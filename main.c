//
//  main.c
//

#include <stdio.h>
#include "Game.h"

int main(int argc, const char * argv[]) {
    Game *game = game_init();
    while(1) {
        PlayRound(game);
    }
    return 0;
}
