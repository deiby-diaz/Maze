#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "maze.h"

typedef enum {ALIVE,FINISHED} ThreadStatus;

typedef struct
{
    int id;
    Cell* cell;
    int tracks;
    ThreadStatus state;
} Thread;

typedef struct node {
    Thread *value;
    struct node *next;
} List;

List* add_thread(List*, Thread*);
Thread* setThread(Thread*, Cell*,int,int,ThreadStatus);
int sizeList(List*);



#endif // THREAD_H_INCLUDED
