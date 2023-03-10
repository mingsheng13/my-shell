//
// Created by cms on 3/10/23.
//
#include <stdio.h>
#include <signal.h>
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

//void signalInProcess(int signal)
//{
//    if (signal == SIGINT)
//    {
//        printf("\n");
//        promptUserInput();
//        fflush(stdout);
//    }
//}
