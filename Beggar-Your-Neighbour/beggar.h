#ifndef BEGGAR_H
#define BEGGAR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include "shuffle.h"
#include "time.h"
#include "queue.h"

/**
 * @brief Function to play one turn of the game for a player.
 * @param player Queue pointer to the player queue whose turn it is to play.
 * @param pile Queue pointer to the pile queue on which cards are added during each turn.
 * @return Queue pointer to the reward queue which either contains all the cards from pile with empty pile or empty reward queue.
*/
Queue *take_turn(Queue *player, Queue *pile);

/**
 * @brief Function to check if the game is finished.
 * The game is finished when only one player has all the cards.
 * @param players Queue double pointer to an array of player queues.
 * @param Nplayers Integer value for the number of players in the game.
 * @return 1 if game is finished, 0 otherwise.
*/
int finished(Queue **players, int Nplayers);

/**
 * @brief The function beggar simulates the game of Beggar My Neighbour
 * @param Nplayers Number of players in the game
 * @param deck Pointer to an array of integers representing the deck of cards
 * @param talkative Integer flag to indicate whether to print game details
 * @return The number of turns played in the game
 * This function takes in the number of players, a deck of cards and a talkative flag
 * as input and simulates the game of Beggar My Neighbour according to the rules of the game.
 * It returns the number of turns played in the game. The deck is shuffled using the shuffle()
 * function from shuffle.c. Players' hands are filled by dealing out the cards from the deck.
 * The game continues until only one player has all the cards. During each turn, the current
 * player lays down a card and performs any required actions, such as paying a penalty, if the
 * card is a penalty card. The turn then passes to the next player. If a player has no cards left,
 * they are skipped. The game continues until only one player has all the cards.
*/
int beggar(int Nplayers, int *deck, int talkative);

#endif /* BEGGAR_H */
