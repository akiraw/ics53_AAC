//exec test

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main() {

	printf("This is the main branch just before forking \n");
	pid_t wpid;
	int status;
	pid_t pid = fork();
	//Child process
	if ( pid == 0) {
		printf("executing ./helloworld from child \n");
		char argvStorage[128][256];
		char *argv[128];
		strcpy(argvStorage[0], "./helloworld");
		argv[0] = argvStorage[0];
		argv[1] = NULL;
		if(execve(argv[0], argv, environ) == -1)
			printf("exec error");
		exit(EXIT_FAILURE);
	} else if(pid < 0) {
		//Error Forking
		printf("fork error");
	} else {
		//Parent process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while( !WIFEXITED(status) && !WIFSIGNALED(status));
	}
	printf("done. \n");
	return 0;
}
