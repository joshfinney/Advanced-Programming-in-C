/**
 * @file queue.h
 * Header file for a queue data structure.
 * @author Josh
*/

#ifndef QUEUE_H
#define QUEUE_H

/**
 * @brief Struct representing a node in the queue.
*/
typedef struct QueueNode {
    int value; /**< The value of the node. */
    struct QueueNode *next; /**< A pointer to the next node in the queue. */
} QueueNode;

/**
 * @brief Struct representing a queue data structure.
*/
typedef struct Queue {
    QueueNode *front; /**< A pointer to the front node in the queue. */
    QueueNode *back; /**< A pointer to the back node in the queue. */
    int size; /**< The number of nodes in the queue. */
} Queue;

/**
 * @brief Create a new queue.
 * This function creates a new queue with the front and back pointers set to NULL
 * and the size set to 0.
 * @return A pointer to the new queue if successful, NULL otherwise.
*/
Queue *queue_create();

/**
 * @brief Add a new element to the back of the queue.
 * This function adds a new element with the specified value to the back of the queue.
 * @param queue A pointer to the queue to add to.
 * @param value The value of the new element.
*/
void queue_enqueue(Queue *queue, int value);

/**
 * @brief Remove and return the element at the front of the queue.
 * This function removes and returns the element at the front of the queue.
 * @param queue A pointer to the queue to remove from.
 * @return The value of the removed element.
*/
int queue_dequeue(Queue *queue);

/**
 * @brief Return the element at the front of the queue without removing it.
 * This function returns the value of the element at the front of the queue without removing it.
 * @param queue A pointer to the queue to peek at.
 * @return The value of the element at the front of the queue.
*/
int queue_peek(Queue *queue);

/**
 * @brief Return the element at the back of the queue without removing it.
 * This function returns the value of the element at the back of the queue without removing it.
 * @param queue A pointer to the queue to peek at.
 * @return The value of the element at the back of the queue.
*/
int queue_peek_back(Queue *queue);

/**
 * @brief Check if the queue is empty.
 * This function returns true if the queue is empty, false otherwise.
 * @param queue A pointer to the queue to check.
 * @return True if the queue is empty, false otherwise.
*/
int queue_is_empty(Queue *queue);

/**
 * @brief Get the number of elements in the queue.
 * This function returns the number of elements in the queue.
 * @param queue A pointer to the queue to check.
 * @return The number of elements in the queue.
*/
int queue_size(Queue *queue);

/**
 * @brief Remove all elements from the queue.
 * This function removes all elements from the queue.
 * @param queue A pointer to the queue to clear.
*/
void queue_clear(Queue *queue);

/**
 * @brief Free the memory used by the queue.
 * This function frees the memory used by the queue.
 * @param queue A pointer to the queue to destroy.
*/
void queue_destroy(Queue *queue);

/**
 * @brief Print the values of the queue.
 * This function prints the values of the elements in the queue.
 * @param queue A pointer to the queue to print.
*/
void queue_print(Queue *queue);

#endif /* QUEUE_H */
