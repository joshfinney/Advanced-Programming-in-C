/**
*
* @file riffle.c
* @brief This program implements the riffle shuffle of an array.
* In a riffle shuffle, the array to be shuffled will be divided into two halves, say A and B, and then reassembled into a new array.
* The first item in the new array will be the first item from one of the two half arrays, chosen with an equal probability;
* that is, there is a 50% chance that it is the first item of array A and 50% chance that it is the first item from array B.
* Likewise, each successive item in the shuffled array is, with equal probability, the next available item of A or B.
* This program defines a procedure riffle_once(void *L, int len, int size, void *work) which performs a single riffle shuffle of the array L
* each of whose len elements is of size size bytes.
* The array work is an additional array of at least the same size as L that can be used as workspace.
* @author Josh
* @bug No known bugs.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Compares two integers.
 * @param a The first integer.
 * @param b The second integer.
 * @return -1 if a < b, 0 if a == b, +1 if a > b.
 */
int cmp_int(void *a, void *b) {
    int x = *((int *) a);
    int y = *((int *) b);
    if (x < y) return -1;
    if (x == y) return 0;
    return 1;
}

/**
 * Compares two strings.
 * @param a The first string.
 * @param b The second string.
 * @return -1 if a < b, 0 if a == b, +1 if a > b.
 */
int cmp_str(void *a, void *b) {
    return strcmp((char *) a, (char *) b);
}

/**
*
* @brief This procedure performs a single riffle shuffle of the array L.
* @param L A pointer to the array to be shuffled.
* @param len The number of elements in the array.
* @param size The size of each element in bytes.
* @param work An additional array of at least the same size as L that can be used as workspace.
* @return Void.
*/
void riffle_once(void *L, int len, int size, void *work) {
    int half = len / 2;
    char *left_hand = (char *) L;
    char *dst = (char *) work;
    char *right_hand = (char *) L + half*size;
    
    int i, j;

    for (i = 0, j = 0; i < half && j < len - half; ) {
        if (rand() % 2) { // when random number generated is odd (similar as tossing a coin, probability = 0.5)
            memcpy(dst, left_hand, size);
            left_hand += size;
            i++;
        } else { // copy from second half of the array
            memcpy(dst, right_hand, size);
            right_hand += size;
            j++;
        }
        dst += size;
    }

    while (i < len/2) { // copy the remaining element in the first half of the array
        memcpy(dst, left_hand, size);
        left_hand += size;
        dst += size;
        i++;
    }

    while (j < len - len/2) { // copy the remaining element in the second half of the array
        memcpy(dst, right_hand, size);
        right_hand += size;
        dst += size;
        j++;
    }

    memcpy(L, work, len*size);
}

/**
 * @brief Shuffles an array by performing N riffles.
 *
 * @param L Pointer to the array to shuffle.
 * @param len Length of the array.
 * @param size Size of each element in the array.
 * @param N Number of riffles to perform.
 */
void riffle(void *L, int len, int size, int N) {
    void *work = malloc(len * size); // allocate memory for workspace
    if (work == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N; i++) {
        riffle_once(L, len, size, work); // shuffle work and copy to L
    }
    free(work); // free dynamically allocated memory
}



/*
Clearly, all the elements in the original array should be in the shuffled array and vice versa (why
do we need to check both ways?).
>   We check because it maybe possible that some elements value remain 0 if it is not shuffled correctly. 
    so We need to check both ways because while the shuffled array should contain all the elements from the original array, 
    it is possible that the original array may contain elements that are not in the shuffled array. 
    Checking both ways ensures that we are not missing any elements in either array.
*/


/**
 * Checks whether the shuffled array contains all elements of the original array and vice versa.
 * @param L The original array.
 * @param len The length of the array.
 * @param size The size of each element in bytes.
 * @param cmp The comparison function to compare two elements.
 * @return 1 if the shuffle is correct, 0 otherwise.
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)) {
    void *shuffled = malloc(len * size);
    if (shuffled == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(shuffled, L, len * size); // Make a copy of the original array
    riffle(shuffled, len, size, 5); // Shuffle the copied array

    // Check that all elements in the original array are in the shuffled array
    for (int i = 0; i < len; i++) {
        int found = 0;
        for (int j = 0; j < len; j++) {
            if (cmp((char *) L + i * size, (char *) shuffled + j * size) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            free(shuffled);
            return 0;
        }
    }

    // Check that all elements in the shuffled array are in the original array
    for (int i = 0; i < len; i++) {
        int found = 0;
        for (int j = 0; j < len; j++) {
            if (cmp((char *) shuffled + i * size, (char *) L + j * size) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            free(shuffled);
            return 0;
        }
    }

    free(shuffled);
    return 1;
}


/**
 * Evaluates the quality of a shuffled integer array
 *
 * The quality of a shuffle is defined as the fraction of times the second item of two adjacent
 * items is larger than the first. A well-shuffled array will have a quality close to 0.5.
 *
 * @param numbers An array of integers
 * @param len The length of the array
 * @return The quality of the shuffle as a float between 0 and 1
 */
float quality(int *numbers, int len) {
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if (numbers[i + 1] > numbers[i]) {
            count++;
        }
    }
    return (float) count / (len - 1); //len-1 because total no. of pairs will be 1 less than the length of array
}


/**
 * Evaluates the average quality of a shuffle of the integers 0, 1, ..., N-1, using riffle to shuffle the array shuffles times.
 *
 * @param N The number of integers to shuffle.
 * @param shuffles The number of times to shuffle the array using riffle.
 * @param trials The number of trials to average the quality over.
 * @return The average quality of the shuffle.
 */
float average_quality(int N, int shuffles, int trials) {
    // Allocate memory for an array of N integers
    int *numbers = (int *) malloc(N * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the array with values 0 to N-1
    for (int i = 0; i < N; i++) {
        numbers[i] = i;
    }

    // Initialize the total quality as 0
    float total_quality = 0.0;
    // Perform the riffle shuffle and quality calculation trials times
    for (int i = 0; i < trials; i++) {
        riffle(numbers, N, sizeof(int), shuffles);
        float q = quality(numbers, N);
        total_quality += q;
    }

    // Free the allocated memory
    free(numbers);

    // Calculate the average quality over all trials and return it
    return total_quality / trials;
}

/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc -c riffle.c -o riffle.o 
 * this function implements riffle_once, riffle, check_shuffle, cmp_int, cmp_str, quality, average_quality functions. 
 */