#include "LDSC_errors.h"
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
  if (!newNode) return NULL;

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
  * @param status Error pointer.
  * @return Length of the linked list as integer type.
  */
int LDSC_linkedList_length(LDSC_linkedList* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return ERROR;
  }

  return self->pd->length;
}

/**
  * @brief Check if linked list is empty.
  * @param self LDSC_linkedList pointer.
  * @param status Error pointer.
  * @return Integer where 1 = empty and 0 = not empty.
  */
int LDSC_linkedList_empty(LDSC_linkedList* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return ERROR;
  }

  return self->pd->length == 0;
}

/**
  * @brief Add item at the end of the linked list.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @param status Error pointer.
  * @details
  * Keep note that prepend performs a shallow copy of the data.
  */
void LDSC_linkedList_append(LDSC_linkedList* self, void* dataPtr, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  if (!dataPtr) {
    if (status) *status = NULL_DATAPTR;
    return;
  }

  Node* newNode = Node_init(dataPtr);
  if (!newNode) {
    if (status) *status = NODE_MALLOC;
    return;
  }

  if (!self->pd->tail) {
    self->pd->head = newNode;
  } else {
    self->pd->tail->next = newNode;
    newNode->prev = self->pd->tail;
  }
  self->pd->tail = newNode;
  
  self->pd->length++;
  return;
}

/**
  * @brief Add item at the front of the linked list.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @param status Error pointer.
  * @details
  * Keep note that append performs a shallow copy of the data.
  */
void LDSC_linkedList_prepend(LDSC_linkedList* self, void* dataPtr, LDSC_error* status) {
  if (status) *status = OK;
  
  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  if (!dataPtr) {
    if (status) *status = NULL_DATAPTR;
    return;
  }

  Node* newNode = Node_init(dataPtr);
  if (!newNode) {
    if (status) *status = NODE_MALLOC;
    return;
  }

  if (!self->pd->head) {
    self->pd->tail = newNode;
  } else {
    self->pd->head->prev = newNode;
    newNode->next = self->pd->head;
  }
  self->pd->head = newNode;

  self->pd->length++;
  return;
}

/**
  * @brief Add item at index of the linked list.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @param index Index to add item at.
  * @param status Error pointer.
  * @details
  * Keep note that add performs a shallow copy of the data.
  */
void LDSC_linkedList_add(LDSC_linkedList* self, void* dataPtr, int index, LDSC_error* status) {
  if (status) *status = OK;
  
  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  if (!dataPtr) {
    if (status) *status = NULL_DATAPTR;
    return;
  }

  if (index < 0) {
    if (status) *status = LESS_THAN_INDEX;
    return;
  }

  if (index > self->pd->length) {
    if (status) *status = GREATER_THAN_INDEX;
    return;
  }

  if (index == 0) return LDSC_linkedList_append(self, dataPtr, status);
  if (index == self->pd->length) return LDSC_linkedList_prepend(self, dataPtr, status);

  Node* newNode = Node_init(dataPtr);
  if (!newNode) {
    if (status) *status = NODE_MALLOC;
    return;
  }

  Node* prevNode = LDSC_linkedList_getNode(self, index - 1);
  Node* nextNode = prevNode->next;

  prevNode->next = newNode;
  newNode->prev = prevNode;
  newNode->next = nextNode;
  nextNode->prev = newNode;

  self->pd->length++;
  return;
}

/**
  * @brief Get item at index.
  * @param self LDSC_linkedList pointer.
  * @param index Index of item to get.
  * @param status Error pointer.
  * @return Data pointer of item at index.
  */
void* LDSC_linkedList_at(LDSC_linkedList* self, int index, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (index < 0) {
    if (status) *status = LESS_THAN_INDEX;
    return NULL;
  }

  if (index >= self->pd->length) {
    if (status) *status = GREATER_THAN_INDEX;
    return NULL;
  }

  Node* targetNode = LDSC_linkedList_getNode(self, index);

  return targetNode->dataPtr;
}

