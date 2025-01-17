#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h> //These 2 libraries are to randomise numbers for a dice roll
#include <time.h>


//Just to check if stack is empty. Returns 1 if stack is empty
int isEmpty(tokenPtr sPtr) {
    return sPtr == NULL;
}

int push(tokenPtr *sPtr, int value) {
    tokenPtr newPtr = malloc(sizeof (token)); //Creating a new token
    if (newPtr != NULL) { //Checking if space is available for the new value
        newPtr->col = value; //Placing the colour in the new token
        newPtr->next = NULL; //There is currently no next element in the stack
        tokenPtr prevPtr = NULL; //Points to previous token in stack
        tokenPtr currPtr = *sPtr; //Points to current token in stack

        //Loop to find the correct position in the list. This needs to be edited
        while (currPtr != NULL) {
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }
        //This is for inserting a new element at the beginning of the stack
        newPtr->next = *sPtr;
        *sPtr = newPtr;
    } else { //If something goes wrong with memory allocation
        printf("%d not stacked. No memory was made available. \n", value);
    }
}

//Function to pop elements of stack. Inefficient but I can't figure out a better way right now
int pop(tokenPtr *sPtr, int value) {
    if (value == (*sPtr)->col) {
        tokenPtr tempPtr = *sPtr; //Hold onto token being removed
        *sPtr = (*sPtr)->next; //De-thread the token from the stack
        free(tempPtr); //Free the tempPtr holding the removed value
    } else {
        tokenPtr prevPtr = *sPtr;
        tokenPtr currPtr = (*sPtr)->next;

        while (currPtr != NULL && currPtr->col != value) {
            prevPtr = currPtr; //These two lines make the stack point to the next token
            currPtr = currPtr->next;
        }
        if (currPtr != NULL) { //To delete the token at currPtr
            tokenPtr tempPtr = currPtr;
            prevPtr->next = currPtr->next;
            return value;
        }
    }
    return '\0';
}

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


//Function to print a line
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
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
    int minTokens = 0; //Minimum number of tokens placed on a square in the first column of the board
    int squareSelected = 0; //Variable to hold the number of the square selected by the user
    int i, j; //Counters for loops

    for (i = 0; i < 4; i++) { //This loop ensures that all tokens are placed on the board
        for (j = 0; j < numPlayers; j++) { //This loop ensures that all players get a chance to place on the board
            printf("%s, please choose a square.\n", players[j].name);
            scanf(" %d", &squareSelected); //Asks where the player wants to place their next token

            if (squareSelected < 0 || squareSelected >= 6) { //If the squareSelected is off the board, the player must choose again
                printf("That square isn't on the board. Pick again. \n");
                j--; //Makes the player choose again by reducing the counter in the loop by 1
            }
            else {
                if (board[squareSelected][0].tokensOnSquare == minTokens) {
                    if (minTokens == 0) {
                        push(&(board[squareSelected][0].stack), players[j].col); //Adds the token to the stack
                        board[squareSelected][0].tokensOnSquare++; //Increments the number of tokens on the square

                        if (((numPlayers * i) + j + 1) % NUM_ROWS == 0) {
                            minTokens++; //Updates the minimum number of tokens every time a multiple of (the number of players) tokens has been placed in the first column
                        }
                    } else if (board[squareSelected][0].stack->col != players[j].col) {
                        push(&(board[squareSelected][0].stack), players[j].col); //Adds the token to the stack
                        board[squareSelected][0].tokensOnSquare++; //Increments the number of tokens on the square

                        if (((numPlayers * i) + j + 1) % NUM_ROWS == 0) {
                            minTokens++; //Updates the minimum number of tokens every time a multiple of (the number of players) tokens has been placed in the first column
                        }
                    } else {
                        printf("There's a token of your colour already there. Pick again. \n\n");
                        j--; //Makes the player choose again by reducing the counter in the loop by 1
                    }
                } else {
                    printf("That square has more than the minimum number of tokens. Pick again. \n\n");
                    j--; //Makes the player choose again by reducing the counter in the loop by 1
                }
            }
        }
    }
    print_board(board); //Prints the baord after all tokens are placed
}

