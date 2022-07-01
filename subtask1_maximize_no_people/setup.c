#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>


int main(int argc, char *argv[]){
	sem_t *SA, *SB, *mutexB;
	//We have to subtract one from the capacity of A to allow people from B to exit the museum.
	SA = sem_open("/SA", O_CREAT, 0600, atoi(argv[1])-1);
	SB = sem_open("/SB", O_CREAT, 0600, atoi(argv[2]));
	mutexB = sem_open("/mutexB", O_CREAT, 0600, 1);
	if (SA==SEM_FAILED || SB==SEM_FAILED || mutexB==SEM_FAILED) {
		perror("sem_open");
	}
	return 0;
}

