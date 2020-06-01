#ifndef READYQUEUE_H
#define READYQUEUE_H
#include "processes.h"

void fillReadyQueue(char *oneLine, process theReadyQueue[48]);

void readyEnqueue(process **inCPU, process *theReadyQueue[48], int *readySize, int *readyBottom);

void readyQueueSort(process *readyQueue[48], int *readySize);

int readyDequeue(process **CPU, process *theReadyQueue[48], int *readySize);

void increaseReadyTime(process *theReadyQueue[48], os theOS, int *readySize);


#endif