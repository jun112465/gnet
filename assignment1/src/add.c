#include "personal.h"

void Add(PINFO_LIST list, PPERSON_INFO person){

    if(person == NULL) return;

    // overflow handling
    if (list->size >= list->max_size)
    {
        list->max_size *= 2;
        PPERSON_INFO tmp = (PPERSON_INFO)calloc(sizeof(PERSON_INFO), list->max_size);
        memcpy(tmp, list->arr, list->size * sizeof(PERSON_INFO));
        free(list->arr);

        list->arr = tmp;
    }

    // add on memory
    list->arr[list->size] = *person;

    // add on file
    FILE *fp = fopen(LIST_FILE, "ab");
    if(fp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }
    fwrite(person, sizeof(PERSON_INFO), 1, fp);
    fclose(fp);

    // add size
    list->size++;


    // free memory
    free(person);
}