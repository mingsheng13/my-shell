//
// Created by cms on 3/9/23.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <wait.h>
#include <time.h>
#include <ctype.h>
#include "utils.h"


void promptUserInput()
{
    printf("%s# ", timestamp());
}

char* userInput()
{
    size_t inputSize = 32;
    char* getInput = (char*)malloc(inputSize * sizeof(char));
    getline(&getInput, &inputSize, stdin);
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

    //allocating mem
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
    pid_t cid;
    cid = fork();

    if (cid == -1)
        perror("fork failed");

    if (cid == 0) //child process
    {
        int i = execvp(args[0], args);
        printf("execvp failed\n");
        exit(i);
    }
    //parent
    signal(SIGINT, SIG_IGN); //catch ctrl c
    int status = 0;
    wait(&status);
    if (WIFEXITED(status))
        printf("exit status = %d\n", WEXITSTATUS(status));
    return status;
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
    char *trimmed = (char*)malloc(sizeof(char));
    strcpy(trimmed, input);
    size_t index = strcspn(input, "\n");
    trimmed[index] = 0;
    return trimmed;
}









