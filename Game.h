//
//  Game.h
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <time.h>
#include "Board.h"
#include "List.h"
#include "Move.h"
#include "Path.h"
#include "Player.h"
#include "Bag.h"

typedef struct _Game_ {
	Board	*board;
	Bag		*bag;
	Player	*player1;
	Player	*player2;
	char	***words;
    int     values[128];
} Game;

Game	*game_init(void);
void    PlayRound(Game *game);

#endif /* Game_h */
