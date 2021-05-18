//
//  Path.h
//

#ifndef Path_h
#define Path_h

#include <stdio.h>
#include <ctype.h>
#include "Crosspath.h"
#include "List.h"
#include "Move.h"
#include "Square.h"


typedef struct _Path_ {
    List    *crosspaths;
    int     dx;
    int     dy;
    List    *moves;
    List    *squares;
    int     used;
} Path;


/* Public Function Definitions */

Path*   path_init(void);
int     path_AddSquare(Path *path, Square *square, char *hand);
void    path_Copy(Path *dst, Path *src);
void    path_FindMoves(Path *path, char ***words, char *hand);
char*   path_MatchWord(List *squares, char *match, char *hand);
void    path_SetDirection(Path *path);
void    path_destroy(Path *path);


#endif /* Path_h */
