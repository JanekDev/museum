#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define N 3

int main() {
	sem_t *Sr;
	int pid;

	Sr = sem_open("/readers", O_CREAT, 0600, N);
	if (Sr==SEM_FAILED) {
		perror("sem_open");
		exit(1);
	}
	pid = getpid();
	while(1) {
		printf("         %d waits for entrance\n", pid);
		sem_wait(Sr);
		printf("INSIDE   %d\n", pid);
		sleep(rand()%5+5);
		printf("         %d leaves\n", pid);
		printf(". . . . . . . . . . . . . . . . . . .\n", pid);
		sem_post(Sr);
		sleep(rand()%3+1);
	}
	sem_close(Sr);
	sem_unlink("/Sr");
}
