#include "maze_solver.h"
#define KWHT  "\x1B[37m"


List *threadArray = NULL;
List *threadFinished = NULL;
typedef struct {
    Maze *maze;
    Cell *cell;
    Thread *thread;
    Orientation orient;

} ThreadInfo;



/**
    <Check for next movement possibilities>
*/

bool canGoDown(Maze* maze, Cell* cell){
    short int nextRow = cell->row + 1;
    if(nextRow < maze->rows)
        return (maze->matrix[nextRow][cell->col]->type != WALL &&
                maze->matrix[nextRow][cell->col]->type != FULL);
    return false;
}

bool canGoRight(Maze* maze, Cell* cell){
    short int nextCol= cell->col + 1;
    if(nextCol < maze->cols)
        return (maze->matrix[cell->row][nextCol]->type != WALL &&
                maze->matrix[cell->row][nextCol]->type != FULL);
    return false;
}

bool canGoLeft(Maze* maze, Cell* cell){
    short int nextCol= cell->col - 1;

    if(nextCol >= 0)
        return (maze->matrix[cell->row][nextCol]->type != WALL &&
                maze->matrix[cell->row][nextCol]->type != FULL);
    return false;
}

bool canGoUp(Maze* maze, Cell* cell){
    short int nextRow = cell->row - 1;
    if(nextRow >= 0)
        return (maze->matrix[nextRow][cell->col]->type != WALL &&
                maze->matrix[nextRow][cell->col]->type != FULL);
    return false;
}

bool fullMaze(Maze* maze){
     int i,j;
     for(i = 0; i < maze->rows; i++){
         for(j = 0; j < maze->cols; j++){
             if(maze->matrix[i][j]->type == EMPTY || maze->matrix[i][j]->type == EXIT)
                return false;
         }
     }
     return true;
}

bool isExit(Cell* cell){
    return cell->type == EXIT;
}



/**
    </Check for next movement possibilities>
*/



/**
    <Get total moves until a wall or matrix edge>
*/

Cell* goDownUntilMazeEdge(Maze* maze, Cell* cell, Thread* thread){
    short int row = cell->row + 1;
    short int col = cell->col;
    cell = maze->matrix[row][col];
    if(isExit(maze->matrix[row][col])){
        threadFinished = add_thread(threadFinished,thread);
    }
    cell->type = FULL;
    cell->orientation = DOWN;
    thread->cell = cell;
    thread->tracks++;
    return cell;
}

Cell* goRightUntilMazeEdge(Maze* maze, Cell* cell, Thread* thread){
    short int col = cell->col + 1;
    short int row = cell->row;
    cell = maze->matrix[row][col];
    if(isExit(maze->matrix[row][col])){
        threadFinished = add_thread(threadFinished,thread);
    }
    cell->type = FULL;
    cell->orientation = RIGHT;
    thread->cell = cell;
    thread->tracks++;
    return cell;
}

Cell* goUpUntilMazeEdge(Maze* maze, Cell* cell,Thread* thread){
    short int row = cell->row - 1;
    short int col = cell->col;
    cell = maze->matrix[row][col];
    if(isExit(maze->matrix[row][col])){
        threadFinished = add_thread(threadFinished,thread);
    }
    cell->type = FULL;
    cell->orientation = UP;
    thread->cell = cell;
    thread->tracks++;
    return cell;
}

Cell* goLeftUntilMazeEdge(Maze* maze, Cell* cell, Thread *thread){
    short int col = cell->col-1;
    short int row = cell->row;
    cell = maze->matrix[row][col];
    if(isExit(maze->matrix[row][col])){
        threadFinished = add_thread(threadFinished,thread);
    }
    cell->type = FULL;
    cell->orientation = LEFT;
    thread->cell = cell;
    thread->tracks++;
    return cell;
}

/**
    <Get total moves until a wall or matrix edge>
*/



/**
    <Change and set the new threads created>
*/

int getNewID(){
    return rand() % 1000000 + 1; // gets the new ID thread
}

void setThreadOrientation(Cell* cell, Orientation orient){
     cell->orientation = orient;
}

/**
    <Change and set the new threads created>
*/



/**
    <Set the new arguments for the new threads>
*/

void setNewThreadParams(Maze* maze, Cell* cell,Thread* thread,int newID,
                           Orientation orient){

     Thread* newThread = malloc(sizeof(Thread));
     int idNewThread = newID;
     int newTrack = thread->tracks;
     setThreadOrientation(cell,orient);
     newThread = setThread(newThread,cell,idNewThread,newTrack,ALIVE);
     threadArray = add_thread(threadArray,newThread);
}

/**
    <Set the new arguments for the new threads>
*/



/**
    <Check the movements for the current thread>
*/


