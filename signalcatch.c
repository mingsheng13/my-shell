
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
