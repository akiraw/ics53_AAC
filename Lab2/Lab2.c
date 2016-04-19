#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void getUserInput(char * uiBuffer);

int main() {
	char uInputBuffer[2048];
	bool ctrloop = true;
	
	//Outer Control Loop
	while ( ctrloop ) {
		getUserInput(uInputBuffer);
		printf("You entered: \n %s \n", uInputBuffer);
		// parser 
		bool interpretLoop = true;
		int index = 0;
		
		while (interpretLoop) {
			bool parseLoop = true;
			int tInfo = 0;
			char tokenBuffer[255];
		
			while(parseLoop) {
				int c = uInputBuffer[index++];
				
				if (c == '\0') {
						parseLoop = false;
						interpretLoop = false;
				}
				else if (c != ' ') 
						tokenBuffer[tInfo++] = c; 
				else if (tInfo != 0)
						parseLoop = false;
				//just loops if there is a leading space
			}
			tokenBuffer[tInfo] = '\0';
		
			printf("\n token: %s \n", tokenBuffer);
		
			if ( strcmp("quit", tokenBuffer) == 0)
				interpretLoop = false;
				ctrloop = false;
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