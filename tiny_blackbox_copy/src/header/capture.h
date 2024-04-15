#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#include "frame_queue.h"
#include "display.h"
#include "record.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FRAME_SIZE WIDTH * HEIGHT
#define RECORD_FILE "record.raw"

void* capture_thread_func(void*);
void replay_init(int* record_end, FILE*, PQUEUE display_queue, PQUEUE record_queue);
