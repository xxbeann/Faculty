#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int g = 2;


int main()
{
	pid_t pid;
	int l = 0;

	printf("PID(%d): Parent g=%d, l=%d \n", getpid(), g, l);
	
	if((pid = fork()) < 0) {
		perror("fork error");
		exit(1);
	}
	
	if(pid == 0) {
		g--;
		l++;
	} 
	else {
		wait(NULL);
		g++;
		l--;
	}
	
	printf("PID(%d)’s: g=%d, l=%d \n", getpid(), g, l);

	exit(0);
}
