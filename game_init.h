#ifndef GAME_INIT_H
#define GAME_INIT_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* GAME_INIT_H */
/*
 * File:   newfile.h
 * Author: lpasqua
 *
 * Created on 06 March 2019, 12:18
 */

//number of rows of the board
#define NUM_ROWS 6
//number of columns of the board
#define NUM_COLUMNS 9


//types of squares

enum stype {
    NORMAL, OBSTACLE
};

//colors of tokens

enum color {
    RED, BLU, GREEN, YELLOW, PINK, ORANGE
};

//defines a token.
//Note each token can be associated with a color

typedef struct token {
    enum color col;
} token;

//Defines a square of the board.

typedef struct square {
    //A square can be a NORMAL or an OBSTACLE square
    enum stype type;
    //the stack of tokens that can be placed on the board square
    token * stack;
    //Keeping track of how many tokens are on each square
    int tokensOnSquare;
} square;

struct stack{
    enum color col;
    //To implement later: number of tokens on the square for this stack
    //Relate this stack to squareSelected
    struct stack *next;
}stack;


typedef struct player {
    char name[30];
    enum color col;
    int tokensOnLastCol;
} player;


/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 *
 */
int initialize_players(player players[]);
