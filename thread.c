#include "thread.h"

/**
    Add a new thread
*/
List* add_thread(List *head, Thread *thread) {
      List *temp =head;

      List *newNode= (List*)malloc(sizeof (List));
      newNode->value=thread;

      if(head==NULL)
      {
          head=newNode;
          head->next=NULL;
          return head;
      }
      else
      {
          while(temp->next!=NULL)
          {
               temp=temp->next;
          }
          newNode->next=NULL;
          temp->next=newNode;
          return head;
      }

}

/**
    Set thread arguments
*/
Thread* setThread(Thread *thread, Cell *cell,int threadID,
                int initialTrack,ThreadStatus newState){

     thread->cell = cell;
     thread->id = threadID;
     thread->tracks = initialTrack;
     thread->state = newState;
     return thread;
}

/**
    Return the size of thread list
*/
int sizeList(List *threadList){
    int length = 0;
    List *temp = threadList;
    while(temp!=NULL){
         if(temp->value->state == FINISHED){
             temp = temp->next;
         }
         else{
             length++;
             temp = temp->next;
         }
    }
    return length;
}


