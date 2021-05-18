//
//  Bag.c
//  scrabble
//

#include "Bag.h"


/* Public Functions */

Bag* bag_init() {
	Bag *bag = NULL;
	if((bag = malloc(sizeof(Bag))) == NULL) {
		return NULL;
	}
	bag->letters = NULL;
	bag->letters = list_init();
    for(int i=0; i<8; i++) { list_Push(bag->letters, "A"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "B"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "C"); }
    for(int i=0; i<3; i++) { list_Push(bag->letters, "D"); }
    for(int i=0; i<11; i++) { list_Push(bag->letters, "E"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "F"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "G"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "H"); }
    for(int i=0; i<8; i++) { list_Push(bag->letters, "I"); }
    for(int i=0; i<1; i++) { list_Push(bag->letters, "J"); }
    for(int i=0; i<1; i++) { list_Push(bag->letters, "K"); }
    for(int i=0; i<3; i++) { list_Push(bag->letters, "L"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "M"); }
    for(int i=0; i<5; i++) { list_Push(bag->letters, "N"); }
    for(int i=0; i<7; i++) { list_Push(bag->letters, "O"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "P"); }
    for(int i=0; i<1; i++) { list_Push(bag->letters, "Q"); }
    for(int i=0; i<5; i++) { list_Push(bag->letters, "R"); }
    for(int i=0; i<3; i++) { list_Push(bag->letters, "S"); }
    for(int i=0; i<5; i++) { list_Push(bag->letters, "T"); }
    for(int i=0; i<3; i++) { list_Push(bag->letters, "U"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "V"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "W"); }
    for(int i=0; i<1; i++) { list_Push(bag->letters, "X"); }
    for(int i=0; i<3; i++) { list_Push(bag->letters, "Y"); }
    for(int i=0; i<1; i++) { list_Push(bag->letters, "Z"); }
    for(int i=0; i<2; i++) { list_Push(bag->letters, "?"); }
	return bag;
}


char* bag_GetLetters(Bag *bag, int number) {
    printf("%i letters in the bag: \n", bag->letters->size);
    Node *bag_letters_node = NULL;
    bag_letters_node = bag->letters->head;
    while(bag_letters_node) {
        printf("%s", bag_letters_node->data);
        bag_letters_node = bag_letters_node->next;
    }
    printf("\n");
	char *letters = NULL;
	if((letters = malloc(sizeof(char) + sizeof(char) * number)) == NULL) {
		return NULL;
	}
    letters[0 + number] = '\0';
	for(int i=0; i<number && bag->letters->size > 0; i++) {
		int index = (rand() % bag->letters->size);
		Node *letter_node = NULL;
		letter_node = list_At(bag->letters, index);
		if(letter_node) {
			char *letter = letter_node->data;
			memcpy(&letters[i], letter, sizeof(char));
			list_Remove(bag->letters, index);
		}
	}
	if(letters) {
		return letters;
	}
	else {
		free(letters);
		return NULL;
	}
}


void bag_destroy(Bag *bag) {
	list_destroy(bag->letters);
	bag->letters = NULL;
	free(bag);
	bag = NULL;
}
