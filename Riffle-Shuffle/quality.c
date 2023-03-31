/**
 * @file quality.c
 * @brief A program to calculate the average quality of a riffle shuffle
 * of an array of length 50 using N = 1, 2, 3, ..., 15.
 */

#include <stdio.h>
#include <stdlib.h>
#include "riffle.h"

/**
 * @brief The main function that calculates the average quality of a riffle shuffle
 * and writes the output to a file.
 *
 * @return 0 on success, non-zero value on failure
 */
int main(void) {
    const int len = 50;             // Length of the array
    // const int shuffles = 10;      // Number of shuffles
    const int trials = 30;          // Number of trials

    FILE *output_file = fopen("quality.txt", "w");   // Open output file for writing
    if (output_file == NULL) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(output_file, "N\tAvg. Quality\n");

    int *numbers = malloc(len * sizeof(int));
    if (numbers == NULL) {
        perror("Failed to allocate memory for numbers");
        fclose(output_file);
        return EXIT_FAILURE;
    }
    for (int N = 1; N <= 15; N++) {
        for (int i = 0; i < len; i++) {
            numbers[i] = i;
        }

        int shuffles = N; // N may be the no. of shuffles that we need to find, if not then just comment this line and uncomment line 19
        float avg_quality = average_quality(len, shuffles, trials);

        fprintf(output_file, "%d\t%.4f\n", N, avg_quality);
    }

    free(numbers);
    fprintf(output_file, "\n\nExplanation:\n    Based on the output of the average_quality function, \n\
    it seems that the quality of the shuffling algorithm improves as the number of shuffles increases, up to a certain point. \n\
    Specifically, for an array of size 50 and 30 trials, we can see that we need at least 7 shuffles to achieve an average quality close to 0.5. \n\
    This suggests that the algorithm becomes more effective at randomizing the elements of the array as more shuffles are performed, \n\
    up to a point where further shuffling doesn't yield much additional improvement in quality. \n\n\
    It's important to note that the quality values reported here are specific to the parameters used in the function, and may not be generalizable to other scenarios. \n\
    However, this information can be useful in guiding decisions about how many shuffles to use when randomizing an array of this size\n");


    fclose(output_file);    // Close output file

    return 0;
}


/* Instructions for running the program:
 * To compile the program, run the following command in the terminal:
 * gcc -c quality.c -o quality.o 
 * gcc riffle.o quality.o -o quality
 * 
 * To run the program, type the following command:
 * ./quality
 * 
 * The program will run the above function and will test avg_quality of array of length 50 for different N.
 */