#include "personal.h"

void Modify(PINFO_LIST list, int index, PPERSON_INFO person){
    if(index < 1 || index > list->size) {
        printf("[ERROR] index out of bound");
        return;
    }
    list->arr[index-1] = *person;

    update_file(list);

    free(person);
}

void modifyCLI(char *input_buffer, PINFO_LIST list)
{
    // search until user input 'N' or 'n'
    while (1){
        int n = search(input_buffer, list);
        if (n == 0)
            break;
    }

    // get new PERSON_INFO and Update
    get_modify_input(input_buffer, list);
}

void get_modify_input(char *input_buffer, PINFO_LIST list){
    int idx;

    printf("[INSERT INDEX] insert 0 to stop\n");
    printf("[INPUT] ");

    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    input_buffer[strlen(input_buffer)-1] = '\0';
    if(!validate_input(input_buffer, 2)){
        printf("[EXCEPTION] only numbers are allowed\n");
        return;
    }

    idx = atoi(input_buffer);
    if(idx <= 0) return;
    if(idx > list->size) {
        printf("[ERROR] index out of bound\n");
        return;
    }

    Modify(list, idx, get_person_info(input_buffer));
}