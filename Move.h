//
//  Move.h
//

#ifndef Move_h
#define Move_h

#include <stdio.h>
#include "Crosspath.h"
#include "List.h"
#include "Square.h"
#include "Word.h"


typedef struct _Move_ {
    List    *crosswords;
    int     points;
    List    *squares;
    int     used;
    Word    *word;
} Move;


/* Public Function Definitions */

Move*   move_init(char *letters, int used, List *squares);
int     move_GetPoints(Move *move, int values[128]);
int     move_MatchCrosswords(Move *move, List *crosspaths, char ***words);
void    move_Print(Move *move, double time_used);
void    move_destroy(Move *move);


#endif /* Move_h */
