#include "personal.h"

void CLI(PLIST);
void MODIFY_CLI(char*, PLIST);

int main(){
    PLIST list = Load();
    CLI(list);
    return 0;
}

void CLOSE(PLIST list){
    PNODE curnode = list->head;
    PNODE tmp;

    while(curnode->next != NULL){
        tmp = curnode;
        curnode = curnode->next;

        free(tmp->person);
        free(tmp);
    }

    free(list);
}

void CLI(PLIST list){
    // buffer for every input
    char input_buffer[INPUT_BUFFER_SIZE] = {'\0',};
    int task_no;

    while(1){
        printf("\n**INSERT TASK NUMBER**\n\n");
        printf("1. [ADD]\n");
        printf("2. [DELETE]\n");
        printf("3. [MODIFY]\n");
        printf("4. [PRINT]\n");
        printf("5. [CLOSE]\n");
        printf("\n[INPUT] ");

        task_no = get_int(input_buffer);

        switch(task_no){
            case 1:
                printf("[TASK] ADD\n");
                Add(list, get_person_info(input_buffer));
                break;
            case 2:
                printf("[TASK] DELETE\n");
                printf("[INSERT INDEX] ");
                Delete(list, get_int(input_buffer));
                break;
            case 3:
                printf("[TASK] MODIFY\n");
                MODIFY_CLI(input_buffer, list);
                break;
            case 4:
                printf("[TASK] PRINT\n");
                PrintInfo(list);
                break;
            case 5:
                printf("[TASK] CLOSE\n");
                CLOSE(list);
                return;
            default:
                printf("[EXCEPTION] WRONG INPUT\n");
                break;
        }
    }
}



void MODIFY_CLI(char *input_buffer, PLIST list)
{
    int idx;
    int again = 0;

    // search until user input 'N' or 'n'
    while (1){
        printf("[SEARCH BY NAME, AGE, PHONE] ");
        fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
        input_buffer[strlen(input_buffer) - 1] = '\0'; // 개행 문자 제거

        printf("[RESULT]\n");
        printf("[INDEX] : [NAME, AGE, PHONE]\n");
        search(input_buffer, list);

        again = ask_search_again(input_buffer);
        if(!again) break;
    }

    printf("[ALARM] insert index to modify OR insert -1 to end\n");
    printf("[INPUT] ");
    idx = get_int(input_buffer);
    if(idx < 0){
        printf("[ALARM] ended\n");
        return;
    } 
    else if(idx >= list->size) {
        printf("[ERROR] index out of bound\n");
        return;
    }else{
        printf("[ALARM] insert new information\n");
        Modify(list, idx, get_person_info(input_buffer));
    }
}