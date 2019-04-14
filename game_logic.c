#include "game_init.h"
#include <stdio.h>
#include <stdlib.h> //These 2 libraries are to randomise numbers for a dice roll
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 *
 * Input: t - pointer to a token
 * Output: initial of the color of the token
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


/*Prototypes for stack push/pop functions. */
struct stack *push(int value, struct stack *top){
    struct stack *current=top;
    top=malloc(sizeof(stack));
    top->col=value;
    top->next=current;
    return top;
}
/*These functions currently aren't in use.
 * Need to be added to play_game and start_game functions*/
struct stack *pop(struct stack *top){
    struct stack *current = top;
    if(current!=NULL){
        top=current->next;
        printf("Stack Data: %d\n", current->col);
        free(current);
    }
    return top;
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

void printLine() {
    printf("   -------------------------------------\n");
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
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
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        srand(time(NULL)); //Randomising a number for the dice roll
        int dice = (rand() % 6)+1;

        /*Maybe I should change the part below to check which squares the player's colour is on,
         then ask which token to move?*/

        int tileNum; //To hold the selected tile number
        printf("Player %d, you rolled a %d. \n", i, dice);
        printf("Which token will you move? Type the number of the tile it's on. \n");
        scanf("%d", &tileNum); //Player selects a the tile on which the token they want to move is on
        if (tileNum <= 0 || tileNum >= 7) { //Not sure if this will actually cause the player to miss a turn. Need to check
            printf("This is an invalid tile number.\n");
            exit(0);  //This is a void function, so I can't use return. Need to find a way to ask the question again
        }
        else if(tileNum != players[i].col){
            //Not sure if this will actually cause the player to miss a turn either. Need to check
            printf("This is not your colour.\n");
            exit(0); //This is a void function, so I can't use return. Need to find a way to ask the question again
        }
        else {
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
                    tileNum-1;
                } else if (move == 'D' || move == 'd') {
                    //Do we need to display where the token goes here? Or just move it?
                    //This is just the code to move it
                    tileNum+1;
                }
                board[tileNum][dice].stack = (token *) malloc(sizeof (token));
                board[tileNum][dice].stack->col = players[i].col;
                board[tileNum][dice].tokensOnSquare++;

            } else if (ans == 'N' || ans == 'n') {
                board[tileNum][dice].stack = (token *) malloc(sizeof (token));
                board[tileNum][dice].stack->col = players[i].col;
                board[tileNum][dice].tokensOnSquare++;
            }
            else{
                printf("Invalid answer. \n");
            }
        }
        print_board(board);
    }
}
