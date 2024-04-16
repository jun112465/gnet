#pragma once
#include "capture.h"
#include <time.h>


#define FRAMEBUFFER_DEVICE "/dev/fb0"

typedef struct display_arg{
    PQUEUE queue;
}DISPLAY_ARG;

void* display_thread_func(void *arg);