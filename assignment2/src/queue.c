#include "../header/queue.h"


PNODE create_node(int data){
    PNODE node = (PNODE)malloc(sizeof(NODE));
    node->data = data;
    node->next = NULL;
    return node;
}

PQUEUE create_queue(){
    PQUEUE q = (PQUEUE)malloc(sizeof(QUEUE));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(PQUEUE queue, int data){
    PNODE newnode = create_node(data);

    if(queue->front == NULL){
        queue->front = newnode;
        queue->rear = newnode;
        return;
    }

    queue->rear->next = newnode;
    queue->rear = newnode;
}

void dequeue(PQUEUE queue){
    if(queue->front == NULL){
        perror("queue is empty");
        exit(1);
    }

    PNODE front = queue->front;
    queue->front = queue->front->next;
    free(front);
}
