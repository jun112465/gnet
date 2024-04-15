#include "personal.h"

PLIST Load(){
    PLIST list;
    FILE *fp;

    list = (PLIST)malloc(sizeof(PLIST));
    list->head = (PNODE)malloc(sizeof(PNODE));
    list->head->next = NULL;
    list->size = 0;

    fp = fopen(LIST_FILE, "ab+");
    if(fp == NULL) {
        printf("Unable to open file\n");
        exit(-1);
    }

    // load to memory
    while(1){
        int n;
        PPERSON_INFO person = (PPERSON_INFO)malloc(sizeof(PERSON_INFO));
        n = fread(person, sizeof(PERSON_INFO), 1, fp);

        if(n == 0){
            free(person);
            break;
        } 

        insert_node(list, person);
    }

    return list;
}