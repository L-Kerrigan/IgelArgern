#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h> //These 2 libraries are to randomise numbers for a dice roll
#include <time.h>

/*
* Returns the first letter associated with the color of the token
*
* Input: t - pointer to a token
* Output: initial of the color of the token
*
*/
char print_token(token *t) {
  if ((*t).col == PINK) return 'P';
  if ((*t).col == RED) return 'R';
  if ((*t).col == BLU) return 'B';
  if ((*t).col == GREEN) return 'G';
  if ((*t).col == ORANGE) return 'O';
  if ((*t).col == YELLOW) return 'Y';
  return '\0';
}



void printLine() {
  printf("   -------------------------------------\n");
}

/*
* Prints the board
*
* Input: the board to be printed.
*/
void print_board(square board[NUM_ROWS][NUM_COLUMNS]) {
  printf("                THE BOARD\n");
  for (int i = 0; i < NUM_ROWS; i++) {

    //prints an horizontal line
    printLine();
    //prints the row number
    printf(" %d ", i);
    char c = '\0';
    //if the square (i,j) is occupied,
    //c is assigned the initial of the color of the token that occupies the square
    for (int j = 0; j < NUM_COLUMNS; j++) {
      if (board[i][j].stack != NULL) {
        c = print_token(board[i][j].stack);
      }//if the square (i,j) is empty
      else {
        //c is assigned 'X' if the square represents an obstacle
        if (board[i][j].type == OBSTACLE)
        c = 'X';
        //c is assigned an empty space otherwise
        else c = ' ';
      }
      printf("| %c ", c);
    }
    printf("|\n");
  }
  printLine();
  //prints the number of the columns at the end of the board
  printf("     0   1   2   3   4   5   6   7   8\n");
}

/*
* Place tokens in the first column of the board
*
* Input: board - a 6x9 array of squares that represents the board
*        players - the array of the players
*        numPlayers - the number of players
*/
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
  //Minimum number of tokens placed on a square in the first column of the board
  int minTokens = 0;
  int squareSelected = 0;
  int i, j; //Counters

  for (i = 0; i < 4; i++) { //These loops ensure that each player places all their tokens on the board
    for (j = 0; j < numPlayers; j++) {
      printf("Player %d please choose a square.\n", j);
      scanf("%d", &squareSelected); //Asks where the player wants to place their next token

      if (squareSelected == minTokens && squareSelected != players[j].col) { //The following instructions add a token to a square.
        //If there's a token already there it will be overwritten. This needs to be changed later
        board[squareSelected][0].stack = (token *) malloc(sizeof (token));
        board[squareSelected][0].stack->col = players[j].col;
        board[squareSelected][0].tokensOnSquare++;

        //Updates the minimum number of tokens every time a multiple of 6 tokens has been placed in the first col
        if (((numPlayers * i) + j + 1) % NUM_ROWS == 0) {
          minTokens++;
        }
      }
    }
  }
}



/*
*  * Manages the logic of the game
*
* Input: board - a 6x9 array of squares that represents the board
*        players - the array of the players
*        numPlayers - the number of players
*/

void chooseToken(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
  for (int i = 0; i < numPlayers; i++) {
    srand(time(NULL)); //Randomising a number for the dice roll
    int dice = (rand() % 6)+1;

    /*Needs to be changed! Player can move any colour.*/

    int tileNum; //To hold the selected tile number
    printf("Player %d, you rolled a %d. \n", i, dice);
    printf("Which token will you move? Type the number of the tile it's on. \n"); //Has to be on the row the dice rolled
    scanf("%d", &tileNum); //Player selects a the tile on which the token they want to move is on
    if (tileNum <= 0 || tileNum >= 7) { //Not sure if this will actually cause the player to miss a turn. Need to check
      printf("This is an invalid tile number.\n");
      //exit(0);  //This is a void function, so I can't use return. Need to find a way to ask the question again
    }
    else if(board[tileNum][dice].type==OBSTACLE){ //Need to check if the tile the token is on is an obstacle, not the future position!!
      obstacleSquares(board[tileNum][dice]);
    }
  char ans;
  printf("Will you move your token up or down? Enter Y or N.\n");
  scanf("%c", &ans);
  if (ans == 'Y' || ans == 'y') {
    char move;
    printf("Press U for up or D for down.\n");
    scanf("%c", &move);
    if (move == 'U' || move == 'u') {
      //Do we need to display where the token goes here? Or just move it?
      //This is just the code to move it
      if(tileNum=0){
        printf("Sorry, you can't move this token further up.\n");
        //Need to add something that asks the question again. Or just leave it and let them move forward
      }
      else{
        tileNum-1;
      }
    }
    else if (move == 'D' || move == 'd') {
      if(tileNum=6){
        printf("Sorry, you can't move this token further down.\n");
        //Need to add something that asks the question again. Or just leave it and let them move forward
      }
      else{
        tileNum+1;
      }
      //Do we need to display where the token goes here? Or just move it?
      //This is just the code to move it
    }
    board[tileNum][dice].stack = (token *) malloc(sizeof (token));
    board[tileNum][dice].stack->col = players[i].col; //This will not work. Figure out how to implement stack properly
    board[tileNum][dice].tokensOnSquare++; //Player also may not choose their own colour ^^
  }
  else if (ans == 'N' || ans == 'n') {
    board[tileNum][dice].stack = (token *) malloc(sizeof (token));
    board[tileNum][dice].stack->col = players[i].col; //This will not work. Figure out how to implement stack properly
    board[tileNum][dice].tokensOnSquare++;  //Player also may not choose their own colour ^^
  }
  else{
    printf("Invalid answer. \n");
  }
  print_board(board);
}
}

//Divide this function up:
//One function to choose the token to move
//Another to move the token once it's confirmed that token isn't on an obstacle square, etc.
/*
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
chooseToken(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);
if(obstacleSquares(board[int i][int j])==1){
chooseToken(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);
//Will this work if the player attempts to chose mulitple unmoveable tokens in a row?
}
else{
moveToken(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);
}
//Currently these functions don't get the info they need and aren't in the correct order
//Needs to call all the functions that play the game and pass the appropriate info. Acts like a mini-main function
} */



/*The function to be called whenever a token lands on its destination. It will check if said square is an obstacle,
and if it is, it will take action. If not, nothing happens. */
/*Maybe make this return a true/false value depending on whether the token can move,
Then call the moveToken function in the play_game function if that token can be moved etc. */
int obstacleSquares(square singleSquare){
  for(int a=0;a<6;a++){
    for(int b=0;b<9;b++){
      if((singleSquare.tokensOnSquare)>0){
        //Implement something that says they can't move this token
        printf("You can't move this token yet. It's on an obstacle square.\n");
        //Call function to choose another token
        return 1; //1=The square is an active obstacle square. Token can't be moved
        //Currently this just starts from the beginning.
        //It needs to give the option for the same player to choose another token. Make a new function?
      }
      else{
        printf("There are no tokens behind this one, so it can now move.\n");
        return 0; //0=The square is no longer an active obstacle square. Token can be moved
      }
    }
  }
}
