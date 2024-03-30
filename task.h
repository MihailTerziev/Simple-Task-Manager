#ifndef TASK_H
#define TASK_H

#include <ucontext.h>


typedef struct tcb_t 
{
    ucontext_t     context; 
    char           symbol;
    struct tcb_t*  next;
} tcb_t;


extern tcb_t  task_queue;
extern tcb_t* cur_task;


void add_task(tcb_t* new_task);
tcb_t* get_first_task();

#endif  // TASK_H