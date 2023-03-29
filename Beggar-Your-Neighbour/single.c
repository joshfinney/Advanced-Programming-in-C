/**
 * @file main.c
 * Main file for the Beggar card game program.
 * @author Josh
*/
#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"

/**
 * @brief Main function that runs the Beggar card game program.
 * This function takes in the number of players as a command line argument,
 * initializes the deck of cards, and calls the beggar function to run the game.
 * The number of turns taken to complete the game is then printed to the console.
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * The first argument should be the number of players.
 * @return 0 if the program completes successfully, 1 otherwise.
*/

int main(int argc, char *argv[]) {
    // Check if the user entered the number of players as a command line argument
    if (argc != 2) {
        printf("Please enter the number of players as a command line argument\n");
        return 1;
    }

    // Convert the user input to an integer
    int Nplayers = atoi(argv[1]);

    // Initialize the deck of cards
    int deck[52];
    int i, j, k = 0;

    //loop through the values 2 to 14 and, for each value, loops through 4 times to add the value to the deck array. This results in an array of size 52 with values from 2 to 14, 4 times each.
    for (i = 2; i <= 14; i++) {
        for (j = 0; j < 4; j++) {
            deck[k] = i;
            k++;
        }
    }

    int deck_length = sizeof(deck) / sizeof(int);
    printf("deck length:{%d}\n\n",deck_length);

    // Call the beggar function
    int talkative = 1;
    int result = beggar(Nplayers, deck, talkative);

    // Print the result
    printf("Number of turns: %d\n", result);

    return 0;
}

/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc beggar.c shuffle.c single.c queue.c -lgsl -lgslcblas -lm -o single
 * To run this program, run the following command in the terminal
 * ./single <no_of_player> eg: ./single 3
 * this main function uses beggar.c file to find the number of turns taken to complete the match and finally prints it
 */
