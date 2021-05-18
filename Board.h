//
//  Board.h
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include "List.h"
#include "Path.h"
#include "Square.h"


typedef struct _Board_ {
    Square*   squares[15][15];
    List*   paths;
} Board;


/* Public Function Definitions */

Board*  board_init(void);
void    board_FindPaths(Board *board, char *hand, int dx);
void    board_FindCrosspaths(Board *board, Path *path);
void    board_Print(Board *board);
void    board_Reset(Board *board);
void    board_Update(Board *board, Move *move);
void    board_destroy(Board *board);


#endif /* Board_h */
