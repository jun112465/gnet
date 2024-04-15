#pragma once
#include <stdint.h>
#define MAX_QUEUE_SIZE 1


typedef struct node{
    uint8_t *frame;
    struct node *next;
}NODE, *PNODE;

typedef struct{
    PNODE front;
    PNODE rear;
    int size; 
}QUEUE, *PQUEUE;


void init_queue(PQUEUE *);
void enqueue(PQUEUE queue, uint8_t *);
void dequeue(PQUEUE queue);
