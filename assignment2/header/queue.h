#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    struct node *next;
    int data;
}NODE, *PNODE;

typedef struct{
    PNODE front;
    PNODE rear;
}QUEUE, *PQUEUE;

PNODE create_node(int);
PQUEUE create_queue();
void enqueue(PQUEUE, int);
void dequeue(PQUEUE);
