#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#ifdef __cplusplus
extern "C" {
  #endif

  #ifdef __cplusplus
}
#endif

#endif /* GAME_LOGIC_H */

//To check if the stack is empty. Returns 1 if the stack is empty
int isEmpty(tokenPtr sPtr);

//Function to add token to a stack
int push(tokenPtr *sPtr, int value);

//Function to delete token from a stack
int pop(tokenPtr *sPtr, int value);


/*
* Returns the first letter associated with the color of the token
*
* Input: t - pointer to a token
* Output: initial of the color of the token
*
*/
char print_token(token *t);


//Function to print a line
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

/*
*  * Manages the logic of the game
*
* Input: board - a 6x9 array of squares that represents the board
*        players - the array of the players
*        numPlayers - the number of players
*/
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

//Function to increment the correct player's tokensOnLastCol when a token is added to a square in the 8th column
void checkLastCol(square board[NUM_ROWS][NUM_COLUMNS], int row, player players[]);

/*The function to be called whenever a token tries to move from an obstacle square.
It will check if there are still tokens behind the square, and if there are, it will take action.
If not, the obstacle square becomes a normal square. */
int obstacleSquares(square board[NUM_ROWS][NUM_COLUMNS], int rows, int columns);

//A function to check if any player has 3 tokens on the last column at the end of each round
int winning_player(player players[], int numPlayers);

//A function to move a token forward. Just to make things neater
void moveTokenForward(square board[NUM_ROWS][NUM_COLUMNS], int row, int column);
