#include "thread.h"

struct Simulation {
    Thread *thread;
    Maze *maze;
};



void start_run(Maze *maze){

List *threads = NULL;
maze->matrix[0][0]->value = '$';

// Crear un nuevo hilo
Thread *first_thread = malloc(sizeof(Thread));
set_thread(first_thread,1,1,0,0);



//Agregar un hilo que inicie todo
threads = add_thread(threads,first_thread);
threads = add_thread(threads,first_thread);

// Vamos recorriendo el laberinto

 while(!fullMaze(maze)){

     move_threads(threads,maze);
     sleep(1);
     printf("\033[2J\033[1;1H");

   }


}



void *update_maze(void *sim){

    struct Simulation *arguments = sim;

    Thread *thread = arguments->thread;
    Maze *maze = arguments->maze;

    free(arguments);

    //Validar el siguiente movimiento
    int rowTemp = thread->row;
    int colTemp = thread->col;


    if(maze->matrix[rowTemp+1][colTemp]== ' '){

        //Actualizar maze y el thread
        maze->matrix[rowTemp+1][colTemp] = '$';
        thread->row++;
        thread->tracks++;
    }
    else if(maze->matrix[rowTemp][colTemp+1]== ' '){

        //Actualizar maze y el thread

        maze->matrix[rowTemp][colTemp+1] = '$';
        thread->col++;
        thread->tracks++;
    }

    else{
            printf("hello world\n");
    }

    //print_maze(maze);




}


void move_threads(List *thread, Maze *labirith){
    List *current;
    current = thread;

    List* current_join = thread;

    while (current != NULL) {

        struct Simulation *simulation = malloc(sizeof(struct Simulation));
        int thread_result;
        simulation->thread = current->value;
        simulation->maze = labirith;

        if(simulation!=NULL){

            thread_result = pthread_create(&current->value->thread, NULL,update_maze,(void*)simulation);

            if(thread_result){
            fprintf(stderr,"Error - pthread_create(). Codigo: %d\n",thread_result);
            return;
            }

    }

    current = current->next;
  }


  while(current_join!=NULL){

    pthread_join(current_join->value->thread,NULL);
    current_join = current_join->next;
  }




}

