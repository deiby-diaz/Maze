#include "thread.h"
/* FOREGROUND */
#define RST   "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

Cell* create_cell(char value, int row, int col){
    Cell *cell = malloc(sizeof(Cell));
    cell->row = row;
    cell->col = col;
    switch(value){
        case '*':
            cell->type = WALL;
            break;
        case '_':
            cell->type = EMPTY;
            break;
        case '/':
            cell->type = EXIT;
            break;
        default:
            cell->type = WALL;
    }
    cell->value = value;
    return cell;
}

/**
    Read file in order to get its maze dimension
*/

Dimensions getMazeDimensions(char* FilePath){
    FILE* SourceFile = fopen(FilePath, "r");
    Dimensions dims;
    int rowCount = 0;
    int colCount = 0;
    char actualChar;
    while((actualChar = getc(SourceFile)) != EOF){
        if(actualChar == '\n')
            rowCount++;
        else
            colCount++;
    }
    colCount = colCount/rowCount;
    dims.rows = rowCount;
    dims.cols = colCount;
    fclose(SourceFile);
    return dims;
}

/**
    Create a new maze from file
*/
Maze* new_maze(char* FilePath){
    Dimensions dims = getMazeDimensions(FilePath);
    Maze *m = malloc(sizeof(Maze));
    allocate_maze(m, FilePath, dims.rows, dims.cols);
    return m;
}

/**
    Allocate maze on memory
*/
void allocate_maze(Maze *m, char* FilePath, int rows, int cols){
    FILE* SourceFile = fopen(FilePath, "r");
    m->rows = rows;
    m->cols = cols;
    m->matrix = (Cell***) malloc(rows * sizeof(Cell**));

    char actualChar;
    int i, j;
    for(i=0; i<rows; i++){
        m->matrix[i] = (Cell**) malloc(cols * sizeof(Cell*));
        for (j=0; j<cols; j++){
            actualChar = getc(SourceFile);
            while(actualChar == '\n')
                actualChar = getc(SourceFile);

            m->matrix[i][j] = create_cell(actualChar, i, j);

        }
    }

    fclose(SourceFile);

}

/**
    Print the maze
*/

void print_maze(Maze *m){
    int i, j;
    printf("\n");
    for (i=0; i<m->rows; i++){
        for (j=0; j<m->cols; j++){
            if(m->matrix[i][j]->type == FULL){
                printf(KRED  "� ");
            }
            else{
                printf(KWHT "%c ", m->matrix[i][j]->value);
            }
        }
        printf("\n");
    }
}


