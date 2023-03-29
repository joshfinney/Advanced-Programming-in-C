/**
 * @file demo_shuffle.c
 * @brief Demo program for the demo shuffle algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "riffle.h"

/**
 * @brief Main function for the demo program.
 *
 * @return 0 on success, non-zero on failure.
 */
int main() {
    srand(time(NULL)); // Seed random number generator

    // Shuffle an array of integers
    int arr_int[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int arr_int_len = sizeof(arr_int) / sizeof(int);
    riffle(arr_int, arr_int_len, sizeof(int), 5);

    // Check that shuffled integer array contains all original elements
    int check_int = check_shuffle(arr_int, arr_int_len, sizeof(int), cmp_int);
    printf("Check shuffled integer array: %s\n\n", check_int ? "PASS" : "FAIL");

    // Print shuffled integer array
    printf("Shuffled integer array:\n");
    printf("• ");
    for (int i = 0; i < arr_int_len; i++) {
        printf("%d ", arr_int[i]);
    }
    printf("\n\n");

    // Shuffle an array of Greek letter names
    const char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};
    int greek_len = sizeof(greek) / sizeof(char *);
    riffle(greek, greek_len, sizeof(char *), 3);

    // Check that shuffled Greek letter array contains all original elements
    int check_greek = check_shuffle(greek, greek_len, sizeof(char *), cmp_str);
    printf("Check shuffled Greek letter array: %s\n\n", check_greek ? "PASS" : "FAIL");

    // Print shuffled Greek letter array
    printf("Shuffled Greek letter array:\n");
    printf("• ");
    for (int i = 0; i < greek_len; i++) {
        printf("%s ", greek[i]);
    }
    printf("\n\n");

    return 0;
}

/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc -c demo_shuffle.c -o demo_shuffle.o 
 * gcc riffle.o demo_shuffle.o -o demo_shuffle
 * 
 * To run the program, type the following command:
 * ./demo_shuffle
 * 
 * The program will run the above function and will test check_shuffle function and will print Pass or Fail
 */