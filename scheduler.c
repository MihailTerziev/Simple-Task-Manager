#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "scheduler.h"
#include "task.h"


void signal_dispatcher(int signum) 
{
    tcb_t* next_task = get_first_task();

    if (next_task != NULL) 
    { 
        add_task(cur_task);
        cur_task = next_task;

        swapcontext(&task_queue.context, &cur_task->context);
    }
}


void init_timer()
{
    struct sigaction sa;
    struct itimerval timer;

    sa.sa_handler = signal_dispatcher;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGALRM, &sa, NULL);

    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_usec = 0;

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
}