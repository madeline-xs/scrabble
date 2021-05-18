//
//  Bag.h
//  scrabble
//

#ifndef Bag_h
#define Bag_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"


typedef struct _Bag_ {
	List	*letters;
} Bag;


/* Public Function Definitions */

Bag*	bag_init(void);
char* 	bag_GetLetters(Bag *bag, int number);
void 	bag_destroy(Bag *bag);


#endif /* Bag_h */