/**
  * @brief Replace item at index.
  * @param self LDSC_linkedList pointer.
  * @param dataPtr Pointer to data.
  * @param index Index of item to replace with dataPtr.
  * @param status Error pointer.
  * @return Data pointer of item that was replaced.
  * @details
  * Keep note that replace performs a shallow copy of the data.
  */
void* LDSC_linkedList_replace(LDSC_linkedList* self, void* dataPtr, int index, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (!dataPtr) {
    if (status) *status = NULL_DATAPTR;
    return NULL;
  }

  if (index < 0) {
    if (status) *status = LESS_THAN_INDEX;
    return NULL;
  }

  if (index >= self->pd->length) {
    if (status) *status = GREATER_THAN_INDEX;
    return NULL;
  }

  Node* targetNode = LDSC_linkedList_getNode(self, index);

  void* replacedDataPtr = targetNode->dataPtr;
  targetNode->dataPtr = dataPtr;

  return replacedDataPtr;
}

/**
  * @brief Remove item at the front of the list.
  * @param self LDSC_linkedList pointer.
  * @param status Error pointer.
  * @return Data pointer of item that was removed.
  */
void* LDSC_linkedList_pop(LDSC_linkedList* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (!self->pd->head)
    return NULL;

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
  * @param status Error pointer.
  * @return Data pointer of item that was removed.
  */
void* LDSC_linkedList_pull(LDSC_linkedList* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

   if (!self->pd->tail)
     return NULL;

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
  * @param status Error pointer.
  * @return Data pointer of item that was removed.
  */
void* LDSC_linkedList_remove(LDSC_linkedList* self, int index, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (index < 0) {
    if (status) *status = LESS_THAN_INDEX;
    return NULL;
  }

  if (index >= self->pd->length) {
    if (status) *status = GREATER_THAN_INDEX;
    return NULL;
  }

  if (index == 0) return LDSC_linkedList_pop(self, status);
  if (index == self->pd->length - 1) return LDSC_linkedList_pull(self, status);

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
  * @param status Error pointer.
  */
void LDSC_linkedList_clear(LDSC_linkedList* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  //while (!self->empty(self, status)) {
  while (self->pd->length != 0) {
    self->pop(self, status);
    if (*status != OK)
      return;
  }

  if (self->pd->length != 0)
    if (status) *status = ERROR;

  return;
}

/**
  * @brief Delete the linked list
  * @param self LDSC_ilnkedList pionter.
  * @param status Error pointer.
  */
void LDSC_linkedList_delete(LDSC_linkedList* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  self->clear(self, status);
  
  if (self->pd->length != 0)
    if (status) *status = DELETE_FAIL;

  free(self->pd);
  free(self);
  return;
}

/**************************************************/

/**
 * @brief Create a new linked list.
 * @param status Error pointer.
 * @return Pointer to a LDSC_linkedList.
 */
LDSC_linkedList* LDSC_linkedList_init(LDSC_error* status) {
  if (status) *status = OK;

  LDSC_linkedList* newLL = malloc(sizeof(LDSC_linkedList));
  if (!newLL) {
    if (status) *status = STRUCTURE_MALLOC;
    return NULL;
  }


  newLL->pd = malloc(sizeof(privateData));
  if (!newLL->pd) {
    if (status) *status = PRIVATEDATA_MALLOC;
    return NULL;
  }

  newLL->pd->length = 0;
  newLL->pd->head = NULL;
  newLL->pd->tail = NULL;

  newLL->length = &LDSC_linkedList_length;
  newLL->empty = &LDSC_linkedList_empty;
  newLL->append = &LDSC_linkedList_append;
  newLL->prepend = &LDSC_linkedList_prepend;
  newLL->add = &LDSC_linkedList_add;
  newLL->at= &LDSC_linkedList_at;
  newLL->replace = &LDSC_linkedList_replace;
  newLL->pop = &LDSC_linkedList_pop;
  newLL->pull = &LDSC_linkedList_pull;
  newLL->remove = &LDSC_linkedList_remove;
  newLL->clear = &LDSC_linkedList_clear;
  newLL->delete = &LDSC_linkedList_delete;

  return newLL;
}

