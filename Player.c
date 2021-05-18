//
//  Player.c
//  scrabble
//

#include "Player.h"


/* Private Function Definitions */

void 	GetLetters(Player *player, Bag *bag);
void    PlayBestMove(Player *player, Board *board, Bag *bag, char ***words, int values[128]);
Move*   GetBestMove(Player *player, Board *board, char ***words, int values[128]);
void 	PlayOpponentMove(Player *player, Board *board, Bag *bag, char ***words, int values[128]);
Move* 	GetOpponentMove(Player *player, Board *board, char ***words, int values[128]);
Square* GetOpponentSquare(Board *board);
char*   GetOpponentWord(void);
void 	GetOpponentLettersUsed(Player *player, Board *board, Path *path);
int 	OpponentMoveIsValid(Player *player, Path *path, Move *move, char ***words);
void 	RemovePlayedLetters(Player *player, Board *board, Move *move);
void 	RemoveNullLettersFromHand(Player *player);


/* Public Functions */

Player* player_init(char *name, Bag *bag) {
    Player *player = NULL;
    if((player = malloc(sizeof(Player))) == NULL) {
        return NULL;
    }
    player->name = name;
    player->points = 0;
	player->letters = NULL;
	if((player->letters = malloc(sizeof(char) * 8)) == NULL) {
		return NULL;
	}
	player->letters = bag_GetLetters(bag, 8);
    return player;
}


void player_Play(Player *player, Board *board, Bag *bag, char ***words, int values[128]) {
    if(strlen(player->letters) > 0) {
        PlayBestMove(player, board, bag, words, values);
    }
}


void player_OpponentPlay(Player *player, Board *board, Bag *bag, char ***words, int values[128]) {
	board_Print(board);
	if(strlen(player->letters) > 0) {
		PlayOpponentMove(player, board, bag, words, values);
	}
}


/* Private Functions */


void GetLetters(Player *player, Bag *bag) {
	int letters_needed = 8 - (int)strlen(player->letters);
	char *new_letters = bag_GetLetters(bag, letters_needed);
	if(new_letters) {
		strcat(player->letters, new_letters);
	}
}


/*
char* GetHand(void) {
    printf("\nPlease Enter Your Letters: \n");
    char* hand = NULL;
    hand = malloc(sizeof(char) * 10);
    fgets(hand, 10, stdin);
    char *end_of_input;
    if ((end_of_input = strchr(hand, '\n')) != NULL) {
        *end_of_input = '\0';
    }
    if(strlen(hand) > 8) {
        return GetHand();
    }
    return hand;
}
 */


void PlayBestMove(Player *player, Board *board, Bag *bag, char ***words, int values[128]) {
    printf("\nEvaluating Options...");
    clock_t start;
    clock_t end;
    double time_used;
    start = clock();
    Move *best_move = NULL;
    best_move = GetBestMove(player, board, words, values);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    if(best_move == NULL) {
        printf("No moves found.\n");
    }
    else {
		player->points += best_move->points;
		move_Print(best_move, time_used);
		RemovePlayedLetters(player, board, best_move);
		GetLetters(player, bag);
        board_Update(board, best_move);
        board_Print(board);
        best_move = NULL;
    }
    board_Reset(board);
}


Move* GetBestMove(Player *player, Board *board, char ***words, int values[128]) {
    printf("\nComputer's letters: %s", player->letters);
    Move *best_move = NULL;
    board_FindPaths(board, player->letters, 1);
    Node *path_node = NULL;
    path_node = board->paths->head;
    while(path_node) {
        Path *path = path_node->data;
        path_FindMoves(path, words, player->letters);
        Node *move_node = NULL;
        move_node = path->moves->head;
        while(move_node) {
            Move *move = move_node->data;
            move_GetPoints(move, values);
            if(best_move == NULL || move->points > best_move->points) {
                best_move = move;
            }
            move_node = move_node->next;
        }
        path_node = path_node->next;
    }
    return best_move;
}


void PlayOpponentMove(Player *player, Board *board, Bag *bag, char ***words, int values[128]) {
	Move *move = NULL;
	move = GetOpponentMove(player, board, words, values);
	player->points += move->points;
	RemovePlayedLetters(player, board, move);
	GetLetters(player, bag);
	board_Update(board, move);
	board_Reset(board);
	move = NULL;
}


