// #include "../header/sort.h"
#include "../header/queue.h"
#include "../header/sort.h"
#include <string.h>


void sort(){
    char input[1024];
    char *token;
    PQUEUE queue = create_queue();

    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1]=0;

    token = strtok(input, " ");
    while(token != NULL){
        enqueue(queue, atoi(token));
        token = strtok(NULL, " ");
    }

    merge_sort(queue->front);

    PNODE node = queue->front;
    while(node != NULL){
        printf("%d\n", node->data);
        node = node->next;
    }
}

NODE* split(NODE *head){
   NODE *fast = head;
   NODE *slow = head;
   NODE *prev = NULL;

    while(fast && fast->next){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // 왼쪽 리스트의 끝을 NULL로 설정하여 리스트 split
    if(prev != NULL){
        prev->next = NULL;
    }

    // 가운데 노드 return
    return slow;
}

PNODE merge(PNODE left_list, PNODE right_list){
    // 오름차순으로 정렬
    // asceding order sort

    NODE dummy;
    PNODE tail = &dummy;

    while(left_list && right_list){
        if(right_list->data > left_list->data){
            tail->next = right_list;
            right_list = right_list->next;
        } else {
            tail->next = left_list;
            left_list = left_list->next;
        }
        tail = tail->next;
    }

    // 나머지 리스트 추가하기
    tail->next = (left_list != NULL) ? left_list : right_list;

    return dummy.next;
}

PNODE merge_sort(PNODE head){
    // 노드가 한개인 경우 아래 코드를 실행하면 스스로를 참조하게 됨. 
    if(head == NULL || head->next == NULL) return head;

    NODE* mid;

    mid = split(head);
    head = merge_sort(head);
    mid = merge_sort(mid);
    head = merge(head, mid);

    return head;
}

