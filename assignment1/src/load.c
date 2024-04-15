#include "personal.h"

PINFO_LIST Load(){
    FILE *fp;
    PINFO_LIST list;

    // initialize list 
    list = (PINFO_LIST)malloc(sizeof(INFO_LIST));
    list->arr = (PPERSON_INFO)calloc(sizeof(PERSON_INFO), LIST_INIT_SIZE);
    list->max_size = LIST_INIT_SIZE;
    list->size = 0;

    // open file 
    fp = fopen(LIST_FILE, "ab+");
    if(fp == NULL) {
        printf("Unable to open file\n");
        exit(-1);
    }

    // load to memory
    while(fread(&list->arr[list->size], sizeof(PERSON_INFO), 1, fp) == 1){
        list->size++;
        if(list->size >= list->max_size){
            list->max_size *= 2;
            PPERSON_INFO tmp = (PPERSON_INFO)calloc(sizeof(PERSON_INFO), list->max_size);
            memcpy(tmp, list->arr, sizeof(PERSON_INFO) * list->size);
            free(list->arr);
            list->arr = tmp;
        }
    } 

    // printf("size : %d\n", list->size);

    // close file
    fclose(fp);

    return list;
}