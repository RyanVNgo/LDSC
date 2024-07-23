#include <LDSC_stack.h>
#include <stdlib.h>

typedef struct LDSC_node {
  void* dataPtr;
  struct LDSC_node* next;
} LDSC_node;

// create and return a new stack node
static LDSC_node* LDSC_node_init(void* dataPtrIn) {
  LDSC_node* newNode = (LDSC_node*)malloc(sizeof(LDSC_node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  return newNode;
}

struct LDSC_stack {
  int length;
  LDSC_node* top;
};

/**
 * @brief Create a new stack
 * @return Pointer to a new stack
 */
LDSC_stack* LDSC_stack_init() {
  LDSC_stack* newStack = (LDSC_stack*)malloc(sizeof(LDSC_stack));
  newStack->length = 0;
  newStack->top = NULL;
  return newStack;
}

/**
 * @brief Get the length of the stack
 * @param stackIn Pointer to LDSC_stack
 * @return Integer representing number of items in the stack
 */
int LDSC_stack_length(LDSC_stack* stackIn) {
  if (!stackIn) return -1;
  return stackIn->length;
}

/**
 * @brief Check if stack is empty
 * @param stackIn Pointer to LDSC_stack
 * @return Integer where empty = 1, non-empty = 0, fail = -1
 */
int LDSC_stack_isEmpty(LDSC_stack* stackIn) {
  if(!stackIn) return -1;
  if (!stackIn->length) return 1;
  return 0;
}
/**
 * @brief Push new item to the stack
 * @param stackIn Pointer to LDSC_stack
 * @param dataPtr Pointer of data to store
 */
void LDSC_stack_push(LDSC_stack* stackIn, void* dataPtrIn) {
  if (!stackIn || !dataPtrIn) return;

  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  newNode->next = stackIn->top;
  stackIn->top = newNode;

  stackIn->length++;
  return;
}

/**
 * @brief Get item on top of stack
 * @param stackIn Pointer to LDSC_stack
 * @return Pointer to data stored at top
 */
void* LDSC_stack_peek(LDSC_stack* stackIn) {
  if (!stackIn || !stackIn->top) return NULL;
  return stackIn->top->dataPtr;
}

/**
 * @brief Remove and return item on top of stack
 * @param stackIn Pointer to LDSC_stack
 * @return Pointer to data stored at top
 */
void* LDSC_stack_pop(LDSC_stack* stackIn) {
  if (!stackIn || !stackIn->top) return NULL;
  
  void* dataOutPtr = stackIn->top->dataPtr;
  LDSC_node* newTop = stackIn->top->next;
  
  free(stackIn->top);
  stackIn->top = newTop;

  stackIn->length--;
  return dataOutPtr;
}