/*
 *  * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
    do {
        for (int i = 0; i < numPlayers; i++) { //Runs through each player to give them a turn
            srand(time(NULL));
            int dice = (rand() % 6); //Randomising a number for the dice roll. Yes I know die don't generally have number 0, but there's a row 0, so I didn't correct this
            int tileNum; //To hold the column number selected by the player in the takeTurn function

            char ans; //To hold the answer the user gives to the following question
            printf("%s, will you move your own token up or down? Enter Y or N.\n", players[i].name);
            scanf(" %c", &ans); //Takes in whether the player wants to move one of their own tokens up or down

            if (ans == 'Y' || ans == 'y') {
                int tileCol, tileRow; //To hold the number of the tile their own token is on that the player wants to move
                printf("Which token would you like to move? Type the row and column. \n");
                scanf(" %d%d", &tileRow, &tileCol); //Takes in location of token to be moved
                if (board[tileRow][tileCol].tokensOnSquare == 0 || isEmpty(board[tileRow][tileCol].stack)) {
                    printf("There are no tokens on this square. \n\n");
                    tileNum = takeTurn(board, players, dice, i);
                    //Again, need to figure out a way to ask the question
                } else if (board[tileRow][tileCol].stack->col != players[i].col) {
                    printf("This is not your token.\n\n");
                    tileNum = takeTurn(board, players, dice, i);
                    //Again, need to figure out a way to ask the question
                } else if (board[tileRow][tileCol].type == OBSTACLE && (obstacleSquares(board, tileRow, tileCol) != 0)) {
                    tileNum = takeTurn(board, players, dice, i);
                }

                else {
                    char move;
                    printf("Press U for up or D for down.\n");
                    scanf(" %c", &move); //Takes in whether the user wishes to move their own token up or down

                    if (move == 'U' || move == 'u') { //This works to move it, but we need to ask which colour token the player wants to move
                        if (tileRow <= 0) {
                            printf("Sorry, you can't move this token further up.\n\n");
                            //Need to add something that asks the question again. Or just leave it and let them move forward
                        } else if (tileRow > 0) {
                            push(&(board[tileRow - 1][tileCol].stack), players[i].col); //Adds token to the stack
                            board[tileRow - 1][tileCol].tokensOnSquare++; //Increments number of tokens on the square

                            board[tileRow][tileCol].tokensOnSquare--; //Decrements number of tokens on the square
                            pop(&(board[tileRow][tileCol].stack), board[tileRow][tileCol].stack->col); //Deletes token from stack
                        }
                        print_board(board); //Prints board at the end of each move
                    }

                    else if (move == 'D' || move == 'd') {
                        if (tileRow >= 5) {
                            printf("Sorry, you can't move this token further down.\n\n");
                            //Need to add something that asks the question again. Or just leave it and let them move forward
                        } else if (tileRow < 5) {
                            push(&(board[tileRow + 1][tileCol].stack), players[i].col); //Adds token to the stack
                            board[tileRow + 1][tileCol].tokensOnSquare++; //Increments number of tokens on the square

                            board[tileRow][tileCol].tokensOnSquare--; //Decrements number of tokens on the square
                            pop(&(board[tileRow][tileCol].stack), board[tileRow][tileCol].stack->col); //Deletes token from stack
                        }
                    }
                    print_board(board); //Prints board at the end of each move
                    tileNum = takeTurn(board, players, dice, i);

                    if ((tileNum + 1) == 8) {
                        checkLastCol(board, dice, players); //Calls function to check if a token has been added to the last column this turn. Doesn't work quite right
                    }
                }
            }

            else if (ans == 'N' || ans == 'n') { //If the player answers no, just move forward the token they chose before
                tileNum = takeTurn(board, players, dice, i);
                if ((tileNum + 1) == 8) {
                    checkLastCol(board, dice, players); //Calls function to check if a token has been added to the last column this turn. Doesn't work quite right
                }
            }
            else {
                printf("Invalid answer. \n\n"); //If they don't give a proper answer, they only get to move their selected token forward
            }

            print_board(board); //Prints board at the end of each round
        }
    } while ((winning_player(players, numPlayers) == 0)); //Keeps code running until a player has 3 tokens in the last column
}

//Increments tokensOnLastCol variable of the player corresponding to the colour of the newly added token on the top of the stack
void checkLastCol(square board[NUM_ROWS][NUM_COLUMNS], int row, player players[]) {
    //Switch statement to increment tokensOnLastCol variable for the player corresponding to the token at the top of the stack (the newest token)
    switch (board[row][8].stack->col) {
        case 0:
            players[0].tokensOnLastCol++;
            break;

        case 1:
            players[1].tokensOnLastCol++;
            break;

        case 2:
            players[2].tokensOnLastCol++;
            break;

        case 3:
            players[3].tokensOnLastCol++;
            break;

        case 4:
            players[4].tokensOnLastCol++;
            break;

        case 5:
            players[5].tokensOnLastCol++;
            break;

        default:
            break;
    }
}

/*The function to be called whenever a token tries to move from an obstacle square. It will check if said square is still an obstacle,
and if it is, it will take action. If not, the obstacle square becomes a normal square.*/
int obstacleSquares(square board[NUM_ROWS][NUM_COLUMNS], int rows, int columns) { //This function needs fixing
    int ret = 0; //The variable to be returned at the end of the function
    for (int a = 0; a < 6; a++) { //Runs through all the squares before the obstacle squares to check for other tokens
        for (int b = 0; b < columns; b++) {
            if ((board[a][b].tokensOnSquare) > 0) {
                ret++; //ret>0=The square is an active obstacle square. Token can't be moved
            }
        }
    }
    if (ret != 0) {
        printf("You can't move this token yet. It's on an obstacle square.\n");
    } else if (ret == 0) {
        printf("There are no tokens behind this one, so it can now move.\n");
        board[rows][columns].type = NORMAL; //Changes the obstacle square to a normal
    }
    //if ret =0, the square is no longer an active obstacle square. Token can be moved. Else it's still an obstacle square and the user misses a turn
    return ret; //This function will act somewhat like a boolean (true/false) function, only with a little more to it
}

