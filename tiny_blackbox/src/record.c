#include "header/record.h"

extern char user_input;

extern pthread_mutex_t record_mutex;

void* record_thread_func(void *arg){
    // capture.c에서 record 파일을 열고
    // r 버튼이 눌리면 파일을 처음부터 다시 쓰기 위해 fseek을 하게 된다. 
    // record 파일은 arg를 통해서 넘어온다. 
    RECORD_ARG *record_arg = (RECORD_ARG*)arg;
    PQUEUE queue = record_arg->queue;
    FILE *record_file = record_arg->record_file;
    int *end = record_arg->end;
    uint8_t *frame=NULL;

    while(!(*end) || queue->front){
        if(user_input == 'q') break;

        pthread_mutex_lock(&record_mutex);
        if(queue->front == NULL){
            pthread_mutex_unlock(&record_mutex);
            usleep(1);
            continue;
        }
        frame = queue->front->frame;
        fwrite(frame, FRAME_SIZE, 1, record_file);
        dequeue(queue);
        pthread_mutex_unlock(&record_mutex);
    }

    free(queue);
    queue=NULL;
    fclose(record_file);
    record_file = NULL;

    pthread_exit(NULL);
}