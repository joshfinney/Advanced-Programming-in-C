/**
 * @file queue.c
 * Implementation of a queue data structure.
 * @author Josh
*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief Create a new queue.
 * This function creates a new queue with the front and back pointers set to NULL
 * and the size set to 0.
 * @return A pointer to the new queue if successful, NULL otherwise.
*/
Queue *queue_create() {
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Error: could not allocate memory for queue.\n");
        return NULL;
    }
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;
    return queue;
}

/**
 * @brief Add a new element to the back of the queue.
 * This function adds a new element with the specified value to the back of the queue.
 * @param queue A pointer to the queue to add to.
 * @param value The value of the new element.
*/
void queue_enqueue(Queue *queue, int value) {
    QueueNode *new_node = malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Error: could not allocate memory for new node.\n");
        return;
    }
    new_node->value = value;
    new_node->next = NULL;

    if (queue_is_empty(queue)) {
        queue->front = new_node;
        queue->back = new_node;
    } else {
        queue->back->next = new_node;
        queue->back = new_node;
    }
    queue->size++;
}

/**
 * @brief Remove and return the element at the front of the queue.
 * This function removes and returns the element at the front of the queue.
 * @param queue A pointer to the queue to remove from.
 * @return The value of the removed element.
*/
int queue_dequeue(Queue *queue) {
    if (queue_is_empty(queue)) {
        printf("Error: cannot dequeue from an empty queue.\n");
        return -1;
    }
    QueueNode *front_node = queue->front;
    int value = front_node->value;
    queue->front = front_node->next;
    queue->size--;
    free(front_node);
    return value;
}

/**
 * @brief Return the element at the front of the queue without removing it.
 * This function returns the value of the element at the front of the queue without removing it.
 * @param queue A pointer to the queue to peek at.
 * @return The value of the element at the front of the queue.
*/
int queue_peek(Queue *queue) {
    if (queue_is_empty(queue)) {
        printf("Error: cannot peek an empty queue.\n");
        return -1;
    }
    return queue->front->value;
}

/**
 * @brief Return the element at the back of the queue without removing it.
 * This function returns the value of the element at the back of the queue without removing it.
 * @param queue A pointer to the queue to peek at.
 * @return The value of the element at the back of the queue.
*/
int queue_peek_back(Queue *queue) {
    if (queue_is_empty(queue)) {
        printf("Error: cannot peek an empty queue.\n");
        return -1;
    }
    
    return queue->back->value;

}

/**
 * @brief Check if the queue is empty.
 * This function returns true if the queue is empty, false otherwise.
 * @param queue A pointer to the queue to check.
 * @return True if the queue is empty, false otherwise.
*/
int queue_is_empty(Queue *queue) {
    return queue->size == 0;
}

/**
 * @brief Get the number of elements in the queue.
 * This function returns the number of elements in the queue.
 * @param queue A pointer to the queue to check.
 * @return The number of elements in the queue.
*/
int queue_size(Queue *queue) {
    return queue->size;
}

/**
 * @brief Remove all elements from the queue.
 * This function removes all elements from the queue.
 * @param queue A pointer to the queue to clear.
*/
void queue_clear(Queue *queue) {
    while (!queue_is_empty(queue)) {
        queue_dequeue(queue);
    }
}

/**
 * @brief Free the memory used by the queue.
 * This function frees the memory used by the queue.
 * @param queue A pointer to the queue to destroy.
*/
void queue_destroy(Queue *queue) {
    QueueNode *current_node = queue->front;
    while (current_node != NULL) {
        QueueNode *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    free(queue);
}

/**
 * @brief Print the values of the queue.
 * This function prints the values of the elements in the queue.
 * @param queue A pointer to the queue to print.
*/
void queue_print(Queue *queue) {
    if (queue == NULL || queue->front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    QueueNode *current_node = queue->front;
    while (current_node != NULL) {
        printf("%d ", current_node->value);
        current_node = current_node->next;
    }
    printf("\n");
}

