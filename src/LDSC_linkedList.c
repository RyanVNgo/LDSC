#include <LDSC_linkedList.h>
#include <stdlib.h>

/** node structure */
typedef struct Node {
  void* dataPtr;
  struct Node* next;
  struct Node* prev;
} Node;

/** create and return a new linked list node */
static Node* Node_init(void* dataPtrIn) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

/* private data structure */
struct privateData {
  int length;
  Node* head;
  Node* tail;
};

/* get node of linkedd list at index */
static Node* LDSC_linkedList_getNode(LDSC_linkedList* self, int index) {
  Node* currNode = self->pd->head;
  for (int i = 0; i < index; i++)
    currNode = currNode->next;
  return currNode;
}

/**************************************************/
/* LDSC_linkedList */

/**
  * @brief Get length of the linked list.
  * @param self LDSC_linkedList pointer.
  * @return Length of the linked list as integer type.
  */
int LDSC_linkedList_length(LDSC_linkedList* self) {
  if (!self) return -1;
  return self->pd->length;
}

/**
  * @brief Check if linked list is empty.
  * @param self LDSC_linkedList pointer.
  * @return Integer where 1 = empty and 0 = not empty.
  */
int LDSC_linkedList_empty(LDSC_linkedList* self) {
  if (!self) return -1;
  return self->pd->length == 0;
}

/**
  * @brief Add item at the end of the linked list.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @return Integer where 1 = success and 0 = failure.
  * @details
  * Keep note that prepend performs a shallow copy of the data.
  */
int LDSC_linkedList_append(LDSC_linkedList* self, void* dataPtr) {
  if (!self || !dataPtr) return -1;
  Node* newNode = Node_init(dataPtr);

  if (!self->pd->tail) {
    self->pd->head = newNode;
  } else {
    self->pd->tail->next = newNode;
    newNode->prev = self->pd->tail;
  }
  self->pd->tail = newNode;
  
  self->pd->length++;
  return 1;
}

/**
  * @brief Add item at the front of the linked list.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @return Integer where 1 = success and 0 = failure.
  * @details
  * Keep note that append performs a shallow copy of the data.
  */
int LDSC_linkedList_prepend(LDSC_linkedList* self, void* dataPtr) {
  if (!self || !dataPtr) return -1;
  Node* newNode = Node_init(dataPtr);

  if (!self->pd->head) {
    self->pd->tail = newNode;
  } else {
    self->pd->head->prev = newNode;
    newNode->next = self->pd->head;
  }
  self->pd->head = newNode;

  self->pd->length++;
  return 1;
}

/**
  * @brief Add item at index of the linked list.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @param index Index to add item at.
  * @return Integer where 1 = success and 0 = failure.
  * @details
  * Keep note that add performs a shallow copy of the data.
  */
int LDSC_linkedList_add(LDSC_linkedList* self, void* dataPtr, int index) {
  if (!self || !dataPtr) return -1;
  if (index < 0 || index > self->pd->length) return 0;
  if (index == 0) return LDSC_linkedList_append(self, dataPtr);
  if (index == self->pd->length) return LDSC_linkedList_prepend(self, dataPtr);

  Node* newNode = Node_init(dataPtr);
  Node* prevNode = LDSC_linkedList_getNode(self, index - 1);
  Node* nextNode = prevNode->next;

  prevNode->next = newNode;
  newNode->prev = prevNode;
  newNode->next = nextNode;
  nextNode->prev = newNode;

  self->pd->length++;
  return 1;
}

/**
  * @brief Replace item at index.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @param index Index of item to replace with dataPtr.
  * @return Data pointer of item that was replaced.
  * @details
  * Keep note that replace performs a shallow copy of the data.
  */
