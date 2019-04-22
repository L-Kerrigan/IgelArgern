/*
* File:   game_logic.h
* Author: Lucy
*
* Created on 08 March 2019, 11:52
*/

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#ifdef __cplusplus
extern "C" {
  #endif




  #ifdef __cplusplus
}
#endif

#endif /* GAME_LOGIC_H */

/*
* Returns the first letter associated with the color of the token
*
* Input: t - pointer to a token
* Output: initial of the color of the token
*
*/
char print_token(token *t);



void printLine();

/*
* Prints the board
*
* Input: the board to be printed.
*/
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);
/*
* Place tokens in the first column of the board
*
* Input: board - a 6x9 array of squares that represents the board
*        players - the array of the players
*        numPlayers - the number of players
*/
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);


int pop(tokenPtr *sPtr, int value);
/*
*  * Manages the logic of the game
*
* Input: board - a 6x9 array of squares that represents the board
*        players - the array of the players
*        numPlayers - the number of players
*/

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);


/*The function to be called whenever a token lands on its destination. It will check if said square is an obstacle,
and if it is, it will take action. If not, nothing happens. */
/*Maybe make this return a true/false value depending on whether the token can move,
Then call the moveToken function in the play_game function if that token can be moved etc. */

int obstacleSquares(square board[NUM_ROWS][NUM_COLUMNS], int rows, int columns);
