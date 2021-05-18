//
//  Player.h
//  scrabble
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <time.h>
#include "Board.h"
#include "Move.h"
#include "Path.h"
#include "Bag.h"


typedef struct _Player_ {
    char	*name;
	char	*letters;
    int 	points;
} Player;


/* Public Function Definitions */

Player*     player_init(char *name, Bag *bag);
void        player_Play(Player *player, Board *board, Bag *bag, char ***words, int values[128]);
void        player_OpponentPlay(Player *player, Board *board, Bag *bag, char ***words, int values[128]);
void        player_destroy(Player *player);

#endif /* Player_h */
