//exec test

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main() {
	printf("executing ./helloworld \n");
	char argvStorage[128][256];
	char *argv[128];
	strcpy(argvStorage[0], "./helloworld");
	argv[0] = argvStorage[0];
	argv[1] = NULL;
	execve(argv[0], argv, environ);
	
	printf("done. \n");
	return 0;
}
