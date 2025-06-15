CC = gcc
AR = ar rcs

all: manager worker main

manager: manager.o
	$(AR) libmanager.a manager.o

worker: worker.o
	$(AR) libworker.a worker.o

main: main.o libmanager.a libworker.a
	$(CC) -o projekt main.o -L. -lmanager -lworker

manager.o: manager.c manager.h
	$(CC) -c manager.c

worker.o: worker.c worker.h
	$(CC) -c worker.c

main.o: main.c manager.h worker.h
	$(CC) -c main.c

clean:
	rm -f *.o *.a projekt
