#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD 100

void * thread_int(void * arg);
void * thread_des(void * arg);
long long num = 0;


