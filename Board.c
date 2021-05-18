//
//  Board.c
//

#include "Board.h"


/* Private Function Definitions */

void    AddCrosspath(Board *board, Path *path, Square *square, int intersection);
void    AddPath(Board *board, Path *path);
int     CrosspathHasSquares(Board *board, Path *path, Square *square);
void    FindPathsFromSquare(Board *board, Square *square, char *hand, int dx);
int     OnBoard(int x, int y);
int     PathIsConnected(Board *board, Path *path);
int     PathIsValid(Board *board, Path *path);
void    ReadLetterMultipliers(Board *board);
void    ReadSquares(Board *board);
void    ReadWordMultipliers(Board *board);
int     SquareIsBlank(Board *board, int x, int y);
int     SquareIsConnected(Board *board, int x, int y);
int     SquareIsNotBlank(Board *board, int x, int y);


/*  Public Functions  */

Board* board_init() {
    Board *board;
    board = malloc(sizeof(Board));
    if(board == NULL) {
        return NULL;
    }
    for(int x=0; x<15; x++) {
        for(int y=0; y<15; y++) {
            Square *square = NULL;
            square = square_init(x, y);
            board->squares[x][y] = square;
        }
    }
    board->paths = NULL;
    board->paths = list_init();
    ReadSquares(board);
    ReadLetterMultipliers(board);
    ReadWordMultipliers(board);
    return board;
}


void board_FindPaths(Board *board, char *hand, int dx) {
    int dy = !dx;
    for(int x=0; x<15; x++) {
        for(int y=0; y<15; y++) {
            FindPathsFromSquare(board, board->squares[x][y], hand, dx);
        }
    }
    if(dx) {
        board_FindPaths(board, hand, dy);
    }
}


void board_Print(Board *board) {
    printf("\nBoard: \n\n   ");
    for(int i=0; i<15; i++) {
        printf("%c%c", i + 65, ' ');
    }
    printf("\n");
    for(int y=0; y<15; y++) {
        if(y < 9) {
            printf("%c", ' ');
        }
        printf("%i ", y + 1);
        for(int x=0; x<15; x++) {
            printf("%c ", board->squares[x][y]->letter);
        }
        printf("\n");
    }
    printf("\n");
}


void board_Reset(Board *board) {
    Node *path_node = NULL;
    path_node = board->paths->head;
    while(path_node) {
        Path *path = path_node->data;
        path_destroy(path);
        path_node = path_node->next;
    }
    list_Erase(board->paths);
}


void board_Update(Board *board, Move *move) {
    int i = 0;
    Node *square_node = NULL;
    square_node = move->squares->head;
    do {
        Square *square = square_node->data;
        board->squares[square->x][square->y]->letter = move->word->letters[i];
        i++;
    } while((square_node = square_node->next));
}


void board_destroy(Board *board) {
    board_Reset(board);
    list_destroy(board->paths);
    board->paths = NULL;
    for(int x=0; x<15; x++) {
        for(int y=0; y<15; y++) {
            free(board->squares[x][y]);
        }
    }
    free(board);
}


/*  Private Functions  */

void FindPathsFromSquare(Board *board, Square *start, char *letters, int dx) {
    int x = start->x;
    int y = start->y;
    int dy = !dx;
    if(SquareIsNotBlank(board, x - dx, y - dy)) {
        return;
    }
    Path *path = NULL;
    path = path_init();
    path->dx = dx;
    path->dy = dy;
    while(OnBoard(x, y) && path_AddSquare(path, board->squares[x][y], letters)) {
        if(PathIsValid(board, path)) {
            AddPath(board, path);
        }
        x += dx;
        y += dy;
    }
    path_destroy(path);
}


int PathIsValid(Board *board, Path *path) {
    if(PathIsConnected(board, path) && path->used > 0) {
        Square *last = path->squares->tail->data;
        int next_x = last->x + path->dx;
        int next_y = last->y + path->dy;
        if(!OnBoard(next_x, next_y)) {
            return 1;
        }
        return SquareIsBlank(board, next_x, next_y);
    }
    return 0;
}


int PathIsConnected(Board *board, Path *path) {
    Node *square_node = path->squares->head;
    do {
        Square *square = square_node->data;
        if(SquareIsConnected(board, square->x, square->y)) {
            return 1;
        }
    } while((square_node = square_node->next));
    return 0;
}


