/**
* @file pig.c
* @brief This file defines a function pig which takes a word in English and returns its Pig Latin translation.
* This program defines a function pig which takes a word in English and returns its Pig Latin translation. 
* If the word starts with a vowel, "way" is appended to the end of the word. 
* If the word starts with a consonant, the first consonant cluster is moved to the end of the word, followed by "ay".
* If the word starts with y then it's treated a consonant else as vowel. 
*
* @author Josh 
* @bug No known bugs.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include "pig.h"

/**
* @brief This function takes a word in English and returns its Pig Latin translation.
* This function first checks if the first character of the word is a vowel. If it is, it simply appends "way" to the end of the word and returns the resulting Pig Latin word. 
* If the first character is a consonant, the function finds the first vowel (including "y" as a vowel) and moves the consonant cluster to the end of the word, followed by "ay". 
* The function then returns the resulting Pig Latin word.
*
* @param word A pointer to the word in English to be translated.
* @return A pointer to the translated Pig Latin word.
*/

char *pig(char *word) {
    char *pig_word = malloc(strlen(word) + 3); // allocate memory for result string
    if (pig_word == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(1);
    }
    if (strchr("aeiouAEIOU", word[0])) { // if word starts with vowel
        strcpy(pig_word, word);
        strcat(pig_word, "way");
    } 
    
    else { // if word starts with consonant
        int i, len = strlen(word);
        for (i = 1; i < len; i++) {
            if (strchr("aeiouyAEIOUY", word[i])) { //also added y in condition 
                break;
            }
        }

        strcpy(pig_word, &word[i]);
        strncat(pig_word, word, i);
        strcat(pig_word, "ay");
    }
    return pig_word;
}


/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc -c pig.c -o pig.o 
 * 
*/ 