/*
Mioto Takahashi
71744696
Software Engineering
*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_LIST 10

struct list{
  struct list *next;
  int content;
};

int main(){
  //generate linearly linked list of random integers
  //the first element is saved as a head pointer for future referencing
  struct list *head;
  head = malloc(sizeof(struct list));
  head->content = rand();
  struct list *prev;
  prev = head;
  for (int i=1; i<NUM_LIST; i++){
    struct list *element;
    element = malloc(sizeof(struct list));
    prev->next = element;
    element->content = rand();
    prev = element;
  }
  prev->next = NULL;

  //printing every element of the list
  struct list *current;
  current = head;
  while(current != NULL){
    printf("%d\n", current->content);
    current = current->next;
  }
}
