#include "personal.h"

void PrintInfo(PINFO_LIST list){


    printf("[MAX_SIZE] %d\n", list->max_size);
    printf("[SIZE] %d\n", list->size);
    printf("[INDEX] : [NAME, AGE, PHONE]\n");
    for (int i = 0; i < list->size; i++)
    {
        PPERSON_INFO person = &list->arr[i];
        printf("[%d] : [%s, %d, %s]\n", i+1, person->szNam, person->nAge, person->szPhone);
    }

}