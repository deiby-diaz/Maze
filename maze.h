#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

typedef struct{
    short int rows;
    short int cols;
} Dimensions;

typedef enum {EMPTY, WALL, EXIT, FULL} CellType;

typedef enum {UP, DOWN, RIGHT, LEFT,UNKNOWN} Orientation;

typedef struct
{
    short int row;
    short int col;
    char value;
    CellType type;
    Orientation orientation;
} Cell;

typedef struct
{
    short int rows;
    short int cols;
    Cell ***matrix;
} Maze;

Maze* new_maze(char* FilePath);
void allocate_maze(Maze *m, char* PathFile, int rows, int cols);
void print_maze(Maze *m);

#endif // Maze_H_INCLUDED
