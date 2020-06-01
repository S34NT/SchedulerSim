#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readyQueue.h"
#define top (0)


void fillReadyQueue(char *oneLine, process theProcesses[48]){

static int count = 47;
int priority;
int beforeIO;
int IOtime;
int totalRuntime;

    //Check that it is a full line being passed in, then use sscanf to parse the line from the file
    if(oneLine[0] != '\n' && oneLine[1] != '\n'){
    
    sscanf(oneLine, "%u %u %u %u", &priority, &beforeIO, &IOtime, &totalRuntime);

    //Initialize the process struct in the last position of theReadyQueue, 
    //Initializing backwards towards zero so they will be in descending order from position 0
    theProcesses[count].priority = priority;
    theProcesses[count].cpu = beforeIO;
    theProcesses[count].io = IOtime;
    theProcesses[count].isRunning = totalRuntime;

    theProcesses[count].curCpu = 0;
    theProcesses[count].curIo = 0;
    theProcesses[count].cpuTotal = 0;
    theProcesses[count].ioTotal = 0;
    theProcesses[count].curPrior = priority;
    theProcesses[count].wait = 0;
    theProcesses[count].waitCount = 0;
    theProcesses[count].waitMax = 0; 
    theProcesses[count].waitMin = -1;
    theProcesses[count].waitSum = 0;
  
    printf("%u ", theProcesses[count].priority);
    printf("%u ", theProcesses[count].cpu);
    printf("%u ", theProcesses[count].io);
    printf("%u ", theProcesses[count].isRunning);
    printf("\n");
    count--;
    }
}


void readyEnqueue(process **inCPU, process *theReadyQueue[48], int *readySize, int *readyBottom){

//Enqueue if process is still running,
//otherwise add to bottom of queue and decrease the size
    if((int)(*inCPU)->isRunning > 1){
        (*inCPU)->cpuTotal += (*inCPU)->curCpu;
        (*inCPU)->waitCount += 1;
        (*inCPU)->wait = 0;
        theReadyQueue[*readySize] = (*inCPU);
        *readySize += 1;
    }else{
        theReadyQueue[*readyBottom] = (*inCPU);
        *readyBottom -= 1;
    }
  
}

int readyDequeue(process **CPU, process *theReadyQueue[48], int *readySize){

    if(*readySize == 0){
        return 1;
    }
    (*CPU) = theReadyQueue[top];
    (*CPU)->curCpu = 0;

    for(int i = 0; i < *readySize; i++){

        theReadyQueue[i] = theReadyQueue[i+1];
    }    
    
    *readySize -= 1;
    return 0;

}


void readyQueueSort(process *theReadyQueue[48], int *readySize){
    

    for (int i = 0; i < *readySize; i++)                     
	{
		for (int j = i+1; j < *readySize; j++)            
		{
			if (theReadyQueue[i]->curPrior < theReadyQueue[j]->curPrior)                
			{
				process *tmp = theReadyQueue[i];         
				theReadyQueue[i] = theReadyQueue[j];            
				theReadyQueue[j] = tmp;             
			}
		}
	}
}

void increaseReadyTime(process *theReadyQueue[48], os theOS, int *readySize){
   

    for(int i = 0; i < *readySize; i++){

        theReadyQueue[i]->wait += 1;
        theReadyQueue[i]->waitSum += 1;

        if(theReadyQueue[i]->wait == theOS.wait){

            theReadyQueue[i]->curPrior += 1;
            theReadyQueue[i]->wait = 0;
        }

    }



}

