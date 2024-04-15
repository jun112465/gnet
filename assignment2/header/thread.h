#include <semaphore.h>
#include <pthread.h>

#include "../header/queue.h"

typedef struct {
    char* id;
    PQUEUE queue;
} THREAD_ARG;

void* print_thread(void *arg);
THREAD_ARG* create_arg(char *, PQUEUE);