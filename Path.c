//
//  Path.c
//

#include "Path.h"


/* Private Function Definitions*/

int     AddLettersToWord(char *word, List *squares, char *match, char *available);
int     AddLetterToWord(char *word, int index, Square *square, char needed, char *available);
char*   GetAvailableLetters(char *hand);char*   path_MatchWord(List *squares, char *match, char *hand);
void    RemoveFromString(char *str, char *chr);


/* Public Functions */

Path* path_init() {
    Path *path;
    path = malloc(sizeof(Path));
    if(path == NULL) {
        return NULL;
    }
    path->crosspaths = list_init();
    path->moves = list_init();
    path->squares = list_init();
    path->used = 0;
    return path;
}


int path_AddSquare(Path *path, Square *square, char *hand) {
    path->used += square->letter == '_';
    if(path->used > strlen(hand)) {
        return 0;
    }
    list_Push(path->squares, square);
    return 1;
}


void path_Copy(Path *dst, Path *src) {
    dst->dx = src->dx;
    dst->dy = src->dy;
    dst->used = src->used;
    list_Copy(dst->squares, src->squares);
}


void path_FindMoves(Path *path, char ***words, char *hand) {
    int size = path->squares->size;
    int i = 0;
    while(words[size][i]) {
        char *word = NULL;
        if((word = path_MatchWord(path->squares, words[size][i], hand))) {
            Move *move = NULL;
            move = move_init(word, path->used, path->squares);
            if(move_MatchCrosswords(move, path->crosspaths, words)) {
                list_Push(path->moves, move);
            }
        }
        i++;
    }
}


void path_destroy(Path *path) {
    Node *move_node = NULL;
    move_node = path->moves->head;
    while(move_node) {
        Move *move = move_node->data;
        move_destroy(move);
        move_node = move_node->next;
    }
    list_destroy(path->moves);
    path->moves = NULL;
    Node *crosspath_node = NULL;
    crosspath_node = path->crosspaths->head;
    while(crosspath_node) {
        Crosspath *crosspath = crosspath_node->data;
        crosspath_destroy(crosspath);
        crosspath_node = crosspath_node->next;
    }
    list_destroy(path->crosspaths);
    path->crosspaths = NULL;
    list_destroy(path->squares);
    path->squares = NULL;
    free(path);
}


char* path_MatchWord(List *squares, char *match, char *hand) {
	char *word = NULL;
	word = malloc(sizeof(char) * (squares->size + 1));
	if(word == NULL) {
		exit(-1);
	}
	char *available = NULL;
	available = GetAvailableLetters(hand);
	if(AddLettersToWord(word, squares, match, available)) {
		free(available);
		return word;
	}
	else {
		free(available);
		free(word);
		return NULL;
	}
}


void path_SetDirection(Path *path) {
    if(path->squares == NULL || path->squares->size < 1) {
        return;
    }
    Node *first = path->squares->head;
    Node *second = first->next;
    if(second) {
        Square *firstSquare = first->data;
        Square *secondSquare = second->data;
        if(secondSquare->x > firstSquare->x) {
            path->dx = 1;
            path->dy = 0;
        }
        else {
            path->dx = 0;
            path->dy = 1;
        }
    }
    else {
        path->dx = 1;
        path->dy = 0;
    }
}


/* Private Functions */


char* GetAvailableLetters(char *hand) {
    char *available = NULL;
    available = malloc((strlen(hand) + 1) * sizeof(char));
    if(available == NULL) {
        return NULL;
    }
    memcpy(available, hand, (strlen(hand) + 1) * sizeof(char));
    available[strlen(hand)] = '\0';
    return available;
}


int AddLettersToWord(char *word, List *squares, char *match, char *available) {
    int i =0;
    Node *square_node = NULL;
    square_node = squares->head;
    do {
        Square *square = NULL;
        square = square_node->data;
        if(!AddLetterToWord(word, i, square, match[i], available)) {
            return 0;
        }
        i++;
    } while((square_node = square_node->next));
    word[i] = '\0';
    return 1;
}


int AddLetterToWord(char *word, int index, Square *square, char needed, char *available) {
    if(square->letter == needed) {
        word[index] = needed;
        return 1;
    }
    else if(square->letter == '_') {
        char *use = strchr(available, needed);
        use = use ? use : strchr(available, '?');
        if(use) {
            word[index] = *use == '?' ? tolower(needed) : needed;
            RemoveFromString(available, use);
            return 1;
        }
    }
    return 0;
}


void RemoveFromString(char *str, char *chr) {
    if(!chr) {
        return;
    }
    int index = (int)(&chr[0] - &str[0]) / sizeof(char);
    memcpy(&str[index], &str[index + 1], strlen(str) - index);
}
