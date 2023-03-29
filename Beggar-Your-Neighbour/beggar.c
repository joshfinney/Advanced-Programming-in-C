/**
 * @file beggar.c
 * @brief Main game logic for Beggar My Neighbour card game.
 * The game is played with a standard deck of 52 cards, divided evenly among a number of players. Each player's hand is
 * kept in a queue. Players take turns playing the top card of their queue, and the winner is the player who collects
 * all of the cards.
 * @author Josh
 * 
*/
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

Queue *take_turn(Queue *player, Queue *pile) {
    Queue *reward = queue_create(); // create a new queue to hold the reward cards
    // Check if current player has no cards left
    if (queue_is_empty(player)) {
        return reward;
    }
    int paying_penalty = 0;
    int penalty = 1;
    // Determine the penalty based on the top card on the pile
    if (queue_is_empty(pile)) {
        penalty = 1;
    } else if (queue_peek_back(pile) == 11) {
        paying_penalty = 1;
        penalty = 1;
    } else if (queue_peek_back(pile) == 12) {
        paying_penalty = 1;
        penalty = 2;
    } else if (queue_peek_back(pile) == 13) {
        penalty = 3;
        paying_penalty = 1;
    } else if (queue_peek_back(pile) == 14) {
        penalty = 4;
        paying_penalty = 1;
    }
    for (int i = 0; i < penalty; i++) {
        if(!queue_is_empty(player)){
            int top_card = queue_dequeue(player); // take the top card from current player's hand
            queue_enqueue(pile, top_card); // add the card to the pile
            // Check if the top card is a penalty card
            // Either current player dont have to pay penalty or current player played penalty card himself
            if (paying_penalty == 0 || top_card >= 11) { 
                return reward; // exit the loop and return an empty reward queue if a penalty card is played
            }
        }
        else{ // current player don't have enough card to pay the penalty so break and add all the cards from pile as reward
            break;
        }
    }
    //code will reach here only if paying_penalty is 1 (current player had to pay the penalty and he hasn't played any penalty card while paying the penalty)

    // transfer all elements from the pile to the reward queue
    while (!queue_is_empty(pile)) {
        int card = queue_dequeue(pile);
        queue_enqueue(reward, card);
    }
    return reward;
}

