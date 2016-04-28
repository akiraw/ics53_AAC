#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

void getUserInput(char * uiBuffer);
int parseUserInput(char tokenArray[][256], const char * uiBuffer);
void printTokens( char tokenArray[][256], int numTokens);

int main() {
	char uiBuffer[2048];
	pid_t backgroundProcessIDs[16];
	bool backgroundRunning[16];
	bool ctrloop = true;
	for ( int i = 0 ; i <  16; ++i )
		backgroundRunning[i] = false;
	
	//Outer Control Loop
	while ( ctrloop ) {
	
		//Prompt and enter user input
		getUserInput(uiBuffer);
		int bufferLength = strlen(uiBuffer);
		
		//background/foreground process handling
		bool background = false;
		if ( (bufferLength != 0 ) && (uiBuffer[bufferLength-1] == '&')) {
			background = true;
			uiBuffer[bufferLength - 1] = '\0';
		}
		//print statement for debugging
		printf("You entered: \n %s \n", uiBuffer);
		
		// parsing user input into array of c strings
		char tokenArray[128][256];
		int count = parseUserInput(tokenArray, uiBuffer);
		//print token array for debugging
		printTokens(tokenArray, count);
		
		//assign matrix of characters into an array of pointers to C strings.
		char *argv[129];
		for (int i = 0 ; i < count; ++i) {
			argv[i] = tokenArray[i];
		}
		argv[count] = NULL;
		
		// execute instruction
		if ( strcmp("quit", tokenArray[0]) == 0) {
			//quit built in
			ctrloop = false;
		} else {
			printf("Executing instructions... \n");
			pid_t wpid;
			int status;
			pid_t pid = fork();
			
			if ( pid == 0 ) {
				printf("Executing instruction from child \n");
				if (execve(argv[0], argv, environ) == -1)
					printf("exec error \n");
				exit(EXIT_FAILURE);
			} else if( pid <  0) {
				//Error forking
				printf("fork error \n");
			} else {
				//Parent process
				if ( !background) {
					do {
						printf("Waiting for child process to terminate \n");
						wpid = waitpid(pid, &status, 0);
					} while( !WIFEXITED(status));
				} else {
					for (int i = 0 ; i <  16; ++i) {
						if ( !backgroundRunning[i]) {
							backgroundProcessIDs[i] = pid;
							backgroundRunning[i] = true;
						}
					}
				}
				
				for ( int i = 0; i <  16; ++i) {
					if ( backgroundRunning[i]) {
						wpid = waitpid(backgroundProcessIDs[i], &status, WNOHANG);
						if ( wpid > 0 ) {
							printf("waitpid reaped background child");
							backgroundRunning[i] = false;
						}
					}
				}
				
			}
			printf("done with process \n");
		}
	}
	return 0;
}

void getUserInput(char * uiBuffer) {
	bool uiloop = true;
	printf("prompt> ");
	//Get User Input
	int index = 0;
	while (uiloop) {
		int c = getchar();

		if ( c == EOF || c == '\n') {
			uiBuffer[index] = '\0';
			uiloop = false;
		}	else 
			uiBuffer[index++] = c;
	}
}

int parseUserInput(char tokenArray[][256], const char * uiBuffer)
{
	int tokenCounter = 0;
	int UIIndex = 0;
	bool parseCrtlLoop = true;
	while(parseCrtlLoop) {
		int tIndex = 0;
		char tokenBuffer[256];
		bool parseLoop = true;
		while(parseLoop) {
			int c = uiBuffer[UIIndex++];
			if (c == '\0') {
				parseLoop = false;
				parseCrtlLoop = false;
			} else if (c != ' ') {
				tokenBuffer[tIndex++] = c; 
			} else if (tIndex != 0) {
				parseLoop = false;
			}
			//just loops if there is a leading space
		}
		tokenBuffer[tIndex] = '\0';
		if ( strcmp(tokenBuffer, "") != 0 )
			strcpy(tokenArray[tokenCounter++], tokenBuffer);
	}
	return tokenCounter;
}

void printTokens(char tokenArray[][256], int numTokens) {
	for ( int i = 0 ; i < numTokens; ++i )
		printf("token at index  %d: %s \n", i, tokenArray[i]);
}