#include <LDSC_linkedList.h>
#include <stdlib.h>

typedef struct LDSC_node {
  void* dataPtr;
  struct LDSC_node* next;
} LDSC_node;

LDSC_node* LDSC_node_init(void* dataPtrIn) {
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

LDSC_node* LDSC_linkedList_getNode(LDSC_linkedList* LLin, int index) {
  if (index < 0) return NULL;
  if (index >= LLin->length) return NULL;
  LDSC_node* returnNode = LLin->head;
  for (int i = 0; i < index; i++)
    returnNode = returnNode->next;
  return returnNode; 
}

int LDSC_linkedList_length(LDSC_linkedList* LLin) {return LLin->length;}

void* LDSC_linkedList_head(LDSC_linkedList* LLin) {
  if (LLin->length == 0) return NULL;
  return LLin->head->dataPtr;
}

void* LDSC_linkedList_tail(LDSC_linkedList* LLin) {
  if (LLin->length == 0) return NULL;
  return LLin->tail->dataPtr;
}

void LDSC_linkedList_append(LDSC_linkedList* LLin, void* dataPtr) {
  if (LLin == NULL) return;
  if (dataPtr == NULL) return;

  LDSC_node* newNode = LDSC_node_init(dataPtr);
  if (LLin->head == NULL) {
    LLin->head = newNode;
    LLin->tail = newNode;
    LLin->length++;
    return;
  }

  LLin->tail->next = newNode;
  LLin->tail = newNode;
  LLin->length++;
  return;
}

void LDSC_linkedList_prepend(LDSC_linkedList* LLin, void* dataPtr) {
  if (LLin == NULL) return;
  if (dataPtr == NULL) return;

  LDSC_node* newNode = LDSC_node_init(dataPtr);
  if (LLin->head == NULL) {
    LLin->head = newNode;
    LLin->tail = newNode;
    LLin->length++;
    return;
  }

  newNode->next = LLin->head;
  LLin->head = newNode;
  LLin->length++;
  return;
}

void* LDSC_linkedList_get(LDSC_linkedList* LLin, int index) {
  if (LLin == NULL) return NULL;
  if (index < 0) return NULL;
  if (index >= LLin->length) return NULL;
  if (index == 0) return LLin->head->dataPtr;
  if (index == LLin->length - 1) return LLin->tail->dataPtr;

  LDSC_node* currNode = LLin->head;
  for (int i = 0; i < index; i++)
    currNode = currNode->next;

  return currNode->dataPtr;
}

void LDSC_linkedList_insert(LDSC_linkedList* LLin, void* dataPtr, int index) {
  if (LLin == NULL) return;
  if (dataPtr == NULL) return;
  if (index < 0) return;
  if (index > LLin->length) return;
  if (index == 0) {LDSC_linkedList_prepend(LLin, dataPtr); return;}
  if (index == LLin->length) {LDSC_linkedList_append(LLin, dataPtr); return;}

  LDSC_node* prevNodeOfInsert = LLin->head;
  for (int i = 0; i < index - 1; i++)
    prevNodeOfInsert = prevNodeOfInsert->next;

  LDSC_node* newNode = LDSC_node_init(dataPtr);
  newNode->next = prevNodeOfInsert->next;
  prevNodeOfInsert->next = newNode;
  LLin->length++;
  return;
}

void* LDSC_linkedList_removeFirst(LDSC_linkedList* LLin) {
  if (LLin == NULL) return NULL;
  if (LLin->length == 0) return NULL;

  LDSC_node* oldHead = LLin->head;
  void* firstDataPtr = oldHead->dataPtr;

  LDSC_node* newHead = oldHead->next;
  LLin->length--;
  LLin->head = newHead;
  if (LLin->length <= 1) LLin->tail = newHead;

  free(oldHead);
  return firstDataPtr;
}

void* LDSC_linkedList_removeLast(LDSC_linkedList* LLin) {
  if (LLin == NULL) return NULL;
  if (LLin->length == 0) return NULL;
  if (LLin->length == 1) {
    void* lastDataPtr = LLin->tail->dataPtr;
    free(LLin->tail);
    LLin->head = NULL;
    LLin->tail = NULL;
    LLin->length--;
    return lastDataPtr;
  }

  LDSC_node* oldTail = LLin->tail;
  void* lastDataPtr = oldTail->dataPtr;

  LDSC_node* newTail = LDSC_linkedList_getNode(LLin, LLin->length - 2);
  LLin->length--;
  LLin->tail = newTail;
  if (LLin->length <= 1) LLin->head = newTail;

  free(oldTail);
  return lastDataPtr;
}
