//
//  Turn.h
//  scrabble
//
//  Created by Kaeleigh H on 10/19/17.
//  Copyright © 2017 Kaeleigh H. All rights reserved.
//

#ifndef Turn_h
#define Turn_h

#include <stdio.h>
#include "Board.h"
#include "Move.h"
#include "Path.h"


typedef struct _Turn_ {
    Move    *move;
} Turn;


/* Public Function Definitions */

void    turn_init(void);
void    turn_Play(Turn *turn, Board *board);
void    turn_destroy(void);


#endif /* Turn_h */
