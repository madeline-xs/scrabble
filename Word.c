//
//  Word.c
//

#include "Word.h"


/* Private Function Definitions */

void AddLetterPoints(Word *word, char letter, Square *square, int values[128]);


/* Public Functions */

Word* word_init(char *letters, List *squares) {
    Word *word = NULL;
    word = malloc(sizeof(Word));
    if(word == NULL) {
        return NULL;
    }
    word->letters = letters;
    word->mult = 1;
    word->points = 0;
    word->squares = squares;
    return word;
}


int word_GetPoints(Word *word, int values[128]) {
    Node *square_node = NULL;
    square_node = word->squares->head;
    int i = 0;
    do {
        Square *square = NULL;
        square = square_node->data;
        AddLetterPoints(word, word->letters[i], square, values);
        i++;
    } while((square_node = square_node->next));
    word->points *= word->mult;
    return word->points;
}


void word_destroy(Word *word) {
    free(word->letters);
    word->squares = NULL;
    free(word);
}


/* Private Functions */

void AddLetterPoints(Word *word, char letter, Square *square, int values[128]) {
    int points;
    points = values[letter];
    if(letter != square->letter) {
        points *= square->letter_mult;
        word->mult *= square->word_mult;
    }
    word->points += points;
}
