#ifndef PERSONAL_H
#define PERSONAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LIST_FILE "infolist"
#define MAX_NAME_LENGTH 10
#define MAX_PHONE_LENGTH 21
#define MAX_LIST_LENGTH 3
#define LIST_INIT_SIZE 1 
#define INPUT_BUFFER_SIZE 1024

typedef struct __tPersonalInfo{

    int nAge;
    char szPhone[MAX_PHONE_LENGTH+2];
    char szNam[MAX_NAME_LENGTH+2];

} PERSON_INFO, *PPERSON_INFO;

typedef struct __tPersonalInfoList{
    PERSON_INFO *arr;
    int max_size;
    int size;
} INFO_LIST, *PINFO_LIST;

// load info to linkedlist
PINFO_LIST Load();

// add info to linkedlist and update file
void Add(PINFO_LIST, PPERSON_INFO);

// delete node from linkedlist and update file
void Delete(PINFO_LIST, int index);

// modify node info and update file
void Modify(PINFO_LIST, int, PPERSON_INFO before);

// print all info
void PrintInfo(PINFO_LIST);

// close main
void Close();


void add_dummy_data(PINFO_LIST);

int equal(PPERSON_INFO p1, PPERSON_INFO p2);

// update file with memory
void update_file(PINFO_LIST list);

// checks whether alphabet or number string
int validate_input(const char *str, int type);

// gets Integer to buffer
int get_int(char *input_buffer);


// cli and modules for modification
void modifyCLI(char *, PINFO_LIST);
void get_modify_input(char *input_buffer, PINFO_LIST list);
int search(char *, PINFO_LIST);
PPERSON_INFO get_person_info(char *input_buffer);

#endif