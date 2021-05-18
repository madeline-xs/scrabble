//
//  Square.c
//

#include "Square.h"


/* Public Functions */

Square* square_init(int x, int y) {
    Square *square = NULL;
    square = malloc(sizeof(Square));
    if(square == NULL) {
        return NULL;
    }
    square->x = x;
    square->y = y;
    square->letter = '_';
    square->letter_mult = 1;
    square->word_mult = 1;
    return square;
}
