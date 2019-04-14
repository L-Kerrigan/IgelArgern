/* 
 * File:   main.c
 * Author: Lucy
 *
 * Created on 08 March 2019, 11:49
 */

/*Check list for the game:
 - Initialise the board. Obstacle square positions already decided
 - Display the board - (Done)
 - Initialise (create) the players -(Done, to be checked)
 - Initialise struct for tokens -(Done, to be checked)
 - Make function to allow players to place tokens at start of game (Done, to be checked)
 - Make function to play game
 - Implement stack for tokens and make use of LIFO principle that it works on
   so the token on top is the only one that can move
 - Implement obstacles squares so that the player can't move the token on that square
   until all the others are level with it. The other tokens can only go as far as that token is
 - Edit main to put it all together -(Kinda done?)
 */





#include <stdio.h>
#include <stdlib.h>

/*
 *
 */
/*
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}
 */
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: lpasqua
 *
 * Created on 06 March 2019, 12:11
 */

#include "game_init.h"
#include "game_logic.h"

/*
 *
 */
int main(int argc, char** argv) {

    //the board is defined as a 2-Dimensional array of squares
    square board[NUM_ROWS][NUM_COLUMNS];

    //an array containing the players (MAX 6 players)
    player players[6];

    //the number of players
    int numPlayers = 0;

    //creates the squares of the board
    initialize_board(board);

    //prints the board
    print_board(board);

    //creates the players and counts them
    numPlayers = initialize_players(players);

    //asks each player to place their tokens
    //on the first column of the board
    place_tokens(board, players, numPlayers);


    //manages the turns of the game and identifies a winner
    play_game(board, players, numPlayers);

    return 0;



}
