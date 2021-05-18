//
//  Crosspath.c
//

#include "Crosspath.h"


/* Public Functions */

Crosspath* crosspath_init(int intersection) {
    Crosspath *crosspath;
    crosspath = malloc(sizeof(Crosspath));
    if(crosspath == NULL) {
        return NULL;
    }
    crosspath->intersection = intersection;
    crosspath->letters = malloc(sizeof(char) * 16);
    crosspath->squares = list_init();
    return crosspath;
}


void crosspath_GetLetters(Crosspath *crosspath) {
    Node *node = crosspath->squares->head;
    int i = 0;
    do {
        Square *square = node->data;
        crosspath->letters[i] = square->letter;
        i++;
    } while((node = node->next));
    crosspath->letters[i] = '\0';
}


void crosspath_destroy(Crosspath *crosspath) {
    free(crosspath->letters);
    list_destroy(crosspath->squares);
    free(crosspath);
}
