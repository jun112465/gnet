#include "header/input.h"

// pp=1 -> play
// pp=0 -> pause
int pp;
char user_input;

extern pthread_mutex_t pause_mutex;

void* input_thread_func(void*){
    char tmp;

    // 터미널에서 enter key 없이 입력 받도록 설정하기.
    init_input();

    // capture 쓰레드와 공유하는 입력 변수를 통해 프로그램 제어 
    // s p r q에 대해서만 값을 넣어서 그 외의 값에는 capture 쓰레드에서 
    // 반응을 하지 않음. 
    // p (pause or play) : pp=1(play), pp=0(pause) capture.c에서 frame을 queue에 넣는 것을 방지
    // r (replay) : capture.c에서 동영상 파일 처음부터 다시 읽기
    // q (quit) : capture.c에서 thread 종료 및 메모리 정리.
    while(user_input != 'q'){
        tmp = getchar();
        if(tmp=='p' || tmp=='r' || tmp=='q') {
            user_input = tmp;
            set_pp();
        }
    }

    // terminal clear
    system("clear");

    // thread destroy
    pthread_exit(NULL);
}

void init_input(){
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    user_input = 'p';
    pp = 1;
}

void set_pp(){
    if (user_input == 'p')
    {
        if (!pp)
            pthread_mutex_unlock(&pause_mutex);

        pp ^= 1;
        // pp ^= 1; // XOR 비트연산. 0->1, 1->0
        // pp = ~pp // NOT 비트연산. 0->1, 1->0
        // pp = !pp; // NOT 논리연산. 0->1, 1->0
    }
    else
    {
        pp = 1;
        pthread_mutex_unlock(&pause_mutex);
    }
}