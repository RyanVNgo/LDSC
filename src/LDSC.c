#include <LDSC.h>
#include <stdlib.h>

struct LDSC_node {
  void* dataPtr;
  LDSC_node* next;
};

LDSC_node* LDSC_node_init(void* dataPtrIn) {
  LDSC_node* newNode = (LDSC_node*)malloc(sizeof(LDSC_node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  return newNode;
}

void* LDSC_node_dataPtr(LDSC_node* nodeIn) {
  return nodeIn->dataPtr;
}

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

void LDSC_linkedList_insert(LDSC_linkedList* LLin, void* dataPtr) {
  LDSC_node* newNode = LDSC_node_init(dataPtr);

  if (LLin->head == NULL) {
    LLin->head = newNode;
    LLin->tail = newNode;
    LLin->length++;
    return;
  }

}

