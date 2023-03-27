/*
 * Name: Ming Sheng Chai
 * Student Number: 21203216
 * Email: ming.chai@ucdconnect.ie
 * */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <ctype.h>
#include <fcntl.h>
#include "utils.h"

int redirect(char** args);

void promptUserInput()
{
    printf("%s# ", timestamp());
}

char* userInput()
{
    size_t inputSize = 128;
    char* getInput = (char*)malloc(inputSize * sizeof(char));
    if (getline(&getInput, &inputSize, stdin) == -1)    //reads an EOF
        exit(0);
    char* firstTrim = trimNewline(getInput);
    char* secondTrim = trimWhitespace(firstTrim);
    return secondTrim;
}

char** splitInput(char* line)
{
    if (strcmp(line, "\0") == 0)    //empty input
        return NULL;

    size_t size = strlen(line);
    int pos = 0;
    char delimiter[] = " \n";

    char *token = strtok(line, delimiter);

    //allocating memory
    char **tokens = (char**)malloc(size * sizeof(char*));

    while(token != NULL)
    {
        tokens[pos++] = token;
        token = strtok(NULL, delimiter);
    }
    tokens[pos] = NULL; //set last string as null
    return tokens;
}

int execProgram(char** args)
{
    if (strcmp(args[0], "cd") == 0)     //check for cd command
    {
        char* HOME = getenv("HOME");    //get home path
        if (args[1] == NULL)    //if no argument given
        {
            chdir(HOME);    //cd to home path
            return 0;
        }

        if (chdir(args[1]))     //cd to args[1] given. if non zero return, error occurred.
        {
            perror("MyShell: cd");
        }
        return 0;
    }

    /*
     * not cd command
     */

    pid_t cid;
    cid = fork();

    if (cid == -1)
        perror("fork");


    if (cid == 0) //child process
    {
        int redirectIndex = redirect(args);     //check if command contains redirection
        if (redirectIndex)
        {
            int f = open(args[redirectIndex + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            dup2(f, 1);     //redirect output
            args[redirectIndex] = NULL;     //ignore arguments after >
        }

        int i = execvp(args[0], args);
        dup2(STDIN_FILENO, 1);  //redirect output to stdout
        perror("execvp");
        exit(i);
    }
    //parent
    int status = 0;
    wait(&status);
//    if (WIFEXITED(status))
//        printf("exit status = %d\n", WEXITSTATUS(status));
    return status;
}

int redirect(char** args)   //return the position of '>'
{
    int i = 0;
    while (*args != NULL)
    {
        if (strchr(*args, '>') != NULL)
            return i;
        args++;
        i++;
    }
    return 0;
}

char* trimWhitespace(char* input)
{
    char* endPtr;
    //trim leading spaces
    while(isspace((char)*input))
        input++;

    if (*input == 0)  //all spaces
        return input;

    //trim trailing spaces
    endPtr = input + strlen(input) - 1;    //points to the last element in input
    while(endPtr > input && isspace((char)*endPtr)) //loop from behind
        endPtr--;

    endPtr[1] = '\0'; //assign null terminator

    return input;
}

char* trimNewline(char* input)
{
    char *trimmed = (char*)malloc(128 * sizeof(char));
    strcpy(trimmed, input);
    size_t index = strcspn(input, "\n");
    trimmed[index] = 0;
    return trimmed;
}