void AddPath(Board *board, Path *source) {
    Path *path = NULL;
    path = path_init();
    path_Copy(path, source);
    board_FindCrosspaths(board, path);
    list_Push(board->paths, path);
}


void board_FindCrosspaths(Board *board, Path *path) {
    int intersection = 0;
    Node *square_node = path->squares->head;
    do {
        Square *square = NULL;
        square = square_node->data;
        if(CrosspathHasSquares(board, path, square)) {
            AddCrosspath(board, path, square, intersection);
        }
        intersection++;
    } while((square_node = square_node->next));
}


int CrosspathHasSquares(Board *board, Path *path, Square *square) {
    if(SquareIsNotBlank(board, square->x, square->y)) {
        return 0;
    }
    if((!OnBoard(square->x + !path->dx, square->y + !path->dy) ||
        SquareIsBlank(board, square->x + !path->dx, square->y + !path->dy)) &&
       (!OnBoard(square->x - !path->dx, square->y - !path->dy) ||
        SquareIsBlank(board, square->x - !path->dx, square->y - !path->dy))) {
        return 0;
    }
    return 1;
}


void AddCrosspath(Board *board, Path *path, Square *square, int intersection) {
    int x = square->x;
    int y = square->y;
    int dx = !path->dx;
    int dy = !path->dy;
    Crosspath *crosspath = NULL;
    crosspath = crosspath_init(intersection);
    do {
        list_Push(crosspath->squares, board->squares[x][y]);
    } while(SquareIsNotBlank(board, (x += dx), (y += dy)));
    x = square->x;
    y = square->y;
    while(SquareIsNotBlank(board, (x -= dx), (y -= dy))) {
        list_Insert(crosspath->squares, board->squares[x][y]);
    }
    crosspath_GetLetters(crosspath);
    if(strchr(crosspath->letters, '_')) {
        list_Push(path->crosspaths, crosspath);
    }
    else {
        crosspath_destroy(crosspath);
    }
}


int OnBoard(int x, int y) {
    return x > -1 && x < 15 && y > -1 && y < 15;
}


int SquareIsBlank(Board *board, int x, int y) {
    return OnBoard(x, y) && board->squares[x][y]->letter == '_';
}


int SquareIsNotBlank(Board *board, int x, int y) {
    return OnBoard(x, y) && board->squares[x][y]->letter != '_';
}


int SquareIsConnected(Board *board, int x, int y) {
    if (SquareIsNotBlank(board, x - 1, y) || SquareIsNotBlank(board, x + 1, y) ||
        SquareIsNotBlank(board, x, y - 1) || SquareIsNotBlank(board, x, y + 1)) {
        return 1;
    }
    else if (x == 7 && y == 7) {
        return 1;
    }
    return 0;
}


void ReadLetterMultipliers(Board *board) {
    FILE *file = NULL;
    if((file = fopen("config/letter_multipliers.txt", "r")) == NULL) {
        return;
    }
    char *buff = NULL;
    if((buff = malloc(17 * sizeof(char))) == NULL) {
        return;
    }
    int y = 0;
    while(fgets(buff, 17, file)) {
        for(int x=0; x<15; x++) {
            board->squares[x][y]->letter_mult = buff[x] - 48;
        }
        y++;
    }
    fclose(file);
}


void ReadSquares(Board *board) {
    int y = 0;
    FILE *file = NULL;
    if((file = fopen("config/board.txt", "r")) == NULL) {
        return;
    }
    char *buff = NULL;
    if((buff = malloc(17 * sizeof(char))) == NULL) {
        return;
    }
    while(fgets(buff, 17, file)) {
        for(int x=0; x<15; x++) {
            board->squares[x][y]->letter = buff[x];
        }
        y++;
    }
    fclose(file);
}


void ReadWordMultipliers(Board *board) {
    int y = 0;
    FILE *file = NULL;
    if((file = fopen("config/word_multipliers.txt", "r")) == NULL) {
        return;
    }
    char *buff = NULL;
    if((buff = malloc(17 * sizeof(char))) == NULL) {
        return;
    }
    while(fgets(buff, 17, file)) {
        for(int x=0; x<15; x++) {
            board->squares[x][y]->word_mult = buff[x] - 48;
        }
        y++;
    }
    fclose(file);
}
