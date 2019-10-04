#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM 10000
#define BUCKET 100000
#define DELTA 2

struct list{
  int value;
  struct list* next;
};

struct int_array{
  int value;
  bool assigned;
};

int main(){
  // linear list
  struct list* head;
  head = malloc(sizeof(struct list));
  head->value = rand();
  struct list* prev;
  prev = head;
  for (int i=1; i<NUM; i++){
    struct list* tmp;
    tmp = malloc(sizeof(struct list));
    prev->next = tmp;
    tmp->value = rand();
    prev = tmp;
  }
  prev->next = NULL;

  // initializing hash table
  struct int_array hash [BUCKET];
  for(int i=0; i<BUCKET; i++){
    hash[i].value = 0;
    hash[i].assigned = false;
  }

  // open addressing
  prev = head;
  int tmp_index;
  while (prev->next != NULL){
    tmp_index = prev->value % BUCKET;
    while (hash[tmp_index].assigned == true){
      tmp_index += DELTA;
    }
    hash[tmp_index].value = prev->value;
    hash[tmp_index].assigned = true;
    prev = prev->next;
  }

  // visualizing values stored in hash
  for(int i=0; i<BUCKET; i++){
    printf("%i\n", hash[i].value);
  }  
}
