#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void* input_thread_func(void *arg);
void init_input();
void set_pp();