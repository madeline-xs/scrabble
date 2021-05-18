//
//  Square.h
//

#ifndef Square_h
#define Square_h

#include <stdio.h>
#include <stdlib.h>


typedef struct _Square_ {
    int     x;
    int     y;
    char    letter;
    int     letter_mult;
    int     word_mult;
} Square;


/* Public Function Definitions */

Square*   square_init(int x, int y);

#endif /* Square_h */
