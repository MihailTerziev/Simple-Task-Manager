#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "scheduler.h"
#include "utils.h"


int main(int argc, char *argv[]) 
{
    initlibrary();

    if (argc < 2) 
    {
        printf("Please provide at least one task!\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) 
    {
        if (create_task(print_task_content, argv[i][0]) != 0)
            return 1;
    }

    loop();
}