#include "personal.h"

void add_dummy_data(PINFO_LIST plist){
    PERSON_INFO person;
    person.nAge = 27;
    snprintf(person.szNam, MAX_NAME_LENGTH, "John Doeabcdefghijklmn");
    snprintf(person.szPhone, MAX_PHONE_LENGTH, "123-456-7890");
    Add(plist, &person);
    

    PERSON_INFO person1;
    person1.nAge = 26;
    snprintf(person1.szNam, MAX_NAME_LENGTH, "abcdefghijklmn");
    snprintf(person1.szPhone, MAX_PHONE_LENGTH, "123-456-7890");
    Add(plist, &person1);
}

int equal(PPERSON_INFO p1, PPERSON_INFO p2){

    if(p1->nAge == p2->nAge
    && strcmp(p1->szNam, p2->szNam)==0
    && strcmp(p1->szPhone, p2->szPhone)==0)
        return 1;
        
    return 0;
}

// update file data with memory list
void update_file(PINFO_LIST list){
    FILE *fp;

    remove(LIST_FILE);

    fp = fopen(LIST_FILE, "wb");
    fwrite(list->arr, sizeof(PERSON_INFO), list->size, fp);

    fclose(fp);
}

int validate_input(const char *str, int type) {
    int (*handler_ptr)(int);

    switch(type){
        case 1: 
            // check all char is alphabet
            handler_ptr = isalpha;
            break;
        case 2:
            // check all char is digit
            handler_ptr = isdigit;
            break;
        default:
            return 0;
    }

    if (str == NULL) return 0; // NULL 포인터가 입력되면 실패로 처리

    while (*str != '\0'){
        if (!handler_ptr(*str))
            return 0; // 알파벳이 아닌 문자가 포함된 경우 실패로 처리
        str++;
    }
    return 1; // 모든 문자가 알파벳이거나 숫자인 경우 성공
}

int search(char *input_buffer, PINFO_LIST list){

    printf("[SEARCH BY NAME, AGE, PHONE] ");

    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    input_buffer[strlen(input_buffer) - 1] = '\0'; // 개행 문자 제거

    printf("[RESULT]\n");
    printf("[INDEX] : [NAME, AGE, PHONE]\n");

    // search by name
    if(validate_input(input_buffer, 1)){
        for(int i=0; i<list->size; i++){
            if(strcmp(list->arr[i].szNam, input_buffer) == 0){
                PPERSON_INFO person = &list->arr[i];
                printf("[%d] : [%s, %d, %s]\n", i + 1, person->szNam, person->nAge, person->szPhone);
            }
        }
    }

    // search by age or phone
    if(validate_input(input_buffer, 2)){
        for (int i = 0; i < list->size; i++){
            if (strcmp(list->arr[i].szPhone, input_buffer)==0 || list->arr[i].nAge==atoi(input_buffer)){
                PPERSON_INFO person = &list->arr[i];
                printf("[%d] : [%s, %d, %s]\n", i + 1, person->szNam, person->nAge, person->szPhone);
            }
        }
    }

    printf("[ALARM] search again? [Y/N] ");
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    input_buffer[strlen(input_buffer) - 1] = '\0';

    if(strcmp(input_buffer, "N")==0 || strcmp(input_buffer, "n")==0) return 0;
    else return 1;
}


PPERSON_INFO get_person_info(char *input_buffer){
    PPERSON_INFO person;

    person = malloc(sizeof(PERSON_INFO));

    printf("[NAME]");
    printf("[MAX_LENGTH=%d] ", MAX_NAME_LENGTH);
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    input_buffer[strlen(input_buffer) - 1] = '\0'; // 개행 문자 제거
    if(!validate_input(input_buffer, 1)){
        printf("[EXCEPTION] only alphabets are allowed\n");
        free(person);
        return NULL;
    }
    strncpy(person->szNam, input_buffer, MAX_NAME_LENGTH);
    person->szNam[MAX_NAME_LENGTH] = '\0';

    printf("[AGE] ");
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    input_buffer[strlen(input_buffer) - 1] = '\0'; // 개행 문자 제거
    if(!validate_input(input_buffer, 2)){
        // NAN 
        printf("[EXCEPTION] only numbers are allowed\n");
        free(person);
        return NULL;
    }
    person->nAge = atoi(input_buffer);


    printf("[PHONE]");
    printf("[MAX_LENGTH=%d] ", MAX_PHONE_LENGTH);
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    input_buffer[strlen(input_buffer) - 1] = '\0'; // 개행 문자 제거
    if(!validate_input(input_buffer, 2)){
        // NAN 
        printf("[EXCEPTION] only numbers are allowed\n");
        free(person);
        return NULL;
    }
    strncpy(person->szPhone, input_buffer, MAX_PHONE_LENGTH);
    person->szPhone[MAX_PHONE_LENGTH] = '\0';

    return person;
}

int get_int(char *input_buffer){
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    input_buffer[strlen(input_buffer) - 1] = '\0'; // 개행 문자 제거
    return atoi(input_buffer);
}


