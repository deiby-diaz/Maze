#include <stdlib.h>
#include <pthread.h>
#include "maze_solver.h"

List* listThreads = NULL;

bool validMaze(Maze* maze){
     return maze->matrix[0][0]->type != WALL;
}

/**
start_menu(): typing the maze file to read and work the file
*/

void start_menu(){
    char file[1024];
    printf("Type your maze file: ");
    scanf("%[^\n]", file);

    // Initialize Maze from "maze" file
    char* FilePath = file;
    Maze* m = new_maze(FilePath);

    inicializeThreads(m);
    solve(m,listThreads);
}

/**
inicializeThreads():  initializes the first cell to be counted
*/

void inicializeThreads(Maze *m){
    Thread* threadFirst = malloc(sizeof(Thread));
    m->matrix[0][0]->orientation = DOWN;
    m->matrix[0][0]->type =FULL;
    if(!validMaze(m)){
        printf("\nINVALID MAZE");
        exit(0);
    }
    setThread(threadFirst,m->matrix[0][0],1,-1,ALIVE);
    listThreads = add_thread(listThreads,threadFirst);
}


int main(int argc , char *argv[])
{
    start_menu(); // Starts the program
    return 0;
}

