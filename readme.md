## Group members
- Caden Duhon
- Zachary Smith

## Responsibilities

We didn't really split up responsibilites like in a 'traditional' group project and instead opted to work on our own separate versions and then merge them at the end to get the best result. This also resulted in both of us gaining a greater understanding of the project. For example, The prompt system was made by Caden and improved By Zachary as well as the other way around for the tokenizer

## Description

The goal of this project was to create a simple imitation of a UNIX shell that was provided some of the utilities of a shell like displaying the file directory the user is currently in, using the `cd` command to change directories, use redirect symbols(`<`,`>`) to input directions or output results from the shell, as well as the use of the standard UNIX commands.

## Instructions

To run the file, first make sure that you doing this on a UNIX-like machine. This shell program will only work on UNIX like machines. Also make sure that you own the C development kit if you wish to compile this program on your own. After downloading TechShell.c, run the commands:

```bash
gcc TechShell.c -o TechShell
```
```bash
./TechShell
```

And congratulations, you are now running the program. You can use simple commands like `ls -a ` or `cd ..` to test whether or not you have it working.


## Incomplete Stuff

To our knowledge, everything that was outlined in the project description is implimented into the program; however, if we were to continue working there would be a lot of features that we would have like to add. such as:

* retracable history using the arrow keys
* tab to autocomplete a file name
* pipe "|"