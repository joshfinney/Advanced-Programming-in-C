/**
* @file main.c
* @brief This program tests the pig function by translating a list of English words to Pig Latin.
* This program creates an array of English words and passes each word to the pig function to translate to Pig Latin. 
* The translated words are then printed to the console.
* @author Josh
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* @brief Main function that tests the pig function by translating a list of English words to Pig Latin.
*
* This function creates an array of English words and passes each word to the pig function to translate to Pig Latin. The translated words are then printed to the console.
*
* @return int The exit status of the program.
*/

char *pig(char *word);

int main() {
    char *words[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};
    int len = sizeof(words)/sizeof(words[0]);

    for (int i = 0; i < len; i++) {
        char *piglatin = pig(words[i]);
        printf("%s => %s\n", words[i], piglatin);
        free(piglatin); // Free dynamically allocated memory
    }

    return 0;
}


/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc -o test_pig test_pig.c pig.c
 * 
 * To run the program, type the following command:
 * ./test_pig
 * 
 * The program will run all the test cases 
 */