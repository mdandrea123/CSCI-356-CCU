/*
 * my_queue.c - Implementation of queue data structure functions provided in my_queue.h
 *
 * Author: Michael Dandrea
 * Course: CSCI 356
 * Date: 10/13/2023
 */
#include <stdio.h>
#include <stdlib.h>
#include "my_queue.h"

queue newqueue() {
    queue q = (queue)malloc(sizeof(struct queueS));
    if (q != NULL) {
        q->front = NULL;
    }
    return q;
}

int isempty(const queue q) {
    return q->front == NULL;
}

void enqueue(queue q, void* item) {
    q_element* new_element = (q_element*)malloc(sizeof(q_element));
    new_element->contents = item;
    new_element->next = NULL;

    if (q->front == NULL) {
        q->front = new_element;
    } else {
        q_element* current = q->front;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_element;
    }
}

void* dequeue(queue q) {
    if (isempty(q)) {
        return NULL;
    }

    void* item = q->front->contents;
    q_element* temp = q->front;
    q->front = q->front->next;
    free(temp);
    return item;
}

void* peek(queue q) {
    if (isempty(q)) {
        return NULL;
    }
    return q->front->contents;
}
