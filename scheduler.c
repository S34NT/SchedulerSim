#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printStats.h"
#include "readyQueue.h"
#include "ioQueue.h"


int main(int argc, char * argv[]){

process *CPU = NULL;
FILE *inFile;
inFile = fopen("a2in.txt", "r");

//Create and malloc the size of one line of the file
char *oneLine;
oneLine = (char *)malloc(sizeof (char) * 15);
int lineSize = 0;

process *theReadyQueue[48];
process *ioQueue[48];
process theProcesses[48];

//Read in the file line by line, and pass the lines to fillReadyQueue method
while(fgets(oneLine, 15, inFile) != NULL){

    fillReadyQueue(oneLine, theProcesses);

    for(int i = 0; i <= 47; i++){

        theReadyQueue[i] = &theProcesses[i];
    }

    memset(oneLine, 0, 15);
}
free(oneLine);
fclose(inFile);

//Initialize the OS struct 
os theOS;
theOS.quantum = 70;
theOS.wait = 20;
int readySize = 48;
int readyBottom = 47;
int ioSize;


int moreProcesses = 1;
int count = 0;

while(moreProcesses != 0){
    
    if(CPU == NULL){
        readyDequeue(&CPU, theReadyQueue, &readySize);
    }
    if((int)CPU->isRunning == 0){ //if current process is finished running
            count++;
        while(readyDequeue(&CPU, theReadyQueue, &readySize) == 1){

            increaseioTime(ioQueue, theReadyQueue, &readySize, &readyBottom, &ioSize);
            increaseReadyTime(theReadyQueue, theOS, &readySize);
        }
    }
    

    if(CPU->curCpu == CPU->cpu){ //if current process reaches time for IO
        puts("sending to IO");
        ioEnqueue(&CPU, ioQueue, &ioSize); //send to ioQueue

        while(readyDequeue(&CPU, theReadyQueue, &readySize) == 1){
            if(count == 47){
                printf("finished");
                printStats(theProcesses,theOS);
                exit(0);
            }

            increaseioTime(ioQueue, theReadyQueue, &readySize, &readyBottom, &ioSize);
            increaseReadyTime(theReadyQueue, theOS, &readySize);
        } 
        readyQueueSort(theReadyQueue, &readySize); //sort ready queue

    }

    if(CPU->curCpu == theOS.quantum){ //if process reaches time quantum send back to the ready queue
        puts("sending to ready");
        readyEnqueue(&CPU, theReadyQueue, &readySize, &readyBottom); //send to readyqueue
        readyQueueSort(theReadyQueue, &readySize);//sort readyqueue
        while(readyDequeue(&CPU, theReadyQueue, &readySize) == 1){
            increaseioTime(ioQueue, theReadyQueue, &readySize, &readyBottom, &ioSize);
            increaseReadyTime(theReadyQueue, theOS, &readySize);
        }  //load new process

    }

    CPU->curCpu++;
    CPU->isRunning--;

    increaseReadyTime(theReadyQueue, theOS, &readySize); //increase the time in readyQueue for all processes in readyQueue
    increaseioTime(ioQueue, theReadyQueue, &readySize, &readyBottom, &ioSize);
    readyQueueSort(theReadyQueue, &readySize);

}




    
}