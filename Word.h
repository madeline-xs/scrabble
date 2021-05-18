//
//  Word.h
//

#ifndef Word_h
#define Word_h

#include <stdio.h>
#include "List.h"
#include "Square.h"


typedef struct _Word_ {
    char    *letters;
    int     mult;
    int     points;
    List    *squares;
} Word;


/* Public Function Definitions */

Word*   word_init(char *letters, List *squares);
int     word_GetPoints(Word *word, int values[128]);
void    word_destroy(Word *word);


#endif /* Word_h */
