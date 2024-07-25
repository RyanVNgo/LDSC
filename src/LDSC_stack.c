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
  newNode->dataPtr = dataPtr;
  newNode->next = NULL;
  return newNode;
}

/**
  * @brief Opaque container for private data.
  */
struct stackPrivate {
  int size;
  Node* top;
};

/**
  * @brief Get size of the stack.
  * @param self Stack pointer.
  * @return Size of the stack as integer type.
  */
int LDSC_stack_size(LDSC_stack* self) {
  if (!self) return -1;
  return self->pd->size;
}

/**
  * @brief Push an item to the stack.
  * @param self Stack pointer.
  * @param dataPtr Pointer to data.
  * @details
  * Keep note that push performs a shallow copy of the data.
  */
void LDSC_stack_push(LDSC_stack* self, void* dataPtr) {
  if (!self || !dataPtr) return;
  Node* newNode = Node_init(dataPtr);
  newNode->next = self->pd->top;
  self->pd->top = newNode;
  self->pd->size++;
  return;
}

/**
  * @brief Check if stack is empty.
  * @param self Stack pointer.
  * @return Integer where 1 = empty and 0 = not empty
  */
int LDSC_stack_isEmpty(LDSC_stack* self) {
  if (!self) return -1;
  return self->pd->size == 0;
}

/**
  * @brief Peek item at the top of the stack.
  * @param self Stack pointer.
  * @return Pointer to data at the top of the stack.
  */
void* LDSC_stack_peek(LDSC_stack* self) {
  if (!self || !self->pd->top) return NULL;
  return self->pd->top->dataPtr;
}

/**
  * @brief Pop an item from the stack.
  * @param self Stack pointer.
  * @return Pointer to data at the top of the stack.
  */
void* LDSC_stack_pop(LDSC_stack* self) {
  if (!self || !self->pd->top) return NULL;
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
  */
void LDSC_stack_delete(LDSC_stack* self) {
  if (!self) return;
  while (self->pd->top) {
    self->pop(self);
  }
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
LDSC_stack* LDSC_stack_init() {
  LDSC_stack* newStack = malloc(sizeof(LDSC_stack));

  newStack->pd = malloc(sizeof(stackPrivate));
  newStack->pd->size = 0;
  newStack->pd->top = NULL;

  newStack->size = &LDSC_stack_size;
  newStack->push = &LDSC_stack_push;
  newStack->isEmpty = &LDSC_stack_isEmpty;
  newStack->peek = &LDSC_stack_peek;
  newStack->pop = &LDSC_stack_pop;
  newStack->delete = &LDSC_stack_delete;

  return newStack;
}
