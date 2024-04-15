#include <termios.h>
#include "header/capture.h"
#include "header/input.h"

char user_input;

int main(){
    // 변수선언
    pthread_t input_thread;
    pthread_t capture_thread;
    user_input = 'p';

    // 입력을 위한 터미널 설정.
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    // 입력 쓰레드, 캡쳐 쓰레드 실행.
    pthread_create(&capture_thread, NULL, capture_thread_func, NULL);
    pthread_create(&input_thread, NULL, input_thread_func, NULL);
    pthread_join(capture_thread, NULL);
    pthread_join(input_thread, NULL);

    // terminal clear
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 터미널 원래 설정으로
    system("clear");

    return 0;
}