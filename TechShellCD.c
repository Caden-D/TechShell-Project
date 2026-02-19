// Name(s): Caden Duhon
// Description: Caden's version of the TechShell Project. To be combined with Zachary's Version to create the final project

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 50


void ZCtokenize(char input[], char *args[]);
void tokenize(char input[], char *args[]);

int main(){ // MAIN

    char wd[SIZE];
    char *wdpointer;
    char input[SIZE];
    char *command[SIZE];

	//char* input;
	//struct ShellCommand command;
		
	// repeatedly prompt the user for input
	for (;;)
	{
        // get the working directory and display the prompt
        wdpointer = getcwd(wd, sizeof(wd));
        printf("%s$ ", wd);

        // get user imput
        fgets(input, sizeof(input), stdin);
	    
        // begin parcing the user input into a usible state
        input[strcspn(input, "\n")] = '\0';

        // clean up the command list for future commands
        for (int i = 0; i < SIZE; i++) {
            command[i] = NULL;
        }
        tokenize(input, command);

        // special case for no command entered
        if (command[0] == NULL) {
            continue;
        }

        // cd command
        if (strcmp(command[0], "cd") == 0){
            if (command[1] == NULL){
                char *home = getenv("HOME");
                if (home == NULL || chdir(home) != 0) {
                perror("cd");
                }
            } else {
                if(chdir(command[1]) != 0){
                    perror("cd");
                }
            }
            continue;
        }
	
	    // fork and execute
        pid_t pid = fork();

        if(pid < 0){
            // error occured
            perror("fork");
        } else if (pid == 0){
            // child
            // check for < or >
            for (int i = 0; command[i] != NULL; i++){

                // apply >
                if (strcmp(command[i], ">") == 0){
                    int fd = open(command[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0) {
                        perror("open");
                        exit(1);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);

                    command[i] = NULL;
                    break;
                }

                // apply <
                if (strcmp(command[i], "<") == 0){
                    int fd = open(command[i+1], O_RDONLY);
                    if (fd < 0) {
                        perror("open");
                        exit(1);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);

                    command[i] = NULL;
                    break;
                }
            }

            execvp(command[0], command);
            perror("exec");
            exit(1);


        } else {
            // parent
            wait(NULL);
            for (int i = 0; command[i] != NULL; i++) {
                free(command[i]);
            }
        }
	}

	exit(0);
}

// borrowed from Zachary
void ZStokenize(char input[], char *args[]){
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

void tokenize(char input[], char *args[]){
    int a = 0;                                      // index for args
    int i = 0;                                      // index for input
    int t = 0;                                      // index for current token

    int inQuotes = 0;                               // used to remember if we are in a set of quotation marks
    static char token[SIZE];                        // memory buffer to hold the token being worked on

    while (input[i] != '\0'){                       // move through the input string char by char until reaching the string terminator

        if (input[i] == '\\'){                      // case for "\"
            i++;                                    // skip the "\"
            if (input[i] != '\0'){                  // make sure we dont add the string terminator
                token[t++] = input[i++];            // add the next character litterally
            }
        } else if (input[i] == '"'){                // case for '"'
            inQuotes = !inQuotes;                   // toggle the flag
            i++;                                    // keep moving
        } else if (input[i] == ' ' && !inQuotes) {  // handle spaces like normal if not in quotes
            if (t > 0) {                            // check of token in empty
                token[t] = '\0';                    // add a string terminator to the end of the buffer
                args[a++] = strdup(token);          // copy the token into the args list
                t = 0;                              // reset the index for the token
            }
            i++;
        } else {                                    // normal case for all other characters
            token[t++] = input[i++];
        }
    }
        if (t > 0) {                                // copy the final token (tokens are copied on hiting a space char)
            token[t] = '\0';
            args[a++] = strdup(token);
        }
        args[a] = NULL;                            // add a NULL to the end of the args list for the execvp function

}
