#include "personal.h"

PNODE create_node(){
    PNODE node = (PNODE)malloc(sizeof(NODE));
    node->next = NULL;
    node->person = NULL;
    return node;
}

void insert_node(PLIST list, PPERSON_INFO person){
    PNODE newnode = create_node();
    newnode->person = person;
    newnode->next = list->head->next;
    list->head->next = newnode;
    list->size++;
}

void delete_node(PLIST list, int index){
    PNODE curnode = list->head;
    PNODE tmp;
    int i;

    for(i=0; i<index; i++){
        curnode = curnode->next;
    }

    if(i == index){
        tmp = curnode->next;
        curnode->next = curnode->next->next; 
        free(tmp);
    }
}

void modify_node(PLIST list, int index, PPERSON_INFO person){
    PNODE curnode = list->head;
    int i;

    for(i=0; i<index; i++){
        curnode = curnode->next;
    }

    if(i == index){
        curnode = curnode->next;
        free(curnode->person);
        curnode->person = person;
    }
}