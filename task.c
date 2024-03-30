#include <stdlib.h>
#include "task.h"


tcb_t  task_queue;
tcb_t* cur_task;


void add_task(tcb_t* new_task) 
{
    new_task->next = NULL;

    if (task_queue.next == NULL) 
        task_queue.next = new_task;
    else 
    {
        tcb_t* last_task = task_queue.next; 

        while (last_task->next != NULL) 
            last_task = last_task->next;
 
        last_task->next = new_task;
    }
}


tcb_t* get_first_task()
{
    if (task_queue.next == NULL) 
        return NULL;

    tcb_t* next_task = task_queue.next;
    task_queue.next = next_task->next;
    next_task->next = NULL;

    return next_task;
}