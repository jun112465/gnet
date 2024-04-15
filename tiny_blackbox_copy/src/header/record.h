#pragma once
#include "capture.h"

typedef struct record_arg{
    PQUEUE queue;
    FILE *record_file;
    int *end;
}RECORD_ARG;

void* record_thread_func(void *arg);