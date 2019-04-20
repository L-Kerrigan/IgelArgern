#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>



/*
* This function creates the board for the first time
*
* Input: board - a 6x9 array of squares
*
*/
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]) {

  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLUMNS; j++) {
      //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
      if ((i == 0 && j == 3) || (i == 1 && j == 6) || (i == 2 && j == 4)
      || (i == 3 && j == 5) || (i == 4 && j == 2) || (i == 5 && j == 7)) {
        board[i][j].type = OBSTACLE;
      } else {
        //creates a normal square otherwise
        board[i][j].type = NORMAL;
      }
      board[i][j].stack = NULL; //Initialised the stack of tokens on each square to NULL
      board[i][j].tokensOnSquare = 0; //Initialised the number of tokens on each square to 0
    }
  }
}

/*
* This function creates players for the first time
*
* Input: the array of players to be initialized
* Output: The number of players of the game
*
*/
int initialize_players(player players[]) {
  int i = 0;
  while (i < 6) {
    printf("%s", "Input the next Player's name: \n"); //Inputting each Facebook user
    fgets(players[i].name,30,stdin);
    //Checks whether a carriage return symbol was provided as input
    if (players[i].name == "\n"){
      break;
    }
    i++;
  }
  return i;
}
