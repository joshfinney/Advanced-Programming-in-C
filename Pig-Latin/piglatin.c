/**
* @file piglatin.c
* @brief This program takes input of English text and translates it to Pig Latin.
* This program repeatedly asks the user for a line of English text and prints the corresponding Pig Latin translation.
* This program uses a function pig from pig.c file which return the translated Pig latin word.
* The program stops when the user inputs an empty line.
*
* @author Josh <id>
* @bug No known bugs.
*/

/* -- Includes -- */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pig.h"

/**
* @brief This function repeatedly asks the user for a line of English text and prints the corresponding Pig Latin translation.
* The program stops when the user inputs an empty line.
* @return Void.
*/

void piglatin() {
    char line[1000];
    while (1) {
        printf("Enter a line of English text (empty line to exit): ");
        fgets(line, sizeof(line), stdin);
        // check input validity
        int valid = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isalpha(line[i]) && !isspace(line[i]) && line[i] != '\n') {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("Invalid input! Input should only contain alphabets, spaces, and new line.\n");
            continue;
        }
        //if input is valid
        if (line[0] == '\n') {
            break;
        }
        char *word = strtok(line, " \t\n");
        while (word != NULL) {
            char *translation = pig(word);
            printf("%s ", translation);
            free(translation);
            word = strtok(NULL, " \t\n");
        }
        printf("\n");
    }
}

/**
* @brief Main function to call piglatin function.
* @return int The exit status of the program.
*/

int main() {
    piglatin();
    return 0;
}

/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc -o piglatin piglatin.c pig.c
 * 
 * To run the program, type the following command:
 * ./piglatin
 * 
 * The program will ask you to input lines of English text, and it will output the corresponding Pig Latin translations. To exit the program, input an empty line. */