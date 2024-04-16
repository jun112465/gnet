#include "header/capture.h"
#include "header/input.h"

int main(){
    // 변수선언
    pthread_t input_thread;
    pthread_t capture_thread;

    // 입력 쓰레드, 캡쳐 쓰레드 실행.
    pthread_create(&capture_thread, NULL, capture_thread_func, NULL);
    pthread_create(&input_thread, NULL, input_thread_func, NULL);

    // 쓰레드 종료 대기.
    pthread_join(capture_thread, NULL);
    pthread_join(input_thread, NULL);

    return 0;
}