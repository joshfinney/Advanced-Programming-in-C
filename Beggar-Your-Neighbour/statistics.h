#ifndef BEGGAR_H
#define BEGGAR_H

#include <limits.h>

typedef struct {
    int shortest;
    int longest;
    float average;
} GameStats;

/**
 * Calculates the shortest, longest, and average number of moves in a game of beggar
 * with the given number of players and number of games.
 *
 * @param Nplayers the number of players in the game
 * @param games the number of games to play
 * @return a GameStats struct containing the shortest, longest, and average number of moves
 */
GameStats statistics(int Nplayers, int games);

#endif /* BEGGAR_H */
