#include "header/input.h"

// pp=1 -> play
// pp=0 -> pause
int pp = 1;
extern char user_input;
extern pthread_mutex_t pause_mutex;

void* input_thread_func(void*){

    // capture 쓰레드와 공유하는 입력 변수를 통해 프로그램 제어 
    // s p r q에 대해서만 값을 넣어서 그 외의 값에는 capture 쓰레드에서 
    // 반응을 하지 않음. 
    char tmp;

    while(user_input != 'q'){
        tmp = getchar();

        if(tmp=='p' || tmp=='r' || tmp=='q') {
            user_input = tmp;

            if (user_input == 'p'){
                if (!pp)
                    pthread_mutex_unlock(&pause_mutex);
                pp ^= 1; // XOR 비트연산. 0->1, 1->0
                // pp = ~pp // NOT 비트연산. 0->1, 1->0
                // pp = !pp; // NOT 논리연산. 0->1, 1->0
            }
            else{
                pp = 1;
                pthread_mutex_unlock(&pause_mutex);
            }
        }

        // p (pause or play) : pp=1(play), pp=0(pause) capture.c에서 frame을 queue에 넣는 것을 방지
        // r (replay) : capture.c에서 동영상 파일 처음부터 다시 읽기
        // q (quit) : capture.c에서 thread 종료 및 메모리 정리.
    }

    pthread_exit(NULL);

}