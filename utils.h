#ifndef UTILS_H
#define UTILS_H


void* initlibrary(); 
void  print_task_content(); 
int   create_task(void (*start_routine)(), char symbol);
void  loop();

#endif  // UTILS_H