#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
	char uInputBuffer[2048];
	bool ctrloop = true;
	
	//Outer Control Loop
	while ( ctrloop ) {
	  
	  bool uiloop = true;
	  printf("prompt> ");
	  //Get User Input
	  int index = 0;
	  while (uiloop) {
		int c = getchar();

		if ( c == EOF || c == '\n') {
			uInputBuffer[index] = '\0';
			uiloop = false;
		}	else {
		  //TODO: Elimiate Whitespace & blank lines
			uInputBuffer[index++] = c;
		}
	  }

	  printf("You entered: \n %s \n", uInputBuffer);
	
	  if ( strcmp("quit", uInputBuffer) == 0)
	    ctrloop = false;
	  }
	return 0;
}