int winning_player(player players[], int numPlayers) {
    int i, j; //Counters
    int tf = 0;
    for (i = 0; i < numPlayers; i++) { //Runs through and checks each player's tokensOnLastCol
        if (players[i].tokensOnLastCol >= 3) {
            tf++; //If a player has 3 or more tokens in the last column then tf is incremented
            printf("Player %d wins!\n", i + 1); //Prints player who won
        }
    }
    return tf; //Returns 0 or a value greater than 0 depending on if a player has 3 tokens on the last column or not
}

int takeTurn(square board[NUM_ROWS][NUM_COLUMNS], player players[], int dice, int num) {
    //This may be in the wrong order. Sidestep first then move forward???
    int tileNum; //To hold the selected tile number
    printf("%s, you rolled a %d. \n", players[num].name, dice);
    printf("Which token will you move on row %d? Type the number of the tile it's on. \n", dice);
    scanf("%d", &tileNum); //Player selects a the tile on which the token they want to move is on
    if (tileNum < 0 || tileNum >= 8) { //Checks if the tile selected is within the range of the columns of the board
        printf("This is an invalid tile number. \n\n");
        //Need to find a way to ask the question again
    }//Latter half of this statement shouldn't be required
    else if (board[dice][tileNum].tokensOnSquare == 0 || isEmpty(board[dice][tileNum].stack)) {
        printf("There are no tokens on this square. \n\n");
        //Need to find a way to ask the question again
    } else if (board[dice][tileNum].type == OBSTACLE && (obstacleSquares(board, dice, tileNum) != 0)) {
        printf("Sorry, you miss a turn!\n\n");
    } else {
        moveTokenForward(board, dice, tileNum);
    }
    return tileNum;
}

//Just a function to neaten up the process of moving a token forward
void moveTokenForward(square board[NUM_ROWS][NUM_COLUMNS], int row, int column) {
    push(&(board[row][column + 1].stack), board[row][column].stack->col); //Adds token to the stack
    board[row][column + 1].tokensOnSquare++; //Increments number of tokens on the square

    board[row][column].tokensOnSquare--; //Decrements number of tokens on the square
    pop(&(board[row][column].stack), board[row][column].stack->col); //Deletes token from stack
}
