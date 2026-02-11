// Name(s): Zachary Smith
// Description: Zachary's version of the TechShell Project. To be combined with Caden's Version for the final version.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 256
#define DEBUG 0

void tokenize(char input[], char *argv[]);

int main(void){

    char wd[SIZE];
    char *wdpointer;
    char input[SIZE];
    char *argv[SIZE];

	// Get the input
	for (;;)
	{
        // get the working directory and display the prompt
        wdpointer = getcwd(wd, sizeof(wd));
        printf("%s$ ", wd);

        // get user input
        fgets(input, sizeof(input), stdin);
	    
        // begin parsing the user input into a usable state
        input[strcspn(input, "\n")] = '\0';

        //tokenize it 
        tokenize(input, argv);

        // If someone just pressed enter, then just restart the loop
        if (argv[0] == NULL){
            continue;
        }
	    
	}

	exit(0);
}

void tokenize(char input[], char *argv[]){
    int i = 0;
    //basic tokenize that only separates based on spaces
    char *token = strtok(input, " ");
    while (token != NULL){
        argv[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    // must set the last value of argv to NULL so that execvp knows where to stop
    argv[i] = NULL;
}
