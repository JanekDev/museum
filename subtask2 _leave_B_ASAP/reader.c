#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>

#define N 3

int main() {
	sem_t *SA, *SB;
	int pid, sleep_time;

	SA = sem_open("/SA", O_RDWR);
	SB = sem_open("/SB", O_RDWR);
	if (SA==SEM_FAILED || SB==SEM_FAILED) {
		perror("sem_open");
		exit(1);
	}

	pid = getpid();

	srand ( time(NULL) % pid );
	sleep_time = (rand() % 5000)*1000;
	printf("sleep_time: %d ms\n", sleep_time/1000);
	while(1) {
		printf("%d waits for entrance to museum \n", pid);
		sem_wait(SA);
		printf("%d entered the hall A \n", pid);
		printf("%d watches the exhibition in A...\n", pid);
		usleep(sleep_time);
		if (rand() % 2 == 0){
			printf("%d wants to enter the hall B \n", pid);
			sem_wait(SB);
			printf("%d entered the hall B \n", pid);
			printf("%d watches the exhibition in B...\n", pid);
			usleep(sleep_time);
			printf("%d wants to leave the museum\n", pid);
			sem_post(SB);
		}
		sem_post(SA);
		printf("%d left the museum\n", pid);
	}
	sem_close(SA);
	sem_close(SB);
	sem_unlink("/SA");
	sem_unlink("/SB");
}
