// Name(s): Caden Duhon
// Description: Caden's version of the TechShell Project. To be combined with Zachary's Version to create the final project

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 50

//////// Some function ideas: ////////////
// Note: Some code is reflected in main that represents these functions,
// but it is up to you to determine how you want to organize your code.

/* 
    A function that causes the prompt to display in the terminal
    This function only consists of two lines, so it is consolidated into the main loop
*/


/*
    A function that takes input from the user.
    It may return return the input to the calling statement or 
    store it at some memory location using a pointer.
    This function is also consolidated into the main loop.
*/ 

/*
    A function that parses through the user input.
    Consider having this function return a struct that stores vital
    information about the parsed instruction such as:
    - The command itself
    - The arguments that come after the command 
        Hint: When formatting your data, 
        look into execvp and how it takes in args.
    - Information about if a redirect was detected such as >, <, or |
    - Information about whether or not a new file 
        needs to be created and what that filename may be.
    

    Some helpful functions when doing this come from string.h and stdlib.h, such as
    strtok, strcmp, strcpy, calloc, malloc, realloc, free, and more

    Be sure to consider/test for situations when a backslash is used to escape the space char
    and when quotes are used to group together various tokens.
*/

/*
    A function that executes the command. 
    This function might take in a struct that represents the shell command.

    Be sure to consider each of the following:
    1. The execvp() function. 
        This can execute commands that already exist, that is, 
        you don't need to recreate the functionality of 
        the commands on your computer, just the shell.
        Keep in mind that execvp takes over the current process.
    2. The fork() function. 
        This can create a process for execvp to take over.
    3. cd is not a command like ls and mkdir. 
        cd is a toold provided by the shell, 
        so you WILL need to recreate the functionality of cd.
    4. Be sure to handle standard output redirect and standard input redirects here 
        That is, there symbols: > and <. 
        Pipe isn't required but could be a nice addition.
*/


int main(){ // MAIN

    char wd[SIZE];
    char *wdpointer;
    char input[SIZE];

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

        //token = strtok(input, " ");
	    
	    // execute the command
	    //executeCommand(command);
	}

	exit(0);
}
