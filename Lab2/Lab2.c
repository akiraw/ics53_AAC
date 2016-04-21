#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void getUserInput(char * uiBuffer);
int parseUserInput(char tokenArray[][256], const char * uiBuffer);
void printTokens( char tokenArray[][256], int numTokens);

int main() {
	char uiBuffer[2048];
	bool ctrloop = true;
	
	//Outer Control Loop
	while ( ctrloop ) {
	
		//Prompt and enter user input
		getUserInput(uiBuffer);
		//print statement for debugging
		printf("You entered: \n %s \n", uiBuffer);
		
		// parsing user input into array of c strings
		char tokenArray[128][256];
		int count = parseUserInput(tokenArray, uiBuffer);
		//print token array for debugging
		printTokens(tokenArray, count);
		
		//bool interpretLoop = true;
		//while (interpretLoop) {
			
		//interpretLoop = false;
			/*
			if ( strcmp("quit", tokenBuffer) == 0)
				interpretLoop = false;
				ctrloop = false;
			*/
		//}
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
		strcpy(tokenArray[tokenCounter++], tokenBuffer);
	}
	return tokenCounter;
}

void printTokens(char tokenArray[][256], int numTokens) {
	for ( int i = 0 ; i < numTokens; ++i )
		printf("token at index  %d: %s \n", i, tokenArray[i]);
}