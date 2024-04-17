# 설명
RAW 동영상 파일을 읽어서 재생, 정지, 리플레이, 녹화 기능을 제공하는 간단한 동영상 플레이어. 5개의 쓰레드로 작동한다. 
- main thread
- input thread : 사용자의 입력값을 받는 쓰레드.
- capture thread : 출력과 녹화를 위한 값 선언 및 display thread, record thread를 실행시키는 역할. 비디오 파일의 frame 데이터를 읽고 출력을 위한 프레임 큐와 녹화를 위한 프레임 큐에 값을 넣는 역할.
- display thread : display queue에서 프레임을 하나씩 꺼내서 frame buffer에 출력하는 역할. 
- record thread : record_queue에서 프레임을 하나씩 꺼내서 새로운 record 파일에 데이터를 쓰는 역할. 

# 구조
- main.c
    - 입력을 받기위한 쓰레드 (input.c), 동영상의 프레임을 저장하는 쓰레드(capture.c)를 각각 실행시키는 역할을 한다. 

- input.c
    - q(quit), r(replay), p(pause OR play) key를 눌렀을 때 user_input에 해당 값이 들어올 수 있도록 한다.

- capture.c
    - 비디오 파일을 열어서 buffer에 프레임을 하나씩 저장하는 역할을 한다. 또한, (q,r,p) key에 대한 처리도 해준다. 동영상의 프레임을 출력하는 display thread, 동영상을 새로 저장하는 record thread를 각각 실행시킨다. 
    - 주요 컴포넌트
        - display_thread
        - display_queue : 프레임의 정보를 노드로 갖고 있는 큐. display.c에서 프레임을 하나씩 꺼내서 프레임버퍼에 출력한다. 
        - record_thread
        - record_queue : 프레임의 정보를 노드로 갖고 있는 큐. record.c에서 프레임을 하나씩 꺼내서 새로운 동영상 파일에 프레임값을 입력한다. 

- frame_queue.c
	- 프레임을 저장하기 위한 node 구조체와 list 구조체와 메소드 구현. (연결리스트로 구현)
	- NODE, *PNODE (uint8_t *frame, PNODE next)
	- QUEUE, *PQUEUE (PNODE front, PNODE rear)
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