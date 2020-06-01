#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ioQueue.h"



void ioEnqueue(process **inCPU, process *ioQueue[48], int *ioSize){
    
    //Reset curCpu and curIo to 0 before adding to the queue
    (*inCPU)->curCpu = 0;
    (*inCPU)->curIo = 0;
    ioQueue[*ioSize] = (*inCPU);
    *ioSize += 1;
}

void ioDequeue(int pos, process *ioQueue[48], int *ioSize){ 
    
    for(int i = pos; i < *ioSize; i++){

       ioQueue[i] = ioQueue[i+1];
    }
    *ioSize -= 1;
}

void increaseioTime(process *ioQueue[48], process *theReadyQueue[48], int *readySize, int *readyBottom, int *ioSize){

if(*ioSize != 0){

    for(int i = 0; i < *ioSize; i++){

        ioQueue[i]->curIo += 1;
        
        if(ioQueue[i]->curIo == ioQueue[i]->io){

            ioQueue[i]->ioTotal += ioQueue[i]->curIo;
            ioQueue[i]->curIo = 0;
            readyEnqueue(&ioQueue[i], theReadyQueue, readySize, readyBottom);
            printf("Sending process from io to ready\n");
            ioDequeue(i, ioQueue, ioSize);
            readyQueueSort(theReadyQueue, readySize);

        }

    }
    
}

}