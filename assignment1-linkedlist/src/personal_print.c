#include "personal.h"

void PrintInfo(PLIST list){
    int i=0;
    PNODE curnode = list->head;
    PPERSON_INFO person;

    printf("[SIZE] %d\n", list->size);
    printf("[INDEX] : [NAME, AGE, PHONE]\n");
    while(curnode->next != NULL){
        curnode = curnode->next;
        person = curnode->person;
        printf("[%d] : [%s, %d, %s]\n", i++, person->szNam, person->nAge, person->szPhone);
    }
}