#include "personal.h"

void Delete(PLIST list, int index){
    if(index < 0 || index >= list->size) {
        printf("[ERORR] index out of bound");
        return;
    }
    
    delete_node(list, index);
    // file에서의 index와 linkedlist에서의 index는 반대이다. 
    file_delete(list->size - index - 1); 
}