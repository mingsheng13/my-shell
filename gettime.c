
#include <bits/types/time_t.h>
#include <malloc.h>
#include <time.h>
#include "utils.h"

char* timestamp()
{
    time_t rawtime;
    struct tm *info;
    char* buffer = (char*)malloc(15 * sizeof(char));

    time( &rawtime );

    info = localtime( &rawtime );

    strftime(buffer,80,"[%d/%m %H:%M]", info);
    return buffer;
}