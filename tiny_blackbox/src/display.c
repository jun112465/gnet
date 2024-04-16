#include "header/display.h"

extern char user_input;
extern int pp;
extern pthread_mutex_t display_mutex;
extern pthread_mutex_t pause_mutex;

void* display_thread_func(void *arg){
    clock_t start, end;
    double cpu_time_used;
    FILE *time_file;

    DISPLAY_ARG *display_arg = (DISPLAY_ARG*)arg;
    PQUEUE queue = display_arg->queue;

    int fbfd;
    uint8_t *frame;
    unsigned char *fb, *p;
    struct fb_var_screeninfo vinfo;

    fbfd = open(FRAMEBUFFER_DEVICE, O_RDWR);
    ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
    fb = (unsigned char *)mmap(0, vinfo.yres_virtual * vinfo.xres_virtual * vinfo.bits_per_pixel / 8, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    time_file = fopen("time", "w");

    while(1){
        start = clock(); // 시작 시간 기록
    
        if(!pp) pthread_mutex_lock(&pause_mutex);
        if(user_input == 'q') break;

        pthread_mutex_lock(&display_mutex);
        if(queue->front == NULL){
            pthread_mutex_unlock(&display_mutex);
            usleep(1);
            continue;
        } 
        frame = queue->front->frame;
        pthread_mutex_unlock(&display_mutex);


        // print
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                p = fb + 4 * (vinfo.xres_virtual * i + j);
                *p = frame[i * WIDTH + j];
                *(p+1) = frame[i * WIDTH + j];
                *(p+2) = frame[i * WIDTH + j];
            }
        }

        pthread_mutex_lock(&display_mutex);
        dequeue(queue);
        pthread_mutex_unlock(&display_mutex);

        usleep(15000);

        end = clock(); // 종료 시간 기록
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // 실행 시간 계산
        fprintf(time_file, "%lf\n", cpu_time_used);
    }

    // free memory
    if(queue->front != NULL) dequeue(queue);
    free(queue);

    // exit thread
    pthread_exit(NULL);
}