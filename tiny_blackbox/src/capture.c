#include "header/capture.h"
// #include "header/frame_queue.h"

#define VIDEO "video.raw"
#define RECORD "record.raw"

void inner_function();

extern char user_input;
extern int pp;

// for display queue mutual exclusion
pthread_mutex_t display_mutex;
// for record queue mutual exclusion
pthread_mutex_t record_mutex;
// for pause handling
pthread_mutex_t pause_mutex;

void* capture_thread_func(void*)
{
    // 변수 선언.
    int record_end = 0;
    DISPLAY_ARG display_arg;
    RECORD_ARG record_arg;
    pthread_t display_thread, record_thread;

    FILE *video_file=NULL, *record_file=NULL;
    PQUEUE record_queue=NULL, display_queue=NULL;
    uint8_t *display_frame=NULL, *record_frame=NULL;

    // init mutex
    pthread_mutex_init(&display_mutex, NULL);
    pthread_mutex_init(&record_mutex, NULL);
    pthread_mutex_init(&pause_mutex, NULL);

    // create queue
    init_queue(&record_queue);
    init_queue(&display_queue);

    // display thread start
    display_arg.queue = display_queue;
    pthread_create(&display_thread, NULL, display_thread_func, (void*)&display_arg);

    // record thread start
    record_file = fopen(RECORD_FILE, "wb+");
    if(record_file == NULL) {
        printf("cannot open file %s", RECORD_FILE);
        perror("capture.c fopen error");
    }
    record_arg.queue = record_queue;
    record_arg.record_file = record_file;
    record_arg.end = &record_end;
    pthread_create(&record_thread, NULL, record_thread_func, (void*)&record_arg);

    // allocate frame memory
    display_frame = (uint8_t *)malloc(FRAME_SIZE);
    record_frame = (uint8_t *)malloc(FRAME_SIZE);

    // start video program
    while (1)
    {
        // open or reload video file
        init_video(&video_file);


        // read_video(video_file, display_queue, record_queue, &record_end, display_frame, record_frame);
        // read video and add frame to queue
        if(read_video(video_file, display_queue, record_queue, &record_end, display_frame, record_frame)){
            // replay를 위한 설정값 설정.
            init_for_replay(&record_end, record_file, record_queue, display_queue);
        }
        else break;
    }

    // wait thread termination 
    pthread_join(display_thread, NULL);
    pthread_join(record_thread, NULL);

    // free frame memory
    free(display_frame);
    free(record_frame);

    pthread_mutex_destroy(&display_mutex);
    pthread_mutex_destroy(&record_mutex);
    pthread_mutex_destroy(&pause_mutex);

    // free video file
    if(video_file != NULL) fclose(video_file);
    video_file = NULL;

    // exit thread
    pthread_exit(NULL);
}

void init_video(FILE **video_file){

    if (*video_file == NULL)
    {
        *video_file = fopen(VIDEO, "rb");
        if (*video_file == NULL)
        {
            printf("cannot open file %s\n", VIDEO);
            perror("capture.c fopen error");
            exit(1);
        }
    }
    else
    {
        fclose(*video_file);
        *video_file = NULL;
        *video_file = fopen(VIDEO, "rb");
        if (*video_file == NULL)
        {
            printf("cannot open file %s\n", VIDEO);
            exit(1);
        }
    }
}

void init_for_replay(int *record_end, FILE *record_file, PQUEUE record_queue, PQUEUE display_queue){
    // pop frames of display queue
    pthread_mutex_lock(&display_mutex);
    if (display_queue->front != NULL)
        dequeue(display_queue);
    pthread_mutex_unlock(&display_mutex);

    // 최초 녹화 성공
    if(user_input != 'r' && !(*record_end)){
        *record_end = 1;
        record_file = NULL;
        record_queue = NULL;
    }

    // 최초 녹화 전 Replay
    if (user_input == 'r' && !(*record_end)){
        while (record_queue->front != NULL)
            dequeue(record_queue);
        fseek(record_file, 0, SEEK_SET);
    }

    user_input = 'p';
}

int read_video(FILE *video_file, PQUEUE display_queue, PQUEUE record_queue, 
int *record_end, uint8_t *display_frame, uint8_t *record_frame){

    if(video_file == NULL) {
        printf("video file is NULL");
        perror("capture.c read_video()");
    }

    while (1)
    {
        // read input
        if (user_input == 'r')
            return 1;
        if (user_input == 'q')
            return 0;

        // check size of display_queue
        pthread_mutex_lock(&display_mutex);
        if (display_queue->size > MAX_QUEUE_SIZE)
        {
            pthread_mutex_unlock(&display_mutex);
            usleep(1);
            continue;
        }
        pthread_mutex_unlock(&display_mutex);

        // read frame
        if (fread(display_frame, 1, FRAME_SIZE, video_file) != FRAME_SIZE)
            break;

        // push frame on display_queue
        pthread_mutex_lock(&display_mutex);
        enqueue(display_queue, display_frame);
        pthread_mutex_unlock(&display_mutex);

        // push frame on record_queue
        if (!*record_end)
        {
            memcpy(record_frame, display_frame, FRAME_SIZE);
            pthread_mutex_lock(&record_mutex);
            enqueue(record_queue, record_frame);
            pthread_mutex_unlock(&record_mutex);
        }
    }

    return 1;
}