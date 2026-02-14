// Name(s): Zachary Smith
// Description: Zachary's version of the TechShell Project. To be combined with Caden's Version for the final version.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 256
#define DEBUG 0

void tokenize(char input[], char *args[]);

int main(void){

    char wd[MAX_SIZE];
    char *wdpointer;
    char input[MAX_SIZE];
    char *args[MAX_SIZE];

	// Main loop
	for (;;)
	{
        // get the working directory and display the prompt
        wdpointer = getcwd(wd, sizeof(wd));
        if (wdpointer == NULL){
            perror("getcwd");
            continue;
        }
        printf("%s $ ", wd);

        // get user input
        fgets(input, sizeof(input), stdin);
	    
        // begin parsing the user input into a usable state
        input[strcspn(input, "\n")] = '\0';

        //tokenize it 
        tokenize(input, args);

        // If someone just pressed enter, then just restart the loop
        if (args[0] == 0) continue;       

        // custom cd 
        if (strcmp(args[0], "cd") == 0){
            if (args[1] == NULL){
                fprintf(stderr, "cd: missing argument\n");
            }
            else {
                if (chdir(args[1] != 0)){
                    perror("cd");
                }
            }
            continue;
        }
        
        // fork() and execvp()

        pid_t pid = fork();

        if (pid < 0){
            perror("fork");
            continue;
        }

        if (pid == 0){
            // Child Process
            execvp(args[0], args);
            // if there is an error
            perror("execvp");
            return 1;
        }
        else {
            // Parent Process
            wait(NULL);
        }
	    
	}

	exit(0);
}

void tokenize(char input[], char *args[]){
    int i = 0;
    //basic tokenize that only separates based on spaces
    char *token = strtok(input, " ");
    while (token != NULL){
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    // must set the last value of argv to NULL so that execvp knows where to stop
    args[i] = NULL;
}
