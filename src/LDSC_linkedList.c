#include <LDSC_linkedList.h>
#include <stdlib.h>

typedef struct LDSC_node {
  void* dataPtr;
  struct LDSC_node* next;
} LDSC_node;

// create and return a new node
static LDSC_node* LDSC_node_init(void* dataPtrIn) {
  LDSC_node* newNode = (LDSC_node*)malloc(sizeof(LDSC_node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  return newNode;
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

// return ptr of node at index
static LDSC_node* LDSC_linkedList_getNode(LDSC_linkedList* LLin, int index) {
  if (index < 0 || index >= LLin->length) return NULL;

  LDSC_node* returnNode = LLin->head;
  for (int i = 0; i < index; i++)
    returnNode = returnNode->next;

  return returnNode; 
}

int LDSC_linkedList_length(LDSC_linkedList* LLin) {return LLin->length;}

void* LDSC_linkedList_head(LDSC_linkedList* LLin) {
  if (!LLin->head) return NULL;
  return LLin->head->dataPtr;
}

void* LDSC_linkedList_tail(LDSC_linkedList* LLin) {
  if (!LLin->tail) return NULL;
  return LLin->tail->dataPtr;
}

void LDSC_linkedList_append(LDSC_linkedList* LLin, void* dataPtrIn) {
  if (!LLin || !dataPtrIn) return;

  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  LDSC_node* oldTail = LLin->tail;
  LLin->tail = newNode;

  if (!oldTail)
    LLin->head = LLin->tail;
  else
    oldTail->next = LLin->tail;

  LLin->length++;
  return;
}

void LDSC_linkedList_prepend(LDSC_linkedList* LLin, void* dataPtrIn) {
  if (!LLin || !dataPtrIn) return;

  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  newNode->next = LLin->head;
  LLin->head = newNode;

  if (!LLin->tail)
    LLin->tail = LLin->head;

  LLin->length++;
  return;
}

void* LDSC_linkedList_get(LDSC_linkedList* LLin, int index) {
  if (!LLin || index < 0 || index >= LLin->length) return NULL;
  
  if (index == 0) return LLin->head->dataPtr;
  if (index == LLin->length - 1) return LLin->tail->dataPtr;
  LDSC_node* targetNode = LDSC_linkedList_getNode(LLin, index);

  return targetNode->dataPtr;
}

void LDSC_linkedList_insert(LDSC_linkedList* LLin, void* dataPtrIn, int index) {
  if (!LLin || !dataPtrIn || index < 0 || index > LLin->length) return;

  if (index == 0) {LDSC_linkedList_prepend(LLin, dataPtrIn); return;}
  if (index == LLin->length) {LDSC_linkedList_append(LLin, dataPtrIn); return;}

  LDSC_node* prevNodeOfInsert = LDSC_linkedList_getNode(LLin, index-1);
  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  newNode->next = prevNodeOfInsert->next;
  prevNodeOfInsert->next = newNode;
  
  LLin->length++;
  return;
}

void* LDSC_linkedList_removeFirst(LDSC_linkedList* LLin) {
  if (!LLin || !LLin->length) return NULL;

  LDSC_node* oldHead = LLin->head;
  void* firstDataPtr = oldHead->dataPtr;
  LLin->head = oldHead->next;

  if (!LLin->head)
    LLin->tail = LLin->head;

  LLin->length--;
  free(oldHead);
  return firstDataPtr;
}

void* LDSC_linkedList_removeLast(LDSC_linkedList* LLin) {
  if (!LLin || !LLin->length) return NULL;

  if (LLin->length == 1) return LDSC_linkedList_removeFirst(LLin);
  
  LDSC_node* oldTail = LLin->tail;
  void* lastDataPtr = oldTail->dataPtr;
  LLin->tail = LDSC_linkedList_getNode(LLin, LLin->length - 2);
  LLin->tail->next = NULL;

  LLin->length--;
  free(oldTail);
  return lastDataPtr;
}

void* LDSC_linkedList_remove(LDSC_linkedList* LLin, int index) {
  if (!LLin || !LLin->length || index < 0 || index >= LLin->length) return NULL;

  if (index == 0) return LDSC_linkedList_removeFirst(LLin);
  if (index == LLin->length - 1) return LDSC_linkedList_removeLast(LLin);

  LDSC_node* prevNodeOfRemove = LDSC_linkedList_getNode(LLin, index - 1);
  LDSC_node* removeNode = prevNodeOfRemove->next;
  void* removeDataPtr = removeNode->dataPtr;
  prevNodeOfRemove->next = removeNode->next;

  LLin->length--;
  free(removeNode);
  return removeDataPtr;
}