void* LDSC_linkedList_replace(LDSC_linkedList* self, void* dataPtr, int index) {
  if (!self || !dataPtr || index <= 0 || index >= self->pd->length) return NULL;
  Node* targetNode = LDSC_linkedList_getNode(self, index);

  void* replacedDataPtr = targetNode->dataPtr;
  targetNode->dataPtr = dataPtr;

  return replacedDataPtr;
}

/**
  * @brief Remove item at the front of the list.
  * @param self LDSC_linkedList pointer.
  * @return Data pointer of item that was removed.
  */
void* LDSC_linkedList_pop(LDSC_linkedList* self) {
  if (!self || !self->pd->head) return NULL;

  Node* targetNode = self->pd->head;
  void* returnData = targetNode->dataPtr;

  self->pd->head = targetNode->next;

  if (self->pd->head)
    self->pd->head->prev = NULL;
  else 
    self->pd->tail = self->pd->head;
  
  self->pd->length--;

  free(targetNode);
  return returnData;
}

/**
  * @brief Remove item at the end of the list.
  * @param self LDSC_linkedList pointer.
  * @return Data pointer of item that was removed.
  */
void* LDSC_linkedList_pull(LDSC_linkedList* self) {
  if (!self || !self->pd->tail) return NULL;

  Node* targetNode = self->pd->tail;
  void* returnData = targetNode->dataPtr;

  self->pd->tail = targetNode->prev;

  if (self->pd->tail)
    self->pd->tail->next = NULL;
  else
    self->pd->head = self->pd->tail;

  self->pd->length--;

  free(targetNode);
  return returnData;
}

/**
  * @brief Remove item at index.
  * @param self LDSC_linkedList pointer.
  * @param index Index of item to remove.
  * @return Data pointer of item that was removed.
  */
void* LDSC_linkedList_remove(LDSC_linkedList* self, int index) {
  if (!self || index < 0 || index >= self->pd->length) return NULL;
  if (index == 0) return LDSC_linkedList_pop(self);
  if (index == self->pd->length - 1) return LDSC_linkedList_pull(self);

  Node* targetNode = LDSC_linkedList_getNode(self, index); 
  void* returnData = targetNode->dataPtr;

  Node* prevNode = targetNode->prev;
  Node* nextNode = targetNode->next;

  prevNode->next = nextNode;
  nextNode->prev = prevNode;

  self->pd->length--;

  free(targetNode);
  return returnData;
}

/**
  * @brief Remove all items in the list.
  * @param self LDSC_linkedList pointer.
  */
void LDSC_linkedList_clear(LDSC_linkedList* self) {
  if (!self) return;
  while (!self->empty(self)) {
    self->pop(self);
  }
  return;
}

/**
  * @brief Delete the linked list
  * @param self LDSC_ilnkedList pionter.
  */
void LDSC_linkedList_delete(LDSC_linkedList* self) {
  if (!self) return;
  self->clear(self);
  free(self->pd);
  free(self);
  return;
}

/**************************************************/

/**
 * @brief Create a new linked list.
 * @return Pointer to a LDSC_linkedList.
 */
LDSC_linkedList* LDSC_linkedList_init() {
  LDSC_linkedList* newLL = malloc(sizeof(LDSC_linkedList));
  newLL->pd = malloc(sizeof(privateData));

  newLL->pd->length = 0;
  newLL->pd->head = NULL;
  newLL->pd->tail = NULL;

  newLL->length = &LDSC_linkedList_length;
  newLL->empty = &LDSC_linkedList_empty;
  newLL->add = &LDSC_linkedList_add;
  newLL->append = &LDSC_linkedList_append;
  newLL->prepend = &LDSC_linkedList_prepend;
  newLL->replace = &LDSC_linkedList_replace;
  newLL->remove = &LDSC_linkedList_remove;
  newLL->pop = &LDSC_linkedList_pop;
  newLL->pull = &LDSC_linkedList_pull;
  newLL->clear = &LDSC_linkedList_clear;
  newLL->delete = &LDSC_linkedList_delete;

  return newLL;
}

