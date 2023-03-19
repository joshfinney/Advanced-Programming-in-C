/**
 * @file riffle.h
 * @brief Header file for riffle.c, a library for shuffling arrays.
 */

#ifndef RIFFLE_H_
#define RIFFLE_H_

#include <stdlib.h>

/**
 * @brief Compares two integers.
 *
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 * @return -1 if the first integer is less than the second, 0 if they are equal, or 1 if the first integer is greater than the second.
 */
int cmp_int(const void *a, const void *b);

/**
 * @brief Compares two strings.
 *
 * @param a Pointer to the first string.
 * @param b Pointer to the second string.
 * @return -1 if the first string is less than the second, 0 if they are equal, or 1 if the first string is greater than the second.
 */
int cmp_str(const void *a, const void *b);

/**
 * @brief Shuffles an array by performing N riffles.
 *
 * @param L Pointer to the array to shuffle.
 * @param len Length of the array.
 * @param size Size of each element in the array.
 * @param N Number of riffles to perform.
 */
void riffle(void *L, int len, int size, int N);

/**
 * @brief Performs one riffle operation on an array.
 *
 * @param L Pointer to the array to riffle.
 * @param len Length of the array.
 * @param size Size of each element in the array.
 * @param work Pointer to a work array of the same size as L.
 */
void riffle_once(void *L, int len, int size, void *work);

/**
 * @brief Checks that an array has been properly shuffled.
 *
 * @param L Pointer to the shuffled array.
 * @param len Length of the array.
 * @param size Size of each element in the array.
 * @param cmp Function to compare two elements in the array.
 * @return 1 if the array has been properly shuffled, 0 otherwise.
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(const void *, const void *));

/**
 * Calculate the quality of a shuffle
 *
 * @param numbers the array of integers to be evaluated
 * @param len the length of the array
 * @return the quality of the shuffle as a fraction
 */
float quality(int *numbers, int len);

/**
 * Calculate the average quality of a shuffle
 *
 * @param N the number of integers to shuffle
 * @param shuffles the number of times to shuffle the array
 * @param trials the number of times to evaluate the shuffle quality
 * @return the average quality of the shuffle as a fraction
 */
float average_quality(int N, int shuffles, int trials);

#endif /* RIFFLE_H_ */
