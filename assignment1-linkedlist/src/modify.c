#include "personal.h"

void Modify(PLIST list, int index, PPERSON_INFO p){
    // modify memory
    modify_node(list, index, p);

    // modify file
    file_modify(list->size-index-1, p);
}