Move* GetOpponentMove(Player *player, Board *board, char ***words, int values[128]) {
    printf("\nYour letters: %s", player->letters);
    printf("\nWhere Are You Playing?");
    printf("\nStarting Coordinate: ");
    Square *first = NULL;
    first = GetOpponentSquare(board);
    printf("Ending Coordinate: ");
    Square *last = NULL;
    last = GetOpponentSquare(board);
    
    List *squares = NULL;
    squares = list_init();
    int dx = last->x - first->x ? 1 : 0;
    int dy = !dx;
    int x = first->x;
    int y = first->y;
    while(x != last->x + dx || y != last->y + dy) {
        list_Push(squares, board->squares[x][y]);
        x += dx;
        y += dy;
    }
    
    char *word = NULL;
    word = GetOpponentWord();
    
    Path *path = NULL;
    path = path_init();
    path->squares = squares;
    path_SetDirection(path);
    GetOpponentLettersUsed(player, board, path);
    board_FindCrosspaths(board, path);
    
    Node *crosspath_node = path->crosspaths->head;
    while(crosspath_node) {
        Crosspath *crosspath = crosspath_node->data;
        printf("Crosspath: %s\n", crosspath->letters);
        crosspath_node = crosspath_node->next;
    }
    
    Move *move = NULL;
    move = move_init(word, path->used, path->squares);
	if(OpponentMoveIsValid(player, path, move, words)) {
		move_GetPoints(move, values);
        move_Print(move, 0);
	}
	else {
		printf("Invalid move. Please try again.");
		GetOpponentMove(player, board, words, values);
	}
    return move;
}


Square* GetOpponentSquare(Board *board) {
    int x = 0;
    int y = 0;
    Square *square  = NULL;
    char *input = NULL;
    input = malloc(sizeof(char) * 10);
    fgets(input, 10, stdin);
    char *end_of_input;
    if ((end_of_input = strchr(input, '\n')) != NULL) {
        *end_of_input = '\0';
    }
    int len_input = (int)strlen(input);
    if(len_input == 2) {
        x = input[0] - 'A';
        y = input[1] - '0' - 1;
    }
    else if(len_input == 3) {
        x = input[0] - 'A';
        y = (input[1] - '0') * 10 + input[2] - '0' - 1;
    }
    if(x >= 0 && x < 15 && y >= 0 && y < 15) {
        square = board->squares[x][y];
    }
    if(!square) {
        printf("\nPlease Enter a Coordinate in the Format A1, B2, etc: \n");
        free(input);
        GetOpponentSquare(board);
    }
    free(input);
    return square;
}


char* GetOpponentWord(void) {
    printf("What Word Are You Playing?\n");
    char *word = NULL;
    word = malloc(sizeof(char) * 16);
    fgets(word, 15, stdin);
    char *end_of_input;
    if ((end_of_input = strchr(word, '\n')) != NULL) {
        *end_of_input = '\0';
    }
    if(strlen(word) < 2) {
        printf("Please enter a word. \n");
        free(word);
        GetOpponentWord();
    }
    return word;
}


void GetOpponentLettersUsed(Player *player, Board *board, Path *path) {
    int i = 0;
    Node *node = path->squares->head;
    do {
        Square *square = node->data;
        if(board->squares[square->x][square->y]->letter != player->letters[i]) {
            path->used++;
        }
        i++;
    } while((node = node->next));
}


int OpponentMoveIsValid(Player *player, Path *path, Move *move, char ***words) {
	if(path_MatchWord(move->squares, move->word->letters, player->letters) &&
	   move_MatchCrosswords(move, path->crosspaths, words)) {
		return 1;
	}
	else {
		return 0;
	}
}


void RemovePlayedLetters(Player *player, Board *board, Move *move) {
	int i = 0;
	Node *node = move->squares->head;
	do {
		Square *square = node->data;
		char *letter = &move->word->letters[i];
		if(board->squares[square->x][square->y]->letter != *letter) {
            char *letter_used = NULL;
            letter_used = malloc(sizeof(char));
			letter_used = strchr(player->letters, *letter);
			if(letter_used == NULL) {
				letter_used = strchr(player->letters, '?');
			}
            printf("Used letter: %s\n", letter_used);
            *letter_used = '@';
		}
		i++;
	} while((node = node->next));
	RemoveNullLettersFromHand(player);
    printf("Letters in hand: %s\n", player->letters);
}


void RemoveNullLettersFromHand(Player *player) {
	char *new_letters = NULL;
	if((new_letters = malloc(sizeof(char) * 8)) == NULL) {
		return;
	}
	int i = 0;
	for(int j=0; j<8; j++) {
		if(player->letters[j] != '@') {
			new_letters[i] = player->letters[j];
			i++;
		}
	}
	memcpy(player->letters, new_letters, sizeof(char) * 8);
	free(new_letters);
	new_letters = NULL;
}
