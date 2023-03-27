/*
 * Name: Ming Sheng Chai
 * Student Number: 21203216
 * Email: ming.chai@ucdconnect.ie
 * */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "utils.h"

void signalHandler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\n");
        promptUserInput();
        fflush(stdout);
    }
}