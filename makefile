CC = gcc
CFLAGS = -ggdb


scheduler: scheduler.o readyQueue.o ioQueue.o printStats.o

scheduler.o: scheduler.c readyQueue.h ioQueue.h processes.h

readyQueue: readyQueue.o

readyQueue.o: readyQueue.h

ioQueue: ioQueue.c 

ioQueue.o: ioQueue.h

printStats: printStats.c

printStats.o: printStats.h

clean:
	rm -f *.o scheduler

run: scheduler
	./scheduler