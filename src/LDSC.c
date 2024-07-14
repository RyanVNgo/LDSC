#include <LDSC.h>
#include <stdlib.h>

struct LDSC_node {
  void* value;
  LDSC_node* next;
};

struct LDSC_linkedList {
  int length;
  LDSC_node* head;
  LDSC_node* tail;
};

LDSC_linkedList* LDSC_linkedList_init() {
  LDSC_linkedList* newLL = (LDSC_linkedList*)malloc(sizeof(LDSC_linkedList));
  newLL->length = 0;
  newLL->head = NULL;
  newLL->tail = NULL;
  return newLL;
}

int LDSC_linkedList_length(LDSC_linkedList* inLL) {return inLL->length;}
LDSC_node* LDSC_linkedList_head(LDSC_linkedList* inLL) {return inLL->head;}
LDSC_node* LDSC_linkedList_tail(LDSC_linkedList* inLL) {return inLL->tail;}

void LDSC_linkedList_insert(void*);

