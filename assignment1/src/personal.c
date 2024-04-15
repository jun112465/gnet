#include "personal.h"

#define INPUT_BUFFER_SIZE 1024

void Close(PINFO_LIST);
void CLI(PINFO_LIST);

int main(){
    // initialize list
    PINFO_LIST plist = NULL;
    plist = Load();
    
    // open cli
    CLI(plist);

    // save memory to file
    Close(plist);

    return 0;
}

void CLI(PINFO_LIST list){
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
                modifyCLI(input_buffer, list);
                break;
            case 4:
                printf("[TASK] PRINT\n");
                PrintInfo(list);
                break;
            case 5:
                printf("[TASK] CLOSE\n");
                return;
            default:
                printf("[EXCEPTION] WRONG INPUT\n");
                break;
        }
    }
}


void Close(PINFO_LIST list){
    if(list != NULL)
        update_file(list);

    PrintInfo(list);

    free(list);
}
