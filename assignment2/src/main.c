#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#include "../header/queue.h"
#include "../header/thread.h"
#include "../header/sort.h"

extern sem_t semaphore;

int main(){

    sort();

    return 0;
}


