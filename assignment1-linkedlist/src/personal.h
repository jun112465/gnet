#ifndef PERSONAL_H
#define PERSONAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LIST_FILE "infolist"
#define LIST_FILE_TMP "tmpfile"

#define MAX_NAME_LENGTH 10
#define MAX_PHONE_LENGTH 21
#define INPUT_BUFFER_SIZE 1024

typedef struct __tPersonalInfo{
    int nAge;
    char szPhone[MAX_PHONE_LENGTH+2];
    char szNam[MAX_NAME_LENGTH+2];

    struct __tPersonalInfo *next;

} PERSON_INFO, *PPERSON_INFO;

typedef struct __tPersonalInfoList{
    PERSON_INFO *head;
    int size;
} INFO_LIST, *PINFO_LIST;

typedef struct node{
    PPERSON_INFO person;
    struct node *next;
}NODE, *PNODE;

typedef struct linkedlist{
    PNODE head;
    int size;
}LIST, *PLIST;

// functions
PLIST Load();
void Add(PLIST, PPERSON_INFO);
void Delete(PLIST, int index);
void Modify(PLIST, int, PPERSON_INFO);
void PrintInfo(PLIST);
void Close(PLIST);

// functions for linked list
PNODE create_node();
void insert_node(PLIST, PPERSON_INFO);
void delete_node(PLIST, int);
void modify_node(PLIST, int, PPERSON_INFO);

// functions for file
void file_add(PPERSON_INFO person);
void file_delete(int index);
void file_modify(int index, PPERSON_INFO person);

// modules
void add_dummy_data(PINFO_LIST);
int equal(PPERSON_INFO p1, PPERSON_INFO p2);
void update_file(PINFO_LIST list);
int validate_input(const char *str, int type);
int get_int(char *input_buffer);
PPERSON_INFO get_person_info(char *input_buffer);
int ask_search_again(char*);
void search(char *, PLIST);


#endif