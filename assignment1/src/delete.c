#include "personal.h"

void Delete(PINFO_LIST list, int index){

    // handling index exception
    if(index < 1 || index > list->size){
        printf("[EXCEPTION] index is out of bound\n");
        return;
    }

    // delete data from memory
    PERSON_INFO person = list->arr[index-1];
    for(int i=index-1; i<list->size-1; i++){
        list->arr[i] =  list->arr[i+1];
    }

    // update size
    list->size--;

    // update file
    // must update size before updating file.
    update_file(list);
    
    printf("[DELETED] name : %s, age : %d, phone : %s\n", 
        person.szNam, person.nAge, person.szPhone);
}
