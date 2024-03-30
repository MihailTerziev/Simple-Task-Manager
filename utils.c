#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "task.h"
#include "scheduler.h"


#define FIBER_STACK     1024 * 64


tcb_t  task_queue;
tcb_t* cur_task;


void* initlibrary() 
{
    task_queue.next = NULL; 
    cur_task = NULL;

    init_timer();
}

 
void print_task_content() 
{
    while (1) 
        printf("%c", cur_task->symbol);
}


int create_task(void (*start_routine)(), char symbol) 
{ 
    tcb_t* new_task = (tcb_t*)malloc(sizeof(tcb_t));

    if (new_task == NULL) 
        return -1;

    getcontext(&new_task->context);
 
    new_task->context.uc_stack.ss_sp = malloc(FIBER_STACK); 
    new_task->context.uc_stack.ss_size = FIBER_STACK; 
    new_task->context.uc_link = &task_queue.context;
    new_task->symbol = symbol;

    makecontext(&new_task->context, start_routine, 0);
    add_task(new_task);

    return 0;
}


void loop()
{
    cur_task = get_first_task();

    while (1) 
    {
        if (cur_task == NULL) 
            exit(0);

        tcb_t* next_task = get_first_task();

        if (next_task != NULL) 
        {
            add_task(cur_task);
            cur_task = next_task;
        }

        swapcontext(&task_queue.context, &cur_task->context);
    }
}