void checkDownMovements(Maze* maze, Cell* cell,Thread* thread){
     Cell *newCell, *newCellAux;
     int newIDLeft, newIDRight;
     if(canGoLeft(maze, cell)){
        newIDLeft = getNewID();
        newCell = goLeftUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCell,thread,newIDLeft,LEFT);
    }
     if(canGoRight(maze, cell)){
        newIDRight = getNewID();
        newCellAux = goRightUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCellAux,thread,newIDRight,RIGHT);
    }

     if(canGoDown(maze, cell)){
        goDownUntilMazeEdge(maze,cell,thread);
    }

}

void checkRightMovements(Maze* maze, Cell* cell,Thread* thread){
    Cell *newCell, *newCellAux;
    int newIDDown, newIDUp;
    if(canGoDown(maze, cell)){
        newIDDown = getNewID();
        newCell = goDownUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCell,thread,newIDDown,DOWN);
    }
    if(canGoUp(maze, cell)){
        newIDUp = getNewID();
        newCellAux = goUpUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCellAux,thread,newIDUp,UP);
    }
    if(canGoRight(maze, cell)){
        goRightUntilMazeEdge(maze,cell,thread);
    }
}

void checkUpMovements(Maze* maze, Cell* cell, Thread* thread){
    Cell *newCell, *newCellAux;
    int newIDLeft, newIDRight;
    if(canGoLeft(maze, cell)){
        newIDLeft = getNewID();
        newCell = goLeftUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCell,thread,newIDLeft,LEFT);
    }
    if(canGoRight(maze, cell)){
        newIDRight = getNewID();
        newCellAux = goRightUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCellAux,thread,newIDRight,RIGHT);
    }
    if(canGoUp(maze, cell)){
        goUpUntilMazeEdge(maze,cell,thread);
    }
}

void checkLeftMovements(Maze* maze, Cell* cell, Thread* thread){
    Cell *newCell, *newCellAux;
    int newIDDown, newIDUp;
    if(canGoDown(maze, cell)){
        newIDDown = getNewID();
        newCell = goDownUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCell,thread,newIDDown,DOWN);
    }
    if(canGoUp(maze, cell)){
        newIDUp = getNewID();
        newCellAux = goUpUntilMazeEdge(maze,cell,thread);
        setNewThreadParams(maze,newCellAux,thread,newIDUp,UP);
    }

    if(canGoLeft(maze, cell)){
        goLeftUntilMazeEdge(maze,cell,thread);
    }

}


/**
    <Check the movements for the current thread>
*/



/**
    <Obtains the possible movements>
*/



void *getPossibleMovements(void* thr){
    ThreadInfo *information = thr;
    Maze *maze = information->maze;
    Cell *cell = information->cell;
    Orientation orient = information->orient;
    Thread *thread = information->thread;
    free(thr);
    switch(orient){
        case DOWN:
            checkDownMovements(maze, cell, thread);
            break;
        case RIGHT:
            checkRightMovements(maze, cell, thread);
            break;
        case UP:
            checkUpMovements(maze, cell, thread);
            break;
        case LEFT:
            checkLeftMovements(maze, cell, thread);
            break;
        default:
            printf("\nUNKNOWN CELL TYPE");
            break;
    }

}


/**
    <Obtains the possible movements>
*/



/**
    <Execute all threads alive>
*/


void executeThreads(Maze* maze, List* listThreads){
       List* current = threadArray;
       int thread_result;
       pthread_t pthread;
       int i = 0;
       while(current!=NULL){
            ThreadInfo *movement = malloc(sizeof(ThreadInfo));
            movement->cell = current->value->cell;
            movement->maze = maze;
            movement->orient = current->value->cell->orientation;
            movement->thread = current->value;
            thread_result = pthread_create(&pthread, NULL,
                                           getPossibleMovements,
                                           (void*)movement);


            if(thread_result){
            fprintf(stderr,"Error - pthread_create(). Codigo: %d\n",thread_result);
            exit(0);
            }


        current = current->next;
        i++;
     }


}

/**
    <Execute all threads alive>
*/


/**
    <Print finished threads>
*/



void printFinalData(List* threadFinished){
     List* data = threadFinished;
     printf(KWHT "\n--------------------------------");
     printf(KWHT "\n       THREADS FINISHED:        ");
     while(data!=NULL){
        printf(KWHT "\nID: %d",data->value->id);
        printf(KWHT "\nSTEPPED CELLS: %d\n",data->value->tracks);
        data = data->next;
     }
     printf(KWHT "\n--------------------------------");

}

/**
    <Print finished threads>
*/



/**
    <Main algorithm>
*/

void solve(Maze* maze, List* listThread){

    threadArray = listThread;
    while(!fullMaze(maze)){
         executeThreads(maze,listThread);
         printf("\e[1;1H\e[2J");
         usleep(SLEEP_TIME);
         print_maze(maze);
   }
   printf("\e[1;1H\e[2J");
   print_maze(maze);
   printFinalData(threadFinished);
   free(threadArray);
   free(threadFinished);
}

/**
    </Main algorithm>
*/
