#include "personal.h"

void Add(PLIST list, PPERSON_INFO person){

    // add on memory
    insert_node(list, person);

    // add on file
    file_add(person);
}