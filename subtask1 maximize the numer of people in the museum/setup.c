#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>


int main(int argc, char *argv[]){
	sem_t *SA, *SB;
	//Na-Nb id the admissible number of processes people in the hall A
	SA = sem_open("/SA", O_CREAT, 0600, atoi(argv[1]));
	SB = sem_open("/SB", O_CREAT, 0600, atoi(argv[2]));
	if (SA==SEM_FAILED || SB==SEM_FAILED) {
		perror("sem_open");
	}
	return 0;
}

