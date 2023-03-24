#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"



int main()
{
    signal(SIGINT, signalHandler);      //register signal interrupt


    while(1)
    {
        promptUserInput();
        char* userCommand = userInput();
        char** args = splitInput(userCommand);

        if(args == NULL) //newline entered
            continue;

        if(strcmp(args[0], "exit") == 0)    //exit shell
            break;

        execProgram(args);
    }

}

