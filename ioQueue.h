#ifndef IOQUEUE_H
#define IOQUEUE_H
#include "readyQueue.h"



void ioEnqueue(process **oneProcess, process *ioQueue[48], int *ioSize);

void ioDequeue(int pos, process *ioQueue[48], int *ioSize);

void increaseioTime(process *ioQueue[48], process *theReadyQueue[48], int *readySize, int *readyBottom, int *ioSize);



#endif