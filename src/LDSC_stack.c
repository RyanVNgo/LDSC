#include "LDSC_errors.h"
#include <LDSC_stack.h>
#include <stdlib.h>

/** node structure */
typedef struct Node {
  void* dataPtr;
  struct Node* next;
} Node;

/** create and return a new stack node */
static Node* Node_init(void* dataPtr) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (!newNode) return NULL;

  newNode->dataPtr = dataPtr;
  newNode->next = NULL;
  return newNode;
}

/**
  * @brief Opaque container for private data.
  */
struct privateData{
  int size;
  Node* top;
};

/**************************************************/
/* LDSC_stack */

/**
  * @brief Get size of the stack.
  * @param self Stack pointer.
  * @param status Error pointer.
  * @return Size of the stack as integer type.
  */
int LDSC_stack_size(LDSC_stack* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return ERROR;
  }
  
  return self->pd->size;
}

/**
  * @brief Push an item to the stack.
  * @param self Stack pointer.
  * @param dataPtr Pointer to data.
  * @param status Error pointer.
  * @details
  * Keep note that push performs a shallow copy of the data.
  */
void LDSC_stack_push(LDSC_stack* self, void* dataPtr, LDSC_error* status) {
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
    if (status) *status = NULL_SELF;
    return;
  }

  newNode->next = self->pd->top;
  self->pd->top = newNode;
  self->pd->size++;
  return;
}

/**
  * @brief Check if stack is empty.
  * @param self Stack pointer.
  * @param status Error pointer.
  * @return Integer where 1 = empty and 0 = not empty
  */
int LDSC_stack_empty(LDSC_stack* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return ERROR;
  }

  return self->pd->size == 0;
}

/**
  * @brief Peek item at the top of the stack.
  * @param self Stack pointer.
  * @param status Error pointer.
  * @return Pointer to data at the top of the stack.
  */
void* LDSC_stack_peek(LDSC_stack* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (!self->pd->top) 
    return NULL;

  return self->pd->top->dataPtr;
}

/**
  * @brief Pop an item from the stack.
  * @param self Stack pointer.
  * @param status Error pointer.
  * @return Pointer to data at the top of the stack.
  */
void* LDSC_stack_pop(LDSC_stack* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (!self->pd->top)
    return NULL;

  Node* oldTop = self->pd->top;
  void* dataTop = oldTop->dataPtr;
  self->pd->top = oldTop->next;
  self->pd->size--;

  free(oldTop);
  return dataTop;
}

/**
  * @brief Delete the stack.
  * @param self Stack pointer.
  * @param status Error pointer.
  */
void LDSC_stack_delete(LDSC_stack* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  while (self->pd->top) {
    self->pop(self, status);
  }

  if (self->pd->size != 0)
    if (status) *status = DELETE_FAIL;

  free(self->pd);
  free(self);
  return;
}

/**
 * @brief Create a new stack.
 * @par Parameters
 *  None.
 * @return Pointer to an LDSC_stack.
 */
LDSC_stack* LDSC_stack_init(LDSC_error* status) {
  if (status) *status = OK;

  LDSC_stack* newStack = malloc(sizeof(LDSC_stack));
  if (!newStack) {
    if (status) *status = STRUCTURE_MALLOC;
    return NULL;
  }

  newStack->pd = malloc(sizeof(privateData));
  if (!newStack->pd) {
    if (status) *status = PRIVATEDATA_MALLOC;
    free(newStack);
    return NULL;
  }

  newStack->pd->size = 0;
  newStack->pd->top = NULL;

  newStack->size = &LDSC_stack_size;
  newStack->push = &LDSC_stack_push;
  newStack->empty = &LDSC_stack_empty;
  newStack->peek = &LDSC_stack_peek;
  newStack->pop = &LDSC_stack_pop;
  newStack->delete = &LDSC_stack_delete;

  return newStack;
}
