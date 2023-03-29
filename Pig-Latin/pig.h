/**
* @file pig.h
* @brief This header file defines the function prototype for the pig function.
* This file defines the pig function, which takes a word in English and returns its Pig Latin translation.
* @author Josh
*/

#ifndef PIG_H
#define PIG_H

/**
* @brief Translates a word in English to its Pig Latin form.
* This function takes a word in English and returns its Pig Latin translation. If the word starts with a vowel, "way" is appended to the end of the word. If the word starts with a consonant, the first consonant cluster is moved to the end of the word, followed by "ay".
* @param word The word in English to be translated.
* @return A pointer to the translated Pig Latin word.
*/
char* pig(char* word);

#endif /* PIG_H */
