/**
 * @file beggar_statistics.h
 * @brief This file contains a function that generates statistics on the game of beggar-my-neighbour
 * The statistics function generates the shortest, longest, and average number of moves required to complete the game of beggar-my-neighbour
*/
#include <limits.h>
#include "beggar.h"

/**
 * @brief A struct containing the statistics for the game of beggar-my-neighbour
 * shortest - The shortest number of moves required to complete the game
 * longest - The longest number of moves required to complete the game
 * average - The average number of moves required to complete the game
*/
typedef struct {
    int shortest;
    int longest;
    float average;
} GameStats;

/**
 * @brief Generates statistics on the game of beggar-my-neighbour
 * The statistics function generates the shortest, longest, and average number of moves required to complete the game of beggar-my-neighbour
 * @param Nplayers The number of players in the game
 * @param games The number of times the game is played to calculate statistics
 * @return GameStats struct containing the shortest, longest, and average number of moves required to complete the game of beggar-my-neighbour
*/
GameStats statistics(int Nplayers, int games) {
    int shortest = INT_MAX;
    int longest = 0;
    float total = 0;

    for (int i = 0; i < games; i++) {
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
        int moves = beggar(Nplayers, deck, 0);

        if (moves < shortest) {
            shortest = moves;
        }
        if (moves > longest) {
            longest = moves;
        }
        total += moves;
    }

    GameStats stats;
    stats.shortest = shortest;///< The shortest number of moves required to complete the game
    stats.longest = longest; ///< The longest number of moves required to complete the game
    stats.average = total / games; ///< The average number of moves required to complete the game

    return stats; ///< GameStats struct containing the shortest, longest, and average number of moves required to complete the game of beggar-my-neighbour
}