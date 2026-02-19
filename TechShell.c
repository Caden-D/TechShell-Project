// Name(s): Zachary Smith & Caden Duhon
// Description: Our final version of the TechShell Project. Built from the best parts of Caden and Zachary's versions.

#include <stdio.h>          // Libraries needed for the shell
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_SIZE 256

void tokenize(char input[], char *args[]);

int main(void){

    char wd[SIZE];          // stores the working directory
    char *wdpointer;        // stores the memory location for 
    char input[SIZE];       // stores the input string taken from the user
    char *command[SIZE];    // stores the formated command line for use in the execvp function

    for(;;){                // start the main loop

        // step 1: prompt and input

        wdpointer = getcwd(wd, sizeof(wd));     // get the working directory
        if (wdpointer == NULL){                 // check for failure
            perror("getcwd");
            continue;
        }
        printf("%s$ ", wd);                     // print the prompt

        fgets(input, sizeof(input), stdin);     // get user input

        // step 2: formating input

        input[strcspn(input, "\n")] = '\0';     // remove the "newline" character

        for (int i = 0; i < SIZE; i++) {        // clear the command list from all tokens
            command[i] = NULL;
        }
        tokenize(input, command);               // generate the command line from the input using the tokenizer

        // step 3: handle special cases (like cd)

        if (command[0] == NULL) {               // special case for no command entered
            continue;
        }

        if (strcmp(command[0], "cd") == 0){     // handle the cd command
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

        char *input_file = NULL;        // stores the file name if stdin
        char *output_file = NULL;       // stores the file name if stdout

        for (int i = 0; args[i] != NULL; i++){ // checks for stdin or stdout
            
            if (strcmp(args[i], "<") == 0){
                input_file = args[i+1];
                args[i] = NULL;
            }

            if (strcmp(args[i], ">") == 0){
                output_file = args[i+1];
                args[i] = NULL;
            }
        }



        // step 4: fork and execute

        pid_t pid = fork();

        if (pid < 0){
            perror("fork");
            continue;
        }

        if (pid == 0){

            if (input_file != NULL){            // handle input redirect
                int fd = open(input_file, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            if (output_file != NULL){           // handle output redirect
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            execvp(args[0], args);              // execute the command
            perror("execvp");
            exit(1);
        }
        else {
            // Parent Process
            wait(NULL);
            for (int i = 0; command[i] != NULL; i++) {      // clean up memory
                free(command[i]);
            }
        }



    }
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
