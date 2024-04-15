# 설명
RAW 동영상 파일을 읽어서 재생, 정지, 리플레이, 녹화 기능을 제공하는 간단한 동영상 플레이어.

# 구조
- **main.c** 
    - 입력을 받기위한 쓰레드 (input.c), 동영상의 프레임을 저장하는 쓰레드(capture.c)를 각각 실행시키는 역할을 한다. 
    - 주요 컴포넌트
        - char user_input (전역변수) 
- input.c
    - s(start), q(quit), r(replay), p(pause) key를 눌렀을 때 user_input에 해당 값이 들어올 수 있도록 한다.

- capture.c
    - 비디오 파일을 열어서 buffer에 프레임을 하나씩 저장하는 역할을 한다. 또한, (q,r,p) key에 대한 처리도 해준다. 동영상의 프레임을 출력하는 display thread, 동영상을 새로 저장하는 record thread를 각각 실행시킨다. 
    - 주요 컴포넌트
        - display_thread
        - display_queue : 프레임의 정보를 노드로 갖고 있는 큐. display.c에서 프레임을 하나씩 꺼내서 프레임버퍼에 출력한다. 
        - record_thread
        - record_queue : 프레임의 정보를 노드로 갖고 있는 큐. record.c에서 프레임을 하나씩 꺼내서 새로운 동영상 파일에 프레임값을 입력한다. 
    - queue.c
        - 프레임을 저장하기 위한 node 구조체와 list 구조체와 메소드 구현.
        - NODE, *PNODE
        - QUEUE, *PQUEUE
        - enqueue()
        - dequeue() 
    - display.c
        - display_thread에서 실행시킬 함수가 구현됐다. 
        - display_queue에서 프레임을 하나씩 꺼내서 프레임버퍼에 출력한다. 
        - capture.c에서 동영상을 무한반복문으로 계속 프레임을 읽어서 display_queue에 저장한다. display_thread에서는 해당 큐에서 q버튼이 눌리기 전까지 지속적으로 프레임버퍼에 프레임 출력.
    - record.c
        - record_thread에서 실행시킬 함수가 구현됐다. 
        - record_queue에서 프레임을 하나씩 꺼내서 새로운 동영상 파일에 저장한다. 
        - 처음 동영상을 다 읽으면 메모리를 해제하고 쓰레드가 종료된다. 


# troubleshooting

### 쓰레드 동기화 
세마포어를 통해 임계영역에 대한 동기화를 하는 경우 항상 스레드가 실행되기전에 세마포어를 미리 초기화 해놓자. 세마포어를 초기화 하지 않은 상태에서 스레드가 실행되어 sem_wait()을 하게되면 무한 기다림에 빠질 수 있다. 
또한, sem_wait()을 두번 연속 사용하여 교착상태에 빠진경우도 있다. sem_post()를 꼭 사용하자. 무한대기 상태에 빠진 경우 초기화가 잘됐는지, sem_post()로 작성해야할 코드를 sem_wait()으로 실수로 작성하진 않았는지 확인하자. 

## munmap_chunck(): invalid pointer


## double free or corruption (out)
동적으로 할당된 메모리에 대해서 다시 해제하는 경우 발생하는 에러.
