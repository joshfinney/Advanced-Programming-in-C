/**
 * @file byn.c
 * @brief Main program for running the Beggar Your Neighbor game simulation
 * This program runs the Beggar Your Neighbor game simulation with varying numbers of players, using the statistics function to
 * calculate the shortest game, longest game, and average game length for each number of players. The results are written to a
 * file named "statistics.txt".
@author Your Name
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "statistics.h"

#define MAX_PLAYERS 52 /**< Maximum number of players that can play the game */
#define MIN_PLAYERS 2 /**< Minimum number of players that can play the game */
#define NUM_TRIALS 100 /**< Minimum number of trials to run the simulation */

/**
 * @brief Main function that runs the Beggar Your Neighbor game simulation
 * The program takes two command line arguments - the maximum number of players and the number of trials to run for each number of players.
 * It calls the statistics function N = [2, Max number of players] times and writes the output to a file named "statistics.txt".
 * @param argc The number of command line arguments
 * @param argv An array of strings containing the command line arguments
 * @return Returns 0 if the program runs successfully, 1 if there is an error
*/
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: byn max_number_of_players num_trials\n");
        return 1;
    }

    int max_players = atoi(argv[1]); /**< The maximum number of players to run the simulation for */
    int num_trials = atoi(argv[2]); /**< The number of trials to run the simulation for */

    if (max_players > MAX_PLAYERS) {
        printf("Error: max number of players cannot exceed %d\n", MAX_PLAYERS);
        return 1;
    }

    if (max_players < MIN_PLAYERS) {
        printf("Error: min number of players cannot be less than %d\n", MAX_PLAYERS);
        return 1;
    }

    if (num_trials < NUM_TRIALS) {
        printf("Error: min number of trials should be at least %d\n", NUM_TRIALS);
        return 1;
    }
    
    FILE *file = fopen("statistics.txt", "w"); /**< File pointer to the output file "statistics.txt" */
    if (file == NULL) {
        printf("Error: failed to open output file\n");
        return 1;
    }

    fprintf(file, "Number of players, Shortest game, Longest game, Average game\n");

    for (int i = 2; i <= max_players; i++) {
        GameStats output = statistics(i, num_trials);
        fprintf(file, "%d,\t\t\t\t\t %d, \t\t\t %d,\t\t %.2f\n\n", i, output.shortest, output.longest, output.average);
    }

    fclose(file);

    printf("Results written to statistics.txt\n");

    return 0;
}

/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc beggar.c shuffle.c byn.c queue.c statistics.c -lgsl -lgslcblas -lm -o byn
 * 
 * To run the program, type the following command:
 * ./byn 3 100
 * 
 * The program will call the statistics function N = [2,  Max number of players] times and will write the output in statistics.txt file
 */