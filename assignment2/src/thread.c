#include <string.h>

#include "../header/queue.h"
#include "../header/thread.h"

sem_t semaphore;

void* print_thread(void *arg){
    THREAD_ARG *thread_arg = (THREAD_ARG*)arg;
    FILE *fp; 
    int data;
    char log[20] = "LOG_";

    fp = fopen(strcat(log, thread_arg->id), "wb+");

    while(1){
        sem_wait(&semaphore);
        if(thread_arg->queue->front == NULL) {
            sem_post(&semaphore);
            fclose(fp);
            pthread_exit(NULL);
        }

        data = thread_arg->queue->front->data; 
        printf("[THREAD %s] %d\n", thread_arg->id, data);
        // print on log
        fprintf(fp, "%d", data);

        dequeue(thread_arg->queue);

        sem_post(&semaphore); 
    }
}

THREAD_ARG* create_arg(char *id, PQUEUE queue){
    THREAD_ARG* arg = malloc(sizeof(THREAD_ARG));
    arg->id = id;
    arg->queue = queue;
    return arg;
}