//
//  Game.c
//

#include "Game.h"


/* Private Function Definitions */

char*   GetName(void);
Move*   GetBestMove(Board *board, char *hand, char ***words, int values[128]);
char*   GetHand(void);
void    PlayTurn(Board *board, char *hand, char ***words, int values[128]);
void    PlayOpponentTurn(Board *board);
Move    *GetOpponentMove(Board *board);
Square* GetOpponentSquare(Board *board);
char*   GetOpponentWord(void);
void    PrintResult(Move *move, double time_used);
char*** ReadDictionary(void);


/* Public Functions */


Game *game_init() {
	Game *game = NULL;
	if((game = malloc(sizeof(Game))) == NULL) {
		return NULL;
	}
	game->board = NULL;
	game->board = board_init();
	game->bag = NULL;
	game->bag = bag_init();
	game->player1 = NULL;
	game->player1 = player_init("Computer", game->bag);
	game->player2 = NULL;
	game->player2 = player_init(GetName(), game->bag);
	game->words = NULL;
	game->words = ReadDictionary();
    game->values[0] = 0;
    game->values[1] = 0;
    game->values[2] = 0;
    game->values[3] = 0;
    game->values[4] = 0;
    game->values[5] = 0;
    game->values[6] = 0;
    game->values[7] = 0;
    game->values[8] = 0;
    game->values[9] = 0;
    game->values[10] = 0;
    game->values[11] = 0;
    game->values[12] = 0;
    game->values[13] = 0;
    game->values[14] = 0;
    game->values[15] = 0;
    game->values[16] = 0;
    game->values[17] = 0;
    game->values[18] = 0;
    game->values[19] = 0;
    game->values[20] = 0;
    game->values[21] = 0;
    game->values[22] = 0;
    game->values[23] = 0;
    game->values[24] = 0;
    game->values[25] = 0;
    game->values[26] = 0;
    game->values[27] = 0;
    game->values[28] = 0;
    game->values[29] = 0;
    game->values[30] = 0;
    game->values[31] = 0;
    game->values[32] = 0;
    game->values[33] = 0;
    game->values[34] = 0;
    game->values[35] = 0;
    game->values[36] = 0;
    game->values[37] = 0;
    game->values[38] = 0;
    game->values[39] = 0;
    game->values[40] = 0;
    game->values[41] = 0;
    game->values[42] = 0;
    game->values[43] = 0;
    game->values[44] = 0;
    game->values[45] = 0;
    game->values[46] = 0;
    game->values[47] = 0;
    game->values[48] = 0;
    game->values[49] = 0;
    game->values[50] = 0;
    game->values[51] = 0;
    game->values[52] = 0;
    game->values[53] = 0;
    game->values[54] = 0;
    game->values[55] = 0;
    game->values[56] = 0;
    game->values[57] = 0;
    game->values[58] = 0;
    game->values[59] = 0;
    game->values[60] = 0;
    game->values[61] = 0;
    game->values[62] = 0;
    game->values[63] = 0;
    game->values[64] = 0;
    game->values[65] = 1;
    game->values[66] = 4;
    game->values[67] = 4;
    game->values[68] = 2;
    game->values[69] = 1;
    game->values[70] = 5;
    game->values[71] = 2;
    game->values[72] = 5;
    game->values[73] = 1;
    game->values[74] = 8;
    game->values[75] = 6;
    game->values[76] = 1;
    game->values[77] = 4;
    game->values[78] = 1;
    game->values[79] = 1;
    game->values[80] = 4;
    game->values[81] = 12;
    game->values[82] = 1;
    game->values[83] = 1;
    game->values[84] = 2;
    game->values[85] = 1;
    game->values[86] = 5;
    game->values[87] = 5;
    game->values[88] = 8;
    game->values[89] = 5;
    game->values[90] = 12;
    game->values[91] = 0;
    game->values[92] = 0;
    game->values[93] = 0;
    game->values[94] = 0;
    game->values[95] = 0;
    game->values[96] = 0;
    game->values[97] = 0;
    game->values[98] = 0;
    game->values[99] = 0;
    game->values[100] = 0;
    game->values[101] = 0;
    game->values[102] = 0;
    game->values[103] = 0;
    game->values[104] = 0;
    game->values[105] = 0;
    game->values[106] = 0;
    game->values[107] = 0;
    game->values[108] = 0;
    game->values[109] = 0;
    game->values[110] = 0;
    game->values[111] = 0;
    game->values[112] = 0;
    game->values[113] = 0;
    game->values[114] = 0;
    game->values[115] = 0;
    game->values[116] = 0;
    game->values[117] = 0;
    game->values[118] = 0;
    game->values[119] = 0;
    game->values[120] = 0;
    game->values[121] = 0;
    game->values[122] = 0;
    game->values[123] = 0;
    game->values[124] = 0;
    game->values[125] = 0;
    game->values[126] = 0;
    game->values[127] = 0;
	return game;
}

void game_Play(Game *game) {
    PlayRound(game);
    board_destroy(game->board);
}


/* Private Functions */

void PlayRound(Game *game) {
    printf("\nScore:\n%s:\t%i\t%s:\t%i\n",
	   game->player1->name, game->player1->points,
	   game->player2->name, game->player2->points);
    player_Play(game->player1, game->board, game->bag, game->words, &game->values);
    player_OpponentPlay(game->player2, game->board, game->bag, game->words, &game->values);
	if(strlen(game->player1->letters) > 0 && strlen(game->player2->letters) > 0) {
		PlayRound(game);
	}
}


char* GetName(void) {
	printf("Enter Name:\n");
    char* name = NULL;
    name = malloc(sizeof(char) * 30);
    fgets(name, 30, stdin);
    char *end_of_input;
    if ((end_of_input = strchr(name, '\n')) != NULL) {
        *end_of_input = '\0';
    }
    if(strlen(name) < 1) {
        printf("Invalid Name\n");
        return GetName();
    }
    return name;
}


char*** ReadDictionary() {
    FILE *file = NULL;
    if((file = fopen("config/words.txt", "r")) == NULL) {
        return NULL;
    }
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char *buff = NULL;
    if((buff = malloc(size * sizeof(char))) == NULL) {
        return NULL;
    }
    fread(buff, sizeof(char), (int) size, file);
    int num_lines = 0;
    int i = 0;
    while(i < size) {
        if(buff[i] == '\n') {
            num_lines++;
        }
        i++;
    }
    rewind(file);
    char ***words = NULL;
    words = malloc(sizeof(char**) * 16);
    if(words == NULL) {
        return NULL;
    }
    for(int i=0; i<16; i++) {
        char **words_subset = NULL;
        words_subset = malloc(sizeof(char*) * 30000);
        if(words_subset == NULL) {
            return NULL;
        }
        words[i] = words_subset;
    }
    int word_counters[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int word_length;
    for(int j=0; j<num_lines; j++) {
        char *word = malloc(sizeof(char) * 16);
        fgets(word, sizeof(char) * 16, file);
        char *end_of_line;
        if ((end_of_line = strchr(word, '\n')) != NULL) {
            *end_of_line = '\0';
        }
        word_length = (int)strlen(word);
        words[word_length][word_counters[word_length]] = word;
        word_counters[word_length]++;
    }
    fclose(file);
    return words;
}
