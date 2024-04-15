#include "header/frame_queue.h"
#include <stdlib.h>
#include <stdint.h>

void init_queue(PQUEUE *queue){
    *queue = malloc(sizeof(QUEUE));
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->size = 0;
}

void enqueue(PQUEUE queue, uint8_t *frame){

    PNODE newnode = malloc(sizeof(NODE));
    newnode->frame = frame;
    newnode->next = NULL;

    if(queue->front == NULL) {
        queue->front = newnode;
        queue->rear = newnode;
    }else{
        queue->rear->next = newnode;
        queue->rear = newnode;
    }

    queue->size++;
}

void dequeue(PQUEUE queue){
    if(queue->front == NULL) return;

    PNODE tmp = queue->front;
    queue->front = queue->front->next;
    if(queue->front == NULL) queue->rear = NULL;
    queue->size--;

    free(tmp);
}