/**
 * @brief Function to check if the game is finished.
 * The game is finished when only one player has all the cards.
 * @param players Queue double pointer to an array of player queues.
 * @param Nplayers Integer value for the number of players in the game.
 * @return 1 if game is finished, 0 otherwise.
*/
int finished(Queue **players, int Nplayers) {
    int count_empty = 0; // Count of empty queues
    int idx_nonempty = -1; // Index of non-empty queue
    int deck_size = 52;
    
    for (int i = 0; i < Nplayers; i++) {
        if (queue_size(players[i]) == 0) { // Check if queue is empty
            count_empty++;
        } else {
            idx_nonempty = i;
        }
    }
    
    if (count_empty == Nplayers - 1 && queue_size(players[idx_nonempty]) == deck_size) { // Check if only one queue is non-empty
        return 1;
    } else {
        return 0;
    }
}

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
int beggar(int Nplayers, int *deck, int talkative) {
    // Initialize variables
    int deck_length = 52;
    /*
    In the shuffle.c provided, if the seed value is negative, then time(NULL) is used to seed the random number generator. 
    This is because time(NULL) returns the current time in seconds since January 1, 1970, which is different for each program run, 
    ensuring that the random number sequence produced by the generator will be different each time the program is run. 
    However, if seed is a non-negative integer, then it is used as the seed value for the random number generator. 
    This can be useful if you want to produce the same sequence of random numbers each time the program is run, by using the same seed value.
    */
    int seed = 10; 
    // shuffle deck using the shuffle function from shuffle.c
    shuffle(deck, deck_length, seed);

    printf("Deck After Shuffle: ");
    for(int i = 0; i < 52; i++){
        printf(" %d", deck[i]);
    }
    printf("\n");
    // int deck_length = sizeof(deck) / sizeof(int);
    Queue **players = malloc(Nplayers * sizeof(Queue *));
    if (players == NULL) {
        printf("Error: failed to allocate memory for players\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < Nplayers; i++) {
        players[i] = queue_create();
    }

    // Fill the players' hands
    for (int i = 0; i < deck_length; i++) {
        int player_index = i % Nplayers;
        queue_enqueue(players[player_index], deck[i]);
    }

    // Initialize other variables
    Queue *pile = queue_create();
    int penalty = 0;
    int turn = 0;
    int penalty_player = -1;
    int current_player = 0;
    int paying_penalty = 0;
    int false_turn = 0;
    
    // Loop until only one player have all the cards, we are not suppose to check who won, we just have to return the no. of turns
    while (!finished(players, Nplayers)) {
        current_player = turn % Nplayers;
        turn++;

        //if current player is the only player left (paying penalty to herself)
        if (penalty_player == current_player){
            break;
        }
        // Check if current player has no cards left
        if (queue_is_empty(players[current_player])) {
            // current player is already out, so we are not counting it a turn. 
            false_turn++;
            continue;
        }

        // Determine the penalty based on the top card on the pile
        if (queue_is_empty(pile)) {
            penalty = 1;
        } else if (queue_peek_back(pile) == 11) {
            paying_penalty = 1;
            penalty = 1;
        } else if (queue_peek_back(pile) == 12) {
            paying_penalty = 1;
            penalty = 2;
        } else if (queue_peek_back(pile) == 13) {
            penalty = 3;
            paying_penalty = 1;
        } else if (queue_peek_back(pile) == 14) {
            penalty = 4;
            paying_penalty = 1;
        }

        // Print current turn and player
        if (talkative != 0) {
            printf("\nTurn %d Player %d to lay %d card\n", turn, current_player, penalty);
            if (paying_penalty == 1) {
                printf("Player %d is paying the penalty of %d cards\n\n", current_player, penalty);
            }printf("Pile: ");
            queue_print(pile);
            printf("\n");
            for (int i = 0; i < Nplayers; i++) {
                printf("Player %d: ", i);
                queue_print(players[i]);
                printf("\n");
            }
        }

        // Call take_turn() and store the result in reward
        Queue *reward = take_turn(players[current_player], pile);
        
        // If reward is not empty, add all values to the previous player's queue who laid the penalty card
        if (!queue_is_empty(reward)) {
            while (!queue_is_empty(reward)) {
                int card = queue_dequeue(reward);
                queue_enqueue(players[penalty_player], card);
            }
            penalty_player = -1; //reset penalty player
        } else{
            // pile won't be empty if it comes in else because either pile can be empty or reward (both can't be empty at same time)
            // if current player laid a penalty card, she'll receive the penalty from next player
            if(queue_peek_back(pile) >= 11){
                penalty_player = current_player;
            }
        }


    }

    // Free the memory used by the players' hands
    for (int i = 0; i < Nplayers; i++) {
        queue_destroy(players[i]);
    }
    free(players);

    // Free the memory used by the pile
    queue_destroy(pile);

    // Subtracting the false turns
    return turn - false_turn;
}

/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc -c beggar.c -o beggar.o 
 * gcc beggar.c shuffle.c single.c queue.c -lgsl -lgslcblas -lm -o single
 * This function implements take turns (to take turn for current player on each turn), 
 * finished (to check if game is finished) and beggar (complete algorithm which uses 
 * finished and take turns and finally return number of turns)
*/



/*
deck length:{52}Deck After Shuffle:  10 6 14 8 13 4 13 2 11 6 14 10 14 4 4 9 5 3 6 5 11 12 10 6 7 5 13 2 7 13 9 12 3 2 11 3 12 9 8 3 14 4 8 7 11 10 7 9 8 2 5 12

Turn 1 Player 0 to lay 1 card
Pile: Queue is empty

Player 0: 10 8 13 6 14 9 6 12 7 2 9 2 12 3 8 10 8 12 

Player 1: 6 13 2 14 4 5 5 10 5 7 12 11 9 14 7 7 2 

Player 2: 14 4 11 10 4 3 11 6 13 13 3 3 8 4 11 9 5 
:
:
:
Turn 333 Player 2 to lay 1 card
Pile: 2 10 5 

Player 0: 13 2 10 6 3 13 4 7 11 5 11 4 6 14 5 12 14 7 4 3 14 8 11 12 5 6 8 9 3 8 7 3 7 13 2 2 12 9 12 6 14 10 4 13 10 9 11 8 

Player 1: Queue is empty

Player 2: 9 
*/